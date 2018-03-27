/**
 * @file WebSocket收到的消息处理类
 * @author yaoxinyu
 * @date 2017/12/6
 */

var commonModule = require('./commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger();
const logRequest = commonModule.logger.getLogger(1);
// 常量模块
const constants = commonModule.constants;
var protoClassify = require('./protoTypeClassify');
var serverMgr = require('./serverMgr');
var wsClientMgr = require('./wsClientMgr');
var avroUtil = require('./common/util/avroUtil');
var socketMgr = require('../src/socketMgr');
// md5加密模块
var md5 = require('md5');

function WebSocketMsgHandle() {
    /**
     * 收到WebSocket消息
     * @param ws WebSocket连接对象
     * @param msg
     */
    this.onMessage = function (ws, msg) {
        // 消息解析，得到JSON格式
        try {
            let taskReq = JSON.parse(msg);
            if (taskReq && taskReq.data) {
                if (!checkWebSocketReq(ws, taskReq)) {
                    logger.error('WebSocket请求消息[%s]校验失败！', msg);
                    return;
                }

                let optCmd = taskReq.data.header.optCmd;
                if (optCmd != 'broadcast_param_9007') {
                    logRequest.debug('收到客户端WebSocket消息：', msg);
                    logger.debug('处理客户端WebSocket消息：', msg);
                }
                let assetNo = taskReq.data.header.assetNo;
                let requestTime = taskReq.data.header.requestTime;
                switch (true) {
                    case ('session_param_6001' === optCmd): {
                        let clientId = taskReq.clientId;
                        let resMsg = buildConnectingResponse(clientId);
                        ws.send(JSON.stringify(resMsg));
                        wsClientMgr.establishSession(resMsg.data.sessionId, ws);
                        logger.info('发送WebSocket连接回复：', resMsg);
                        break;
                    }
                    case (protoClassify.isBroadProtoI(optCmd)): {
                        // 广播业务请求处理
                        if (!serverMgr.isServerRunning(constants.SERVER_TYPE.BROADCAST)) {
                            // 广播服务未启动，则启动广播服务
                            serverMgr.startServer(constants.SERVER_TYPE.BROADCAST);
                        }

                        // 将任务发送到广播服务子进程
                        let broadcastTask = {};
                        broadcastTask.name = constants.PROCESS_MESSAGE_DEFINE.BROADCAST_MSG.TASK_REQ;
                        broadcastTask.data = taskReq.data;
                        serverMgr.sendMsg(constants.SERVER_TYPE.BROADCAST, JSON.stringify(broadcastTask));
                        break;
                    }
                    case (protoClassify.isVideoProtoI(optCmd)): {
                        // 视频业务请求处理
                        if (!serverMgr.isServerRunning(constants.SERVER_TYPE.VIDEO)) {
                            // 视频服务未启动，则启动视频服务
                            serverMgr.startServer(constants.SERVER_TYPE.VIDEO);
                        }

                        // 将任务发送到视频服务子进程
                        let videoTask = {};
                        videoTask.name = constants.PROCESS_MESSAGE_DEFINE.VIDEO_MSG.TASK_REQ;
                        videoTask.data = taskReq.data;
                        serverMgr.sendMsg(constants.SERVER_TYPE.VIDEO, JSON.stringify(videoTask));
                        break;
                    }
                    case (protoClassify.isBigScreenProtoI(optCmd)): {
                        // 大屏业务请求处理
                        if (!serverMgr.isServerRunning(constants.SERVER_TYPE.BIG_SCREEN)) {
                            // 大屏服务未启动，则启动大屏服务
                            serverMgr.startServer(constants.SERVER_TYPE.BIG_SCREEN);
                        }

                        // 将任务发送到大屏服务子进程
                        let bigScreenTask = {};
                        bigScreenTask.name = constants.PROCESS_MESSAGE_DEFINE.BIG_SCREEN_MSG.TASK_REQ;
                        bigScreenTask.data = taskReq.data;
                        serverMgr.sendMsg(constants.SERVER_TYPE.BIG_SCREEN, JSON.stringify(bigScreenTask));
                        break;
                    }
                    default:
                        switch (true) {
                            case /\\*param*/.test(optCmd):
                                logger.debug('不是广播的I类协议数据，转发到集控，optCmd: ', optCmd);
                                socketMgr.pushDataForI(taskReq.data);
                                break;
                            case /\\*data*/.test(optCmd):
                                logger.debug('不是广播的II类协议数据，转发到集控，optCmd: ', optCmd);
                                socketMgr.pushDataForII(taskReq.data);
                                break;
                            default:
                                logger.error('无法处理的WebSocket信息，optCmd：', optCmd);
                                break;
                        }
                        break;
                }
                // 以assetNo+requestTime作为key，value值为sessionId
                if (assetNo && requestTime) {
                    let arrAssetNo = assetNo.split('|');
                    for (let i = 0, len = arrAssetNo.length; i < len; i++) {
                        wsClientMgr.addWebSocketConn(arrAssetNo[i], requestTime, taskReq.sessionId);
                    }
                }
            }
        } catch (exception) {
            logger.error('处理WebSocket信息异常：' + exception.message);
        }
    };
}

/**
 * 建立WebSocket连接时发送的响应数据
 * @return json数据
 */
function buildConnectingResponse(clientId) {
    let sessionId = wsClientMgr.generateSessionId();
    let resInfo = {
        clientId: clientId,
        data: {
            header: {
                optCmd: 'session_param_6001'
            },
            sessionId: sessionId
        }
    };
    let msg = JSON.stringify(resInfo);
    let response = JSON.parse(msg); //由JSON字符串转换为JSON对象
    return response;
}

/**
 * 对WebSocket数据计算MD5值
 * @param clientId
 * @param sessionId
 * @param data
 */
function calcMD5Value(clientId, sessionId, data) {
    let strData = clientId + '' + sessionId + md5(JSON.stringify(data));
    let md5Value = md5(strData);
    return md5Value;
}

/**
 * 校验WebSocket请求数据
 * @return {boolean} 检验成功返回true 失败返回false
 */
function checkWebSocketReq(ws, req) {
    let clientId = req.clientId;
    let sessionId = req.sessionId;
    let reqCheckSum = req.checkSum;   // 发过来请求的md5检验值
    let data = req.data;

    if (sessionId == null) {
        // 尚未返回给客户端sessionId
        return true;
    }

    let localCheckSum = calcMD5Value(clientId, sessionId, data);  // 本地校验值
    let isValid = true;
    let code = 200;
    let msg = 'OK';
    do {
        // 检查会话ID的合法性
        if (!wsClientMgr.isSessionLegal(sessionId, ws)) {
            logger.info('会话ID对应的连接不合法[sessionId=%s]！', sessionId);
            isValid = false;
            code = 100;
            msg = '非法的会话连接';
            break;
        }

        // 检查消息结构的合法性
        if (reqCheckSum == null) {
            logger.info('WebSocket数据请求消息格式错误！');
            isValid = false;
            code = 100;
            msg = 'checkSum字段不存在';
            break;
        }

        // 检查数据的合法性
        if (reqCheckSum != localCheckSum) {
            logger.error('md5值不相等，源md5=%s，计算的md5=%s！', reqCheckSum, localCheckSum);
            isValid = false;
            code = 100;
            msg = '数据校验错误';
            break;
        }

        let optCmd = data.header.optCmd;
        let avroData = avroUtil.getAvroDataByOptCmd(data, optCmd);
        if (!avroData) {
            logger.error('处理WebSocket消息[%s]，avro序列化失败！', req);
            isValid = false;
            code = 100;
            msg = 'avro序列化失败';
            break;
        }
    } while (false);

    let response = buildCheckResponse(clientId, sessionId, reqCheckSum, code, msg);
    logger.info('WebSocket发送校验回复：', response);
    ws.send(response);

    return isValid;
}

/**
 * WebSocket消息检验后返回给客户端的数据
 * @param clientId 客户端请求对应值
 * @param sessionId 客户端请求对应值
 * @param checkSum 客户端请求对应值
 * @param code 200成功 100失败
 * @param message 错误消息 成功为“OK”
 * @return json字符串
 */
function buildCheckResponse(clientId, sessionId, checkSum, code, message) {
    let resInfo = {
        clientId: clientId,
        sessionId: sessionId,
        checkSum: checkSum,
        data: {
            code: code,
            msg: message
        }
    };
    let response = JSON.stringify(resInfo);
    return response;
}


var wsMsgHandle = new WebSocketMsgHandle();
module.exports = wsMsgHandle;
