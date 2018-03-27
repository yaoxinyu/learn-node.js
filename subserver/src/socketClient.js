/**
 * @file Describe the file
 * @author yaoxinyu
 * @date 2017/12/2
 */

var net = require('net');
var commonModule = require('./commonModuleExport');
const logger = commonModule.logger.getLogger();
// 数据分段大小16KB
const segmentSize = 16384;
// 断线重连间隔（1分钟）
const ReconnectCycle = 60000;


/**
 * socket客户端对象
 */
function SocketClient() {
    var client = new net.Socket();  // 连接句柄
    var isConnected = false;        // 是否连接成功
    var reConnectTimer = null;      // 断线重连定时器
    var serverIP;                   // 连接的服务器IP
    var serverPort;                 // 连接的服务器端口

    /**
     * 连接服务器，外部手动调用
     * @param host 服务器IP
     * @param port 端口
     */
    this.connect = function (host, port) {
        serverIP = host;
        serverPort = port;
        // 建立连接
        logger.info('发起socket连接：' + host + ':' + port);
        client.connect(port, host);
        // client.setKeepAlive(true, 10000);

        // 添加“connect”事件处理函数
        client.on('connect', onConnected);

        // 添加“close”事件处理函数
        client.on('close', onClose);

        // 添加“end”事件处理函数
        client.on('end', onEnd);

        // 添加“error”事件处理函数
        client.on('error', onError);

        // 添加“data”事件处理函数
        client.on('data', onRecv);
    };

    /**
     * 主动断开连接
     */
    this.disConnect = function () {
        if (isConnected) {
            logger.info('客户端主动断开socket连接！');
            client.end();
            isConnected = false;
        }
    };

    /**
     * 发送数据
     * @param buffer 数据
     * @param length 数据长度
     */
    this.send = function (buffer, length) {
        if (!isConnected) {
            logger.error('socket未连接，无法发送数据！');
            return;
        }

        logger.info('socket发送数据长度：' + length);
        let leftLen = length;
        let totalSendLen = 0;
        while (leftLen > 0) {
            // 本次发送的数据长度
            let sendLen = leftLen < segmentSize ? leftLen : segmentSize;
            // 发送数据
            let sendBuffer = new Buffer(sendLen);
            buffer.copy(sendBuffer, 0, totalSendLen, sendLen);
            client.write(sendBuffer, 'utf-8');

            // 更新剩余数据大小
            leftLen -= sendLen;
            // 已发送的数据大小
            totalSendLen += sendLen;
        }
    };

    /**
     * 断开重连
     */
    var reConnect = function () {
        logger.info('socket发起重连...');
        client.connect(serverPort, serverIP);
    };

    /**
     * 连接成功回调
     */
    var onConnected = function () {
        logger.info('socket成功连接到服务器！');
        isConnected = true;

        if (reConnectTimer) {
            // 重连成功
            logger.info('重连成功!');
            clearInterval(reConnectTimer);
            reConnectTimer = null;
        }
    };

    /**
     * 收到socket另一端发送FIN包时，触发该事件
     */
    var onEnd = function () {
        logger.info('收到socket服务端FIN包');
        isConnected = false;
        // 发起重连
        if (reConnectTimer == null) {
            reConnectTimer = setInterval(reConnect, ReconnectCycle);
        }
    };

    /**
     * 发生错误回调
     */
    var onError = function (err) {
        logger.error('socket错误信息：' + err.message);
        // 完全关闭连接
        client.destroy();
        isConnected = false;
        // 发起重连
        if (reConnectTimer == null) {
            reConnectTimer = setInterval(reConnect, ReconnectCycle);
        }
    };

    /**
     * close事件回调，关闭socket触发
     */
    var onClose = function (had_error) {
        logger.info('socket连接已关闭:', had_error);
        isConnected = false;
    };

    /**
     * 接收数据回调
     */
    var onRecv = function (data) {
        logger.info('socket收到数据：', data);
        // TODO 数据解析处理
    };

    /**
     * 数据处理
     */
    var dataProcess = function () {

    };
}


var client = new SocketClient();
module.exports = client;