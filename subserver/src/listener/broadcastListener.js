/**
 * @file 对广播状态信息，操作结果信息的业务处理，
 * 根据需要把数据封装成广播状态信息II类协议，告警信息II类协议，设备状态
 * Created by wangweizhen on 2017/11/6.
 */

var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);
var db = require('../common/util/db');
var avroUtil = require('../common/util/avroUtil');
var wsClientMgr = require('../wsClientMgr');
var storageMgr = require('../storageMgr');
var socketMgr = require('../socketMgr');
function BroadcastListener() {

    /**
     * 广播状态II类协议
     * @param header 协议头
     * @param statusResp 状态数据信息
     */
    var broadcastStatus = function (header, statusResp) {
        let status = statusResp.status;
        let uVolume = statusResp.uVolume;
        let login = statusResp.login;
        let call = statusResp.call;
        //广播状态数据，II类协议数据格式封装
        let broadcastData = {};
        header.optCmd = 'broadcast_data_9005';
        broadcastData.header = header;
        broadcastData.status = status;
        broadcastData.login = login;
        broadcastData.call = call;
        broadcastData.volume = uVolume;
        //调用websocket接口推送所有客户端
        wsClientMgr.pushBusiDataForII(broadcastData);
        //调用存储接口存储广播状态
        storageMgr.storage(broadcastData);
        //调用socket接口，发送广播状态II类协议数据到集控
        socketMgr.pushDataForII(broadcastData);
    };

    /**
     * 告警II类协议
     * @param header 协议头数据
     * @param statusResp 广播状态信息
     */
    var alarm = function (header, statusResp) {
        let assetNo = header.assetNo ? header.assetNo : '';
        let status = statusResp.status;
        let alarm = [{'alarmCode': '0002', 'alarmFlag': 200}];
        if (status == 3) {
            // 处理‘0502’开头的资产类型（求助器），3：呼叫等待
            if (assetNo.startsWith('0502')) {
                alarm = [{'alarmCode': '0027', 'alarmFlag': 100}]
            }
        } else if (status == 6) {
            // 处理‘0502’开头的资产类型（求助器），6：对讲中
            if (assetNo.startsWith('0502')) {
                alarm = [{'alarmCode': '0027', 'alarmFlag': 200}]
            }
        } else if (status == 1) {
            alarm = [{'alarmCode': '0002', 'alarmFlag': 100}]
        }
        //告警信息II类协议
        let alarmData = {};
        header.optCmd = 'ad_data_9001';
        alarmData.header = header;
        alarmData.alarmTime = header.responseTime;
        alarmData.data = alarm;
        //调用存储
        // storageMgr.storage(alarmData);
        //调用socket发送告警状态II类协议到集控
        socketMgr.pushDataForII(alarmData);
    };

    /**
     * 设备状态II类协议
     * @param header 协议头数据
     * @param statusResp 广播状态信息
     */
    var deviceStatus = function (header, statusResp) {
        let status = statusResp.status;
        let deviceType = '1';
        let onlineType = '1';
        if (status == 1) {
            deviceType = '2';
            onlineType = '2';
        }
        //设备状态II类协议
        let statusData = {};
        header.optCmd = 'ad_data_9500';
        statusData.header = header;
        statusData.deviceTypeTime = header.responseTime;
        statusData.deviceType = deviceType;
        statusData.onlineType = onlineType;
        //调用socket接口，发送设备状态II类协议到集控
        socketMgr.pushDataForII(statusData);
    };

    /**
     * 把广播状态封装成II广播类协议，告警二类协议，设备状态II类协议
     * @param msg 包含广播状态信息的JSON的数据
     * @return {Promise.<void>}
     */
    var broadcast9005 = async function (msg) {
        let data = msg;
        let header = data.header;
        let statusResps = data.data.statusResp;
        for (let i = 0, len = statusResps.length; i < len; i++) {
            let statusResp = statusResps[i];
            let ip = statusResp.devIP;
            //根据设备IP查询出对应的资产编号
            let result = await storageMgr.queryAssetCodeByIp(ip);
            if (!result) {
                header.assetNo = ip;
            } else {
                header.assetNo = result.device_code;
            }
            //广播状态打包II类协议并操作
            broadcastStatus(header, statusResp);
            //告警状态打包II类协议并操作
            alarm(header, statusResp);
            //设备装填打包II类协议并操作
            deviceStatus(header, statusResp);
        }

    };

    /**
     * 广播操作结果的封装
     * 文件列表
     * @param msg
     */
    var broadcast9004 = function (msg) {
        let res = {};
        res.header = msg.header;
        res.data = msg.data.fileResp;
        //广播操作结果发送给客户端
        wsClientMgr.sendBusiDataForII(res);
    };

    /**
     * 广播操作结果的封装
     * 广播播放、停止广播、开始喊话、停止喊话、文件列表、音量控制、状态、
     * 上传文件、添加方案、删除方案、修改方案、添加会话设备、删除会话设备等
     * @param msg
     */
    var broadcast9003 = function (msg) {
        let data = msg;
        //调用websocket发送到指定客户端
        let resData = {};
        resData.header = data.header;
        resData.code = data.data.code;
        resData.optType = data.data.optType;
        wsClientMgr.sendBusiDataForII(resData);
    };

    /**
     * 广播操作结果的封装
     * 增加设备、删除设备、
     * @param msg
     */
    var broadcast9006 = function (msg) {
        let data = msg;
        //调用websocket发送到指定客户端
        let resData = {};
        resData.header = data.header;
        resData.code = data.data.code;
        resData.msg = data.data.msg;
        resData.devId = data.data.devId;
        //资产同步，新增，修改，删除设备操作结果，推送给集控
        socketMgr.pushDataForII(resData);
    };

    /**
     * 对广播操作结果，广播状态返回数据的业务处理
     * @param msg
     * @return {Promise.<void>}
     */
    this.onMessage = async function (msg) {
        if (!msg || !msg.header) {
            logger.error('广播操作结果MQ消息错误：', msg);
            return;
        }
        let data = msg;
        let header = data.header;
        let optCmd = header.optCmd;
        switch (optCmd) {
            case 'broadcast_data_9006':
                logger.info('广播设备增加/修改/删除结果，原始操作结果数据：', data);
                broadcast9006(data);
                break;
            case 'broadcast_data_9005':
                logger.info('广播状态业务处理，原始广播状态数据：', data);
                broadcast9005(data);
                break;
            case 'broadcast_data_9004':
                logger.info('广播操作结果业务处理，原始广播操作结果数据：', data);
                broadcast9004(data);
                break;
            case 'broadcast_data_9003':
                logger.info('广播操作结果业务处理，原始广播操作结果数据：', data);
                broadcast9003(data);
                break;
            default:
                logger.error('广播状态信息，操作结果信息业务处理模块未能识别optCmd命令：', optCmd);
        }
    };
}


module.exports = new BroadcastListener();
