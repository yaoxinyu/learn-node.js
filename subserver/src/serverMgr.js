/**
 * 服务管理模块，功能描述：包括对广播服务、资产同步服务、视频服务、大屏服务、事务联动服务的启动和停止
 * @author yaoxinyu
 * @date 2017/11/30
 */

var commonModule = require('../src/commonModuleExport');
const logger = commonModule.logger.getLogger();
var globalData = require('./globalDataCache');
const serverType = commonModule.constants.SERVER_TYPE;
var childProcessMgr = require('./childProcessMgr');
var linkAffair = require('./linkAffair/linkAffairServer');


function ServerMgr() {
    /**
     * 启动所有的服务
     */
    this.startAllServer = function () {
        try {
            let configData = globalData.getConfigData();
            let startFlag = configData.startOptions;
            // 根据配置的启动标记判断是否启动对应服务
            if (startFlag.broadcast) {
                this.startServer(serverType.BROADCAST);
            }
            if (startFlag.video) {
                this.startServer(serverType.VIDEO);
            }
            if (startFlag.asset) {
                this.startServer(serverType.ASSETSYNC);
            }
            if (startFlag.bigScreen) {
                this.startServer(serverType.BIG_SCREEN);
            }
            if (startFlag.linkAffair) {
                this.startServer(serverType.LINK_AFFAIR);
            }
        } catch (exception) {
            logger.error('读取配置信息异常：', exception.message);
            return;
        }
    };

    /**
     * 启动对应的服务
     * @param type 参照constant.js中SERVER_TYPE_DEFINE的定义
     */
    this.startServer = function (type) {
        if (this.isServerRunning(type)) {
            return;
        }

        switch (type) {
            case serverType.BROADCAST:
            // 开启子进程工作
                logger.info('启动广播服务...');
                childProcessMgr.startProcess(serverType.BROADCAST);
                break;
            case serverType.ASSETSYNC:
                logger.info('启动资产同步服务...');
                break;
            case serverType.VIDEO:
            // 开启子进程工作
                logger.info('启动视频服务...');
                childProcessMgr.startProcess(serverType.VIDEO);
                break;
            case serverType.BIG_SCREEN:
                logger.info('启动大屏服务...');
                childProcessMgr.startProcess(serverType.BIG_SCREEN);
                break;
            case serverType.LINK_AFFAIR:
                logger.info('启动事务联动服务...');
                linkAffair.start();
                break;
            default:
                logger.error('错误的服务类型[%s]，无法启动服务！', type);
                break;
        }
    };

    /**
     * 重启对应的服务
     * @param type 参照constant.js中SERVER_TYPE_DEFINE的定义
     */
    this.reStartServer = function (type) {
        if (this.isServerRunning(type)) {
            return;
        }

        switch (type) {
            case serverType.BROADCAST:
            // 重启一个子进程工作
                logger.info('重启广播服务...');
                childProcessMgr.startProcess(serverType.BROADCAST);
                break;
            case serverType.ASSETSYNC:
                logger.info('重启资产同步服务...');
                break;
            case serverType.VIDEO:
            // 重启一个子进程工作
                logger.info('重启视频服务...');
                childProcessMgr.startProcess(serverType.VIDEO);
                break;
            case serverType.BIG_SCREEN:
                logger.info('重启大屏服务...');
                childProcessMgr.startProcess(serverType.BIG_SCREEN);
                break;
            case serverType.LINK_AFFAIR:
                logger.info('重启事务联动服务...');
                linkAffair.start();
                break;
            default:
                logger.error('错误的服务类型[%s]，无法重启服务！', type);
                break;
        }
    };

    /**
     * 停止对应的服务
     * @param type 参照constant.js中SERVER_TYPE_DEFINE的定义
     */
    this.stopServer = function (type) {
        if (this.isServerRunning(type)) {
            switch (type) {
                case serverType.BROADCAST:
                    logger.info('停止广播服务...');
                    break;
                case serverType.ASSETSYNC:
                    logger.info('停止资产同步服务...');
                    break;
                case serverType.VIDEO:
                    logger.info('停止视频服务...');
                    break;
                case serverType.BIG_SCREEN:
                    logger.info('停止大屏服务...');
                    break;
                case serverType.LINK_AFFAIR:
                    logger.info('停止事务联动服务...');
                    break;
                default:
                    logger.error('错误的服务类型[%s]，无法停止服务！', type);
                    break;
            }
            childProcessMgr.stopProcess(type);
        }
    };

    /**
     * 判断服务是否在运行
     * @param type 参照constant.js中SERVER_TYPE_DEFINE的定义
     * @return {boolean}
     */
    this.isServerRunning = function (type) {
        return childProcessMgr.isProcessExist(type);
    };

    /**
     * 向指定服务进程发送消息
     * @param type 参照constant.js中SERVER_TYPE_DEFINE的定义
     * @param msg json string
     */
    this.sendMsg = function (type, msg) {
        childProcessMgr.sendMessage(type, msg);
    };
}


// 实例
var serverMgr = new ServerMgr();
module.exports = serverMgr;