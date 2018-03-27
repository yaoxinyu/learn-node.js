/**
 * 视频服务模块，功能描述：
 * 1、监听消息请求，解析消息，分发任务；
 * 2、发送操作结果回复
 * 说明：广播服务在子进程中运行
 * @author 潘翔
 * @date 2017/11/24
 */

var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);
// 常量模块
const constants = commonModule.constants;
// MQ模块
var mqUtil = require('../activeMQMgr');

// 轮巡任务模块
var scheduleTask = require('./asyncVideoProcessor');
var sql = require('../common/util/sql');
var storageMgr = require('../storageMgr');

function VideoServer() {
    //启动标志
    let isStarted = false;

    /**
     * start:初始化启动，初始化相关的配置信息
     * by 潘翔 on 2017/11/24
     */
    this.start = async function () {
        if (!isStarted) {
            logger.info('视频服务ActiveMQ初始化....');
            mqUtil.initByLocalConfig();

            logger.info('视频服务进程-数据库初始化...');
            await storageMgr.init();

            logger.info('开始定时查询视频状态和事件');
            scheduleTask.start();
            isStarted = true;
        }
    };
}

// 视频服务模块启动
var videoServer = new VideoServer();
videoServer.start();


/**
 * 接收主进程的消息
 * @param name 消息的名称
 * @param msg 消息内容：JSON string
 */
process.on('message', async function (msg) {
    try {
        msg = JSON.parse(msg);
        let name = msg.name;
        let data = msg.data;
        if (name == constants.PROCESS_MESSAGE_DEFINE.VIDEO_MSG.TASK_REQ) {
            logger.info('视频服务子进程接收到主进程的任务信息[%s]', JSON.stringify(msg));
            scheduleTask.pushTask(data);
        }
    }
    catch (exception) {
        logger.error('视频服务子进程解析主进程发来的消息异常,信息[%s]', exception.message);
    }
});
