/**
 * Created by panxiang on 2018/2/1.
 */

var linkAffairDB = require('../DB/linkAffairDao');
var videoExecutor = require('./videoActionMgr');
var broadcastExecutor = require('./broadcastActionMgr');
var textExecutor = require('./textActionMgr');
var actionDataPusher = require('./dataPush/actionDataPusher');
var commonModule = require('../../commonModuleExport');
var insertLinkageAffairLog = require('./insertLinkageAffairLog');
const logger = commonModule.logger.getLogger(0);

/**
 * ExecuteActionHandler:执行动作处理器，开始执行动作的入口，将填充的信息发送给业务系统
 * by 潘翔 on 2018/2/1
 */
function ExecuteActionHandler() {
    /**
     * handleMessage:处理传来的信息,对外提供的接口
     * @param
     *      message:动作相关的信息包含告警的信息,动作信息中包含资产编号,包含事件EventCode
     * by 潘翔 on 2018/2/1
     */
    this.handleMessage = async function (message) {
        try {
            let actionID = message.actionId;
            logger.info('事务联动-开始执行动作, 事务联动相关的message信息：', message);
            let arrActionConditionParamModel = await linkAffairDB.getActionConditionParamsByActionId(actionID);//得到就是json数组
            //一个动作ID可能会有很多条件
            logger.info('事务联动-根据动作ID查询d_action_mode_param表的结果是:', arrActionConditionParamModel);
            if (arrActionConditionParamModel) {
                logger.info('事务联动-开始遍历arrActionConditionParamModel');
                for (let actionConditionParamModel of arrActionConditionParamModel) {
                    let actionParam = actionConditionParamModel.actionParam;//这个是对象
                    if (actionParam.useFlag === 0) {
                        continue;
                    }
                    let actionExecuter = getActionExecuter(actionConditionParamModel.actionMode);
                    if (actionExecuter) {
                        await actionExecuter.excuteAction(actionConditionParamModel, message);
                        // 插入动作日志
                        await insertLinkageAffairLog.logAfterAction(actionConditionParamModel, message);
                    }
                }
                logger.info('事务联动-结束遍历arrActionConditionParamModel');
            }
        } catch (err) {
            logger.error('事务联动-执行动作异常：', err.message);
        }
    }

    /**
     * 返回对应动作大类的执行器
     * @param actionMode 动作大类
     * @return {*}
     */
    var getActionExecuter = function (actionMode) {
        let actionExecuter = null;
        switch (actionMode) {
            case '1':
            // 视频动作执行器
                logger.info('事务联动-大类-执行视频动作');
                actionExecuter = videoExecutor;
                break;
            case '2':
            // 广播动作执行器
                logger.info('事务联动-大类-执行广播动作');
                actionExecuter = broadcastExecutor;
                break;
            case '3':
            // 文字动作执行器
                logger.info('事务联动-大类-执行文字动作');
                actionExecuter = textExecutor;
                break;
            case '4':
                logger.info('事务联动-大类-执行GIS闪动作');
                // GIS闪动执行器
                break;
            default:
                logger.error('找不到对应动作大类[%s]的执行器！', actionMode);
                break;
        }

        return actionExecuter;
    };
}

var executeActionHandler = new ExecuteActionHandler();
module.exports = executeActionHandler;