/**
 * @file tcp server类
 * @author yaoxinyu
 * @date 2017/12/25
 */

var net = require('net');  // net模块
const SOCK_TIMEOUT = 300 * 1000; // 套接字空闲超时时间
const PIECE_SIZE = 16 * 1024;    // 发送的分片大小
const SCHEDULE_SPAN = 500;
const RECV_TIMEOUT = 30000;   // 接收数据超时

/**
 * socket client类
 * @param socket 构造参数 socket句柄
 * @constructor
 */
function SockClient(socket) {
    var sock = socket;  // 套接字句柄
    var recvBuffer;     // 接收的数据缓冲区，包括本次收到的数据与上次未处理完的数据
    var sendBuffer;     // 发送数据队列，元素为buffer数据
    var lastSendTick = 0;     // 上次发送数据的tick
    var lastRecvTick = 0;     // 上次接收数据的tick
    const msgHeaderLen = 5;   // 头部长度5字节，第4、5两个字节为body长度

    setInterval(driverSendTask, SCHEDULE_SPAN);
    function driverSendTask() {
        if (sendBuffer) {
            let curTick = new Date().getTime();
            let length = sendBuffer.length;
            if (length >= PIECE_SIZE) {
                // 立即发送数据
                let leftLen = length;
                while (leftLen > 0) {
                    // 本次发送的数据长度
                    let sendLen = leftLen < PIECE_SIZE ? leftLen : PIECE_SIZE;
                    // 发送数据
                    let sendBuffer = new Buffer(sendLen);
                    sendBuffer.copy(sendBuffer, 0, 0, sendLen);
                    sock.write(sendBuffer, 'utf-8');

                    // 更新剩余数据大小
                    leftLen -= sendLen;
                    // 更新缓冲区
                    sendBuffer = sendBuffer.slice(sendLen);
                }
                lastSendTick = curTick;
            } else {
                // 延迟发送数据
                if (lastSendTick == 0 || curTick - lastSendTick > 1000) {
                    socket.write(sendBuffer, 'utf-8');
                    sendBuffer = new Buffer(0);
                    lastSendTick = curTick;
                }
            }
        }
    }

    /**
     * 接收数据回调
     * @param data {buffer} 本次收到的数据
     */
    this.onRecvData = function (data) {
        let curTick = new Date().getTime();
        // 如果距离上一次接收数据的时间过长，认为有问题，丢弃掉缓存数据
        if (lastRecvTick == 0 || curTick - lastRecvTick > RECV_TIMEOUT) {
            if (lastRecvTick > 0 && recvBuffer && recvBuffer.length > 0) {
                console.log('丢弃的超时数据：', recvBuffer);
            }
            recvBuffer = new Buffer(data);
        } else {
            recvBuffer = Buffer.concat([recvBuffer, data]);
        }
        lastRecvTick = curTick;

        // 数据处理
        onDataProcess();
    };

    /**
     * socket 发送数据 异步调用
     * @param data
     */
    this.sendData = function (data) {
        if (sendBuffer) {
            sendBuffer = Buffer.concat([sendBuffer, new Buffer(data)]);
        } else {
            sendBuffer = new Buffer(data);
        }
    };

    /**
     * 对缓冲区数据进行处理
     */
    var onDataProcess = function () {
        // 约定消息分为消息头+消息体，消息头中包含了消息的长度信息
        // 消息格式：命令（1字节）+类型（1字节）+数据来源（1字节）+数据长度（2字节）+数据（n字节）
        // 1、如果收到的长度小于包头长度，继续等待接收，暂不处理；
        // 2、收到的长度大于包头长度，解析出body长度，当总长度>=消息长度时进行解析并处理，并拆分缓存剩余数据
        // 3、如果消息不能正确解析，丢弃掉
        let dataLen = recvBuffer.length;
        while (dataLen >= msgHeaderLen) {
            try {
                // 解析数据
                let bodyLen = recvBuffer.readInt16BE(3);
                if (dataLen < (msgHeaderLen + bodyLen)) {
                    break;
                }
                let cmd = recvBuffer.readInt8(0);
                let devType = recvBuffer.readInt8(1);
                let dataSource = recvBuffer.readInt8(2);
                let fullMsg = recvBuffer.slice(0, msgHeaderLen + bodyLen);
                console.log('处理完整的数据：', fullMsg);
                switch (cmd) {
                // 根据不同的cmd处理不同的业务
                    default:
                        console.log('无法处理的数据cmd=', cmd);
                        break;
                }
                // 更新缓存数据
                recvBuffer = recvBuffer.slice(msgHeaderLen + bodyLen);
                dataLen = recvBuffer.length;
            } catch (exception) {
                console.log('解析数据出现异常！');
                recvBuffer = new Buffer(0);
                dataLen = 0;
            }
        }
    };
}

