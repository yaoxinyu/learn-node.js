/**
 * Created by panxiang on 2018/2/28.
 */
var linkAffairDB = require('../DB/linkAffairDao');
var commonModule = require('../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function InsertLinkageAffairLog() {
    'use strict';
    /**
     * logAfterAction:执行动作后插入日志
     * @param
     *      actionModeParamModel:动作作参数模型JSON类型
     *      linkageAffairMessage:动作的原始信息JSON类型
     * by 潘翔 on 2018/2/28
     */
    this.logAfterAction = async function (actionModeParamModel, linkageAffairMessage) {
        logger.info('事务联动-插入动作日志...');
        try {
            let actionLogModel = {};
            logger.info('事务联动-插入动作日志，条件模型[%s],动作信息:[%s]', JSON.stringify(actionModeParamModel), JSON.stringify(linkageAffairMessage));
            let arrEventCode = linkageAffairMessage.eventCode.split(',');
            let eventTime = formatDate(new Date(linkageAffairMessage.eventTime));
            logger.info('事务联动-插入动作日志，事件编号:[%s],时间:[%s]', arrEventCode, eventTime);
            actionLogModel.abId = actionModeParamModel.abId;
            actionLogModel.eventCode = linkageAffairMessage.eventCode;
            actionLogModel.actionMode = actionModeParamModel.actionMode;
            actionLogModel.actionCode = actionModeParamModel.actionCodeName;
            actionLogModel.dtActionTouch = eventTime;
            let arrEventName = [];
            let deviceId = '';
            let eventLevel = '';
            let orgCode = '';
            let orgName = '';
            let roadName = '';
            for (let eventCode of arrEventCode) {
                let arrLogModel = await linkAffairDB.findActionLogParams(actionModeParamModel.abId, eventCode, linkageAffairMessage.assetNo);
                logger.info('事务联动-插入动作日志，查询动作日志参数相关表得到的结果:', arrLogModel);
                if (arrLogModel) {
                    for (let i = 0; i < arrLogModel.length; i++) {
                        if (i === 0) {
                            deviceId = arrLogModel[0].deviceId;
                            eventLevel = arrLogModel[0].eventLevel;
                            orgCode = arrLogModel[0].orgCode;
                            orgName = arrLogModel[0].orgName;
                            roadName = arrLogModel[0].roadName;
                        }
                        arrEventName.push(arrLogModel[i].eventName);
                    }
                }
            }
            actionLogModel.deviceId = deviceId;
            actionLogModel.eventName = arrEventName.join(',');
            actionLogModel.eventLevel = eventLevel;
            actionLogModel.orgCode = orgCode;
            let msg = '';
            msg += eventTime;//日期
            msg += '设备编号为 ';
            msg += linkageAffairMessage.assetNo;
            msg += ',';
            msg += '在';
            msg += '';
            msg += orgName;
            msg += (roadName ? roadName : '');
            msg += '发生 ';
            msg += actionLogModel.eventName;
            msg += '动作方式是';
            msg += actionModeParamModel.actionCodeName;
            msg += ',';
            msg += '告警等级是';
            msg += eventLevel;
            msg += '!';
            actionLogModel.actionContent = msg;
            logger.info('事务联动-待插入的动作日志信息：', actionLogModel);
            let result = await linkAffairDB.insertActionLog(actionLogModel);
            logger.info('事务联动-动作日志插入结果是:', result);
        }
        catch (err) {
            logger.error('事务联动-动作日志插入异常：', err.message);
        }
    };

    /**
     * formatDate 格式化时间
     * @param eventTime
     * by 潘翔 on 2018/2/28
     */
    function formatDate(eventTime) {
        let year = eventTime.getFullYear();
        let month = eventTime.getMonth() + 1;
        let date = eventTime.getDate();
        let hour = eventTime.getHours();
        let minute = eventTime.getMinutes();
        let second = eventTime.getSeconds();
        return year + '-' + month + '-' + date + ' ' + hour + ':' + minute + ':' + second;
    }
}

var insertLinkageAffairLog = new InsertLinkageAffairLog();
module.exports = insertLinkageAffairLog;