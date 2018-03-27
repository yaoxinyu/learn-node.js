/**
 * @file Describe the file 广播动作-喊话
 * @author yaoxinyu
 * @date 2018/3/13
 */

var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var commonAction = require('./commonBroadcastAction');

function CallOperation() {
    /**
     * 广播动作-喊话
     * @param actionConditionParam 动作条件 JSON格式
     * @param message 动作信息 JSON格式
     */
    this.call = async function (actionConditionParam, message) {
        logger.info('事务联动-广播动作-喊话，开始执行广播喊话');
        try {
            await commonAction.commonExecute(actionConditionParam, message);
        } catch (err) {
            logger.error('事务联动-广播动作-喊话执行异常：', err.message);
        }
    };
}

var call = new CallOperation();
module.exports = call;