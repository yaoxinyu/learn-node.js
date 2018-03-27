/**
 * Created by panxiang on 2018/2/5.
 */
/**
 * screenshotAction 执行截图动作
 * by 潘翔 on 2018/2/2
 */

var commonVideoAction = require('./commonVideoAction');
var serverType = require('../../../common/constant');
var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function ScreenshotAction() {
    /**
     * executeAction 执行截图动作
     * @param
     *      actionModeParamModel:动作作参数模型JSON类型
     *      arrResponseMsg:待填充的信息，JSON数组格式类型
     *      message:触发动作相关信息，JSON格式
     * by 潘翔 on 2018/2/2
     */
    this.executeAction = async function (actionModeParamModel, message) {
        try {
            let arrActionParam = await commonVideoAction.commonExecute(actionModeParamModel, message);
            logger.info('事务联动-视频动作-视频截图，执行截图的参数[%s]', JSON.stringify(arrActionParam));
            if (arrActionParam && arrActionParam.length > 0) {
                await executeScreenshot(arrActionParam);
            }
        } catch (err) {
            logger.error('事务联动-视频动作-视频截图执行异常：', err.message);
        }
    };

    /**
     * executeScreenshot 执行截图
     * @param
     *      arrActionParam:执行截图所需的参数,是一个集合，存放一些列资产编号
     * by 潘翔 on 2018/2/2
     */
    async function executeScreenshot(arrActionParam) {
        try {
            let serverMgr = require('../../../serverMgr');
            logger.info('事务联动-视频动作-视频截图，开始发送截图参数');
            let arrAssetNo = [];
            let arrData = [];
            for (let actionParam of arrActionParam) {
                let temp = {};
                arrAssetNo.push(actionParam.assetNo);
                temp.interval = actionParam.preRecTime;
                temp.maxSnapNum = actionParam.duration;
                temp.startOffset = actionParam.startOffset;
                arrData.push(temp);
            }
            let execRecordIProtocol = {};
            execRecordIProtocol.header = {};
            execRecordIProtocol.header.assetNo = arrAssetNo.join('|');
            execRecordIProtocol.header.equipType = '0';//TODO 暂定为0
            execRecordIProtocol.header.requestTime = new Date().getTime();
            execRecordIProtocol.header.dataSource = '0';
            execRecordIProtocol.header.optCmd = 'safe_param_6018';
            execRecordIProtocol.data = arrData;
            logger.info('事务联动-视频动作-视频截图，发送截图的I类协议[%s]', JSON.stringify(execRecordIProtocol));
            let videoTask = {};
            videoTask.name = commonModule.constants.PROCESS_MESSAGE_DEFINE.VIDEO_MSG.TASK_REQ;
            videoTask.data = execRecordIProtocol;
            serverMgr.sendMsg(serverType.SERVER_TYPE.VIDEO, JSON.stringify(videoTask));
        } catch (err) {
            logger.error('事务联动-视频动作-视频截图，发送视频截图I类协议异常：', err.message);
        }
    }
}

var screenshotAction = new ScreenshotAction();
module.exports = screenshotAction;