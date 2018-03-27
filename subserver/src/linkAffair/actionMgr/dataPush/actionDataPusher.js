/**
 * @file 推送动作数据到业务系统
 * @author yaoXinYu
 * @date 2018/2/5
 */

const logger = require('../../../common/util/logger').getLogger(0);
var wsClientMgr = require('../../../wsClientMgr');
var avroUtil = require('../../../common/util/avroUtil');


/**
 * 动作数据推送到业务系统类
 */
class ActionDataPusher {
    constructor() {
        // this.textPusher = new TextActionPusher();
        // this.videoPusher = new VideoActionPusher();
        // this.broadcastPusher = new BroadcastActionPusher();
    }

    /**
     * 推送相关动作数据到业务系统
     * @param actionData JSON格式
     */
    pushActionData(actionData) {
        try {
            logger.info('准备推送动作数据到业务系统：', JSON.stringify(actionData));
            let jsonData = actionData;
            if (!jsonData || !jsonData.header || !jsonData.data) {
                logger.error('动作推送数据格式不正确！');
                return;
            }
            if (jsonData.header.optCmd !== 'ad_data_9700') {
                logger.error('动作推送数据错误的optCmd：', jsonData.header.optCmd);
                return;
            }
            if (jsonData.data === '') {
                logger.warn('动作推送数据为空，不推送到业务系统!');
                return;
            }
            // 对数据做avro校验
            let avroData = avroUtil.getAvroDataByOptCmd(jsonData, 'ad_data_9700');
            if (avroData) {
                wsClientMgr.pushActionDataToWeb(jsonData);
            } else {
                logger.error('动作推送数据avro校验失败！');
            }
        } catch (exception) {
            logger.error('推送动作数据到业务系统出现异常：', exception.message);
        }
    }

    /**
     * 推送事务联动返回到业务系统的II类数据
     * @param response 返回的II类数据 JSON格式
     * @response.targetAssetNo
     * @response.eventCode
     * @response.actionMoreMessages Array
     */
    pushLinkAffairResponse(response) {
        try {
            logger.info('事务联动-返回给业务系统的动作信息内容是：', JSON.stringify(response));
            if (response && response.actionMoreMessages && response.actionMoreMessages.length > 0) {
                let protocolRes = {};
                protocolRes.header = {};
                protocolRes.header.assetNo = response.targetAssetNo;
                protocolRes.header.equipType = '0';
                protocolRes.header.optCmd = 'ad_data_9700';
                protocolRes.header.requestTime = 0;
                protocolRes.header.responseTime = new Date().getTime();
                protocolRes.header.dataSource = '0';
                protocolRes.header.code = 200;
                protocolRes.header.msg = 'OK';
                protocolRes.data = JSON.stringify(response);
                logger.info('事务联动-推送给业务系统的数据：', protocolRes);
                this.pushActionData(protocolRes);
            }
        } catch (exception) {
            logger.error('推送事务联动返回到业务系统的数据出现异常：', exception.message);
        }
    }
}


// 导出实例
var actionPusher = new ActionDataPusher();
module.exports = actionPusher;