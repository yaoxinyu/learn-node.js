/**
 * @file 事务联动逻辑处理模块
 *
 * @author wangWeiZHen
 * @date 2018/1/31
 */
var linkAffProcess = require('./linkAffProcess');
var logger = require('../../common/util/logger').getLogger(3);

var LogicOperation = function () {
    /**
     * 事务联动逻辑处理入口
     * @param msg
     */
    this.handleMessage  = function (msg) {
        logger.debug('事务联动-处理事务联动MQ监听到的数据：', msg);
        let optCmd = null;
        let data = null;
        let header = null;
        try{
            data = msg.data;
            header = data.header;
            optCmd = header.optCmd;
        }catch (err){
            logger.error('事务联动-数据解析错误.error:', err.message);
            return;
        }
        switch (optCmd){
            case 'ad_data_9001':
                logger.info('事务联动-根据optCmd: 对告警数据进行条件解析');
                linkAffProcess.ConditionExpression.analysisAndAction(msg, '2');
                break;
            case 'ad_data_9500':
                logger.info('事务联动-根据optCmd: 对设备状态数据进行条件解析');
                linkAffProcess.ConditionExpression.analysisAndAction(msg, '3');
                break;
            default:
                logger.info('事务联动-根据optCmd: 对业务数据进行条件解析');
                linkAffProcess.ConditionExpression.analysisAndAction(msg, '1');
                break;
        }
        return;
    }
};
module.exports = new LogicOperation();