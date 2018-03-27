var busiHttpReq = require('./httpBusiReq.js');
var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);

var WebBusiHttpHandlers = require('./webBusiHttpHandlers');

/**
 * SendBusinessHttpReq:用来封装发送业务的Http请求
 * by 潘翔 on 2017/12/23
 */
function SendBusinessHttpReq() {
    /**
     *sendBusiReqData:发送不同业务的Http请求数据
     * @param
     *      data:发送的请求数据（json）
     * by 潘翔 on 2017/12/23
     */
    this.sendBusiReqData = function (data) {
        var optCmd = data.header.optCmd;
        switch (optCmd) {
            case 'safe_param_6010'://云台控制开始，不需要返回, Get
                logger.info('发送云台控制开始的请求[%s]', JSON.stringify(data));
                sendPtzControl(data, 1000);
                break;
            case 'safe_param_6011'://云台控制结束，不需要返回, Get
                logger.info('发送云台控制结束的请求[%s]', JSON.stringify(data));
                sendPtzControl(data, 1001);
                break;
            case 'safe_param_6021'://设置预置点
                logger.info('发送设置预置点的请求[%s]', JSON.stringify(data));
                sendPtzControl(data);
                break;
            case 'safe_param_6020'://云台PTZ控制
                logger.info('发送云台PTZ控制的请求[%s]', JSON.stringify(data));
                sendPtzControl(data, data.params.join(','));
                break;
            case 'safe_param_6012'://视频播放, Get
                logger.info('发送视频播放的请求[%s]', JSON.stringify(data));
                sendPlayVideo(data);
                break;
            case 'safe_param_6013'://录像列表查询
                logger.info('发送查询录像列表的请求[%s]', JSON.stringify(data));
                sendQuerRecordAndScreenshotList(data);
                break;
            case 'safe_param_6014'://截图列表查询
                logger.info('发送查询截图列表的请求[%s]', JSON.stringify(data));
                sendQuerRecordAndScreenshotList(data);
                break;
            case 'safe_param_6015'://触发录像(自动停止)
            case 'safe_param_6016'://触发录像(手动开始)
            case 'safe_param_6017'://触发录像(手动结束)
            case 'safe_param_6018'://触发截图
                logger.info('发送触发录像业务的请求[%s]', JSON.stringify(data));
                sendTriggerVideo(data);
                break;
            case 'safe_param_6019'://录像设置
                logger.info('发送录像设置的请求[%s]', JSON.stringify(data));
                sendRecordPlan(data);
                break;
            default:
                logger.error('视频业务类型不存在，optCmd=', optCmd);
                break;
        }
    };

    /**
     * sendPtzControlStart:发送云台控制开始Http请求
     * @param
     *      data:云台开始的数据信息
     *      param:云台控制的参数
     * by 潘翔 on 2017/12/23
     */
    async function sendPtzControl(data, param) {
        let arrAssetNo = data.header.assetNo.split('|');
        for (let i = 0; i < arrAssetNo.length; i++) {
            let singleData = {};
            singleData.header = {};
            singleData.body = {};
            singleData.header.assetNo = arrAssetNo[i];
            singleData.header.equipType = data.header.equipType;
            singleData.header.requestTime = data.header.requestTime;
            singleData.header.dataSource = data.header.dataSource;
            singleData.header.optCmd = data.header.optCmd;
            singleData.body.command = data.command;
            singleData.body.speed = data.speed;
            if (param)
                singleData.body.params = param;
            else
                singleData.body.params = data.params;
            if (data.orientation)
                singleData.body.orientation = data.orientation;//0
            else
                singleData.body.orientation = 0;
            let httpReq = new busiHttpReq.webHttpBusiReq(singleData);
            httpReq.sendHttpReq();
        }
    }

    /**
     * sendPlayVideo:Web发送视频播放,主要用来返回URL地址
     * @param
     *      data:web发送视频播放的信息
     * by 潘翔 on 2017/12/25
     */
    async function sendPlayVideo(data) {
        let arrAssetNo = data.header.assetNo.split('|');
        let header = data.header;
        for (let i = 0; i < arrAssetNo.length; i++) {
            let assetNo = arrAssetNo[i];
            header.assetNo = assetNo;
            let singleData = {};
            singleData.header = header;
            singleData.body = data.type;
            let httpReq = new busiHttpReq.webHttpBusiReq(singleData);
            httpReq.sendHttpReq();
        }
    }

    /**
     * sendQuerRecordAndScreenshotList:发送查询录像列表和截图列表的查询的http请求
     * @param
     *      data:来自web的请求命令数据
     * by 潘翔 2018/1/6
     */
    async function sendQuerRecordAndScreenshotList(data) {
        let arrAssetNo = data.header.assetNo.split('|');
        for (let i = 0; i < arrAssetNo.length; i++) {
            let singleData = {};
            singleData.header = {};
            singleData.body = {};
            singleData.header.assetNo = arrAssetNo[i];
            singleData.header.equipType = data.header.equipType;
            singleData.header.requestTime = data.header.requestTime;
            singleData.header.dataSource = data.header.dataSource;
            singleData.header.optCmd = data.header.optCmd;
            singleData.body.beginTime = data.beginTime;
            singleData.body.endTime = data.endTime;
            let httpReq = new busiHttpReq.webHttpBusiReq(singleData);
            httpReq.sendHttpReq();
        }
    }

    /**
     * sendTriggerVideo:发送触发录像的http请求，包括自动自动停止。手动开始，手动结束和触发截图
     * @param
     *      data:来自web的请求命令数据
     * by 潘翔 2018/1/6
     */
    async function sendTriggerVideo(data) {
        logger.info('发送录像触发业务信息:', JSON.stringify(data));
        let arrAssetNo = data.header.assetNo.split('|');
        let busiHttpHandles = new WebBusiHttpHandlers;
        busiHttpHandles.setReqCount(arrAssetNo.length);
        for (let i = 0; i < arrAssetNo.length; i++) {
            let singleData = {};
            singleData.header = {};
            singleData.header.assetNo = arrAssetNo[i];
            singleData.header.equipType = data.header.equipType;
            singleData.header.requestTime = data.header.requestTime;
            singleData.header.dataSource = data.header.dataSource;
            singleData.header.optCmd = data.header.optCmd;
            if (data.data) {
                let info = data.data[i];
                singleData.body = info;
            }
            let httpReq = new busiHttpReq.webHttpBusiReq(singleData, busiHttpHandles);
            httpReq.sendHttpReq();
        }
    }

    /**
     * sendRecordPlan:web发送录像计划请求
     * @param
     *      data:web发送来的录像配置的请求
     *      optCmd:返回的操作码
     * by 潘翔 on 2017/12/24
     */

    async function sendRecordPlan(data) {//录像配置下面不支持多个，只能for一下
        logger.info('发送录像配置业务信息:', JSON.stringify(data));
        let arrAssetNo = data.header.assetNo.split('|');
        let webBusiHttpHandlers = new WebBusiHttpHandlers;
        webBusiHttpHandlers.setReqCount(arrAssetNo.length);
        for (let i = 0; i < arrAssetNo.length; i++) {
            let singleData = {};
            singleData.header = {};
            singleData.header.assetNo = arrAssetNo[i];
            singleData.header.equipType = data.header.equipType;
            singleData.header.requestTime = data.header.requestTime;
            singleData.header.dataSource = data.header.dataSource;
            singleData.header.optCmd = data.header.optCmd;
            singleData.body = {};
            singleData.body.recordTime = data.data[i].duration;
            singleData.body.preRecordTime = data.data[i].preRecTime;
            singleData.body.streamType = data.data[i].streamType;
            singleData.body.audioRec = 1; // 1记录音频 2不记录音频
            singleData.body.holdTime = 3; // 保存三天
            singleData.body.disable = 1; // 不启用高级参数
            let httpReq = new busiHttpReq.webHttpBusiReq(singleData, webBusiHttpHandlers);
            httpReq.sendHttpReq();
        }
    }
}

module.exports = new SendBusinessHttpReq();