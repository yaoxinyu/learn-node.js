/**
 * 广播服务异步任务处理模块
 * 注意：由广播服务模块来启动该模块
 * 功能描述：
 * 1、接收外部创建的广播任务，将其加入任务队列；
 * 2、轮巡任务队列，将有超时的任务从队列中移除，并通过MQ发送回复消息；
 * 3、未超时的任务，调用C++扩展模块获取操作结果。
 *  （1）未获取到等下次轮巡继续；
 *  （2）获取到操作结果，通过MQ发送回复消息，并从任务队列移除。
 * 4、定时获取设备状态推送信息；
 * 5、定时获取所有的设备状态信息
 * @author yaoxinyu
 * @date 2017/11/2
 */

var dataCache = require('./broadcastDataCache');
var mqMgr = require('../activeMQMgr');
var commonModule = require('../commonModuleExport');
// 常量模块
const constants = commonModule.constants;
// 日志模块
const logger = commonModule.logger.getLogger(0);
// 任务操作结构定义模块
var operDefine = require('./broadcastOperDefine');


// 定义任务超时时间
const TASK_TIMEOUT = 15000; // 单位ms
// 定义上传文件超时时间
// const UPLOAD_FILE_TIMEOUT = 180 * 1000; // 单位ms
// 定义任务轮巡时间间隔
const SCHEDULE_TIME = 50; // 单位ms
// 定义获取所有设备状态的时间间隔
const QUERY_DEVSTAT_SPAN = 3600 * 1000; // 单位ms
// 美电贝尔广播C++扩展模块
var aebellOper;
// 其他厂商C++扩展模块 TODO


