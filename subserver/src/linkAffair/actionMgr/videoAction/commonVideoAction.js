/**
 * Created by panxiang on 2018/2/6.
 */
/**
 * CommVideoAction 和视频相关的共同的部分
 * by 潘翔 on 2018/2/2
 */
'use strict';
var linkAffairDB = require('../../DB/linkAffairDao');
var commonModule = require('../../../commonModuleExport');
const serverType = commonModule.constants.SERVER_TYPE;
const logger = commonModule.logger.getLogger(0);//subServer
var dataPusher = require('../dataPush/actionDataPusher');

function CommonVideoAction() {
    /**
     * 视频动作共通的执行函数
     * @param actionModeParamModel 动作参数 JSON格式
     * @param message 动作信息 JSON格式
     */
    this.commonExecute = async function (actionModeParamModel, message) {
        let arrActionParam = [];
        try {
            let isExecByDevParam = await this.executeByDeviceParamConfig(actionModeParamModel, message, arrActionParam);
            logger.info('事务联动-视频动作，查找d_action_device_param表的结果是:', isExecByDevParam);
            if (!isExecByDevParam) {
                arrActionParam.length = 0;
                await this.executeByNearDevice(actionModeParamModel, message, arrActionParam);
            }
        } catch (err) {
            logger.error('事务联动-视频动作-共通执行异常：', err.message);
        }

        return arrActionParam;
    };

    /**
     * executeByConfig : 根据d_action_device_param表的联动配置执行联动
     * @param
     *      actionModeParamModel:动作作参数模型JSON类型
     *      message:触发动作相关信息,JSON格式
     *      OUT arrActionParam:执行动作的集合，在外面执行动作
     * @return
     *      true : 按照d_action_device_param配置表执行动作
     *      false: 找到附近1公里范围内的设备执行动作
     * by 潘翔 on 2018/2/2
     */
    this.executeByDeviceParamConfig = async function (actionModeParamModel, message, arrActionParam) {
        let assetNo = message.assetNo;
        logger.info('事务联动-视频动作，被监控的资产编号是[%s]', assetNo);
        try {
            let actionMode = actionModeParamModel.actionMode;
            let actionCode = actionModeParamModel.actionCode;
            let ampId = actionModeParamModel.ampId;
            logger.info('事务联动-视频动作，动作参数ID[%s], 动作ID[%s]', ampId, actionModeParamModel.abId);
            let arrMonitorDeviceParamModel = await linkAffairDB.getDeviceByActionModeParamId(ampId, assetNo);
            logger.info('事务联动-视频动作，查询d_action_device_param表结果是:', arrMonitorDeviceParamModel);
            if (arrMonitorDeviceParamModel && arrMonitorDeviceParamModel.length > 0) {
                // 推送到业务系统
                let responseMessage = {};
                responseMessage.targetAssetNo = message.assetNo;
                responseMessage.eventCode = message.eventCode;
                responseMessage.actionMoreMessages = [];
                for (let monitorDeviceParamModel of arrMonitorDeviceParamModel) {
                    let strActionParam = monitorDeviceParamModel.actionParam;
                    let jsonActionParam = JSON.parse(strActionParam);
                    let actionTemp = {};
                    let jumpAction = {};
                    let responseMsg = {};
                    logger.info('事务联动-视频动作，联动设备的动作参数是:', jsonActionParam);
                    if (jsonActionParam.useFlag === '1') {
                        logger.info('事务联动-视频动作，每个联动设备动作参数中的动作小类是[%s]', jsonActionParam.modeCode);
                        if (!jsonActionParam.modeCode || (jsonActionParam.modeCode === actionModeParamModel.actionCode)) {
                            responseMsg.actionMode = actionModeParamModel.actionMode;
                            responseMsg.actionCode = actionModeParamModel.actionCode;
                            responseMsg.assetNo = monitorDeviceParamModel.monitorDeviceNo;
                            if (jsonActionParam.presettingBit) {
                                responseMsg.presettingBit = jsonActionParam.presettingBit;
                            }
                            if (jsonActionParam.presettingBit && jsonActionParam.presettingBit !== '') {
                                jumpAction.assetNo = monitorDeviceParamModel.monitorDeviceNo;//这个不是资产编号
                                jumpAction.presettingBit = Number(jsonActionParam.presettingBit);
                            }
                            logger.info('事务联动-视频动作，设备[%s]跳转预置位的参数[%s]', monitorDeviceParamModel.monitorDeviceNo, JSON.stringify(jumpAction));
                            actionTemp = getActionParam(actionCode, monitorDeviceParamModel);
                            logger.info('事务联动-视频动作，设备[%s]获得动作的参数是：', monitorDeviceParamModel.monitorDeviceNo, actionTemp);
                            if (actionTemp) {
                                actionTemp.assetNo = monitorDeviceParamModel.monitorDeviceNo;
                                arrActionParam.push(actionTemp);
                            }
                            if (jumpAction) {
                                jumpToPreset(jumpAction);
                            }
                            if (actionMode === '1' && actionCode === '3') {
                                // 视频播放动作需要推送到业务系统
                                responseMessage.actionMoreMessages.push(responseMsg);
                            }
                        }
                    }
                }
                if (responseMessage.actionMoreMessages.length > 0) {
                    dataPusher.pushLinkAffairResponse(responseMessage);
                }
                return true;
            } else {
                logger.info('事务联动-视频动作，在d_action_device_param表中没有查到联动设备');
            }
        }
        catch (err) {
            logger.error('事务联动-视频动作执行异常：', err.message);
        }
        return false;
    };

    /**
     * executeByNear : 找到附近1公里以内的设备进行动作
     * @param actionModeParamModel 动作参数。
     * @param message
     * @param OUT arrActionParam 待执行动作的集
     * by 潘翔 on 2018/2/2
     */
    this.executeByNearDevice = async function (actionModeParamModel, message, arrActionParam) {
        let assetNo = message.assetNo;
        logger.info('事务联动-视频动作-executeByNearDevice，开始查找附近的联动设备');
        logger.info('事务联动-视频动作-executeByNearDevice，被监控的资产编号是[%s]', assetNo);
        try {
            let actionMode = actionModeParamModel.actionMode;
            let actionCode = actionModeParamModel.actionCode;
            let strActionParam = actionModeParamModel.actionParam;
            logger.info('事务联动-视频动作-executeByNearDevice，动作参数的条件中的动作大类的类型是[%s], 小类是[%s]', actionMode, actionCode);
            logger.info('事务联动-视频动作-executeByNearDevice，动作条件是:', strActionParam);
            let jsonActionParam = JSON.parse(strActionParam);
            let useFlag = jsonActionParam.useFlag;
            logger.info('事务联动-视频动作-executeByNearDevice，动作启用是[%s]', useFlag);
            if (useFlag === 1) {
                logger.info('事务联动-视频动作-executeByNearDevice，在数据库中寻找方圆1公里的设备');
                let arrMonitorDeviceParamModel = await linkAffairDB.getCameraDeviceByAssetNo(assetNo);//查到方圆1公里的联动设备
                logger.info('事务联动-视频动作-executeByNearDevice，在数据库中寻找方圆1公里的设备结果:', arrMonitorDeviceParamModel);
                if (!arrMonitorDeviceParamModel || arrMonitorDeviceParamModel.length == 0) {
                    return;
                }
                // 推送到业务系统
                let responseMessage = {};
                responseMessage.targetAssetNo = message.assetNo;
                responseMessage.eventCode = message.eventCode;
                responseMessage.actionMoreMessages = [];
                for (let monitorDeviceParamModel of arrMonitorDeviceParamModel) {
                    let actionTemp = {};
                    let jumpAction = {};
                    let responseMsg = {};
                    responseMsg.assetNo = monitorDeviceParamModel.monitorDeviceNo;
                    responseMsg.actionMode = actionModeParamModel.actionMode;
                    responseMsg.actionCode = actionModeParamModel.actionCode;
                    if (jsonActionParam.presettingBit) {
                        responseMsg.presettingBit = jsonActionParam.presettingBit;
                    }
                    if (jsonActionParam.presettingBit && jsonActionParam.presettingBit !== '') {
                        jumpAction.assetNo = monitorDeviceParamModel.monitorDeviceNo;
                        jumpAction.presettingBit = Number(jsonActionParam.presettingBit);
                    }
                    logger.info('事务联动-视频动作-executeByNearDevice，设备[%s]跳转预置位动作参数是[%s]', monitorDeviceParamModel.monitorDeviceNo, JSON.stringify(jumpAction));
                    actionTemp = getActionParam(actionModeParamModel.actionCode, actionModeParamModel);
                    logger.info('事务联动-视频动作-executeByNearDevice，设备[%s]获得的动作的参数是：', monitorDeviceParamModel.monitorDeviceNo, actionTemp);
                    if (actionTemp) {
                        actionTemp.assetNo = monitorDeviceParamModel.monitorDeviceNo;
                        arrActionParam.push(actionTemp);
                    }
                    if (jumpAction) {
                        jumpToPreset(jumpAction);
                    }
                    if (actionMode === '1' && actionCode === '3') {
                        // 视频播放动作需要推送到业务系统
                        responseMessage.actionMoreMessages.push(responseMsg);
                    }
                }
                if (responseMessage.actionMoreMessages.length > 0) {
                    dataPusher.pushLinkAffairResponse(responseMessage);
                }
            }
        }
        catch (err) {
            logger.error('事务联动-视频动作-executeByNearDevice执行异常：', err.message);
        }
    };

    /**
     * getActionParam:根据动作小类和联动条件模型得到动作参数
     * @param
     *      actionCode:动作小类
     *      actionParamModel:动作条件模型
     * @return
     *      返回动作参数
     * by 潘翔 on 2018/2/2
     */
    function getActionParam(actionCode, actionParamModel) {
        let temp = null;
        try {
            let strActionParam = actionParamModel.actionParam;
            let jsonActionParam = JSON.parse(strActionParam);
            logger.info('事务联动-视频动作，动作小类是[%s], 动作参数是[%s]', actionCode, strActionParam);
            if (actionCode === '1') {
                //截图
                if (jsonActionParam.count && (jsonActionParam.count !== '0')) {
                    temp = {};
                    temp.maxSnapNum = Number(jsonActionParam.count);//TODO 这个默认是多少
                    temp.interval = jsonActionParam.interval ? (Number(jsonActionParam.interval)) : 40;
                }
                logger.info('事务联动-视频动作，获取截图参数:', temp);
            }
            else if (actionCode === '2') {
                //录像
                if (jsonActionParam.recordTime && (jsonActionParam.recordTime !== '0')) {
                    temp = {};
                    temp.duration = Number(jsonActionParam.recordTime);
                    temp.preRecTime = jsonActionParam.beforeTime ? (Number(jsonActionParam.beforeTime)) : 0;
                    temp.streamType = 0;
                }
                logger.info('事务联动-视频动作，获取录像参数:', temp);
            }
        }
        catch (err) {
            logger.error('事务联动-视频动作，获取动作参数异常：', err.message);
        }
        return temp;
    }

    /**
     * JumpToPreset:转动到预置位
     * @param actionParam:跳转预置位的动作参数
     * by 潘翔 on 2018/2/2
     */
    function jumpToPreset(actionParam) {
        logger.info('事务联动-视频动作，跳转到预置位开始');
        try {
            let serverMgr = require('../../../serverMgr');
            if (actionParam) {
                let assetNo = actionParam.assetNo;
                let presettingBit = actionParam.presettingBit;
                let ptzControlIProtocol = {};
                ptzControlIProtocol.header = {}
                ptzControlIProtocol.header.assetNo = assetNo;
                ptzControlIProtocol.header.equipType = '0';//TODO,暂时定为0
                ptzControlIProtocol.header.requestTime = new Date().getTime();
                ptzControlIProtocol.header.dataSource = '0';
                ptzControlIProtocol.header.optCmd = 'safe_param_6021';
                ptzControlIProtocol.command = '103';
                ptzControlIProtocol.speed = 0;//TODO
                ptzControlIProtocol.orientation = 0;
                ptzControlIProtocol.params = [];
                ptzControlIProtocol.params.push(presettingBit);
                logger.info('发送跳转预置位的I类协议[%s]', JSON.stringify(ptzControlIProtocol));
                let videoTask = {};
                videoTask.name = commonModule.constants.PROCESS_MESSAGE_DEFINE.VIDEO_MSG.TASK_REQ;
                videoTask.data = ptzControlIProtocol;
                serverMgr.sendMsg(serverType.VIDEO, JSON.stringify(videoTask));
            }
        } catch (err) {
            logger.error('事务联动-视频动作，发送跳转预置位异常：', err.message);
        }
    }
}

var commonVideoAction = new CommonVideoAction();
module.exports = commonVideoAction;