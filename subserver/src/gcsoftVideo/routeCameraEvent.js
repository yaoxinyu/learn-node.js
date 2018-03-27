/**
 * 接收视频事件模块，业务如下：
 * 1、将原始事件数据转为II类协议的数据
 * 2、将二类协议数据通过数据库接口进行存储
 * 3、将二类协议数据发送给集控
 * 4、将二类协议数据发送给WEB客户端
 * @author 潘翔
 * @date 2017/12/01
 */
var commonModule = require('../commonModuleExport');
var dbManage = require('../storageMgr');
var packProtocolII = require('../gcsoftVideo/packProtocolII');
var sockertMgr = require('../socketMgr');
var eventTable = require('./eventTable');
const logger = commonModule.logger.getLogger(0);

var CameraEvent = function() {

}

CameraEvent.prototype.businessProcess = async function(data, res) {
    logger.info('接收到视频平台推送的事件数据：', data);
    logger.info('事件数据的类型是[%s]', typeof data);
    try {
        let request = JSON.parse(data);
        let cameraId = request.devId;//根据摄像机ID找到资产编号和设备ID
        var assetNo = await dbManage.queryDeviceIdByVideoId(cameraId);
        /*if(!assetNo) {
         logger3.error("该摄像机[%s]没有资产编号", cameraId);
         console.log("没有这个摄像机");
         return;
         }*/
        let level = request.level;//事件级别
        let type = request.type;//事件类型
        let subType = request.subType;//事件子类型
        let status = request.status;//1 -- 事件发生 2 -- 事件取消
        let desc = request.data;//事件数据，就是一个描述
        let time = request.time;
        let mainControlStatusII = {};
        let mainControlAlaramII = {};
        assetNo = '10009';
        packProtocolII.packHeader(mainControlStatusII, assetNo, 'ad_data_9500');
        packProtocolII.packHeader(mainControlAlaramII, assetNo, 'ad_data_9001');
        let devStatus = eventTable[type][subType].status;
        let devAlarm = eventTable[type][subType].alarm;
        mainControlStatusII.deviceTypeTime = new Date().getTime();
        mainControlStatusII.deviceType = devStatus.deviceType;
        mainControlStatusII.onlineType = devStatus.onlineType;
        mainControlAlaramII.alarmTime = new Date().getTime();
        mainControlAlaramII.data = [];
        mainControlAlaramII.data.push(devAlarm);
        logger.info('推送到集控socket的II类设备状态数据：', JSON.stringify(mainControlStatusII));
        logger.info('推送到集控socket的II类告警数据', JSON.stringify(mainControlAlaramII));
        sockertMgr.pushDataForII(mainControlStatusII);
        sockertMgr.pushDataForII(mainControlAlaramII);
    } catch(err) {
        logger.error('处理视频平台推送事件数据异常：', err.message);
    }
};

var cameraEvent = new CameraEvent();
module.exports = cameraEvent;