/**
 * socket client管理类
 * @constructor
 */
function SockClientMgr() {
    var clientMap = {};   // tcp client句柄管理，key值为host+port，value值为SockClient对象

    /**
     * 客户端建立连接
     * @param sock socket句柄
     */
    this.onClientConnected = function (sock) {
        // 保存socket句柄
        if (sock) {
            let key = sock.remoteAddress + ':' + sock.remotePort;
            let sockClient = new SockClient(sock);
            clientMap[key] = sockClient;
        }
    };

    /**
     * 客户端断开连接
     * @param sock socket句柄
     */
    this.onClientClosed = function (sock) {
        // 移除socket句柄
        if (sock) {
            let key = sock.remoteAddress + ':' + sock.remotePort;
            delete clientMap[key];
        }
    };

    /**
     * 获取对应的socket句柄
     * @param host
     * @param port
     * @return socket
     */
    this.getClientSock = function (sock) {
        if (sock) {
            let key = sock.remoteAddress + ':' + sock.remotePort;
            return clientMap[key];
        }
        return null;
    };

    /**
     * clear
     */
    this.clear = function () {
        clientMap = {};
    };
}

function TcpServer() {
    var tcpIP;        // 服务器地址
    var tcpPort;      // 服务器端口
    var serverSock;   // tcp server句柄
    var clientMgr = new SockClientMgr();   // tcp client句柄管理

    /**
     * 创建tcp服务器 如果host为域名，在外部用dns模块解析出IP地址
     * @param host IP地址
     * @param port 端口
     */
    this.createServer = function (host, port) {
        // 保存信息
        tcpIP = host;
        tcpPort = port;
        if (serverSock) {
            serverSock.close();
        }
        // 创建socket
        serverSock = net.createServer();
        serverSock.listen(port, host);
        console.log('Server listening on ' + host + ':' + port);

        /**
         * 监听客户端连接事件
         */
        serverSock.on('connection', function (sock) {
            console.log('client connected: ' + sock.remoteAddress + ':' + sock.remotePort);
            // 加入map
            clientMgr.onClientConnected(sock);
            sock.setTimeout(SOCK_TIMEOUT);

            // 监听数据接收
            sock.on('data', function (data) {
                console.log('收到来自[%s:%s]的数据：', sock.remoteAddress, sock.remotePort, data);
                // 数据接收
                let sockClient = clientMgr.getClientSock(sock);
                if (sockClient) {
                    sockClient.onRecvData(data);
                }
            });

            // 监听socket连接关闭
            sock.on('end', function () {
                console.log('Client[%s:%s] is closed', sock.remoteAddress, sock.remotePort);
                clientMgr.onClientClosed(sock);
            });

            // 超时事件，空闲了5分钟将其断开
            sock.on('timeout', function () {
                console.log('idle timeout, disconnect client[%s:%s]', sock.remoteAddress, sock.remotePort);
                sock.end();
            });

            // 监听socket error事件
            sock.on('error', function (err) {
                console.log('socket错误信息：' + err.message);
            });
        });

        /**
         * 监听sever close事件
         */
        serverSock.on('close', function () {
            console.log('Server is now closed');
            // 清空
            serverSock = null;
            clientMgr.clear();
        });

        /**
         * 监听error事件
         */
        serverSock.on('error', function (err) {
            console.log('Error occurred:', err.message);
        });
    };

    /**
     * 主动关闭tcp server，会触发close事件
     */
    this.closeServer = function () {
        serverSock.close();
        serverSock = null;
    };
}


// 外部需要new对象
module.exports = TcpServer;