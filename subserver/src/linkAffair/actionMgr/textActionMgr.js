/**
 * @file 文字动作处理模块
 * @author yaoxinyu
 * @date 2018/1/29
 */
var messageHandler = require('./messageHandler');
var wordBroadcastAction = require('./textAction/wordBroadcastAction');
var wordEmailAction = require('./textAction/wordEmaiAction');
var wordPageAction = require('./textAction/wordPageAction');
var wordSMSAction = require('./textAction/wordSMSAction');
var wordBigScreenAction = require('./textAction/wordBigSCreenAction');
var commonModule = require('../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function TextActionMgr() {
    /**
     * 执行文字动作
     * @param actionConditionParamModel 动作条件模型 JSON类型
     * @param message 原始的告警相关的数据 JSON格式
     * @return {Promise.<void>}
     */
    this.excuteAction = async function (actionConditionParamModel, message) {
        // 根据具体动作类型调用对应的处理接口
        try {
            // let actionMode = actionConditionParamModel.actionMode;
            // let actionCode = actionConditionParamModel.actionCode;
            let actionId = actionConditionParamModel.abId;//动作ID
            let actionParam = actionConditionParamModel.actionParam;//这个是字符串
            let paramJSON = JSON.parse(actionParam);
            let types = paramJSON.type;
            if (!types) {
                logger.error('事务联动-文字动作，没有发现type属性值！');
                return;
            }
            let content = paramJSON.content;//字符串
            //文字替换
            let replaceContent = await messageHandler.replaceMsgContent(content, message.assetNo, message.eventCode, actionId);
            logger.info('事务联动-文字动作，转换后的content:', replaceContent);
            for (let type of types) {
                if (type.code === '1') {//平台提醒
                    logger.info('事务联动-小类-执行平台提醒动作');
                    actionConditionParamModel.actionCodeName = '平台提醒';
                    wordPageAction.executeAction(replaceContent, message);
                }
                else if (type.code === '2') {//邮件提醒
                    logger.info('事务联动-小类-执行邮件提醒动作');
                    actionConditionParamModel.actionCodeName = '邮件提醒';
                    wordEmailAction.executeAction(replaceContent, type.param);
                }
                else if (type.code === '3') {//短信提醒
                    logger.info('事务联动-小类-执行短信提醒动作');
                    actionConditionParamModel.actionCodeName = '短信提醒';
                    wordSMSAction.executeAction(replaceContent, type, actionConditionParamModel, message);
                }
                else if (type.code === '4') {//广播提醒
                    logger.info('事务联动-小类-执行广播提醒动作');
                    actionConditionParamModel.actionCodeName = '广播提醒';
                    wordBroadcastAction.executeAction(replaceContent, type, actionConditionParamModel, message);
                }
                else if (type.code === '5') {//大屏提醒
                    logger.info('事务联动-小类-执行大屏提醒动作');
                    actionConditionParamModel.actionCodeName = '大屏提醒';
                    wordBigScreenAction.executeAction(replaceContent, type, actionConditionParamModel, message);
                }
                else {
                    logger.warn('事务联动-未识别的文字动作类型：', type.code);
                }
            }
        } catch (err) {
            logger.error('事务联动-执行文字动作异常：', err.message);
        }
    };
}

var textActionMgr = new TextActionMgr();
module.exports = textActionMgr;