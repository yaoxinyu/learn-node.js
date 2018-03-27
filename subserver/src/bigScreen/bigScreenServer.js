/**
 * 大屏服务模块，功能描述：
 * @author wangweizhen
 * @date 2018/1/17
 */

var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);
// 常量模块
const constants = commonModule.constants;
var activeMQMgr = require('../activeMQMgr');
var storageMgr = require('../storageMgr');
var bigScreenOper = require('./bigScreenOperation');


function BigScreenServer() {
    // 启动标志
    var isStarted = false;

    /**
     * 模块启动
     */
    this.start = async function () {
        if (!isStarted) {
            // 数据库初始化
            logger.info('大屏服务进程-数据库初始化...');
            await storageMgr.init();

            // activeMQ初始化
            logger.info('大屏服务进程-activeMQ初始化...');
            activeMQMgr.initByLocalConfig();
            await commonModule.sleep(3000);
            isStarted = true;
        }
    };

    /**
     * 请求任务
     * @param req 外部发来的请求消息
     */
    this.taskReq = function (req) {
        if (!req) {
            logger.error('大屏任务请求为空！');
            return;
        }
        logger.info('开始处理大屏任务请求：', req);
        bigScreenOper.dealOperation(req);
    };
}

// 模块启动
var server = new BigScreenServer();
server.start();


/**
 * 接收主进程的消息
 * @param name 消息的名称
 * @param msg 消息内容：JSON string
 */
process.on('message', function (msg) {
    // 解析消息并处理
    try {
        msg = JSON.parse(msg);
        let name = msg.name;
        let data = msg.data;
        if (name === constants.PROCESS_MESSAGE_DEFINE.BIG_SCREEN_MSG.TASK_REQ) {
            // 收到一个大屏任务请求消息
            server.taskReq(data);
        } else {
            logger.error('大屏服务收到主进程无法处理的消息：%s！', msg);
        }
    } catch (exception) {
        logger.error('大屏服务解析主进程发来的消息异常: ' + exception.message);
    }
});