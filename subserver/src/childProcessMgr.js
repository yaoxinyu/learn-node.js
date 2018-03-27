/**
 * 子进程管理模块，功能描述：
 * 1、开启/关闭子进程；
 * 2、管理子进程的句柄；
 * 3、向子进程发送消息
 * @author yaoxinyu
 * @date 2017/11/30
 */

var child_process = require('child_process');
var commonModule = require('../src/commonModuleExport');
const logger = commonModule.logger.getLogger();
const constants = commonModule.constants;
var fileUtil = commonModule.fileUtil;


/**
 * 根据serverType获取对应服务的名称
 * @param serverType
 */
function getServerNameByType(serverType) {
    switch (serverType) {
        case constants.SERVER_TYPE.BROADCAST:
            return '广播服务';
        case constants.SERVER_TYPE.ASSETSYNC:
            return '资产同步服务';
        case constants.SERVER_TYPE.VIDEO:
            return '视频服务';
        case constants.SERVER_TYPE.BIG_SCREEN:
            return '大屏服务';
        case constants.SERVER_TYPE.LINK_AFFAIR:
            return '事务联动服务';
        default:
            return '未知服务';
    }
}

function ChildProcessMgr() {
    /**
     * 进程句柄存储 key值为服务类型 value为子进程句柄
     */
    var processMap = new Map();

    /**
     * 开启子进程
     * @param serverType
     */
    this.startProcess = function (serverType) {
        let serverName = getServerNameByType(serverType);
        if (processMap.has(serverType)) {
            logger.info('[%s]子进程已开启', serverName);
            return;
        }

        let workerProcess = null;  // 子进程句柄对象
        switch (serverType) {
            case constants.SERVER_TYPE.BROADCAST:
                workerProcess = child_process.fork(fileUtil.getRootPath() + 'src/broadcast/broadcastServer.js');
                // 监听进程退出事件
                workerProcess.on('exit', function () {
                    logger.info('广播服务子进程退出[pid:%s]', workerProcess.pid);
                    processMap.delete(constants.SERVER_TYPE.BROADCAST);
                    let serverMgr = require('../src/serverMgr');
                    serverMgr.reStartServer(constants.SERVER_TYPE.BROADCAST);
                });
                break;
            case constants.SERVER_TYPE.ASSETSYNC:
            // workerProcess = child_process.fork(fileUtil.getRootPath() + 'src/assetSync/asset-sync.js');
            // // 监听进程退出事件
            // workerProcess.on('exit', function () {
            //     logger.info("资产同步服务子进程退出[pid:%s]", workerProcess.pid);
            //     processMap.delete(constants.SERVER_TYPE.ASSETSYNC);
            //     let serverMgr = require('../src/serverMgr');
            //     serverMgr.reStartServer(constants.SERVER_TYPE.ASSETSYNC);
            // });
                break;
            case constants.SERVER_TYPE.VIDEO:
                workerProcess = child_process.fork(fileUtil.getRootPath() + 'src/gcsoftVideo/videoServer.js');
                // 监听进程退出事件
                workerProcess.on('exit', function () {
                    logger.info('视频服务子进程退出[pid:%s]', workerProcess.pid);
                    processMap.delete(constants.SERVER_TYPE.VIDEO);
                    let serverMgr = require('../src/serverMgr');
                    serverMgr.reStartServer(constants.SERVER_TYPE.VIDEO);
                });
                break;
            case constants.SERVER_TYPE.BIG_SCREEN:
                workerProcess = child_process.fork(fileUtil.getRootPath() + 'src/bigScreen/bigScreenServer.js');
                // 监听进程退出事件
                workerProcess.on('exit', function () {
                    logger.info('大屏服务子进程退出[pid:%s]', workerProcess.pid);
                    processMap.delete(constants.SERVER_TYPE.BIG_SCREEN);
                    let serverMgr = require('../src/serverMgr');
                    serverMgr.reStartServer(constants.SERVER_TYPE.BIG_SCREEN);
                });
                break;
            case constants.SERVER_TYPE.LINK_AFFAIR:
                break;
            default:
                logger.error('错误的服务类型[%s]，无法启动服务！', serverType);
                break;
        }
        if (workerProcess != null) {
            // 保存子进程句柄
            logger.info('开启一个子进程[pid=%s]，[%s]启动...', workerProcess.pid, serverName);
            processMap.set(serverType, workerProcess);
        }
    };

    /**
     * 结束子进程
     * @param serverType
     */
    this.stopProcess = function (serverType) {
        let process = processMap.get(serverType);
        if (process) {
            let serverName = getServerNameByType(serverType);
            logger.info('主动关闭子进程，[%s]停止...', serverName);
            process.kill();
            processMap.delete(serverType);
        }
    };

    /**
     * 进程是否已存在
     * @param serverType
     * @return {boolean}
     */
    this.isProcessExist = function (serverType) {
        let process = processMap.get(serverType);
        if (process) {
            return true;
        }
        return false;
    };

    /**
     * 向子进程发送消息
     * @param serverType
     * @param msg JSON字符串
     */
    this.sendMessage = function (serverType, msg) {
        let process = processMap.get(serverType);
        if (process) {
            process.send(msg);
        }
    };
}

// 实例
var childProcessMgr = new ChildProcessMgr();
module.exports = childProcessMgr;