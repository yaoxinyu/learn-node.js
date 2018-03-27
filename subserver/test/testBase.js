/**
 * @file 测试用例基类
 * Created by yaoxinyu on 2018/3/19.
 */

var md5 = require('md5');
// http测试客户端
var httpClient = require('http');
var WebSocketClient = require('websocket').client;
const WebSocketUrl = 'ws://127.0.0.1:9009';  // 分控协议网关WebSocket地址
const assetSyncOptions = {
    hostname: '127.0.0.1',  // 分控协议网关资产同步http post地址
    port: 9010,
    path: '/asset',
    method: 'post',
    headers: {
        'Content-Type': 'application/json; charset=UTF-8'
    }
};  // 分控协议网关资产同步http请求

function TestBase() {
    var isInit = false;
    var isWSConnected = false; // WebSocket是否连接成功
    var client = new WebSocketClient(); // WebSocket Client
    var wsConnection = null; // WebSocket连接句柄
    var wsSessionID = 0; // WebSocket sessionID
    var reconnectTimer = null;

    /**
     * 初始化
     */
    this.init = function () {
        if (isInit) {
            return;
        }

        // 监听连接失败
        client.on('connectFailed', function (error) {
            console.error('WebSocket连接失败: ' + error.toString());
            if (!reconnectTimer) {
                reconnectTimer = setInterval(connectWS, 60000);
            }
        });

        // 监听连接
        client.on('connect', function (connection) {
            console.info('WebSocket连接成功.');
            wsConnection = connection;
            isWSConnected = true;
            if (reconnectTimer) {
                clearInterval(reconnectTimer);
                reconnectTimer = null;
            }

            connection.on('error', function (error) {
                console.error('WebSocket连接出错: ' + error.toString());
                isWSConnected = false;
                reConnectWS();
            });

            connection.on('close', function () {
                console.warn('WebSocket连接关闭');
                isWSConnected = false;
                reConnectWS();
            });

            connection.on('message', function (message) {
                console.info('接收到WebSocket服务端数据: ' + message.utf8Data);
                try {
                    let jsonData = JSON.parse(message.utf8Data).data;
                    if (jsonData.header && jsonData.header.optCmd === 'session_param_6001') {
                        // 保存WebSocket会话ID
                        wsSessionID = jsonData.sessionId;
                    }
                } catch (exception) {
                    console.error('处理WebSocket服务端数据异常：', exception.message);
                }
            });
        });

        connectWS();
        isInit = true;
    };

    /**
     * 连接分控协议网关WebSocket
     */
    var connectWS = function () {
        if (isWSConnected) {
            return;
        }
        client.connect(WebSocketUrl);
    };

    /**
     * 重连分控协议网关WebSocket
     */
    var reConnectWS = function () {
        if (!reconnectTimer) {
            reconnectTimer = setInterval(connectWS, 60000);
        }
    };

    /**
     * 运行建立WebSocket会话测试用例
     */
    this.runConnectCase = function () {
        let connectInfo = {
            clientId: '111111',
            data: {
                header: {
                    optCmd: 'session_param_6001'
                }
            }
        };
        console.info('运行建立WebSocket会话测试用例...');
        console.info('WebSocket发送建立会话请求数据：', connectInfo);
        sendWsMessage(connectInfo);
    };

    /**
     * 发送WebSocket消息到服务端
     * @param message JSON格式
     */
    var sendWsMessage = function (message) {
        if (!isWSConnected) {
            console.warn('WebSocket未连接，无法发送消息！');
            return;
        }

        try {
            let data = JSON.stringify(message);
            if (wsConnection) {
                wsConnection.sendUTF(data);
            }
        } catch (exception) {
            console.error('WebSocket发送数据异常：', exception.message);
        }
    };

    /**
     * 发送WebSocket业务请求
     * @param req 请求消息 JSON格式
     */
    this.sendBusiReq = function (req) {
        try {
            console.info('WebSocket发送业务请求，原始数据：', req);
            req.sessionId = wsSessionID;
            req.checkSum = calcMD5Value(req.clientId, req.sessionId, req.data);
            console.info('WebSocket发送业务请求，处理后的数据：', req);
            sendWsMessage(req);
        } catch (exception) {
            console.error('WebSocket发送业务请求异常：', exception.message);
        }
    };

    /**
     * 计算协议中的md5值
     * @param clientId
     * @param sessionId
     * @param data
     */
    var calcMD5Value = function (clientId, sessionId, data) {
        let strData = clientId + '' + sessionId + md5(JSON.stringify(data));
        let md5Value = md5(strData);
        return md5Value;
    };

    /**
     * 发送资产同步请求
     * @param assetAsyncReq 资产同步请求消息 JSON格式
     */
    this.sendAssetSyncRequest = function (assetAsyncReq) {
        let req = httpClient.request(assetSyncOptions, function (res) {
            console.info('资产同步收到http响应，状态码=%s, 头部信息=%s', res.statusCode, JSON.stringify(res.headers));
            res.setEncoding('utf8');
            var recvBuffer = '';
            res.on('data', function (chunk) {
                recvBuffer += chunk;
            });
            res.on('end', function () {
                console.info('收到http响应数据：', recvBuffer);
            });
        });

        req.on('error', function (e) {
            console.error('资产同步http请求错误: ' + e.message);
        });

        // 发送资产同步请求数据
        console.info('发送http资产同步请求数据：', JSON.stringify(assetAsyncReq));
        req.write(JSON.stringify(assetAsyncReq));
        req.end();
    };
}


var testBase = new TestBase();
testBase.init();

// 导出
module.exports = testBase;