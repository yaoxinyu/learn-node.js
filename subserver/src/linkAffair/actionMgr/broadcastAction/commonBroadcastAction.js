/**
 * @file Describe the file 广播动作共通
 * @author yaoxinyu
 * @date 2018/3/13
 */

var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var linkAffairDB = require('../../DB/linkAffairDao');
var dataPusher = require('../dataPush/actionDataPusher');

function CommonBroadcastAction() {
    /**
     * 广播动作共通的执行函数
     * @param actionModeParamModel 动作参数 JSON格式
     * @param message 动作信息 JSON格式
     */
    this.commonExecute = async function (actionModeParamModel, message) {
        let arrActionParam = [];
        try {
            let isExecByDevParam = await this.executeByDeviceParamConfig(actionModeParamModel, message, arrActionParam);
            logger.info('事务联动-广播动作，查找d_action_device_param表的结果是:', isExecByDevParam);
            if (!isExecByDevParam) {
                arrActionParam.length = 0;
                await this.executeByNearDevice(actionModeParamModel, message, arrActionParam);
            }
        } catch (err) {
            logger.error('事务联动-广播动作-共通执行异常：', err.message);
        }

        return arrActionParam;
    };

    /**
     * 根据d_action_device_param表的联动配置执行联动
     * @param actionModeParamModel 动作参数 JSON格式
     * @param message 动作信息 JSON格式
     * @param arrActionParam 执行动作的参数集合，返回给外部具体执行
     * @return {Promise.<boolean>}
     */
    this.executeByDeviceParamConfig = async function (actionModeParamModel, message, arrActionParam) {
        let assetNo = message.assetNo;
        let actionMode = actionModeParamModel.actionMode;
        let actionCode = actionModeParamModel.actionCode;
        let ampId = actionModeParamModel.ampId;
        // let actionId = actionModeParamModel.abId;
        logger.info('事务联动-广播动作，开始查询联动设备，动作参数：', actionModeParamModel);
        try {
            let arrMonitorDeviceParamModel = await linkAffairDB.getDeviceByActionModeParamId(ampId, assetNo);
            logger.info('事务联动-广播动作，查询d_action_device_param表结果是：', arrMonitorDeviceParamModel);
            if (arrMonitorDeviceParamModel && arrMonitorDeviceParamModel.length > 0) {
                logger.info('事务联动-广播动作，联动设备的个数[%s]', arrMonitorDeviceParamModel.length);
                // 推送到业务系统的信息
                let responseMessage = {};
                responseMessage.targetAssetNo = assetNo;
                responseMessage.eventCode = message.eventCode;
                responseMessage.actionMoreMessages = [];
                for (let model of arrMonitorDeviceParamModel) {
                    let actionParam = model.actionParam; // JSON字符串类型
                    let jsonActionParam = JSON.parse(actionParam);
                    let responseMsg = {};
                    logger.info('事务联动-广播动作，联动设备的动作参数是：', jsonActionParam);
                    if (jsonActionParam.useFlag === '1') {
                        // 动作启用标志为1
                        if (!jsonActionParam.modeCode || (jsonActionParam.modeCode === actionCode)) {
                            // actionCode匹配
                            if (actionCode === '2') {
                                // 广播喊话动作需要推送到业务系统
                                responseMsg.actionMode = actionMode;
                                responseMsg.actionCode = actionCode;
                                responseMsg.assetNo = model.monitorDeviceNo;
                                if (jsonActionParam.sound) {
                                    responseMsg.sound = Number(jsonActionParam.sound);
                                }
                                logger.info('事务联动-广播动作，喊话动作信息：', responseMessage);
                                responseMessage.actionMoreMessages.push(responseMsg);
                            } else if (actionCode === '1') {
                                // 将动作参数返回给外部执行动作
                                let actionTemp = {};
                                actionTemp.assetNo = model.monitorDeviceNo;
                                actionTemp.volume = Number(jsonActionParam.sound);
                                actionTemp.fileId = [];
                                let fileList = jsonActionParam.playFile.split[','];
                                for (let id of fileList) {
                                    let fileId = Number(id);
                                    actionTemp.fileId.push(fileId);
                                }
                                logger.info('事务联动-广播动作，音乐播放动作信息：', actionTemp);
                                arrActionParam.push(actionTemp);
                            }
                        }
                    }
                }
                if (responseMessage.actionMoreMessages.length > 0) {
                    dataPusher.pushLinkAffairResponse(responseMessage);
                }
                return true;
            }
        } catch (err) {
            logger.error('事务联动-广播动作执行异常：', err.message);
        }
        return false;
    };

    /**
     * 找到附近1公里以内的设备进行联动
     * @param actionModeParamModel 动作参数 JSON格式
     * @param message 动作信息 JSON格式
     * @param arrActionParam 执行动作的参数集合，返回给外部具体执行
     * @return {Promise.<void>}
     */
    this.executeByNearDevice = async function (actionModeParamModel, message, arrActionParam) {
        logger.info('事务联动-广播动作，开始查找附近的联动设备，动作参数：', actionModeParamModel);
        let assetNo = message.assetNo;
        let actionMode = actionModeParamModel.actionMode;
        let actionCode = actionModeParamModel.actionCode;
        let actionParam = actionModeParamModel.actionParam;
        try {
            let jsonActionParam = JSON.parse(actionParam);
            let useFlag = jsonActionParam.useFlag;
            logger.info('事务联动-广播动作-executeByNearDevice，动作启用标志是[%s]', useFlag);
            if (useFlag === 1) {
                let arrMonitorDeviceParamModel = await linkAffairDB.getCameraDeviceByAssetNo(assetNo);
                logger.info('事务联动-广播动作-executeByNearDevice，查询附近1公里的联动设备结果：', arrMonitorDeviceParamModel);
                if (!arrMonitorDeviceParamModel || arrMonitorDeviceParamModel.length == 0) {
                    return;
                }
                // 推送到业务系统
                let responseMessage = {};
                responseMessage.targetAssetNo = assetNo;
                responseMessage.eventCode = message.eventCode;
                responseMessage.actionMoreMessages = [];
                for (let model of arrMonitorDeviceParamModel) {
                    if (actionCode === '2') {
                        // 广播喊话动作需要推送到业务系统
                        let responseMsg = {};
                        responseMsg.actionMode = actionMode;
                        responseMsg.actionCode = actionCode;
                        responseMsg.assetNo = model.monitorDeviceNo;
                        if (jsonActionParam.sound) {
                            responseMsg.sound = Number(jsonActionParam.sound);
                        }
                        logger.info('事务联动-广播动作-executeByNearDevice，喊话动作信息：', responseMessage);
                        responseMessage.actionMoreMessages.push(responseMsg);
                    } else if (actionCode === '1') {
                        // 将动作参数返回给外部执行动作
                        let actionTemp = {};
                        actionTemp.assetNo = model.monitorDeviceNo;
                        actionTemp.volume = Number(jsonActionParam.sound);
                        actionTemp.fileId = [];
                        let fileId = Number(jsonActionParam.playFile);
                        actionTemp.fileId.push(fileId);
                        logger.info('事务联动-广播动作-executeByNearDevice，音乐播放动作信息：', actionTemp);
                        arrActionParam.push(actionTemp);
                    }
                }
                if (responseMessage.actionMoreMessages.length > 0) {
                    dataPusher.pushLinkAffairResponse(responseMessage);
                }
            }
        }
        catch (err) {
            logger.error('事务联动-广播动作-executeByNearDevice执行异常：', err.message);
        }
    };
}

var commonBroad = new CommonBroadcastAction();
module.exports = commonBroad;