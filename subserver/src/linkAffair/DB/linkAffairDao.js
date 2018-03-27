/**
 * Created by wangweizhen on 2018/1/29.
 */

var commonModule = require('../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var sql = require('../../common/util/sql');
var dbUtil = require('../../common/util/db');
var linkAffModel = require('./linkAffairModel');
var cloneObj = require('../../common/commonFunction');

var DbUtil = function () {

    /**
     * 根据资产编号查询资产事务联动动作配置信息
     * @param assetNo 资产编号
     * @return {Promise.<*>}
     */
    this.getActionEventByAssetNo = async function (assetNo) {
        let arrActionEvent = [];
        let temp = null;
        let results = await dbUtil.queryList('findActionEventByAssetNo', [assetNo.substring(0, 4), '1', '0', assetNo]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionEvent.eventCode = result.eventCode;
                linkAffModel.actionEvent.deviceType = result.deviceType;
                linkAffModel.actionEvent.actionId = result.actionId;
                temp = cloneObj.clone(linkAffModel.actionEvent);
                arrActionEvent.push(temp);
            }
        } else {
            arrActionEvent = null;
        }
        return arrActionEvent;
    };

    /**
     * 根据动作ID查询资产事务联动动作条件信息
     * @param actionId 动作ID
     * @return {Promise.<*>}
     */
    this.getActionConditionsByActionId = async function (actionId) {
        let arrActionCondition = [];
        let temp = null;
        let results = await dbUtil.queryList('findActionConditionsByActionId', actionId);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionCondition.abId = result.abId;
                linkAffModel.actionCondition.acId = result.acId;
                linkAffModel.actionCondition.condition = result.condition;
                linkAffModel.actionCondition.unitTime = result.unitTime;
                temp = cloneObj.clone(linkAffModel.actionCondition);
                arrActionCondition.push(temp);
            }
        } else {
            arrActionCondition = null;
        }
        return arrActionCondition;
    };

    /**
     * 根据动作ID查询资产事务联动动作参数
     * @param arrActionId 数组，多个动作ID
     * @return {Promise.<*>}
     */
    this.getActionConditionParamsByActionId = async function (arrActionId) {
        let arrActionConditionParams = [];
        let temp = null;
        let results = await dbUtil.queryList('findActionConditionParamsByActionId', ['1', arrActionId]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionConditionParams.ampId = result.ampId;
                linkAffModel.actionConditionParams.abId = result.abId;
                linkAffModel.actionConditionParams.actionCode = result.actionCode;
                linkAffModel.actionConditionParams.actionMode = result.actionMode;
                linkAffModel.actionConditionParams.actionParam = result.actionParam;
                temp = cloneObj.clone(linkAffModel.actionConditionParams);
                arrActionConditionParams.push(temp);
            }
        } else {
            arrActionConditionParams = null;
        }
        return arrActionConditionParams;
    };

    /**
     * 根据资产编号查询资产信息
     * @param eventCode 事件编码
     * @param adId 动作ID
     * @param assetNo 资产编号
     * @return {Promise.<Array>}
     */
    this.getAssetByAssetNo = async function (eventCode, adId, assetNo) {
        let arrAssetInfo = [];
        let temp = null;
        let results = await dbUtil.queryList('findAssetByAssetNo', [eventCode, adId, '0', assetNo]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.assetInfo.assetName = result.assetName;
                linkAffModel.assetInfo.firstType = result.firstType;
                linkAffModel.assetInfo.secondType = result.secondType;
                linkAffModel.assetInfo.eventName = result.eventName;
                temp = cloneObj.clone(linkAffModel.assetInfo);
                arrAssetInfo.push(temp);
            }
        } else {
            arrAssetInfo = null;
        }
        return arrAssetInfo;
    };

    /**
     * 根据动作方式参数配置编号查询设备与监控参数配置信息
     * @param ampId a动作方式参数配置编号
     * @return {Promise.<null>}
     */
    this.getDeviceByActionModeParamId = async function (ampId, deviceId) {
        let arrDeviceInfo = [];
        let temp = null;
        let results = await dbUtil.queryList('findDeviceByActionModeParamId', [ampId, deviceId]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.deviceInfo.adpId = result.adpId;
                linkAffModel.deviceInfo.ampId = result.ampId;
                linkAffModel.deviceInfo.deviceId = result.deviceId;
                linkAffModel.deviceInfo.monitorDeviceId = result.monitorDeviceId;
                linkAffModel.deviceInfo.deviceNo = result.deviceNo;
                linkAffModel.deviceInfo.monitorDeviceNo = result.monitorDeviceNo;
                linkAffModel.deviceInfo.actionCode = result.actionCode;
                linkAffModel.deviceInfo.actionParam = result.actionParam;
                temp = cloneObj.clone(linkAffModel.deviceInfo);
                arrDeviceInfo.push(temp);
            }

        } else {
            arrDeviceInfo = null;
        }
        return arrDeviceInfo;
    };

    /**
     * 根据停车被监控设备查询最近的联动设备
     * @param assetNo 资产编号
     * @return {Promise.<Array>}
     */
    this.getParkDeviceByNear = async function (assetNo) {
        let arrParkDevice = [];
        let temp = null;
        let results = await dbUtil.queryList('findParkDeviceByNear', [assetNo, '0']);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.parkDevice.monitorDeviceNo = result.monitorDeviceNo;
                temp = cloneObj.clone(linkAffModel.parkDevice);
                arrParkDevice.push(temp);
            }
        } else {
            arrParkDevice = null;
        }
        return arrParkDevice;
    };

    /**
     * 根据地区编号和联系方式查询联系地址
     * @param ccId 主键
     * @return {Promise.<Array>}
     */
    this.getConcatNumberById = async function (ccId) {
        let arrConcatNumber = [];
        let temp = null;
        let results = await dbUtil.queryList('findConcatNumberById', [ccId]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.concatNumber.emailAddress = result.emailAddress;
                linkAffModel.concatNumber.phoneNumber = result.phoneNumber;
                linkAffModel.concatNumber.orgCode = result.orgCode;
                linkAffModel.concatNumber.concatName = result.concatName;
                temp = cloneObj.clone(linkAffModel.concatNumber);
                arrConcatNumber.push(temp);
            }
        } else {
            arrConcatNumber = null;
        }
        return arrConcatNumber;
    };

    /**
     * 查询邮件服务器配置信息
     * @return {Promise.<Array>}
     */
    this.getEmailConfig = async function () {
        let arrEmailConfig = [];
        let temp = null;
        let results = await dbUtil.queryList('getEmailConfig');
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.emailConfig.serverConfig = result.serverConfig;
                temp = cloneObj.clone(linkAffModel.emailConfig);
                arrEmailConfig.push(temp);
            }
        } else {
            arrEmailConfig = null;
        }
        return arrEmailConfig;
    };

    /**
     * 根据动作ID查询有效日期表
     * @param abId 动作ID
     * @return {Promise.<Array>}
     */
    this.getActionTimeRealByActionId = async function (abId) {
        let arrActionTimeReal = [];
        let temp = null;
        let results = await dbUtil.queryList('findActionTimeRealByActionId', [abId]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionTimeReal.abId = result.abId;
                linkAffModel.actionTimeReal.dtValidBegin = result.dtValidBegin;
                linkAffModel.actionTimeReal.dtValidEnd = result.dtValidEnd;
                temp = cloneObj.clone(linkAffModel.actionTimeReal);
                arrActionTimeReal.push(temp);
            }
        } else {
            arrActionTimeReal = null;
        }
        return arrActionTimeReal;
    };


    /**
     * 根据变量编码查询变量设置表
     * @param varCode 变量编码
     * @return {Promise.<Array>}
     */
    this.getActionEventVarByVarCode = async function (varCode) {
        let arrActionEventVar = [];
        let temp = null;
        let results = await dbUtil.queryList('findActionEventVarByVarCode', [varCode, '1']);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionEventVar.varName = result.varName;
                linkAffModel.actionEventVar.varCode = result.varCode;
                temp = cloneObj.clone(linkAffModel.actionEventVar);
                arrActionEventVar.push(temp);
            }
        } else {
            arrActionEventVar = null;
        }
        return arrActionEventVar;
    };

    /**
     * 根据设备类型和事件编码查询表达式
     * @param deviceType 设备类型
     * @param eventCode 事件编码
     * @param varName 事件名字
     * @return {Promise.<Array>} 表达式信息
     */
    this.getExpressionInfo = async function (deviceType, eventCode, varName) {
        let arrActionEventVar = [];
        let temp = null;
        let results = await dbUtil.queryList('getExpressionInfo', [deviceType, eventCode, varName]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionEventVar.varName = result.varName;
                linkAffModel.actionEventVar.varCode = result.varCode;
                temp = cloneObj.clone(linkAffModel.actionEventVar);
                arrActionEventVar.push(temp);
            }
        } else {
            arrActionEventVar = null;
        }
        return arrActionEventVar;
    };

    /**
     * 根据动作ID查询周期设置表
     * @param abId 动作ID
     * @return {Promise.<Array>}
     */
    this.getActionCycleRealByActionId = async function (abId) {
        let arrActionCycleReal = [];
        let temp = null;
        let results = await dbUtil.queryList('findActionCycleRealByActionId', [abId, '1']);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionCycleReal.abId = result.abId;
                linkAffModel.actionCycleReal.cycleDay = result.cycleDay;
                linkAffModel.actionCycleReal.cycleHour = result.cycleHour;
                temp = cloneObj.clone(linkAffModel.actionCycleReal);
                arrActionCycleReal.push(temp);
            }
        } else {
            arrActionCycleReal = null;
        }
        return arrActionCycleReal;
    };

    /**
     * 获取视频播放信息
     * @param deviceCode
     * @return {Promise.<Array>}
     */
    this.getVideoInfoByDeviceCode = async function (deviceCode) {
        let arrVideoInfo = [];
        let temp = null;
        let results = await dbUtil.queryList('getVideoInfoByDeviceCode', deviceCode);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.videoInfo.orgCode = result.orgCode;
                linkAffModel.videoInfo.usiCamId = result.usiCamId;
                temp = cloneObj.clone(linkAffModel.videoInfo);
                arrVideoInfo.push(temp);
            }
        } else {
            arrVideoInfo = null;
        }
        return arrVideoInfo;
    };

    /**
     *根据被监控设备查询最近的摄像头设备
     * @param assetNo 资产编号
     * @return {Promise.<Array>}
     */
    this.getCameraDeviceByAssetNo = async function (assetNo) {
        let arrCameraDevice = [];
        let temp = null;
        let results = await dbUtil.queryList('findCameraDeviceByAssetNo', [assetNo, '0']);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.cameraDevice.monitorDeviceNo = result.monitorDeviceNo;
                temp = cloneObj.clone(linkAffModel.cameraDevice);
                arrCameraDevice.push(temp);
            }
        } else {
            arrCameraDevice = null;
        }
        return arrCameraDevice;
    };

    /**
     * 根据服务id获取服务的ip、端口.
     * @param serviceId 服务ID
     * @param serviceType 服务类型
     * @return {Promise.<Array>}
     */
    this.getServiceInfoByServiceId = async function (serviceId, serviceType) {
        let arrServiceInfo = [];
        let temp = null;
        let results = await dbUtil.queryList('getServiceInfoByServiceId', [serviceId, serviceType]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.serviceInfo.ip = result.ip;
                linkAffModel.serviceInfo.port = result.port;
                temp = cloneObj.clone(linkAffModel.serviceInfo);
                arrServiceInfo.push(temp);
            }
        } else {
            arrServiceInfo = null;
        }
        return arrServiceInfo;
    };

    /**
     * 根据资产编号获取资产记录数据
     * @param assetNo 资产编号
     * @return {Promise.<Array>} 资产实体
     */
    this.getAssetDataByAssetNo = async function (assetNo) {
        let arrAssetData = [];
        let temp = null;
        let results = await dbUtil.queryList('getAssetDataByAssetNo', [assetNo]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.assetData.deviceID = result.deviceID;
                linkAffModel.assetData.equipType = result.equipType;
                linkAffModel.assetData.macAddr = result.macAddr;
                linkAffModel.assetData.factoryCode = result.factoryCode;
                linkAffModel.assetData.firstTypeCode = result.firstTypeCode;
                linkAffModel.assetData.secondTypeCode = result.secondTypeCode;
                linkAffModel.assetData.orgNo = result.orgNo;
                linkAffModel.assetData.lampID = result.lampID;
                linkAffModel.assetData.roadID = result.roadID;
                temp = cloneObj.clone(linkAffModel.assetData);
                arrAssetData.push(temp);
            }
        } else {
            arrAssetData = null;
        }
        return arrAssetData;
    };

    /**
     * 根据区域获取服务的ip、端口.
     * @param orgCode 区域
     * @param serviceType 服务类型
     * @return {Promise.<Array>}
     */
    this.getServiceInfoByOrgCode = async function (orgCode, serviceType) {
        let arrServiceInfo = [];
        let temp = null;
        let results = await dbUtil.queryList('getServiceInfoByOrgCode', [orgCode, serviceType]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.serviceInfo.ip = result.ip;
                linkAffModel.serviceInfo.port = result.port;
                temp = cloneObj.clone(linkAffModel.serviceInfo);
                arrServiceInfo.push(temp);
            }
        } else {
            arrServiceInfo = null;
        }
        return arrServiceInfo;
    };

    /**
     * 查询大屏信息
     * @param type 1: 停车场， 2：其他（RFID， 环境）String
     * @param assetNo 资产编号
     * @return {Promise.<Array>}
     */
    this.getBigScreenInfoByTypeAndId = async function (type, assetNo) {
        let arrBigScreenInfo = [];
        let temp = null;
        let results = await dbUtil.queryList('getBigScreenInfoByTypeAndId', [type, assetNo]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.bigScreenInfo.bigScreenAssetNo = result.bigScreenAssetNo;
                linkAffModel.bigScreenInfo.macAddr = result.macAddr;
                linkAffModel.bigScreenInfo.serviceId = result.serviceId;
                temp = cloneObj.clone(linkAffModel.bigScreenInfo);
                arrBigScreenInfo.push(temp);
            }
        } else {
            arrBigScreenInfo = null;
        }
        return arrBigScreenInfo;
    };

    this.getBigScreenServiceByAssetNo = async function (assetNo, dataType) {
        let screenServiceList = [];
        // 查询大屏服务信息
        let screenList = [];
        if (dataType == '1') {
            screenList = await this.getBigScreenInfoByTypeAndId(dataType, assetNo);
        } else {
            // 查询资产信息
            let assetData = await this.getAssetDataByAssetNo(assetNo);
            if (assetData) {
                screenList = await this.getBigScreenInfoByTypeAndId(dataType, assetData[0].deviceID);
            }
        }

        // 查询资产信息
        if (screenList && screenList.length > 0) {
            for (let screenInfo of screenList) {
                let serviceInfo = await this.getServiceInfoByServiceId(screenInfo.serviceId, '31');
                if (serviceInfo) {
                    serviceInfo[0].macAddr = screenInfo.macAddr;
                    screenServiceList.push(serviceInfo[0]);
                    continue;
                } else {
                    let bigSreenAsset = await this.getAssetDataByAssetNo(serviceInfo.bigScreenAssetNo);
                    if (bigSreenAsset) {
                        serviceInfo = await this.getServiceInfoByOrgCode(bigSreenAsset[0].orgNo, '31');
                        serviceInfo[0].macAddr = screenInfo.macAddr;
                        screenServiceList.push(serviceInfo[0]);
                    }
                }
            }
        }

        return screenServiceList;
    };

    /**
     * 根据资产编号获取停车监测数据.
     * @param assetNo
     * @return {Promise.<void>}
     */
    this.getSpotPlaceIdByAssetNo = async function (assetNo) {
        let result = await dbUtil.query('getSpotPlaceIdByAssetNo', [assetNo, 0]);
        if (result != -1 && result) {
            return result;
        } else {
            return null;
        }
    };
    /**
     *事务联动日志
     * @param params 数组，需要插入日志字段。
     device_id,设备ID
     ab_id,动作 动作配置ID
     event_code,事件类型
     event_name,事件名称
     event_level,事件级别
     org_code,地区编码
     action_code,动作类型
     action_content,
     dt_action_touch,
     * @return {Promise.<*>}
     */
    this.insertActionLog = async function (jsonData) {
        try {
            let params = [];
            params.push(jsonData.deviceId);
            params.push(jsonData.abId);
            params.push(jsonData.eventCode);
            params.push(jsonData.eventName);
            params.push(jsonData.eventLevel);
            params.push(jsonData.orgCode);
            params.push(jsonData.actionCode);
            params.push(jsonData.actionContent);
            params.push(jsonData.dtActionTouch);
            let result = await dbUtil.insert('insertActionLog', params);
            return result;
        } catch (err) {
            return null;
        }
    };

    /**
     *根据动作ID以及事件编码获取日志相关参数
     * @param abId
     * @param eventCode
     * @param assetNo
     * @return {Promise.<Array>}
     */
    this.findActionLogParams = async function (abId, eventCode, assetNo) {
        let arrActionLogParams = [];
        let temp = null;
        let results = await dbUtil.queryList('findActionLogParams', [eventCode, assetNo, abId]);
        if (results != -1 && results.length > 0) {
            for (let result of results) {
                linkAffModel.actionLogParams.actionName = result.actionName;
                linkAffModel.actionLogParams.eventLevel = result.eventLevel;
                linkAffModel.actionLogParams.eventName = result.eventName;
                linkAffModel.actionLogParams.orgCode = result.orgCode;
                linkAffModel.actionLogParams.orgName = result.orgName;
                linkAffModel.actionLogParams.deviceId = result.deviceId;
                linkAffModel.actionLogParams.roadName = result.roadName;
                temp = cloneObj.clone(linkAffModel.actionLogParams);
                arrActionLogParams.push(temp);
            }
        } else {
            arrActionLogParams = null;
        }
        return arrActionLogParams;
    };

    this.getAssetNoByDeviceId = async function (deviceId) {
        let result = await dbUtil.query('queryAssetNoByDeviceId', [deviceId]);
        if (result != -1 && result) {
            return result.device_code;
        }
        logger.error('查询assetNo失败，assetNo：', assetNo);
        return null;
    }
};

module.exports = new DbUtil();