/**
 * @file 事务联动服务模块
 * @author yaoxinyu
 * @date 2018/1/30
 */

var mailUtil = require('../common/util/mailUtil');
var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);
// 大屏推送模块
var screenPusher = require('../bigScreen/dataPush/dataPusher');
var DataOperation = require('./handler/DataOperation');

function LinkAffairServer() {
    // 启动标志
    var isStarted = false;

    /**
     * 模块启动
     */
    this.start = function () {
        if (!isStarted) {
            // 相关模块初始化
            logger.info('邮件模块初始化');
            if (mailUtil.init()) {
                logger.info('邮件模块初始化成功');
            } else {
                logger.error('邮件模块初始化失败');
            }
            logger.info('大屏推送模块初始化.');
            screenPusher.init();

            isStarted = true;
            logger.info('事务联动服务模块初始化结束.');
        }
    };

    /**
     * 事务联动消息处理
     * @param linkData JSON格式 事务联动数据
     */
    this.processLinkData = function (linkData) {
        if (!isStarted) {
            logger.error('无法处理该事务联动数据-服务模块未启动！');
            return;
        }

        if (!linkData) {
            logger.error('事务联动-请求数据为空！');
            return;
        }

        // 交给事务联动数据解析模块处理 异步
        DataOperation.actionJudgment(linkData);
    };
}


var server = new LinkAffairServer();

module.exports = server;






