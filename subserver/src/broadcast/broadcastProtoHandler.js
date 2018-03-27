/**
 * 广播协议处理模块，功能描述：
 * 1、解析Avro数据格式的广播协议；
 * 2、响应数据用Avro数据格式组装；
 * @author yaoxinyu
 * @date 2017/10/31
 */

var commonModule = require('../commonModuleExport');
var sleep = commonModule.sleep;
// 常量模块
const constants = commonModule.constants;
// 日志模块
const logger = commonModule.logger.getLogger(0);
const fileUtil = commonModule.fileUtil;
var operDefine = require('./broadcastOperDefine');
var operInfo = operDefine.operInfo;
var storageMgr = require('../storageMgr');
var dataCache = require('./broadcastDataCache');
// 轮巡任务模块
var scheduleTask = require('./asyncTaskProcessor');
var mqMgr = require('../activeMQMgr');


function BroadcastProtoHandler() {
    /**
     *
     * @param data 按厂商划分后的任务请求数据
     * @param taskMgr 对应设备厂商的任务管理器
     * @param header 原始请求的数据头
     */
    this.taskHandle = function (data, taskMgr, header) {
        if (data == null || data.header == null) {
            logger.error('任务请求数据错误！');
            return;
        }

        // 任务信息
        let taskInfo = {};
        taskInfo.req = data;
        taskInfo.taskMgr = taskMgr;
        taskInfo.header = header;
        let assetNos = [];
        if (data.header.assetNo != null && data.header.assetNo != '') {
            assetNos = data.header.assetNo.split('|');
        }
        taskInfo.assetNos = assetNos;

        // 任务分发
        switch (data.header.optCmd) {
            case 'broadcast_param_9003':
            // 广播
                switch (data.optType) {
                    case constants.BROADCAST_REQ_PARAM.START:
                        // 开始广播
                        logger.debug('开始广播......');
                        startBroadcastTask(taskInfo);
                        break;
                    case constants.BROADCAST_REQ_PARAM.STOP:
                        // 停止广播 支持多个
                        logger.debug('停止广播......');
                        stopBroadcastTask(taskInfo);
                        break;
                    case constants.BROADCAST_REQ_PARAM.ADJUST_VOLUME:
                        // 调整音量
                        logger.debug('调整音量......');
                        adjustVolumeTask(taskInfo);
                        break;
                    case constants.BROADCAST_REQ_PARAM.QUERY_FILE:
                        // 查询文件列表
                        logger.debug('查询文件列表......');
                        queryAllFileTask(taskInfo);
                        break;
                    case constants.BROADCAST_REQ_PARAM.DEVICE_STATUS:
                        // 状态 do nothing
                        break;
                    default:
                        logger.error('错误的广播操作：' + data.header.optCmd);
                        doErrorResponse(data, '错误的广播操作类型');
                        break;
                }
                break;
            case 'broadcast_param_9004':
            // 喊话
                if (data.optType == constants.CALL_REQ_PARAM.START) {
                // 开始喊话
                    logger.debug('开始喊话......');
                    startCallTask(taskInfo);
                } else if (data.optType == constants.CALL_REQ_PARAM.STOP) {
                // 停止喊话
                    logger.debug('停止喊话......');
                    stopCallTask(taskInfo);
                } else {
                    logger.error('错误的喊话操作：' + data.optType);
                    doErrorResponse(data, '错误的广播喊话操作类型');
                }
                break;
            case 'broadcast_param_9005':
            // 增加/修改设备
                if (data.optType == constants.DEV_REQ_PARAM.ADD) {
                // 增加设备
                    logger.debug('增加设备......');
                    addDeviceTask(taskInfo);
                } else if (data.optType == constants.DEV_REQ_PARAM.UPDATE) {
                // 修改设备
                    logger.debug('修改设备......');
                    updateDeviceTask(taskInfo);
                } else {
                    logger.error('错误的设备操作：', data.optType);
                    doErrorResponse(data, '错误的广播设备操作类型');
                }
                break;
            case 'broadcast_param_9006':
            // 删除设备
                logger.debug('删除设备......');
                delDeviceTask(taskInfo);
                break;
            case 'broadcast_param_9007':
            // 上传文件
                logger.debug('上传文件......');
                uploadFileTask(taskInfo);
                break;
            case 'broadcast_param_9008':
            // 添加/修改方案
                let addPlanInfo = operInfo.addPlanInfo;
                addPlanInfo.planName = data.planName;
                addPlanInfo.taskList = [];
                let planTaskInfo = {};
                planTaskInfo.taskName = data.taskName;
                planTaskInfo.strBeginTime = data.planBeginTime;
                planTaskInfo.strEndTime = data.planEndTime;
                planTaskInfo.strDoworkTime = data.taskBeginTime;
                planTaskInfo.strTaskFinishTime = data.taskEndTime;
                planTaskInfo.nCycleMode = data.cycleMode;
                planTaskInfo.strTaskRunDate = data.taskRunDate;
                // 设备列表信息
                planTaskInfo.devList = data.deviceList;
                // 文件列表信息
                planTaskInfo.fileList = data.fileList;
                // 播放模式信息
                planTaskInfo.playMode = data.playMode;
                planTaskInfo.replayTimes = data.playTimes;
                planTaskInfo.volume = data.volume;
                planTaskInfo.playDuration = 0;
                addPlanInfo.taskList.push(planTaskInfo);

                if (data.optType == constants.PLAN_REQ_PARAM.ADD) {
                // 添加方案
                    logger.debug('添加方案......');
                    addPlanTask(addPlanInfo, taskMgr, header);
                } else if (data.optType == constants.PLAN_REQ_PARAM.UPDATE) {
                // 修改方案
                    logger.debug('修改方案......');
                    updatePlanTask(addPlanInfo, taskMgr, header);
                } else {
                    logger.error('错误的方案操作：' + data.optType);
                    doErrorResponse(data, '错误的方案操作类型');
                }
                break;
            case 'broadcast_param_9009':
            // 删除方案
                logger.debug('删除方案......');
                delPlanTask(taskInfo);
                break;
            case 'broadcast_param_9010':
            // 添加/删除会话设备
                if (data.optType == constants.SESSION_DEV_REQ_PARAM.ADD) {
                // 添加会话设备
                    logger.debug('添加会话设备......');
                    addSessionDeviceTask(taskInfo);
                } else if (data.optType == constants.SESSION_DEV_REQ_PARAM.DELETE) {
                // 删除会话设备
                    logger.debug('删除会话设备......');
                    delSessionDeviceTask(taskInfo);
                } else {
                    logger.error('错误的会话设备操作：' + data.optType);
                    doErrorResponse(data, '错误的会话设备操作类型');
                }
                break;
            default:
                logger.error('无法识别的任务请求：' + data.header.optCmd);
                break;
        }
    };

    /**
     * 广播请求失败回复错误信息——对外接口
     * @param req 原始任务请求
     * @param errMsg {string} 错误描述
     */
    this.doBroadcastErrResponse = function (req, errMsg) {
        doErrorResponse(req, errMsg);
    };

    /**
     * 广播请求失败回复错误信息——内部接口
     * @param req 原始任务请求
     * @param errMsg {string} 错误描述
     */
    var doErrorResponse = function (req, errMsg) {
        try {
            let isNeedSend = true;
            let resInfo = {};
            resInfo.header = {};
            resInfo.header.assetNo = req.header.assetNo;
            resInfo.header.equipType = req.header.equipType;
            resInfo.header.requestTime = req.header.requestTime;
            resInfo.header.responseTime = new Date().getTime();
            resInfo.header.dataSource = req.header.dataSource;
            resInfo.header.code = 100;
            resInfo.header.msg = errMsg;
            resInfo.data = {};
            resInfo.data.code = 100;
            switch (req.header.optCmd) {
                case 'broadcast_param_9003':
                case 'broadcast_param_9004':
                case 'broadcast_param_9007':
                case 'broadcast_param_9008':
                case 'broadcast_param_9009':
                case 'broadcast_param_9010':
                // 广播开始/停止、喊话开始/停止、查询文件、上传文件、增/删/改方案、添加/删除会话设备
                    resInfo.header.optCmd = 'broadcast_data_9003';
                    resInfo.data.optType = operDefine.getResOptType(req.header.optCmd, req.optType);
                    break;
                case 'broadcast_param_9005':
                case 'broadcast_param_9006':
                // 广播设备增/删/改
                    resInfo.header.optCmd = 'broadcast_data_9006';
                    resInfo.data.devId = '';
                    resInfo.data.msg = errMsg;
                    break;
                default:
                    isNeedSend = false;
                    break;
            }
            if (isNeedSend) {
                mqMgr.sendBusiDataForII(resInfo);
            }
        } catch (exception) {
            logger.error('发送广播任务错误回复MQ信息异常：', exception.message);
        }
    };

    /**
     * 开始广播
     */
    var startBroadcastTask = async function (taskInfo) {
        let broadcastInfo = operInfo.broadcastInfo;
        broadcastInfo.uVolume = taskInfo.req.volume;
        broadcastInfo.arraySrc = [...taskInfo.req.fileId];
        broadcastInfo.arrayDst = [];
        for (let assetNo of taskInfo.assetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(assetNo);
            if (!result) {
                continue;
            }
            broadcastInfo.arrayDst.push(result.ip);
        }
        if (broadcastInfo.arraySrc.length > 0 && broadcastInfo.arrayDst.length > 0) {
            let task = taskInfo.taskMgr.startBroadcast(broadcastInfo);
            dataCache.setTaskHeadInfo(task.taskId, taskInfo.header);
            scheduleTask.pushTask(task);
        } else {
            doErrorResponse(taskInfo.req, '广播操作目标为空');
        }
    };

    /**
     * 停止广播
     */
    var stopBroadcastTask = async function (taskInfo) {
        let header = taskInfo.header;
        for (let assetNo of taskInfo.assetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(assetNo);
            if (!result) {
                let errReq = taskInfo.req;
                errReq.header.assetNo = assetNo;
                doErrorResponse(errReq, '停止广播操作IP为空');
                continue;
            }
            let task = taskInfo.taskMgr.stopBroadcast(result.ip);
            header.assetNo = assetNo;
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);
            await sleep(100);
        }
    };

    /**
     * 开始喊话
     */
    var startCallTask = async function (taskInfo) {
        let info = operInfo.callInfo;
        info.uVolume = taskInfo.req.volume;
        info.dst = [];
        for (let assetNo of taskInfo.assetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(assetNo);
            if (!result) {
                continue;
            }
            info.dst.push(result.ip);
        }
        let dstAssetNos = [];
        if (taskInfo.req.dstAssetNo != null && taskInfo.req.dstAssetNo != '') {
            dstAssetNos = taskInfo.req.dstAssetNo.split('|');
        }
        for (let dstAssetNo of dstAssetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(dstAssetNo);
            if (!result) {
                doErrorResponse(taskInfo.req, '喊话源设备IP为空');
                continue;
            }
            info.src = result.ip;

            let task = taskInfo.taskMgr.startCall(info);
            dataCache.setTaskHeadInfo(task.taskId, taskInfo.header);
            scheduleTask.pushTask(task);
        }
    };

    /**
     * 停止喊话
     */
    var stopCallTask = async function (taskInfo) {
        let header = taskInfo.header;
        for (let assetNo of taskInfo.assetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(assetNo);
            if (!result) {
                let errReq = taskInfo.req;
                errReq.header.assetNo = assetNo;
                doErrorResponse(errReq, '停止喊话操作IP为空');
                continue;
            }
            let task = taskInfo.taskMgr.stopCall(result.ip);
            header.assetNo = assetNo;
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);
            await sleep(50);
        }
    };

    /**
     * 调整音量
     */
    var adjustVolumeTask = async function (taskInfo) {
        let volumeInfo = operInfo.volumeInfo;
        volumeInfo.uVolume = taskInfo.req.volume;
        let header = taskInfo.header;
        for (let assetNo of taskInfo.assetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(assetNo);
            if (!result) {
                let errReq = taskInfo.req;
                errReq.header.assetNo = assetNo;
                doErrorResponse(errReq, '广播调整音量操作IP为空');
                continue;
            }
            volumeInfo.dst = result.ip;
            let task = taskInfo.taskMgr.adjustVolume(volumeInfo);
            header.assetNo = assetNo;
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);
            await sleep(50);
        }
    };

    /**
     * 查询文件
     */
    var queryAllFileTask = function (taskInfo) {
        let task = taskInfo.taskMgr.queryAllFile();
        dataCache.setTaskHeadInfo(task.taskId, taskInfo.header);
        scheduleTask.pushTask(task);
    };

    /**
     * 添加设备
     */
    var addDeviceTask = async function (taskInfo) {
        let header = taskInfo.header;
        let deviceList = taskInfo.req.data;
        if (!deviceList || deviceList.length == 0) {
            doErrorResponse(taskInfo.req, '添加设备列表为空');
            return;
        }
        for (let devInfo of deviceList) {
            let info = operInfo.addDevInfo;
            info.devCode = devInfo.devCode;
            info.devType = devInfo.devType;
            info.devName = devInfo.devName;
            info.devIP = devInfo.devIP;
            info.devId = '';  // 添加时不需要该字段

            let task = taskInfo.taskMgr.addDevice(info);
            header.assetNo = devInfo.devCode;
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);

            await sleep(100);
        }
    };

    /**
     * 修改设备
     */
    var updateDeviceTask = async function (taskInfo) {
        let header = taskInfo.header;
        let deviceList = taskInfo.req.data;
        if (!deviceList || deviceList.length == 0) {
            doErrorResponse(taskInfo.req, '修改设备列表为空');
            return;
        }
        for (let devInfo of deviceList) {
            let info = operInfo.addDevInfo;
            info.devCode = devInfo.devCode;
            info.devType = devInfo.devType;
            info.devName = devInfo.devName;
            info.devIP = devInfo.devIP;
            info.devId = devInfo.devId;

            let task = taskInfo.taskMgr.updateDevice(info);
            header.assetNo = devInfo.devCode;
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);

            await sleep(100);
        }
    };

    /**
     * 删除设备
     */
    var delDeviceTask = async function (taskInfo) {
        let header = taskInfo.header;
        let devIdArray = [];
        if (taskInfo.req.devId != null && taskInfo.req.devId != '') {
            devIdArray = taskInfo.req.devId.split('|');
        }
        if (devIdArray.length == 0) {
            doErrorResponse(taskInfo.req, '删除设备列表为空');
            return;
        }
        for (let devId of devIdArray) {
            let info = operInfo.delDevInfo;
            info.devCode = taskInfo.assetNos[i];
            info.devId = devId;
            let task = taskInfo.taskMgr.delDevice(info);
            header.assetNo = taskInfo.assetNos[i];
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);

            await sleep(100);
        }
    };

    /**
     * 上传文件
     */
    var uploadFileTask = function (taskInfo) {
        try {
            let info = operInfo.fileUploadInfo;
            info.fileName = taskInfo.req.data.fileName;
            info.fileType = taskInfo.req.data.fileType;
            info.fileSize = taskInfo.req.data.fileSize;
            let timeStap = new Date().getTime() + '-' + info.fileName;
            let uploadDirPath = fileUtil.getRootPath();
            let index = uploadDirPath.lastIndexOf('\\');
            if (index != -1) {
                uploadDirPath = uploadDirPath.substr(0, index) + '\\upload';
            }
            if (!fileUtil.fileExist(uploadDirPath)) {
                fileUtil.createDir(uploadDirPath);
            }
            let filePath = fileUtil.path.join(uploadDirPath, timeStap);
            let fileData = new Buffer(taskInfo.req.data.fileData, 'base64').toString('binary'); // 将数据进行base64解码
            let isWrite = fileUtil.writeFileSync(filePath, fileData, 'binary');
            if (!isWrite) {
                logger.error('文件未成功保存到upload文件夹！');
                return;
            }
            info.filePath = filePath;
            let task = taskInfo.taskMgr.uploadFile(info);
            dataCache.setTaskHeadInfo(task.taskId, taskInfo.header);
            scheduleTask.pushTask(task);
        } catch (exception) {
            logger.error('解析上传文件数据异常:' + exception.message);
        }
    };

    /**
     * 添加方案
     */
    var addPlanTask = function (planInfo, taskMgr, header) {
        let taskInfo = taskMgr.addOrUpdatePlan(planInfo, 1);
        dataCache.setTaskHeadInfo(taskInfo.taskId, header);
        scheduleTask.pushTask(taskInfo);
    };

    /**
     * 修改方案
     */
    var updatePlanTask = function (planInfo, taskMgr, header) {
        let taskInfo = taskMgr.addOrUpdatePlan(planInfo, 2);
        dataCache.setTaskHeadInfo(taskInfo.taskId, header);
        scheduleTask.pushTask(taskInfo);
    };

    /**
     * 删除方案
     */
    var delPlanTask = function (taskInfo) {
        let delPlanInfo = operInfo.delPlanInfo;
        delPlanInfo.planName = taskInfo.req.planName;
        let task = taskInfo.taskMgr.delPlan(delPlanInfo);
        dataCache.setTaskHeadInfo(task.taskId, taskInfo.header);
        scheduleTask.pushTask(task);
    };

    /**
     * 添加会话设备
     */
    var addSessionDeviceTask = async function (taskInfo) {
        let info = operInfo.sessionDevInfo;
        let result = await storageMgr.queryBroadcastIPByAssetNo(taskInfo.req.assetNo);
        if (!result) {
            doErrorResponse(taskInfo.req, '添加会话设备时会话中设备IP为空');
            return;
        }
        if (!taskInfo.assetNos || taskInfo.assetNos.length == 0) {
            doErrorResponse(taskInfo.req, '添加会话设备列表为空');
            return;
        }

        info.sessionDevIP = result.ip;
        let header = taskInfo.header;
        for (let assetNo of taskInfo.assetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(assetNo);
            if (!result) {
                let errReq = taskInfo.req;
                errReq.header.assetNo = assetNo;
                doErrorResponse(errReq, '添加的会话设备IP为空');
                continue;
            }
            info.devIP = result.ip;
            let task = taskInfo.taskMgr.addSessionDev(info);
            header.assetNo = assetNo;
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);
            await sleep(30);
        }
    };

    /**
     * 删除会话设备
     */
    var delSessionDeviceTask = async function (taskInfo) {
        let info = operInfo.sessionDevInfo;
        let result = await storageMgr.queryBroadcastIPByAssetNo(taskInfo.req.assetNo);
        if (!result) {
            doErrorResponse(taskInfo.req, '删除会话设备时会话中设备IP为空');
            return;
        }
        if (!taskInfo.assetNos || taskInfo.assetNos.length == 0) {
            doErrorResponse(taskInfo.req, '删除会话设备列表为空');
            return;
        }

        info.sessionDevIP = result.ip;
        let header = taskInfo.header;
        for (let assetNo of taskInfo.assetNos) {
            let result = await storageMgr.queryBroadcastIPByAssetNo(assetNo);
            if (!result) {
                let errReq = taskInfo.req;
                errReq.header.assetNo = assetNo;
                doErrorResponse(errReq, '删除的会话设备IP为空');
                continue;
            }
            info.devIP = result.ip;
            let task = taskInfo.taskMgr.delSessionDev(info);
            header.assetNo = assetNo;
            dataCache.setTaskHeadInfo(task.taskId, header);
            scheduleTask.pushTask(task);
            await sleep(30);
        }
    };
}


var protoHandle = new BroadcastProtoHandler();
module.exports = protoHandle;