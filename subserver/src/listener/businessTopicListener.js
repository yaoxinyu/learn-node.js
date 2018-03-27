/**
 * @file 收到MQ的II类业务回复数据，推送给客户端
 * @author yaoxinyu
 * @date 2017/12/20
 */


var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger();
var wsClientMgr = require('../wsClientMgr');
var LinkAffairServer = require('../linkAffair/linkAffairServer');
function BusinessTopicListener() {
    /**
     * MQ消息回调并处理
     * @param msg JSON格式
     */
    this.onMessage = function (msg) {
        LinkAffairServer.processLinkData(msg);
        //调用WebSocket发送对应客户端
        logger.info('WebSocket发送II类业务回复数据给客户端：', JSON.stringify(msg));
        wsClientMgr.sendBusiDataForII(msg);
    };
}


var businessListener = new BusinessTopicListener();
module.exports = businessListener;