/**
 * Created by panxiang on 2018/2/1.
 */
var linkAffairDB = require('../DB/linkAffairDao');
var commonModule = require('../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function MessageHandler() {
    /**
     * replaceMsgContent:替换d_action_mode_param表中的action_param字段中的content字段
     * @param
     *      content:要替换的内容,string类型
     *      assetNO:资产编号
     *      strArrEventCode:事件编码的数组（可能有多个）
     *      abID:动作ID
     * @return
     *      返回拼接后的字符串
     * by 潘翔 on 2018/2/1
     */
    this.replaceMsgContent = async function (content, assetNO, strArrEventCode, abID) {
        //需要查表 AssetInfoModel asset = LinkageAffairsService.getInstance().findAssetByAssetNo(assetNo, eventCode, abId);
        try {
            let arrEventCode = strArrEventCode.split(',');
            let regex = /\{[a-zA-z0-9_$]{1,}\}/g;
            let firstType;
            let secondType;
            let assetName;
            let arrEventName = [];
            for (let eventCode of arrEventCode) {
                logger.info('根据动作ID[%s]，资产编号[%s]，事件编码[%s]查询资产信息...', abID, assetNO, eventCode);
                let assetInfoModel = await linkAffairDB.getAssetByAssetNo(eventCode, abID, assetNO);
                logger.info('查询到的资产信息：', assetInfoModel);
                if (!assetInfoModel) {
                    return content;
                }
                firstType = assetInfoModel[0].firstType;
                secondType = assetInfoModel[0].secondType;
                assetName = assetInfoModel[0].assetName;
                arrEventName.push(assetInfoModel[0].eventName);
            }
            let matchArr = content.match(regex);
            for (let value of matchArr) {
                if (value === '{assetNo}') {
                    content = content.replace('{assetNo}', assetNO);
                }
                if (value === '{assetName}') {
                    content = content.replace('{assetName}', assetName)
                }
                if (value === '{bigType}') {
                    content = content.replace('{bigType}', firstType);
                }
                if (value === '{smallType}') {
                    content = content.replace('{smallType}', secondType);
                }
                if (value === '{eventName}') {
                    content = content.replace('{eventName}', arrEventName.join(','));
                }
            }
            logger.info('返回拼接后的文字内容：', content);
            return content;
        } catch (err) {
            logger.error('拼接动作文字信息异常：', err.message);
        }
    }
}
var messageHandler = new MessageHandler();
module.exports = messageHandler;