/**
 * WebSocket服务模块，功能描述：
 * 1、启动WebSocket服务，监听并管理连接；
 * 2、监听消息请求，解析消息；
 * 3、发送响应回复
 * @author yaoxinyu
 * @date 2017/11/12
 */

var express = require('express');
var app = express();
var http = require('http');
var WebSocket = require('ws');
var commonModule = require('../src/commonModuleExport');
// 日志模块
const logServer = commonModule.logger.getLogger(0);
// 常量模块
const constants = commonModule.constants;
const fileUtil = commonModule.fileUtil;
var schedule = require('../src/common/util/schedule');
var globalData = require('../src/globalDataCache');
var avroUtil = require('../src/common/util/avroUtil');
var httpReq = require('../src/httpRequests');

var serverMgr = require('../src/serverMgr');
var storageMgr = require('../src/storageMgr');
var activeMQMgr = require('../src/activeMQMgr');
var wsClientMgr = require('../src/wsClientMgr');
var socketMgr = require('../src/socketMgr');
var wsMsgHandle = require('../src/wsMessageHandle');

var server; // http server对象
var wsServer; // WebSocket server对象

/**
 * 模块初始化函数
 */
async function init() {
    // 初始化读取配置文件数据缓存
    logServer.info('初始化加载配置...');
    loadConfig();

    // avro协议缓存初始化
    logServer.info('avro缓存初始化...');
    // 地区编码缓存初始化
    logServer.info('地区编码缓存初始化...');
    // ActiveMQ管理模块初始化
    logServer.info('主进程ActiveMQ初始化...');
    // 存储管理模块初始化
    logServer.info('主进程存储管理模块初始化...');
    // 上面四个同步放在一起并行await
    // await Promise.all([avroCacheInit(), httpReq.reqOrg(), activeMQMgr.init(), storageMgr.init()]);
    await activeMQMgr.init();
    await commonModule.sleep(3000);

    // socket管理模块初始化
    logServer.info('socket初始化...');
    socketMgr.init();

    // 启动所有服务
    serverMgr.startAllServer();

    // 定时删除上传的音乐文件
    logServer.info('启动定时删除上传音乐文件...');
    timerDeleteUploadFile();

    // 定时删除截图
    logServer.info('启动定时删除截图...');
    timerDeleteImagesFile();

    // 启动定时重启广播子进程——貌似运行时间长了调用美电贝尔dll没有响应，原因不明，暂时这样解决
    logServer.info('启动定时重启广播子进程...');
    timerRestartBroadProcess();

    server = http.createServer(app);
    wsServer = new WebSocket.Server({ server });

    server.listen(constants.WS_SERVER.PORT, function listening() {
        logServer.info('WebSocket服务器启动成功，监听端口:' + constants.WS_SERVER.PORT);
    });

    wsServer.on('connection', function connection(ws, req) {
        if (wsClientMgr.isConnected(ws)) {
            logServer.warn('WebSocket连接已存在！');
            return;
        }

        wsClientMgr.onClientConnect(ws);
        let ip = req.connection.remoteAddress;
        logServer.info('客户端[IP:%s]WebSocket连接成功，加入到集合中，当前连接数[%s]', ip, wsClientMgr.wsSize());

        // 监听消息事件
        ws.on('message', function incoming(data) {
            if (!avroUtil.isInit) {
                logServer.info('avro缓存未初始化，无法处理该消息：', data);
                return;
            }
            // 消息处理
            wsMsgHandle.onMessage(ws, data);
        });

        // 监听退出事件
        ws.on('close', function (code, message) {
            logServer.info('WebSocket客户端退出，code:%s，message:%s！', code, message);
            wsClientMgr.onClientClose(ws);
        });
    });
}

/**
 * 定期删除上传的音乐文件
 */
function timerDeleteUploadFile() {
    let uploadDirPath = fileUtil.getRootPath();
    let index = uploadDirPath.lastIndexOf('\\');
    if (index != -1) {
        uploadDirPath = uploadDirPath.substr(0, index) + '\\upload';
    }
    // 初始化立即执行一次
    fileUtil.emptyFolder(uploadDirPath);
    let rule = new schedule.jobRule();
    rule.second = [59];
    rule.minute = [59];
    rule.hour = [23];
    schedule.jobMgr.newJob(rule, function () {
        logServer.info('执行定时任务，清空upload文件夹.');
        fileUtil.emptyFolder(uploadDirPath);
    });
}

/**
 * 定期删除截图
 */
function timerDeleteImagesFile() {
    let imagesDirPath = fileUtil.getRootPath();
    let year = new Date().getYear() + 1900;
    let month = new Date().getMonth() + 1;
    imagesDirPath = imagesDirPath + commonModule.constants.PICTURE_PATH + year + '/' + month;
    // 初始化立即执行一次
    // fileUtil.deleteFile(imagesDirPath,600000);
    let rule = new schedule.jobRule;
    rule.second = [59];
    rule.minute = [59];
    rule.hour = [23];
    schedule.jobMgr.newJob(rule, function () {
        logServer.info('执行定时任务，删除时间较久的截图.');
        fileUtil.deleteFile(imagesDirPath);
    });
}

/**
 * Avro协议数据缓存
 * @return {Promise.<void>}
 */
async function avroCacheInit() {
    await httpReq.reqProtocol();
    // avro协议缓存初始化
    avroUtil.fastInit(globalData.getProtoDataCache(), globalData.getRelaCache());
}

/**
 * 加载配置
 */
function loadConfig() {
    try {
        let configData = globalData.getConfigData();
        let startOptions = configData.startOptions;
        if (startOptions.mainServer === true) {
            globalData.setMainSubFlag(true);
        } else {
            globalData.setMainSubFlag(false);
        }
        logServer.info('加载配置完成.');
    }
    catch (exception) {
        logServer.error('加载配置异常: ' + exception.message);
        return;
    }
}

/**
 * 定时重启广播子进程(每天01:59:59执行一次)
 */
function timerRestartBroadProcess() {
    let rule = new schedule.jobRule();
    rule.second = [59];
    rule.minute = [59];
    rule.hour = [1];
    schedule.jobMgr.newJob(rule, function () {
        logServer.info('执行定时任务，重启广播服务子进程.');
        serverMgr.stopServer(constants.SERVER_TYPE.BROADCAST);
    });
}

// init();
exports.start = init;