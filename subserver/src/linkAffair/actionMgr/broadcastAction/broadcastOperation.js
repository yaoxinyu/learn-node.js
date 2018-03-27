/**
 * @file Describe the file 广播动作-播放音乐
 * @author yaoxinyu
 * @date 2018/3/13
 */

var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var serverType = require('../../../common/constant').SERVER_TYPE;
var commonAction = require('./commonBroadcastAction');

function BroadcastOperation() {
    /**
     * 广播动作-播放音乐
     * @param actionConditionParam 动作条件 JSON格式
     * @param message 动作信息 JSON格式
     */
    this.playMusic = async function (actionConditionParam, message) {
        try {
            let arrActionParam = await commonAction.commonExecute(actionConditionParam, message);
            logger.info('事务联动-广播动作-音乐播放，执行动作的参数：', JSON.stringify(arrActionParam));
            if (arrActionParam && arrActionParam.length > 0) {
                arrActionParam.forEach((actionParam) => sendBroadcastPlayMusicI(actionParam));
            }
        } catch (exception) {
            logger.error('事务联动-广播动作-音乐播放执行异常：', exception.message);
        }
    };

    /**
     * 发送广播音乐播放I类协议
     * @param actionParam 动作参数
     */
    var sendBroadcastPlayMusicI = function (actionParam) {
        try {
            let serverMgr = require('../../../serverMgr');
            if (actionParam) {
                let startBroadcastProtoI = {};
                startBroadcastProtoI.header = {}
                startBroadcastProtoI.header.assetNo = actionParam.assetNo;
                startBroadcastProtoI.header.equipType = null;
                startBroadcastProtoI.header.requestTime = new Date().getTime();
                startBroadcastProtoI.header.dataSource = '0';
                startBroadcastProtoI.header.optCmd = 'broadcast_param_9003';
                startBroadcastProtoI.optType = '01';
                startBroadcastProtoI.volume = actionParam.volume;
                startBroadcastProtoI.fileId = [...actionParam.fileId];
                logger.info('广播动作-发送音乐播放的I类协议[%s]', JSON.stringify(startBroadcastProtoI));

                let broadcastTask = {};
                broadcastTask.name = commonModule.constants.PROCESS_MESSAGE_DEFINE.BROADCAST_MSG.TASK_REQ;
                broadcastTask.data = startBroadcastProtoI;
                serverMgr.sendMsg(serverType.BROADCAST, JSON.stringify(broadcastTask));
            }
        } catch (err) {
            logger.error('事务联动-广播动作，发送音乐播放I类协议异常：', err.message);
        }
    };
}

var broadcast = new BroadcastOperation();
module.exports = broadcast;