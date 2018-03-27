/**
 /**
 * 数据存储管理模块，功能描述：
 * 1、数据库连接初始化工作；
 * 2、存储数据到数据库；
 * 3、查询数据
 * @author yaoxinyu
 * @date 2017/11/30
 */

var commonModule = require('./commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var fileUtil = require('./common/util/fileUtil');
const filePath = fileUtil.path.join(fileUtil.getRootPath(), 'resource/config/sql.xml');
var sql = require('./common/util/sql');
var dbUtil = require('../src/common/util/db');
var avroUtil = require('./common/util/avroUtil');
let dataStructDefine = require('./dataStructDefine');
function StorageMgr() {
    /**
     * 初始化
     */
    this.init = async function () {
        // 数据库初始化加载xml
        logger.info('数据库初始化加载xml......');
        await sql.loadSqlFile(filePath);
        logger.info('数据库加载xml结束......');

        // 数据库初始化连接池
        dbUtil.initPool();
    };

    /**
     * 根据IP查询资产编号
     * @param ip IP
     * @return 资产编号
     */
    this.queryAssetCodeByIp = async function (ip) {
        let result = await dbUtil.query('queryAssetCodeByIp', ip);
        if (result != -1 && result) {
            return result;
        }
        logger.error('根据IP查询资产编号失败，IP：', ip);
        return null;
    };

    /**
     * 根据资产编号查询广播设备IP
     * @param assetNo 资产编号
     * @return IP
     */
    this.queryBroadcastIPByAssetNo = async function (assetNo) {
        let result = await dbUtil.query('queryBroadcastByAssetNo', assetNo);
        if (result != -1 && result) {
            return result;
        }
        logger.error('根据资产编号查询广播设备IP失败，资产编号：', assetNo);
        return null;
    };

    /**
     * 根据资产编号查询对应厂商类型
     * @param assetNo 资产编号
     * @return 厂商类型code
     */
    this.queryFactoryByAssetNo = async function (assetNo) {
        let result = await dbUtil.query('queryFactoryCodeByAssetNo', assetNo);
        if (result != -1 && result) {
            return result.factory_code;
        }
        logger.error('查询厂商类型失败，资产编号：', assetNo);
        return null;
    };

    /**
     * 根据资产编号查询资产信息
     * @param assetNo 资产编号
     * @return 资产信息
     */
    var queryAllByAssetNo = async function (assetNo) {
        let result = await dbUtil.query('queryAllByAssetNo', assetNo);
        if (result != -1 && result) {
            return result;
        }
        logger.error('查询资产信息失败，资产编号：', assetNo);
        return null;
    };


    /**
     * 根据资产编号查询资产remark
     * @param assetNo 资产编号
     * @return 资产remark
     */
    this.queryRemarkByAssetNo = async function (assetNo) {
        let result = await dbUtil.query('queryRemarkByAssetNo', assetNo);
        if (result != -1 && result) {
            return result.remark;
        }
        logger.error('查询remark失败，资产编号：', assetNo);
        return null;
    };

    /**
     * 根据资产编号查询ip和port
     * @param assetNo 资产编号
     * @return 资产ip,port
     */
    this.queryIpAndPortByAssetNo = async function (assetNo) {
        let result = await dbUtil.query('queryIpAndPortByAssetNo', assetNo);
        if (result != -1 && result) {
            return result;
        }
        result = await dbUtil.query('queryIpAndPortByAssetNoAndOrg', assetNo);
        if (result != -1 && result) {
            return result;
        }
        logger.error('查询ip,port失败，资产编号：', assetNo);
        return null;
    };

    /**
     * 根据视频ID查询deviceId
     * @param videoId 视频服务返回的ID
     * @return deviceId
     */
    this.queryDeviceIdByVideoId = async function (videoId) {
        let result = await dbUtil.query('queryDeviceCodeByUsiCamId', videoId);
        if (result != -1 && result) {
            return result.device_code;
        }
        logger.error('查询视频deviceId失败，videoId：', videoId);
        return null;
    };

    /**
     * 根据deviceId查询视频ID
     * @param deviceId
     * @return 视频ID
     */
    this.queryVideoIdByDeviceId = async function (DeviceId) {
        let result = await dbUtil.query('queryUsiCamIdByDeviceCode', DeviceId);
        if (result != -1 && result) {
            return result.usi_cam_id;
        }
        logger.error('查询VideoId失败，DeviceId：', DeviceId);
        return null;
    };

    /**
     * 保存设备状态历史表信息 d_device_status_history
     * 更新设备状态信息 d_device_status
     * @param devStatus 参照dataStructDefine.js中DevStatusInfo
     */
    var saveDeviceStatusHistory = async function (devStatus) {
        let param = [devStatus.running, devStatus.onLine, devStatus.assetNo];
        let result = await dbUtil.insert('service0909902001DeviceStatusHistory', param);
        if (result == -1) {
            logger.error('保存设备状态历史表失败，资产编号= ', devStatus.assetNo);
            return null;
        }
    };

    /**
     * 更新设备状态信息 d_device_status
     * @param devStatus
     * @return {Promise.<null>}
     */
    var saveDeviceStatus = async function (devStatus) {
        let param = [devStatus.running, devStatus.runningChanged, devStatus.onLine, devStatus.onLineChanged,
            devStatus.userModify, devStatus.assetNo];
        let result = await dbUtil.update('service0909902001DeviceStatusUpt', param);
        if (result == -1) {
            logger.error('更新设备状态信息失败，资产编号=%s！', devStatus.assetNo);
            return null;
        }
    };

    /**
     * 查询事件状态信息 e_device_event
     * @param eventStatus 参照dataStructDefine.js中EventStatusInfo
     */
    this.queryEventStatus = async function (eventStatus) {
        let param = [eventStatus.deviceId, eventStatus.eventTime, eventStatus.eventSecondTypeCode];
        let result = await dbUtil.queryList('service0909901001DeviceEventQuery', param);
        if (result != -1) {
            return result;
        }
    };

    /**
     * 保存事件状态信息 e_device_event
     * @param eventStatus 参照dataStructDefine.js中EventStatusInfo
     */
    var saveEventStatus = async function (eventStatus) {
        let param = [eventStatus.eventTime, eventStatus.deviceId, eventStatus.orgCode, eventStatus.roadId,
            eventStatus.eventCode, eventStatus.eventCode];
        let result = await dbUtil.insert('service0909901001DeviceEventInsert', param);
        if (result == -1) {
            logger.error('插入事件状态信息失败，事件id=%s！', eventStatus.deviceId);
        }
    };

    /**
     * 更新事件状态信息 e_device_event
     * @param eventStatus 参照dataStructDefine.js中EventStatusInfo
     */
    var updateEventStatus = async function (eventStatus) {
        let param = [eventStatus.deviceId, eventStatus.eventTime, eventStatus.eventCode];
        let result = await dbUtil.update('service0909901001DeviceEventUpt', param);
        if (result == -1) {
            logger.error('更新事件状态信息失败，事件id=%s！', eventStatus.deviceId);
        }
    };

    /**
     * 保存广播状态信息 d_broadcast_status
     * @param broadcastStatus 参照dataStructDefine.js中BroadcastStatusInfo
     */
    var saveBroadcastDevStatus = async function (broadcastStatus) {
        let param = [broadcastStatus.deviceId, broadcastStatus.responseTime, broadcastStatus.status, broadcastStatus.uVolume];
        let result = await dbUtil.insert('updateBroadcastStatus', param);
        if (result == -1) {
            logger.error('保存广播状态信息失败，资产编号=%s！', broadcastStatus.assetNo);
        }
    };

    /**
     * 广播状态存储业务
     * @param msg 广播状态II类协议数据
     * @return {Promise.<null>}
     */
    var broadcastStatus = async function (msg) {
        let data = msg;
        let header = data.header;
        let assetNo = header.assetNo;
        let responseTime = header.responseTime;
        let result = await queryAllByAssetNo(assetNo);
        if (!result) {
            return null;
        }

        //广播状态信息
        let broadcastStatus = dataStructDefine.broadcastStatus;
        broadcastStatus.deviceId = result.device_id;
        broadcastStatus.responseTime = responseTime;
        broadcastStatus.status = data.status; // 1 未连通 2 空闲 3 喊话等待中 4正在响铃 5寻呼工作中 6对讲工作中 7广播工作中
        broadcastStatus.uVolume = data.volume; // 音量
        saveBroadcastDevStatus(broadcastStatus);
    };

    /**
     * 事件告警存储业务
     * @param msg
     * @return {Promise.<null>}
     */
    var eventStatus = async function (msg) {
        let data = msg;
        let header = data.header;
        let assetNo = header.assetNo;
        let result = await queryAllByAssetNo(assetNo);
        if (!result) {
            return null;
        }

        //告警信息数据
        let eventStatus = dataStructDefine.eventStatus;
        eventStatus.deviceId = result.device_id;
        eventStatus.eventTime = data.alarmTime;
        eventStatus.orgCode = result.org_code;
        eventStatus.roadId = result.road_id;
        for (let alarmInfo of data.data) {
            eventStatus.eventCode = alarmInfo.alarmCode;
            if (alarmInfo.alarmFlag == 200) {
                updateEventStatus(eventStatus);
            } else {
                saveEventStatus(eventStatus);
            }
        }
    };

    /**
     * 设备状态存储业务
     * @param msg
     * @return {Promise.<void>}
     */
    var devStatus = async function (msg) {
        let data = msg;
        let header = data.header;
        let assetNo = header.assetNo;
        //设备状态信息数据
        let devStatus = dataStructDefine.devStatus;//设备状态信息
        let deviceTypeTime = data.deviceTypeTime;
        let deviceType = data.deviceType;
        let onlineType = data.onlineType;
        if (onlineType == '0') {
            onlineType = '2';
        }
        devStatus.assetNo = assetNo;//资产编号
        devStatus.onLine = onlineType;//在线状态
        devStatus.running = deviceType;//运行状态
        devStatus.onLineChanged = deviceTypeTime;//在线状态变更时间
        devStatus.runningChanged = deviceTypeTime;//运行状态变更
        devStatus.userModify = 'collector';//
        saveDeviceStatusHistory(devStatus);
        saveDeviceStatus(devStatus);
    };
    /**
     * 存储II类业务数据到数据库
     * @param data JSON格式的Ⅱ类业务数据
     */
    this.storage = async function (msg) {
        let data = msg;
        let msgType = typeof msg;
        if (msgType === 'String') {
            try {
                data = JSON.parse(msg);
            } catch (err) {
                logger.error('接收到的存储数据类型转换错误：', err.message);
                return null;
            }
        }
        let header;
        let optCmd;
        try {
            header = data.header;
            optCmd = header.optCmd;
            let schema = avroUtil.getSchemaByOptcmd(optCmd);
            let avroData = avroUtil.parseJsonToAvro(data, schema);
            if (!avroData) {
                return;
            }
        } catch (err) {
            logger.error('不是正确的II协议，avro校验未通过');
            return null;
        }
        header = data.header;
        optCmd = header.optCmd;
        switch (optCmd) {
            case 'broadcast_data_9005':
                logger.info('广播状态数据存储，广播状态II类协议数据：', data);
                broadcastStatus(data);
                break;
            case 'ad_data_9001':
                logger.info('告警信息数据存储，告警信息II类协议数据：', data);
                eventStatus(data);
                break;
            case 'ad_data_9500':
                logger.info('设备状态数据存储，设备状态II类协议数据：', data);
                devStatus(data);
                break;
            default:
                logger.error('此II类协议数据不需要存储，optCmd= ', optCmd);
        }
    };
}

var storageMgr = new StorageMgr();
module.exports = storageMgr;