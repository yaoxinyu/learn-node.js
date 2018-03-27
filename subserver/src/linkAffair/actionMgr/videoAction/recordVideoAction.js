/**
 * Created by panxiang on 2018/2/2.
 */
/**
 * RecordVideoAction 录制视频
 * by 潘翔 on 2018/2/2
 */
'use strict';
var commonVideoAction = require('./commonVideoAction');
var serverType = require('../../../common/constant');
var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function RecordVideoAction() {
    /**
     * executeAction 执行录制视频的动作
     * @param
     *      actionModeParamModel:动作作参数模型JSON类型
     *      message:触发动作相关信息 JSON格式
     * by 潘翔 2018/2/2
     */
    this.executeAction = async function (actionModeParamModel, message) {
        try {
            let arrActionParam = await commonVideoAction.commonExecute(actionModeParamModel, message);
            logger.info('事务联动-视频动作-视频录像,执行录像的参数：', JSON.stringify(arrActionParam));
            if (arrActionParam && arrActionParam.length > 0) {
                await executeRecord(arrActionParam);
            }
        } catch (err) {
            logger.info('事务联动-视频动作-视频录像执行异常：', err.message);
        }
    };

    /**
     * executeRecord 执行录像
     * @param
     *      arrActionParam:执行录像所需的参数,是一个集合，存放一些列资产编号
     * by 潘翔 on 2018/2/2
     */
    async function executeRecord(arrActionParam) {
        try {
            let serverMgr = require('../../../serverMgr');
            logger.info('事务联动-视频动作-视频录像，开始发送录像参数');
            let arrAssetNo = [];
            let arrData = [];
            for (let actionParam of arrActionParam) {
                let temp = {};
                arrAssetNo.push(actionParam.assetNo);
                temp.preRecTime = actionParam.preRecTime;
                temp.duration = actionParam.duration;
                temp.streamType = actionParam.streamType;
                arrData.push(temp);
            }
            let execRecordIProtocol = {};
            execRecordIProtocol.header = {};
            execRecordIProtocol.header.assetNo = arrAssetNo.join('|');
            execRecordIProtocol.header.equipType = null;
            execRecordIProtocol.header.requestTime = new Date().getTime();
            execRecordIProtocol.header.dataSource = '0';
            execRecordIProtocol.header.optCmd = 'safe_param_6019';
            execRecordIProtocol.data = arrData;
            logger.info('事务联动-视频动作-视频录像，请求的I类协议是[%s]', JSON.stringify(execRecordIProtocol));
            let videoTask = {};
            videoTask.name = commonModule.constants.PROCESS_MESSAGE_DEFINE.VIDEO_MSG.TASK_REQ;
            videoTask.data = execRecordIProtocol;
            serverMgr.sendMsg(serverType.SERVER_TYPE.VIDEO, JSON.stringify(videoTask));
        } catch (err) {
            logger.error('事务联动-视频动作-视频录像，发送视频录像I类协议异常：', err.message);
        }
    }
}

var recordVideoAction = new RecordVideoAction();
module.exports = recordVideoAction;