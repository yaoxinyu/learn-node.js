/**
 * 广播服务模块，功能描述：
 * 1、监听消息请求，解析消息，分发任务；
 * 2、发送操作结果回复
 * 说明：广播服务在子进程中运行
 * @author yaoxinyu
 * @date 2017/11/2
 */

var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);
// 常量模块
const constants = commonModule.constants;
// 协议处理对象
var protoHandler = require('./broadcastProtoHandler');
// 任务管理器生产类对象
var taskMgrFac = require('./taskMgrFactory');
// 轮巡任务模块
var scheduleTask = require('./asyncTaskProcessor');

var activeMQMgr = require('../activeMQMgr');
var storageMgr = require('../storageMgr');


function BroadcastServer() {
    // 启动标志
    var isStarted = false;

    /**
     * 模块启动
     */
    this.start = async function () {
        if (!isStarted) {
            // 数据库初始化
            logger.info('广播服务进程-数据库初始化...');
            await storageMgr.init();

            // activeMQ初始化
            logger.info('广播服务进程-activeMQ初始化...');
            activeMQMgr.initByLocalConfig();
            await commonModule.sleep(3000);

            // 任务管理器模块初始化
            logger.info('广播服务进程-任务管理器模块初始化...');
            taskMgrFac.init();

            // 开启轮巡任务
            scheduleTask.start();

            isStarted = true;
        }
    };

    /**
     * 请求任务
     * @param req 外部发来的请求消息
     */
    this.taskReq = async function (req) {
        if (!req) {
            logger.error('广播任务请求为空！');
            return;
        }

        logger.info('根据不同厂商类型分发广播请求任务...');
        let factoryAssetNoMap = {}; // 厂商与资产编号的映射
        let header = req.header;    // 保存消息原始头部
        let assetNos = [];
        // 解析出资产编号
        if (header.assetNo != null && header.assetNo != '') {
            assetNos = header.assetNo.split('|');
        }
        if (assetNos.length == 0) {
            protoHandler.doBroadcastErrResponse(req, '资产编号为空');
            return;
        }

        for (let assetNo of assetNos) {
            // 解析出厂商类型
            let facType = await storageMgr.queryFactoryByAssetNo(assetNo);
            if (!facType) {
                // 默认为美电贝尔厂商
                facType = '014';
            }
            if (facType) {
                logger.info('解析出设备厂家类型：资产编号[%s],厂商[%s]', assetNo, facType);
                if (factoryAssetNoMap[facType]) {
                    factoryAssetNoMap[facType] += '|' + assetNo;
                } else {
                    factoryAssetNoMap[facType] = assetNo;
                }
            }
        }
        for (let facType in factoryAssetNoMap) {
            // 根据厂商类型获取对应的任务管理对象
            let taskMgr = taskMgrFac.getManager(facType);
            if (taskMgr) {
                req.header.assetNo = factoryAssetNoMap[facType];
                // 执行操作
                protoHandler.taskHandle(req, taskMgr, header);
            } else {
                protoHandler.doBroadcastErrResponse(req, '广播厂家错误');
            }
        }
    };
}

// 模块启动
var server = new BroadcastServer();
server.start();


/**
 * 接收主进程的消息
 * @param name 消息的名称
 * @param msg 消息内容：JSON string
 */
process.on('message', async function (msg) {
    // 解析消息并处理
    try {
        msg = JSON.parse(msg);
        let name = msg.name;
        let data = msg.data;
        if (name === constants.PROCESS_MESSAGE_DEFINE.BROADCAST_MSG.TASK_REQ) {
            // 收到一个广播任务请求消息
            // logger.info("广播服务收到主进程任务消息: ", data);
            server.taskReq(data);
        } else {
            logger.error('广播服务收到主进程无法处理的消息：%s！', msg);
        }
    } catch (exception) {
        logger.error('广播服务解析主进程发来的消息异常: ' + exception.message);
    }
});



