/**
 * Created by panxiang on 2018/2/2.
 * 执行平台提醒的文字动作
 */
var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var dataPusher = require('../dataPush/actionDataPusher');

function WordPageAction() {
    /**
     * 执行平台提醒的文字动作
     * @param content 文字内容
     * @param message 动作数据 JSON格式
     */
    this.executeAction = function (content, message) {
        logger.info('事务联动-文字动作，开始处理文字提示组装发送到平台');
        let actionInfo = {
            actionMode: 3,              // 动作大类
            actionCode: 1,              // 动作小类
            assetNo: message.assetNo,   // 资产编号
            content: content            // 动作内容
        };
        let responseMessage = {};
        responseMessage.targetAssetNo = message.assetNo;
        responseMessage.eventCode = message.eventCode;
        responseMessage.actionMoreMessages = [];
        responseMessage.actionMoreMessages.push(actionInfo);
        // 推送到业务系统
        dataPusher.pushLinkAffairResponse(responseMessage);
    }
}

var wordPageAction = new WordPageAction();
module.exports = wordPageAction;
