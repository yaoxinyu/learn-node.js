/**
 * @file 收到MQ的II类告警数据，推送给所有客户端
 * @author yaoxinyu
 * @date 2017/12/6
 */

var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger();
var wsClientMgr = require('../wsClientMgr');
var LinkAffairServer = require('../linkAffair/linkAffairServer');
function AlarmTopicListener() {
    /**
     * MQ消息回调并处理
     * @param msg JSON格式
     */
    this.onMessage = function (msg) {
        try {
            LinkAffairServer.processLinkData(msg);
            let header = msg.header;
            let optCmd = header.optCmd;
            if (optCmd === 'ad_data_9001') {
                //调用WebSocket发送到所有客户端
                logger.info('WebSocket推送II类告警数据给所有客户端：', msg);
                wsClientMgr.pushBusiDataForII(msg);
            } else {
                logger.error('收到MQ消息[topic=mq.alarm]，无法处理该optCmd：', optCmd);
            }
        } catch (exception) {
            logger.error('处理MQ消息[topic=mq.alarm]异常：', exception.message);
        }
    };
}


var alarmListener = new AlarmTopicListener();
module.exports = alarmListener;

