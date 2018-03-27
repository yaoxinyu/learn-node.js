/**
 * WebSocket client管理模块，功能描述：
 * 1、管理WebSocket client连接句柄；
 * 2、向客户端发送消息；
 * @author yaoxinyu
 * @date 2017/11/30
 */

var md5 = require('md5');
var commonModule = require('./commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger();
var globalData = require('./globalDataCache');


function WebSocketClientMgr() {
    /**
     * WebSocket请求与会话的映射，key值为deviceCode+requestTime，value值为sessionId
     */
    var wsClientMap = new Map();

    /**
     * WebSocket连接会话缓存，key值为sessionId，value为WebSocket连接句柄
     */
    var wsClientSessionMap = new Map();

    /**
     * WebSocket连接会话ID，动态增长
     * @type {number}
     */
    var wsSessionId = 0;

    /**
     * WebSocket对象集合
     * @type {Set}
     */
    var wsClientSet = new Set();

    /**
     * 加入集合
     * @param ws WebSocket对象
     */
    this.onClientConnect = function (ws) {
        wsClientSet.add(ws);
    };

    /**
     * 判断对象是否已存在
     * @param ws WebSocket对象
     */
    this.isConnected = function (ws) {
        if (wsClientSet.has(ws)) {
            return true;
        }
        return false;
    };

    /**
     * 检查会话对应的连接是否合法
     * @param sessionId
     * @param ws
     * @return {boolean}
     */
    this.isSessionLegal = function (sessionId, ws) {
        if (wsClientSessionMap.get(sessionId) === ws) {
            return true;
        }
        return false;
    };

    /**
     * 建立一个新会话
     * @param sessionId
     * @param ws
     */
    this.establishSession = function (sessionId, ws) {
        wsClientSessionMap.set(sessionId, ws);
    };

    /**
     * 客户端退出/断开连接
     * @param wsClient
     */
    this.onClientClose = function (wsClient) {
        // 从wsClientSet中移除
        if (wsClientSet.has(wsClient)) {
            wsClientSet.delete(wsClient);
        }

        // 从wsClientMap中移除
        for (let [key, sessionId] of wsClientMap.entries()) {
            if (wsClientSessionMap.get(sessionId) === wsClient) {
                wsClientMap.delete(key);
            }
        }

        // 从wsClientSessionMap中移除
        for (let [sessionId, wsObj] of wsClientSessionMap.entries()) {
            if (wsObj === wsClient) {
                wsClientSessionMap.delete(sessionId);
            }
        }
    };

    /**
     * 返回连接数
     */
    this.wsSize = function () {
        return wsClientSet.size;
    };

    /**
     * 添加WebSocket请求与会话的映射
     * @param deviceCode 资产编号
     * @param requestTime 请求时间
     * @param sessionID 会话ID
     */
    this.addWebSocketConn = function (deviceCode, requestTime, sessionID) {
        let key = deviceCode + '||' + requestTime;
        wsClientMap.set(key, sessionID);
    };

    /**
     * 移除WebSocket连接
     * @param deviceCode 资产编号
     * @param requestTime 请求时间
     */
    this.removeWebSocketConn = function (deviceCode, requestTime) {
        let key = deviceCode + '||' + requestTime;
        if (wsClientMap.get(key) != null) {
            wsClientMap.delete(key);
        }
    };

    /**
     * 获取对应的WebSocket连接
     * @param deviceCode 资产编号
     * @param requestTime 请求时间
     */
    this.getWebSocketConn = function (deviceCode, requestTime) {
        let key = deviceCode + '||' + requestTime;
        if (wsClientMap.get(key) != null) {
            let sessionId = wsClientMap.get(key);
            return wsClientSessionMap.get(sessionId);
        }
        return null;
    };

    /**
     * 获取对应的sessionId
     * @param deviceCode 资产编号
     * @param requestTime 请求时间
     */
    this.getSessionId = function (deviceCode, requestTime) {
        let key = deviceCode + '||' + requestTime;
        return wsClientMap.get(key);
    };

    /**
     * 生成WebSocket连接唯一的会话ID
     * @return {number}
     */
    this.generateSessionId = function () {
        wsSessionId += 1;
        return wsSessionId;
    };

    /**
     * 推送Ⅱ类业务数据到所有的客户端
     * @param data JSON格式的Ⅱ类业务数据
     */
    this.pushBusiDataForII = function (data) {
        try {
            let jsonData = JSON.parse(JSON.stringify(data));
            for (let [sessionId, wsClient] of wsClientSessionMap) {
                if (wsClient) {
                    let response = buildWebSocketResponse(sessionId, jsonData);
                    wsClient.send(response);
                    logger.debug('WebSocket推送数据给客户端：', response);
                }
            }
        } catch (exception) {
            logger.error('WebSocket推送Ⅱ类业务数据出现异常：', exception.message);
        }
    };

    /**
     * 发送Ⅱ类业务数据到指定客户端
     * @param data JSON格式的Ⅱ类业务数据
     */
    this.sendBusiDataForII = function (msg) {
        try {
            let data = JSON.parse(JSON.stringify(msg));
            if (data && data.header) {
                let assetNo = data.header.assetNo;
                let requestTime = data.header.requestTime;
                let assetNos = assetNo.split('|');
                if (!assetNos[0]) {
                    return;
                }
                let wsClient = this.getWebSocketConn(assetNos[0], requestTime);
                if (wsClient) {
                    let sessionId = this.getSessionId(assetNos[0], requestTime);
                    let response = buildWebSocketResponse(sessionId, data);
                    wsClient.send(response);
                    logger.info('WebSocket发送回复给客户端：', response);
                    // 回复之后将该条记录从wsClientMap中移除
                    for (let assetNo of assetNos) {
                        this.removeWebSocketConn(assetNo, requestTime);
                    }
                } else {
                    // 如果本服务为地区主服务，则未找到对应websocket连接时推送给所有和主服务连接的客户端
                    if (globalData.isMainServer()) {
                        for (let wsConn of wsClientSessionMap.values()) {
                            if (wsConn) {
                                // sessionId统一赋值-1
                                let subRes = buildWebSocketResponse(-1, data);
                                wsConn.send(subRes);
                                logger.info('主服务WebSocket推送数据给客户端：', subRes);
                            }
                        }
                    } else {
                        logger.error('该请求[资产编号=%s,请求时间=%s]对应的连接句柄不存在！', assetNos[0], requestTime);
                    }
                }
            }
        } catch (exception) {
            logger.error('WebSocket发送Ⅱ类业务数据到客户端出现异常：', exception.message);
        }
    };

    /**
     * 推送动作数据到业务系统
     * @param data JSON格式的动作数据
     */
    this.pushActionDataToWeb = function (data) {
        try {
            for (let [sessionId, wsClient] of wsClientSessionMap) {
                if (wsClient) {
                    let response = buildWebSocketResponse(sessionId, data);
                    wsClient.send(response);
                    logger.info('WebSocket推送动作数据给客户端：', response);
                }
            }
        } catch (exception) {
            logger.error('WebSocket推送动作数据到业务系统出现异常：', exception.message);
        }
    };
}

/**
 * WebSocket返回给客户端的数据
 * @param sessionId 会话ID
 * @param data 数据
 * @return json字符串
 */
function buildWebSocketResponse(sessionId, data) {
    let clientId = '111111';
    let md5Data = md5(JSON.stringify(data));
    let strData = clientId + '' + sessionId + md5Data;
    let md5Value = md5(strData);
    let resInfo = {
        clientId: clientId,
        sessionId: sessionId,
        checkSum: md5Value,
        data: data
    };
    let response = JSON.stringify(resInfo);
    return response;
}


var wsClientMgr = new WebSocketClientMgr();
module.exports = wsClientMgr;