function AsyncTaskProcessor() {
    // map结构，key值为任务ID，value为任务开始时间
    var taskTickMap = new Map();
    // map结构，key值为任务ID，value为任务信息
    var taskInfoMap = new Map();
    // 任务队列，存放taskInfo
    var taskQueue = [];
    // 启动标志
    var isStarted = false;
    // 上一次获取所有设备状态信息的时间
    var lastGetAllDevStatTick = 0;

    /**
     * 模块启动
     */
    this.start = function () {
        if (!isStarted) {
            aebellOper = require('./aebell/build/Release/aebellBroadcast');
            logger.info('广播服务轮巡任务启动...');
            // 启动轮巡
            setInterval(schedule, SCHEDULE_TIME);
            isStarted = true;
        }
    };

    /**
     * 执行轮巡任务
     */
    var schedule = function () {
        // 获取设备状态推送信息
        timerGetAutoDevStatus();
        // 获取所有设备状态信息
        timerGetAllDevStatus();
        // 处理任务队列
        processTaskQueue();
    };

    var processTaskQueue = function () {
        // 对taskQueue进行逆序遍历处理，对于超时的、已处理完的、无效的任务，从任务队列移除
        for (let i = taskQueue.length - 1; i >= 0; i--) {
            // 移除标记
            let removeFlag = false;
            // 首先检查超时
            let taskId = taskQueue[i].taskId;
            let timeout = checkTaskTimeout(taskId);
            if (timeout == 1) {
                // 任务超时，发送响应消息并从队列移除
                logger.error('该任务ID[%s]超时，发送回复并移除.', taskId);
                doTimeoutResponse(taskId);
                removeFlag = true;
            } else if (timeout == 2) {
                // 任务ID无效，从队列移除
                logger.error('该任务ID[%s]无效，将其移除.', taskId);
                removeFlag = true;
            } else {
                // 未超时，获取任务操作结果
                let result = getTaskResult(taskId);
                if (result != null && result.bRespond == 1) {
                    // 发送响应消息
                    doResponse(taskId, result);
                    removeFlag = true;
                }
            }

            if (removeFlag) {
                // 清除对应任务的缓存信息
                taskQueue.splice(i, 1);
                taskTickMap.delete(taskId);
                taskInfoMap.delete(taskId);
                dataCache.removeTaskHeadInfo(taskId);
            }
        }
    };

    /**
     * 获取设备推送状态，该任务为常驻任务，单独轮巡
     */
    var timerGetAutoDevStatus = function () {
        // 美电贝尔的设备状态
        let devStatusInfo = aebellOper.getAutoDeviceStatus();
        if (devStatusInfo && devStatusInfo.deviceResp.length > 0) {
            logger.info('获取到（美电贝尔）设备状态推送信息: ', devStatusInfo);
            sendDevStatusResponse(devStatusInfo.deviceResp);
        }
    };

    /**
     * 获取所有设备状态信息，该任务为常驻任务，单独轮巡
     */
    var timerGetAllDevStatus = function () {
        // 美电贝尔的设备状态
        let curTick = new Date().getTime();
        if (lastGetAllDevStatTick == 0 || curTick - lastGetAllDevStatTick > QUERY_DEVSTAT_SPAN) {
            let devStatusInfo = aebellOper.getAllDeviceStatus();
            if (devStatusInfo && devStatusInfo.deviceResp.length > 0) {
                logger.info('获取到（美电贝尔）设备所有的设备状态信息: ', devStatusInfo);
                sendDevStatusResponse(devStatusInfo.deviceResp);

                lastGetAllDevStatTick = curTick;
            }
            // 没获取到数据，不更新lastGetAllDevStatTick
        }
    };

    /**
     * 通过MQ发送设备状态信息
     * @param {array} deviceResp 设备状态信息
     */
    var sendDevStatusResponse = function (deviceResp) {
        let resInfo = {};
        resInfo.header = {};
        resInfo.header.assetNo = '';
        resInfo.header.equipType = null;
        resInfo.header.optCmd = 'broadcast_data_9005';
        resInfo.header.requestTime = 0;
        resInfo.header.responseTime = new Date().getTime();
        resInfo.header.dataSource = '0'; // 0：分控系统 1：运维系统
        resInfo.header.code = 200;
        resInfo.header.msg = 'OK';
        resInfo.data = {};
        resInfo.data.optType = '07';
        resInfo.data.code = 200;
        resInfo.data.statusResp = [];
        for (let device of deviceResp) {
            let devInfo = {};
            devInfo.devIP = device.deviceIP;
            devInfo.status = device.uState;
            devInfo.login = 1;
            devInfo.call = 2;
            devInfo.uVolume = device.uVolume;
            resInfo.data.statusResp.push(devInfo);
        }

        // "Data0400503005" MQ发送
        logger.info('通过MQ发送广播设备状态信息:', JSON.stringify(resInfo));
        mqMgr.sendBusiDataForII(resInfo);
    };

    /**
     * 加入任务队列
     * @param {object} taskInfo 任务基础信息
     * @param taskInfo.taskId 任务ID
     * @param taskInfo.taskType 任务类型
     * @param taskInfo.facType 设备厂家类型
     */
    this.pushTask = function (taskInfo) {
        if (taskInfo) {
            let taskId = taskInfo.taskId;
            let taskType = taskInfo.taskType;
            let taskTypeName = operDefine.getTaskTypeName(taskInfo.taskType);
            let facType = taskInfo.facType;
            logger.debug('加入轮巡任务，[任务ID:%s,任务类型:%s-%s,设备类型:%s]', taskId, taskType, taskTypeName, facType);
            // 记录任务开始时间
            let curTick = new Date().getTime();
            taskTickMap.set(taskId, curTick);
            // 记录任务信息
            taskInfoMap.set(taskId, taskInfo);
            // 加入队首（这里为什么不是队尾，因为轮巡时对数组遍历采用的逆序，保证先加入的任务先处理）
            taskQueue.unshift(taskInfo);
        } else {
            logger.error('push一个无效的轮巡任务！');
        }
    };

    /**
     * 获取任务操作结果
     * @param taskId
     * @return {object} 获取到返回数据，否则返回null
     */
    var getTaskResult = function (taskId) {
        let result = null;
        // 根据任务类型和设备厂商类型，调用对应模块接口
        let facType = taskInfoMap.get(taskId).facType;
        if (facType === constants.BROADCAST_FACTORY.AEBELL) {
            result = aebellOper.getTaskResponse(taskId);
        } else if (facType === constants.BROADCAST_FACTORY.PASTAR) {
            // TODO 目前没有
        } else {
            // TODO 移除队列？
            logger.error('无法识别的厂商类型：', facType);
        }
        return result;
    };

    /**
     * @param taskId 任务ID
     * @param data 发送的数据
     */
    var doResponse = function (taskId, data) {
        // 组装数据，通过MQ发送
        let headInfo = dataCache.getTaskHeadInfo(taskId);
        let resInfo = {};
        resInfo.header = {};
        resInfo.header.assetNo = headInfo.assetNo;
        resInfo.header.equipType = headInfo.equipType;
        resInfo.header.requestTime = headInfo.requestTime;
        resInfo.header.responseTime = new Date().getTime();
        resInfo.header.dataSource = headInfo.dataSource; // 原样返回
        resInfo.header.code = 200;
        resInfo.header.msg = 'OK';
        resInfo.data = {};

        let taskType = taskInfoMap.get(taskId).taskType;
        switch (taskType) {
            case operDefine.taskType.START_BROADCAST:
            case operDefine.taskType.STOP_BROADCAST:
            case operDefine.taskType.ADJUST_VOLUME:
            case operDefine.taskType.START_CALL:
            case operDefine.taskType.STOP_CALL:
            case operDefine.taskType.UPLOAD_FILE:
            case operDefine.taskType.ADD_PLAN:
            case operDefine.taskType.MODIFY_PLAN:
            case operDefine.taskType.DEL_PLAN:
            case operDefine.taskType.ADD_SESSION_DEV:
            case operDefine.taskType.DEL_SESSION_DEV:
                logger.info('获取到广播业务操作结果信息：[taskId:%s, info:%s]', taskId, JSON.stringify(data));
                // "Data0400503003"
                resInfo.header.optCmd = 'broadcast_data_9003';
                resInfo.data.optType = operDefine.getTaskTypeCode(taskType);
                resInfo.data.code = (data.operRet == 1) ? 200 : 100;
                break;
            case operDefine.taskType.DEVICE_STATUS:
            // 不可能走到这个分支
                break;
            case operDefine.taskType.QUERY_FILE:
            // 文件列表信息
                logger.info('获取到广播文件列表信息：[taskId:%s, info:%s]', taskId, JSON.stringify(data));
                // "Data0400503004"
                resInfo.header.optCmd = 'broadcast_data_9004';
                resInfo.data.fileResp = data.fileResp;
                break;
            case operDefine.taskType.ADD_DEVICE:
            case operDefine.taskType.UPDATE_DEVICE:
            case operDefine.taskType.DEL_DEVICE: {
                logger.info('获取到广播设备操作结果信息：[taskId:%s, info:%s]', taskId, JSON.stringify(data));
                // "Data0400503006"
                resInfo.header.optCmd = 'broadcast_data_9006';
                if (taskType == operDefine.taskType.ADD_DEVICE || taskType == operDefine.taskType.UPDATE_DEVICE) {
                    resInfo.data.devId = data.devId;
                } else {
                    resInfo.data.devId = '-1';
                }
                resInfo.data.code = (data.operRet == 1) ? 200 : 100;
                let errCode = Number(data.errCode);
                resInfo.data.msg = (data.operRet == 1) ? 'OK' : operDefine.getErrorDesc(errCode);
                break;
            }
            default:
                break;
        }

        // 发送MQ
        logger.info('通过MQ发送广播任务回复信息', JSON.stringify(resInfo));
        mqMgr.sendBusiDataForII(resInfo);
    };

    /**
     * 发送超时任务的响应数据
     * @param taskId 任务ID
     */
    var doTimeoutResponse = function (taskId) {
        // 组装数据，通过MQ发送
        let headInfo = dataCache.getTaskHeadInfo(taskId);
        let resInfo = {};
        resInfo.header = {};
        resInfo.header.assetNo = headInfo.assetNo;
        resInfo.header.equipType = headInfo.equipType;
        resInfo.header.requestTime = headInfo.requestTime;
        resInfo.header.responseTime = new Date().getTime();
        resInfo.header.dataSource = headInfo.dataSource;
        resInfo.header.code = 200;
        resInfo.header.msg = 'OK';
        resInfo.data = {};
        resInfo.data.code = 100;

        let taskType = taskInfoMap.get(taskId).taskType;
        if (taskType == operDefine.taskType.ADD_DEVICE
            || taskType == operDefine.taskType.UPDATE_DEVICE
            || taskType == operDefine.taskType.DEL_DEVICE) {
            resInfo.header.optCmd = 'broadcast_data_9006';
            resInfo.data.devId = '';
            resInfo.data.msg = '获取操作结果超时';
        } else {
            resInfo.header.optCmd = 'broadcast_data_9003';
            resInfo.data.optType = operDefine.getTaskTypeCode(taskType);
        }
        // 发送MQ
        logger.info('通过MQ发送广播任务响应超时信息', JSON.stringify(resInfo));
        mqMgr.sendBusiDataForII(resInfo);
    };

    /**
     * 检查任务是否超时
     * @param taskId
     * @return int 0未超时 1超时 2任务ID无效
     */
    var checkTaskTimeout = function (taskId) {
        let res = 0;
        let startTick = taskTickMap.get(taskId);
        if (startTick == null) {
            logger.error('无效的任务ID：', taskId);
            res = 2;
        } else {
            let taskInfo = taskInfoMap.get(taskId);
            if (taskInfo) {
                let curTick = new Date().getTime();
                if (taskInfo.taskType == operDefine.taskType.UPLOAD_FILE) {
                    // 判断上传文件任务是否超时由底层去判断
                    // res = ((curTick - startTick) > UPLOAD_FILE_TIMEOUT) ? 1 : 0;
                } else {
                    // 判断普通任务是否超时
                    res = ((curTick - startTick) > TASK_TIMEOUT) ? 1 : 0;
                }
            }
        }
        return res;
    };
}


// 单例
var processor = new AsyncTaskProcessor();
module.exports = processor;


