/**
 * Created by panxiang on 2018/2/2.
 */
/**
 * 执行视频播放的动作
 * by 潘翔 on 2018/2/2
 */
var serverMgr = require('../../../serverMgr');
var commonVideoAction = require('./commonVideoAction');
var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);//subServer

function PlayVideoAction() {
    /**
     * executeAction 执行播放视频的动作
     * @param
     *    actionModeParamModel:动作参数模型，JSON类型
     *    message:触发动作相关信息, JSON对象类型
     * by 潘翔 on 2018/2/2
     */
    this.executeAction = async function (actionModeParamModel, message) {
        logger.info('事务联动-视频动作-播放视频，开始执行视频播放');
        try {
            await commonVideoAction.commonExecute(actionModeParamModel, message);
        } catch (err) {
            logger.error('事务联动-视频动作-播放视频执行异常：', err.message);
        }
    };
}

var playVideoAction = new PlayVideoAction();
module.exports = playVideoAction;