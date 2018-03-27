/**
 * @file 广播动作处理模块
 * @author yaoxinyu
 * @date 2018/1/29
 */

var commonModule = require('../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var playMusic = require('./broadcastAction/broadcastOperation');
var call = require('./broadcastAction/callOperation');

function BroadcastActionMgr() {
    /**
     * 执行广播动作
     * @param actionConditionParam 动作条件 JSON格式
     * @param message 动作信息 JSON格式
     */
    this.excuteAction = function (actionConditionParam, message) {
        // 根据具体动作类型调用对应的处理接口
        try {
            let actionCode = actionConditionParam.actionCode;
            switch (actionCode) {
                case '1': // 播放音乐
                    logger.info('事务联动-小类-执行播放动作');
                    actionConditionParam.actionCodeName = '音乐播放';
                    playMusic.playMusic(actionConditionParam, message);
                    break;
                case '2': // 喊话
                    logger.info('事务联动-小类-执行喊话动作');
                    actionConditionParam.actionCodeName = '广播喊话';
                    call.call(actionConditionParam, message);
                    break;
                default:
                    logger.error('事务联动-错误的广播动作小类[%s]', actionCode);
                    break;
            }
        } catch (err) {
            logger.error('事务联动-执行广播动作异常：', err.message);
        }
    };
}


var broadcastActionMgr = new BroadcastActionMgr();
module.exports = broadcastActionMgr;
