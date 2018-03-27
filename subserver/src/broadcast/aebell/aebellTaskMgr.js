/**
 * 广播业务管理器模块，功能描述：
 * 1、对外导出采用工厂模式创建一个新对象；
 * 2、根据任务类型，开启对应任务；
 * 3、采用轮巡方式监听异步操作的回调结果，并将结果发送
 * @author yaoxinyu
 * @date 2017/10/31
 */

var commonModule = require('../../commonModuleExport');
// 日志模块
// const logger = commonModule.logger.getLogger(0);
// 常量模块
const contants = commonModule.constants;
// 任务操作结构定义模块
var operDefine = require('../broadcastOperDefine');
// 任务ID生成器模块
var taskIdGen = require('../taskIdGenerator');
// 美电贝尔设备操作模块
var aebellOper = require('./aebellDeviceOperation');


/**
 * 定义美电贝尔广播任务管理类
 */
function AebellTaskMgr() {
    /**
     * 生成任务信息
     * @param taskType
     */
    var generateTaskInfo = function (taskType) {
        let taskInfo = new operDefine.taskBaseInfo();
        taskInfo.taskId = taskIdGen.generateTaskId();
        taskInfo.taskType = taskType;
        taskInfo.facType = contants.BROADCAST_FACTORY.AEBELL;

        return taskInfo;
    };

    /**
     * 注册设备状态推送回调接口
     */
    // this.RegisterAutoDevStatus = function () {
    //     if (aebellOper.isAlreadLogin()) {
    //         aebellOper.registerDeviceStatusCB();
    //     }
    // };

    /**
     * 查询文件列表
     * @return {object} taskInfo
     */
    this.queryAllFile = function () {
        let taskInfo = generateTaskInfo(operDefine.taskType.QUERY_FILE);
        aebellOper.queryAllFile(taskInfo.taskId);

        return taskInfo;
    };

    /**
     * 开始广播
     * @param broadcastInfo 广播任务信息
     * @return {object} taskInfo
     */
    this.startBroadcast = function (broadcastInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.START_BROADCAST);
        aebellOper.startBroadcast(taskInfo.taskId, broadcastInfo);

        return taskInfo;
    };

    /**
     * 停止广播
     * @param dstIP 停止目标设备IP
     * @return {object} taskInfo
     */
    this.stopBroadcast = function (dstIP) {
        let taskInfo = generateTaskInfo(operDefine.taskType.STOP_BROADCAST);
        aebellOper.stopBroadcast(taskInfo.taskId, dstIP);

        return taskInfo;
    };

    /**
     * 开始喊话
     * @param callInfo 喊话任务信息
     * @return {object} taskInfo
     */
    this.startCall = function (callInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.START_CALL);
        aebellOper.startCall(taskInfo.taskId, callInfo);

        return taskInfo;
    };

    /**
     * 停止喊话
     * @param dstIP 停止目标设备IP
     * @return {object} taskInfo
     */
    this.stopCall = function (dstIP) {
        let taskInfo = generateTaskInfo(operDefine.taskType.STOP_CALL);
        aebellOper.stopCall(taskInfo.taskId, dstIP);

        return taskInfo;
    };

    /**
     * 调整音量
     * @param volumeInfo
     * @return {object} taskInfo
     */
    this.adjustVolume = function (volumeInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.ADJUST_VOLUME);
        aebellOper.adjustVolume(taskInfo.taskId, volumeInfo);

        return taskInfo;
    };

    /**
     * 添加设备
     * @param devInfo
     * @return {object} taskInfo
     */
    this.addDevice = function (devInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.ADD_DEVICE);
        aebellOper.addDevice(taskInfo.taskId, devInfo);

        return taskInfo;
    };

    /**
     * 修改设备
     * @param devInfo
     * @return {object} taskInfo
     */
    this.updateDevice = function (devInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.UPDATE_DEVICE);
        aebellOper.updateDevice(taskInfo.taskId, devInfo);

        return taskInfo;
    };

    /**
     * 删除设备
     * @param devInfo
     * @return {object} taskInfo
     */
    this.delDevice = function (devInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.DEL_DEVICE);
        aebellOper.delDevice(taskInfo.taskId, devInfo);

        return taskInfo;
    };

    /**
     * 上传文件
     * @param uploadInfo
     * @return {object} taskInfo
     */
    this.uploadFile = function (uploadInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.UPLOAD_FILE);
        aebellOper.uploadFile(taskInfo.taskId, uploadInfo);

        return taskInfo;
    };

    /**
     * 添加/修改方案
     * @param PlanOperInfo
     * @param operType 1添加 2修改
     */
    this.addOrUpdatePlan = function (planOperInfo, operType) {
        let taskInfo;
        if (1 == operType) {
            taskInfo = generateTaskInfo(operDefine.taskType.ADD_PLAN);
            aebellOper.addPlan(taskInfo.taskId, planOperInfo);
        } else if (2 == operType) {
            taskInfo = generateTaskInfo(operDefine.taskType.MODIFY_PLAN);
            aebellOper.updatePlan(taskInfo.taskId, planOperInfo);
        }

        return taskInfo;
    };

    /**
     * 删除方案
     * @param planOperInfo
     */
    this.delPlan = function (planOperInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.DEL_PLAN);
        aebellOper.delPlan(taskInfo.taskId, planOperInfo);

        return taskInfo;
    };

    /**
     * 添加会话中的设备
     * @param SessionDevOperInfo
     */
    this.addSessionDev = function (SessionDevOperInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.ADD_SESSION_DEV);
        aebellOper.addSessionDev(taskInfo.taskId, SessionDevOperInfo);

        return taskInfo;
    };

    /**
     * 删除会话中的设备
     * @param SessionDevOperInfo
     */
    this.delSessionDev = function (SessionDevOperInfo) {
        let taskInfo = generateTaskInfo(operDefine.taskType.DEL_SESSION_DEV);
        aebellOper.delSessionDev(taskInfo.taskId, SessionDevOperInfo);

        return taskInfo;
    };
}


/**
 * 外部引用时创建新实例
 * @return {AebellTaskMgr}
 */
function createInstance() {
    return new AebellTaskMgr();
}


module.exports = createInstance();




