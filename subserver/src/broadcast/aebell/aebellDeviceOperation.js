/**
 * 美电贝尔广播设备操作模块，功能描述：
 * 1、调用底层C++扩展模块接口实现对应操作
 * 2、对外提供设备操作接口；
 * @author yaoxinyu
 * @date 2017/10/31
 */

var commonModule = require('../../commonModuleExport');
// 日志模块
const logServer = commonModule.logger.getLogger(0);
const logRequest = commonModule.logger.getLogger(1);
var globalData = require('../../globalDataCache');
// 任务操作结构定义模块
var operDefine = require('../broadcastOperDefine');
// 美电贝尔广播C++扩展模块
var aebellOper = require('./build/Release/aebellBroadcast');


/**
 * 美电贝尔设备操作类
 */
function AebellDeviceOper() {
    // 登录信息
    var loginInfo = operDefine.operInfo.loginInfo;
    // 是否已登录
    var isLogin = false;
    // 是否已注册设备状态回调函数
    var isRegisterCB = false;
    // 重连次数
    var retryCount = 0;

    /**
     * 美电贝尔广播服务连接失败时进行重连
     */
    var reConnect = function () {
        // 前5次重试，间隔一分钟，后续重试间隔为5分钟
        retryCount++;
        logServer.info('重连美电贝尔广播服务，当前重连次数[%s]', retryCount);
        if (retryCount <= 5) {
            setTimeout(login, 60000);
        } else {
            setTimeout(login, 300000);
        }
    };

    /**
     * 通过读取本地配置文件初始化连接信息
     */
    this.init = function () {
        // 加载dll
        aebellOper.startModule();
        // 读取美电贝尔配置信息
        try {
            let configData = globalData.getConfigData();
            configData = JSON.parse(JSON.stringify(configData));
            let jsonData = configData.broadcastConfig;
            loginInfo.copyValue(jsonData);
            login();
        }
        catch (exception) {
            logServer.error('读取美电贝尔配置信息异常：', exception.message);
        }
    };

    /**
     * 判断是否已登录
     * @return {boolean}
     */
    this.isLogined = function () {
        return isLogin;
    };

    /**
     * 登录服务
     */
    var login = function () {
        if (isLogin) {
            logServer.info('美电贝尔广播服务已登录！');
            return;
        }
        if (loginInfo) {
            isLogin = aebellOper.login(loginInfo);
            if (isLogin && !isRegisterCB) {
                registerDeviceStatusCB();
            }
        }
        let result = isLogin ? '成功' : '失败';
        logServer.info('登录美电贝尔广播服务:' + result);
        if (!isLogin) {
            // 重连广播服务
            reConnect();
        } else {
            retryCount = 0;
        }
    };

    /**
     * 断开连接
     */
    this.logout = function () {
        if (isLogin) {
            let result = aebellOper.logout() ? '成功' : '失败';
            isLogin = false;
            logServer.info('断开美电贝尔广播服务连接:' + result);
        }
        else {
            logServer.info('美电贝尔广播服务未连接！');
        }
    };

    /**
     * 开始广播
     * @param taskId 任务ID
     * @param broadcastInfo 广播信息
     */
    this.startBroadcast = function (taskId, broadcastInfo) {
        logRequest.debug('开始广播请求：[任务ID:%s, 任务信息:%s]...', taskId, JSON.stringify(broadcastInfo));
        aebellOper.startBroadcast(taskId, broadcastInfo);
    };

    /**
     * 停止广播
     * @param taskId 任务ID
     * @param dstIP 目标设备IP
     */
    this.stopBroadcast = function (taskId, dstIP) {
        logRequest.debug('停止广播请求：[任务ID:%s, 设备IP:%s]...', taskId, dstIP);
        aebellOper.stopBroadcast(taskId, dstIP);
    };

    /**
     * 查询文件列表
     * @param taskId 任务ID
     */
    this.queryAllFile = function (taskId) {
        logRequest.debug('查询文件列表请求：[任务ID:%s]...', taskId);
        aebellOper.queryAllFile(taskId);
    };

    /**
     * 调整设备音量
     * @param taskId 任务ID
     * @param volumeInfo 音量信息
     */
    this.adjustVolume = function (taskId, volumeInfo) {
        logRequest.debug('调整设备音量请求：[任务ID:%s, 任务信息:%s]...', taskId, JSON.stringify(volumeInfo));
        aebellOper.adjustVolume(taskId, volumeInfo);
    };

    /**
     * 开始喊话
     * @param taskId 任务ID
     * @param callInfo 喊话信息
     */
    this.startCall = function (taskId, callInfo) {
        logRequest.debug('开始喊话请求：[任务ID:%s, 任务信息:%s]...', taskId, JSON.stringify(callInfo));
        aebellOper.startCall(taskId, callInfo);
    };

    /**
     * 停止喊话
     * @param taskId 任务ID
     * @param dstIP 目标设备IP
     */
    this.stopCall = function (taskId, dstIP) {
        logRequest.debug('停止喊话请求：[任务ID:%s, 设备IP:%s]...', taskId, dstIP);
        aebellOper.stopCall(taskId, dstIP);
    };

    /**
     * 添加设备
     * @param taskId 任务ID
     * @param deviceInfo 设备信息
     */
    this.addDevice = function (taskId, deviceInfo) {
        logRequest.debug('添加设备请求：[任务ID:%s, 任务信息:%s]...', taskId, JSON.stringify(deviceInfo));
        aebellOper.addDevice(taskId, deviceInfo);
    };

    /**
     * 修改设备
     * @param taskId 任务ID
     * @param deviceInfo 设备信息
     */
    this.updateDevice = function (taskId, deviceInfo) {
        logRequest.debug('修改设备请求：[任务ID:%s, 任务信息:%s]...', taskId, JSON.stringify(deviceInfo));
        aebellOper.updateDevice(taskId, deviceInfo);
    };

    /**
     * 删除设备
     * @param taskId 任务ID
     * @param devInfo 删除的设备信息
     */
    this.delDevice = function (taskId, devInfo) {
        logRequest.debug('删除设备请求：[任务ID:%s, 设备信息:%s]...', taskId, JSON.stringify(devInfo));
        aebellOper.delDevice(taskId, devInfo.devId);
    };

    /**
     * 上传文件
     * @param taskId 任务ID
     * @param uploadInfo 上传的文件信息
     */
    this.uploadFile = function (taskId, uploadInfo) {
        logRequest.debug('上传文件请求：[任务ID=%s,文件名=%s]...', taskId, uploadInfo.fileName);
        aebellOper.uploadFile(taskId, uploadInfo);
    };

    /**
     * 添加方案
     * @param taskId
     * @param planOperInfo
     */
    this.addPlan = function (taskId, planOperInfo) {
        logRequest.debug('添加方案请求：[任务ID=%s,方案信息=%s]...', taskId, JSON.stringify(planOperInfo));
        aebellOper.addPlan(taskId, planOperInfo);
    };

    /**
     * 修改方案
     * @param taskId
     * @param planOperInfo
     */
    this.updatePlan = function (taskId, planOperInfo) {
        logRequest.debug('修改方案请求：[任务ID=%s,方案信息=%s]...', taskId, JSON.stringify(planOperInfo));
        aebellOper.updatePlan(taskId, planOperInfo);
    };

    /**
     * 删除方案
     * @param taskId
     * @param planOperInfo
     */
    this.delPlan = function (taskId, planOperInfo) {
        logRequest.debug('删除方案请求：[任务ID=%s,方案名称=%s]...', taskId, planOperInfo.planName);
        aebellOper.delPlan(taskId, planOperInfo);
    };

    /**
     * 添加会话中的设备
     * @param taskId
     * @param SessionDevOperInfo
     */
    this.addSessionDev = function (taskId, SessionDevOperInfo) {
        logRequest.debug('添加会话设备请求：[任务ID=%s,添加设备IP=%s]...', taskId, SessionDevOperInfo.devIP);
        aebellOper.addSessionDev(taskId, SessionDevOperInfo);
    };

    /**
     * 删除会话中的设备
     * @param taskId
     * @param SessionDevOperInfo
     */
    this.delSessionDev = function (taskId, SessionDevOperInfo) {
        logRequest.debug('删除会话设备请求：[任务ID=%s,删除设备IP=%s]...', taskId, SessionDevOperInfo.devIP);
        aebellOper.delSessionDev(taskId, SessionDevOperInfo);
    };

    /**
     * 注册设备状态推送回调函数
     */
    var registerDeviceStatusCB = function () {
        if (!isRegisterCB) {
            logServer.debug('注册美电贝尔设备状态推送回调######');
            aebellOper.registerDeviceStatusCB();
            isRegisterCB = true;
        }
    };
}

// 对象初始化时就去连接美电贝尔广播服务
var aebellDevOper = new AebellDeviceOper();
aebellDevOper.init();


module.exports = aebellDevOper;
