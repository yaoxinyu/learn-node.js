/**
 * 主进程处理视频进程传过来的内部数据，将内部数据转换为二级数据发送，存储
 * @author 潘翔
 * @date 2017/11/29
 */

var packProtocolII = require('../gcsoftVideo/packProtocolII');
var dbManage = require('../storageMgr');
var sockertMgr = require('../socketMgr');
var webSocketMgr = require('../wsClientMgr');
var commonModule = require('../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function VideoListener() {
    this.onMessage = function(msg) {
        var header = msg.header;
        var optCmd = header.optCmd;
        switch (optCmd) {
            case 'safe_data_9005':
                handleStatus(msg);//返回状态
                break;
            case 'safe_data_9006':
                handleEvent(msg);//返回事件
                break;
            case 'safe_data_9012'://视频播放
                returnPlayVideoURL(msg);
                break;
            case 'safe_data_9013'://录像列表查询
                returnQueryVideoList(msg);
                break;
            case 'safe_data_9014':// 截图列表查询
                returnScreenshotList(msg);
                break;
            case 'safe_data_9015':// 触发录像（自动停止）
            case 'safe_data_9016'://触发录像（手动开始）
            case 'safe_data_9017'://触发录像（手动结束）
                returnExecRecord(msg);
                break;
            case 'safe_data_9018'://触发截图
                returnExecScreenShot(msg);
                break;
            case 'safe_data_9019'://录像设置
                returnVideoConfig(msg);
                break;
            case 'safe_data_9021'://预置位
                returnPreset(msg);
                break;
            default:
                logger.error('业务类型不存在，optCmd=', optCmd);
                break;
        }
    };

    /**
     * handleStatus:将状态发送打包II级数发送Json格式
     * @param
     *      msg:待打包II级数据的原始数据
     * by 潘翔 on 2017/12/23
     */
    var handleStatus = async function(msg) {
        logger.info('主进程接收到摄像机状态的数据[%s]', JSON.stringify(msg));
        var nCount = msg.data.dataCount;
        for(var i = 0; i < nCount; i++) {
            var cameraId = msg.data.dataList[i].devId;
            var assetNo = await dbManage.queryDeviceIdByVideoId(cameraId);
            if(!assetNo) {
                logger.error('该摄像机[%s]没有对应的资产编号', cameraId);
                continue;
            }
            var webStatusII = {};//传回给WEB端的二类协议
            var mainControlStatusII = {};//二类协议的设备状态
            var mainControlAlaramII = {};//二类协议的设备告警
            packProtocolII.packHeader(mainControlStatusII, assetNo, 'ad_data_9500');
            packProtocolII.packMainControlCameraStatus(mainControlStatusII, msg.data.dataList[i]);
            packProtocolII.packHeader(mainControlAlaramII, assetNo, 'ad_data_9001');
            packProtocolII.packMainControlCameraAlarm(mainControlAlaramII, msg.data.dataList[i]);
            packProtocolII.packHeader(webStatusII, assetNo, 'safe_data_9005');
            packProtocolII.packWebStatus(webStatusII, msg.data.dataList[i]);
            logger.info('发送给集控的II类告警数据[%s]', JSON.stringify(mainControlAlaramII));
            logger.info('发送给集控的II类状态数据[%s]', JSON.stringify(mainControlStatusII));
            sockertMgr.pushDataForII(mainControlStatusII);
            sockertMgr.pushDataForII(mainControlAlaramII);
            sockertMgr.pushDataForII(webStatusII);
            webSocketMgr.pushBusiDataForII(webStatusII);
        }
    };


    /**
     * 处理事件的业务
     */
    var handleEvent = function() {

    };

    /**
     * returnPlayVideoURL:将播放视频msg打包成II数据并将此数据发送给客户端
     * @param
     *      data:原始的内部定义的数据（包含header和body）,此数据是json对象数据
     *  by 潘翔 on 2017/12/25
     */
    function returnPlayVideoURL(data) {
        let code = data.header.code;
        let msg = data.header.msg;
        let body = data.data;
        let webPlayVideoII = {};
        webPlayVideoII.header = data.header;
        packProtocolII.packReturWebPlayVideoWebSocket(webPlayVideoII, body, code, msg);
        logger.info('播放视频的信息:', webPlayVideoII);
        webSocketMgr.pushBusiDataForII(webPlayVideoII);
    }

    /**
     * returnQueryVideoList: 将msg打包成II级数据并返回查询录像列表
     * @param
     *      data:原始的内部定义的数据（包含header和body）,此数据是json对象数据
     *  by 潘翔 on 2017/12/23
     */
    function returnQueryVideoList(data) {
        logger.info('主进程接受到MQ的消息业务类型是查询录像列表,消息体是[%s]', JSON.stringify(data));
        let webVideoListII = {};
        let body = data.data;
        webVideoListII.header = data.header;
        packProtocolII.packReturnWebQueryVideoList(webVideoListII, body);
        logger.info('发送给业务系统的查询录像列表的数据是[%s]', JSON.stringify(webVideoListII));
        webSocketMgr.pushBusiDataForII(webVideoListII);
    }

    /**
     * returnVideoConfig:返回打包II级录像配置、并将II级数据给客户端
     * @param
     *      data:原始的内部定义的数据（包含header和body）,此数据是json对象数据
     * by 潘翔 on 2017/12/23
     */
    function returnVideoConfig(data) {
        logger.info('主进程接受到MQ的消息业务类型是录像配置,消息体是[%s]', JSON.stringify(data));
        let webVideoConfigII = {};
        webVideoConfigII.header = data.header;
        let body = data.data;
        packProtocolII.packWebExecRecordAndVideoConfig(webVideoConfigII, body);
        logger.info('发送给业务系统的录像配置的数据是[%s]', JSON.stringify(webVideoConfigII));
        webSocketMgr.pushBusiDataForII(webVideoConfigII);
    }

    /**
     * returnPreset:返回预置位、并将II级数据给客户端
     * @param
     *      data:原始的内部定义的数据（包含header和body）,此数据是json对象数据
     * by 潘翔 on 2017/12/23
     */
    function returnPreset(data) {
        logger.info('主进程接收到MQ的消息业务类型是预置位,消息体是[%s]', JSON.stringify(data));
        let webPreSetII = {};
        webPreSetII.header = data.header;
        let body = data.data;
        packProtocolII.packWebPreset(webPreSetII, body);
        logger.info('发送给业务系统的预置位数据是[%s]', JSON.stringify(webPreSetII));
        webSocketMgr.pushBusiDataForII(webPreSetII);
    }

    /**
     * returnVideoConfig:返回打包II级录像截图的数据、并将II级数据给客户端
     * @param
     *      data:原始的内部定义的数据（包含header和body）,此数据是json对象数据
     * by 潘翔 on 2017/12/23
     */
    function returnScreenshotList(data)
    {

    }

    /**
     * returnExecRecord:返回打包触发录像II级数据，并将II级数据返回给客户端
     * @param
     *      data:原始的内部定义的数据（包含header和body）,此数据是json对象数据
     * by 潘翔 on 2017/12/23
     */
    function returnExecRecord(data) {
        logger.info('主进程接受到MQ的消息业务类型是触发录像,消息体是[%s]', JSON.stringify(data));
        let webExecRecordII = {};
        webExecRecordII.header = data.header;
        let msg = data.data;
        packProtocolII.packWebExecRecordAndVideoConfig(webExecRecordII, msg);
        logger.info('发送给业务系统的触发录像的的数据是[%s]', JSON.stringify(webExecRecordII));
        webSocketMgr.pushBusiDataForII(webExecRecordII);
    }

    /**
     * returnExecScreenShot:返回打包触发截图II级数据，并将II级数据返回给客户端
     * @param
     *      data:原始的内部定义的数据（包含header和body）,此数据是json对象数据
     * by 潘翔 on 2017/12/23
     */
    function returnExecScreenShot(data) {
        logger.info('主进程接受到MQ的消息业务类型是触发截图,消息体是[%s]', JSON.stringify(data));
        let webExecScreenII = {};
        webExecScreenII.header = data.header;
        let msg = data.data;
        packProtocolII.packWebExecRecordAndVideoConfig(webExecScreenII, msg);
        logger.info('发送给业务系统的触发截图的的数据是[%s]', JSON.stringify(webExecScreenII));
        webSocketMgr.pushBusiDataForII(JSON.stringify(webExecScreenII));
    }
}

module.exports = new VideoListener();
