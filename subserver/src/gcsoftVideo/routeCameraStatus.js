/**
 * 接收视频状态模块，业务如下：
 * 1、将原始状态数据转为II类协议的数据
 * 2、将二类协议数据通过数据库接口进行存储
 * 3、将二类协议数据发送给集控
 * 4、将二类协议数据发送给WEB客户端
 * 5、返回视频服务的回复信息给tomcat
 * @author 潘翔
 * @date 2017/11/30
 */
var commonModule = require('../commonModuleExport');
var logger = commonModule.logger.getLogger(3);
var dbManage = require('../storageMgr');
var packVideoProtocolII = require('../gcsoftVideo/packProtocolII');
var sockertMgr = require('../socketMgr');
var webSocketMgr = require('../wsClientMgr');
var CameraStatus = function () {
};

CameraStatus.prototype.businessProcess = async function(data, res) {
    try {
        logger.info('http接收到视频服务推送的设备状态数据：', data);
        let request = JSON.parse(data);
        var cameraId = request.devId;
        var assetNo = await dbManage.queryDeviceIdByVideoId(cameraId);
        if(!assetNo) {
            logger.error('该摄像机[%s]没有资产编号', cameraId);
            return;
        }
        var mainControlStatusII = {};
        var mainControlAlaramII = {};
        var webStatusII = {};
        packVideoProtocolII.packHeader(mainControlStatusII, assetNo, 'ad_data_9500');
        packVideoProtocolII.packHeader(mainControlAlaramII, assetNo, 'ad_data_9001');
        packVideoProtocolII.packHeader(webStatusII, assetNo, 'safe_data_9005');
        packVideoProtocolII.packMainControlCameraStatus(mainControlStatusII, request);
        packVideoProtocolII.packMainControlCameraAlarm(mainControlAlaramII, request);
        packVideoProtocolII.packWebStatus(webStatusII, request);
        logger.info('推送到集控socket的II类设备状态数据:', JSON.stringify(mainControlStatusII));
        logger.info('推送到集控socket的II类告警数据:', JSON.stringify(mainControlAlaramII));
        sockertMgr.pushDataForII(mainControlStatusII);
        sockertMgr.pushDataForII(mainControlAlaramII);
        sockertMgr.pushDataForII(webStatusII);
        webSocketMgr.pushBusiDataForII(webStatusII);
        var response = {
            'retCode' : 200,
            'errMsg' : '',
            'dataCount' : 0
        }
        res.writeHead(200, {'Content-Type': 'text/plain'});
        res.write(JSON.stringify(response));
        res.end();
    }
    catch(err) {
        logger.error('处理视频平台推送状态数据异常：', err.message);
    }
};

var devStaus = new CameraStatus();
module.exports = devStaus;