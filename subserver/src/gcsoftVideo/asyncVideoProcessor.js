/**
 * 视频服务异步任务处理模块
 * 注意：由视频服务模块来启动该模块
 * 功能描述：
 * 1、接收外部创建的视频任务，将其加入任务队列；
 * 2、轮巡任务队列，将有超时的任务从队列中移除，并通过MQ发送回复消息；
 * 3、定时获取设备状态推送信息；
 * 4、定时获取所有的设备状态信息
 * @author 潘翔
 * @date 2017/11/27
 */

// 定义任务轮巡时间间隔
var commonModule = require('../commonModuleExport');
var sendStatusEventReq = require('./sendSatusEventReq');
var sendBusiHttpReq = require('./sendBusinessReq');

// 日志模块
const logger = commonModule.logger.getLogger(0);

const SCHEDULE_TIME = 300 * 1000; // 单位ms

function AysncVideoProcessor() {

    //启动标志
    var isStarted = false;
    /**
     * 模块启动
     */
    this.start = function () {
        if (!isStarted) {
            //发送Http订阅url
            sendHttpSubscibe();
            //启动轮巡查询设备的状态
            timerGetCamearStatus();
            setInterval(timerGetCamearStatus, SCHEDULE_TIME);
            isStarted = true;
        }
    };

    var sendHttpSubscibe = function () {
        logger.info('初始化时向视频平台发送事件订阅和状态订阅');
        let eventSubReq = new sendStatusEventReq.cameareEventSubHttpReq();
        eventSubReq.sendHttpReq();
        let statusSubReq = new sendStatusEventReq.cameraStatusSubHttpReq();
        statusSubReq.sendHttpReq();
    };

    /**
     * 定时发送查询摄像机状态的请求
     * by 潘翔 on 2018/1/10
     */
    var timerGetCamearStatus = function () {
        let httpStatusReq = new sendStatusEventReq.queryCameraStatusHttpReq();
        httpStatusReq.sendHttpReq();
    };

    /**
     * pushTask:插入新的业务数据,调用
     * @param
     *      busiData:业务数据
     * by 潘翔 on 2017/12/23
     */
    this.pushTask = function (busiData) {
        if (busiData) {
            sendBusiHttpReq.sendBusiReqData(busiData);
        }
    };
}

var videoProcessor = new AysncVideoProcessor();
module.exports = videoProcessor;

