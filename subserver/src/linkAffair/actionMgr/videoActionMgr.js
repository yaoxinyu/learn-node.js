/**
 * @file 视频动作处理模块
 * @author yaoxinyu
 * @date 2018/1/29
 */
var playVideoAction = require('./videoAction/playVideoAction');
var recordAction = require('./videoAction/recordVideoAction');
var screenAction = require('./videoAction/screenshotAction');
var commonModule = require('../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function VideoActionMgr() {
    /**
     * 执行视频动作
     * @param actionConditionParamModel 动作参数的模型 JSON类型
     * @param message 触发动作的设备相关信息 JSON格式
     */
    this.excuteAction = async function (actionConditionParamModel, message) {
        // 根据具体动作类型调用对应的处理接口
        try {
            let actionCode = actionConditionParamModel.actionCode;
            switch (actionCode) {
                case '1'://截图
                    logger.info('事务联动-小类-执行截图动作');
                    actionConditionParamModel.actionCodeName = '视频拍照';
                    await screenAction.executeAction(actionConditionParamModel, message);
                    break;
                case '2'://录像
                    logger.info('事务联动-小类-执行录像动作');
                    actionConditionParamModel.actionCodeName = '视频录像';
                    await recordAction.executeAction(actionConditionParamModel, message);
                    break;
                case '3'://播放
                    logger.info('事务联动-小类-执行播放动作');
                    actionConditionParamModel.actionCodeName = '视频跟踪'; //视频播放
                    await playVideoAction.executeAction(actionConditionParamModel, message);
                    break;
                default:
                    logger.error('事务联动-错误的视频动作小类[%s]', actionCode);
                    break;
            }
        } catch (err) {
            logger.error('事务联动-执行视频动作异常：', err.message);
        }
    };
}


var videoActionMgr = new VideoActionMgr();
module.exports = videoActionMgr;