/**
 * 广播服务的共通操作结构定义
 * @author yaoxinyu
 * @date 2017/11/2
 */

var aebellError = require('../common/errorDefine').AEBELL;

/**
 * 定义任务类型枚举
 */
const TASK_TYPE = {
    START_BROADCAST: 1,         // 开始广播
    STOP_BROADCAST: 2,          // 停止广播
    QUERY_FILE: 3,              // 查询文件列表
    ADJUST_VOLUME: 4,           // 调整音量
    DEVICE_STATUS: 5,           // 设备状态推送
    START_CALL: 6,              // 开始喊话
    STOP_CALL: 7,               // 停止喊话
    ADD_DEVICE: 8,              // 添加设备——资产同步
    UPDATE_DEVICE: 9,           // 修改设备——资产同步
    DEL_DEVICE: 10,             // 删除设备——资产同步
    UPLOAD_FILE: 11,            // 上传文件
    ADD_PLAN: 12,               // 添加方案
    DEL_PLAN: 13,               // 删除方案
    MODIFY_PLAN: 14,            // 修改方案
    ADD_SESSION_DEV: 15,        // 添加会话设备
    DEL_SESSION_DEV: 16,        // 删除会话设备
};

/**
 * 定义错误码枚举
 */
const ErrorDefine = {
    UnknowError: -1,
    Succeed: 0,
    ServerDisConnect: 1,
    DBOperateError: 2,
    NoPermission: 3,
    CommandTimeout: 4,
    ServerCommandTimeout: 5,
    SessionNotFound: 6,
    SessionClosed: 7,
    UserOrPasswordError: 8,
    OnLoginState: 9,
    OnLogoutState: 10,
    LoginFailed: 11,
    QueryRangeError: 12,
    RecordNotExist: 13,
    FileNotFound: 14,
    FileNumOutofRange: 15,
    UploadFileExisted: 16,
    WriteUploadDataError: 17,
    WorkStatusError: 18,
    DeviceNotFound: 19,
    DeviceDisconnected: 20,
    DeviceTypeError: 21,
    CtrlDeviceBusy: 22,
    TalkDeviceBusy: 23,
    DeviceRestricted: 24,
    NoDeviceSetting: 25,
    NoAllocDevice: 26,
    BroadcastError: 27,
    TaskError: 28,
    TastNotFound: 29,
    PolicySuspended: 30,
    FunctionNoSupport: 31,
    AdmeasuredUser: 32,
    ExistingIP: 33,
    ExistingPhoneNo: 34,
    ExistingGroupNo: 35,
    ExistingName: 36,
    LicenseCodeError: 37,
    LicenseIsOld: 38,
    LicenseInValid: 39,
    FunctionRestricted: 40,
};

/**
 * 定义设备状态枚举
 */
const DEVICE_STATUS = {
    Disconnect: 1,       // 未接通
    Free: 2,             // 空闲
    CallWaiting: 3,      // 呼叫等待
    Ringing: 4,          // 正在响铃
    Calling: 5,          // 寻呼工作中
    Talking: 6,          // 对讲工作中
    Broadcasting: 7,     // 广播工作中
};

/**
 * 定义设备类型枚举
 */
const DEVICE_TYPE = {
    MEDIA: 1,             // 音频播放器
    CALL_TALK: 2,         // 对讲呼叫设备
    AID: 3,               // 一键求助器
    AID_PA: 4             // 平安求助器
};

/**
 * 定义广播任务基础信息
 */
function TaskBaseInfo() {
    this.taskId = 0;      // 任务ID
    this.taskType = 0;    // 任务类型，参照TASK_TYPE定义
    this.facType = '';    // 设备厂家类型
}

/**
 * 定义任务回复基础信息
 */
function RespondBaseInfo() {
    this.optType = 0;  // 任务类型，参照TASK_TYPE定义
    this.code = 0;     // 任务操作结果，100失败 200成功
}

/**
 * 定义查询文件列表回复信息
 */
function RespondFileInfo() {
    this.fileId = 0;     // 文件ID
    this.fileName = '';  // 文件名称，必须是UTF-8编码
}

/**
 * 定义增/删/改设备回复信息
 */
function RespondDevInfo() {
    this.devId = '';    // 广播设备的ID
    this.code = 0;      // 操作结果，100失败 200成功
    this.msg = '';      // 错误信息
}

/**
 * 定义设备状态推送信息
 */
function AutoDeviceInfo() {
    this.deviceIP = '';      // 设备IP
    this.status = 0;         // 设备状态 参照DEVICE_STATUS
}

/**
 * 定义广播服务连接信息
 */
function LoginInfo() {
    this.IP = '';           // 广播服务IP
    this.port = 0;          // 广播服务端口
    this.userName = '';     // 登录用户名
    this.passwd = '';       // 登录密码

    /**
     * 赋值函数
     * @param {Object} loginInfo
     */
    this.copyValue = function (loginInfo) {
        this.IP = loginInfo.IP;
        this.port = loginInfo.port;
        this.userName = loginInfo.userName;
        this.passwd = loginInfo.password;
    };
}

/**
 * 定义广播操作信息
 */
function BroadcastOperInfo() {
    this.arraySrc = [];    // 播放文件ID，数组类型
    this.arrayDst = [];    // 目标设备IP，数组类型
    this.uVolume = 0;      // 广播音量
}

/**
 * 定义喊话操作信息
 */
function CallOperInfo() {
    this.src = '';       // 喊话源设备IP
    this.dst = [];       // 喊话目标设备IP，数组类型
    this.uVolume = 0;    // 喊话音量
}

/**
 * 定义音量控制操作信息
 */
function VolumeControlInfo() {
    this.dst = '';    // 音量调整目标设备IP
    this.uVolume = 0; // 调整的音量大小
}

/**
 * 定义添加/修改设备操作信息
 */
function AddDevOperInfo() {
    this.devCode = '';      // 资产编号
    this.devName = '';      // 设备名称（资产名称）
    this.devType = 0;       // 设备类型，参照DEVICE_TYPE枚举
    this.devIP = '';        // 设备IP地址
    this.devId = '';        // 广播设备Id，修改设备信息时使用
}

/**
 * 定义删除设备操作信息
 */
function DelDevOperInfo() {
    this.devCode = '';      // 资产编号
    this.devId = '';        // 广播设备Id
}

/**
 * 定义文件上传操作信息
 */
function UploadFileOperInfo() {
    this.fileName = '';   // 文件名（包括后缀名），需转成UTF-8编码
    this.fileType = 0;    // 文件类型：0广播文件 1告警文件
    this.fileSize = 0;    // 文件大小：字节
    this.filePath = '';   // 文件上传到的服务器路径
}

/**
 * 定义方案中的广播定时任务信息
 */
function TimerBroadcastInfo() {
    // 任务基本信息
    this.taskName = '';        // 任务名称（UTF8编码）
    // 任务执行时间信息
    this.strBeginTime;					// 定时开始日期  字符串格式
    this.strEndTime;					// 定时结束日期	字符串格式
    this.strDoworkTime;				    // 每次开始的具体时间  字符串格式
    this.nCycleMode;				    // 循环模式：1每天 2每周 3每月
    this.strTaskRunDate;				// 每周0到6表示周日到周六；每月为1－31天；多天使用“,”分隔
    this.strTaskFinishTime;				// 任务的具体结束时间 字符串格式
    // 设备列表信息
    this.devList = [];         // 设备列表，数组，元素为IP
    // 文件列表信息
    this.fileList = [];        // 文件列表，数组，元素为文件ID
    // 播放模式信息
    this.playMode;			   // 播放模式 0单曲、1单曲循环、2顺序、3循环、4随机
    this.replayTimes;		   // 播放次数，0表示连续
    this.playDuration;		   // 播放持续时间(秒)0表示不使用
}

/**
 * 定义添加/修改方案操作信息
 */
function AddUpdatePlanOperInfo() {
    this.planName = '';     // 方案名称（UTF8编码）
    this.taskList = [];     // 方案下面的任务列表，数组成员为TimerBroadcastInfo
}

/**
 * 定义删除方案操作信息
 */
function DelPlanOperInfo() {
    this.planName = '';   // 方案名称（UTF8编码）
}

/**
 * 定义添加/删除会话设备操作信息
 */
function SessionDevOperInfo() {
    this.sessionDevIP = '';    // 会话中设备IP
    this.devIP = '';           // 添加/删除的设备IP
}

/**
 * 定义任务操作信息（执行任务+停止任务）
 */
function TaskOperInfo() {
    this.planName = '';    // 方案名称（UTF8编码）
    this.taskName = '';    // 任务名称（UTF8编码）
}

/**
 * 获取对应任务类型的名称，方便查看日志信息
 * @param taskType 任务类型枚举 参照TASK_TYPE
 * @return {string} 任务类型名称
 */
function getTaskTypeName(taskType) {
    switch (taskType) {
        case TASK_TYPE.START_BROADCAST:
            return '开始广播';
        case TASK_TYPE.STOP_BROADCAST:
            return '停止广播';
        case TASK_TYPE.QUERY_FILE:
            return '查询文件';
        case TASK_TYPE.ADJUST_VOLUME:
            return '调整音量';
        case TASK_TYPE.DEVICE_STATUS:
            return '设备状态';
        case TASK_TYPE.START_CALL:
            return '开始喊话';
        case TASK_TYPE.STOP_CALL:
            return '停止喊话';
        case TASK_TYPE.ADD_DEVICE:
            return '添加设备';
        case TASK_TYPE.UPDATE_DEVICE:
            return '修改设备';
        case TASK_TYPE.DEL_DEVICE:
            return '删除设备';
        case TASK_TYPE.UPLOAD_FILE:
            return '上传文件';
        case TASK_TYPE.ADD_PLAN:
            return '添加方案';
        case TASK_TYPE.DEL_PLAN:
            return '删除方案';
        case TASK_TYPE.MODIFY_PLAN:
            return '修改方案';
        case TASK_TYPE.ADD_SESSION_DEV:
            return '添加会话设备';
        case TASK_TYPE.DEL_SESSION_DEV:
            return '删除会话设备';
        default:
            return '未知任务';
    }
}

/**
 * 获取回复操作类型的code值，外部协议和内部协议数据格式的映射
 * @param taskType 任务类型枚举 参照TASK_TYPE
 * @return {string} 任务类型code
 */
function getTaskTypeCode(taskType) {
    switch (taskType) {
        case TASK_TYPE.START_BROADCAST:
            return '01';
        case TASK_TYPE.STOP_BROADCAST:
            return '02';
        case TASK_TYPE.START_CALL:
            return '03';
        case TASK_TYPE.STOP_CALL:
            return '04';
        case TASK_TYPE.QUERY_FILE:
            return '05';
        case TASK_TYPE.ADJUST_VOLUME:
            return '06';
        case TASK_TYPE.UPLOAD_FILE:
            return '07';
        case TASK_TYPE.ADD_PLAN:
            return '08';
        case TASK_TYPE.DEL_PLAN:
            return '09';
        case TASK_TYPE.MODIFY_PLAN:
            return '10';
        case TASK_TYPE.ADD_SESSION_DEV:
            return '11';
        case TASK_TYPE.DEL_SESSION_DEV:
            return '12';
        default:
            return '00';
    }
}

/**
 * 获取回复操作类型的code值
 * @param optCmd 任务类型枚举 参照TASK_TYPE
 * @param reqOptType 请求中的optType
 * @return {string} optType
 */
function getResOptType(optCmd, reqOptType) {
    let resOptType = '00';
    switch (optCmd) {
        case 'broadcast_param_9003':
            if (reqOptType == '01') {
            // 开始广播
                resOptType = '01';
            } else if (reqOptType == '02') {
            // 停止广播
                resOptType = '02';
            } else if (reqOptType == '03') {
            // 查询文件列表
                resOptType = '05';
            } else if (reqOptType == '04') {
            // 调整音量
                resOptType = '06';
            }
            break;
        case 'broadcast_param_9004':
            if (reqOptType == '01') {
            // 开始喊话
                resOptType = '03';
            } else if (reqOptType == '02') {
            // 停止喊话
                resOptType = '04';
            }
            break;
        case 'broadcast_param_9007':
        // 上传文件
            resOptType = '07';
            break;
        case 'broadcast_param_9008':
            if (reqOptType == '01') {
            // 添加方案
                resOptType = '08';
            } else if (reqOptType == '02') {
            // 修改方案
                resOptType = '10';
            }
            break;
        case 'broadcast_param_9009':
        // 删除方案
            resOptType = '09';
            break;
        case 'broadcast_param_9010':
            if (reqOptType == '01') {
            // 添加会话设备
                resOptType = '11';
            } else if (reqOptType == '02') {
            // 删除会话设备
                resOptType = '12';
            }
            break;
        default:
            break;
    }

    return resOptType;
}

/**
 * 获取错误码描述
 * @param errCode 美电贝尔错误码 数值类型
 * @return {string} 错误码描述
 */
function getErrorDesc(errCode) {
    switch (errCode) {
        case ErrorDefine.UnknowError:
            return aebellError.UnknowError;
        case ErrorDefine.Succeed:
            return aebellError.Succeed;
        case ErrorDefine.ServerDisConnect:
            return aebellError.ServerDisConnect;
        case ErrorDefine.DBOperateError:
            return aebellError.DBOperateError;
        case ErrorDefine.NoPermission:
            return aebellError.NoPermission;
        case ErrorDefine.CommandTimeout:
            return aebellError.CommandTimeout;
        case ErrorDefine.ServerCommandTimeout:
            return aebellError.ServerCommandTimeout;
        case ErrorDefine.SessionNotFound:
            return aebellError.SessionNotFound;
        case ErrorDefine.SessionClosed:
            return aebellError.SessionClosed;
        case ErrorDefine.UserOrPasswordError:
            return aebellError.UserOrPasswordError;
        case ErrorDefine.OnLoginState:
            return aebellError.OnLoginState;
        case ErrorDefine.OnLogoutState:
            return aebellError.OnLogoutState;
        case ErrorDefine.LoginFailed:
            return aebellError.LoginFailed;
        case ErrorDefine.QueryRangeError:
            return aebellError.QueryRangeError;
        case ErrorDefine.RecordNotExist:
            return aebellError.RecordNotExist;
        case ErrorDefine.FileNotFound:
            return aebellError.FileNotFound;
        case ErrorDefine.FileNumOutofRange:
            return aebellError.FileNumOutofRange;
        case ErrorDefine.UploadFileExisted:
            return aebellError.UploadFileExisted;
        case ErrorDefine.WriteUploadDataError:
            return aebellError.WriteUploadDataError;
        case ErrorDefine.WorkStatusError:
            return aebellError.WorkStatusError;
        case ErrorDefine.DeviceNotFound:
            return aebellError.DeviceNotFound;
        case ErrorDefine.DeviceDisconnected:
            return aebellError.DeviceDisconnected;
        case ErrorDefine.DeviceTypeError:
            return aebellError.DeviceTypeError;
        case ErrorDefine.CtrlDeviceBusy:
            return aebellError.CtrlDeviceBusy;
        case ErrorDefine.TalkDeviceBusy:
            return aebellError.TalkDeviceBusy;
        case ErrorDefine.DeviceRestricted:
            return aebellError.DeviceRestricted;
        case ErrorDefine.NoDeviceSetting:
            return aebellError.NoDeviceSetting;
        case ErrorDefine.NoAllocDevice:
            return aebellError.NoAllocDevice;
        case ErrorDefine.BroadcastError:
            return aebellError.BroadcastError;
        case ErrorDefine.TaskError:
            return aebellError.TaskError;
        case ErrorDefine.TastNotFound:
            return aebellError.TastNotFound;
        case ErrorDefine.PolicySuspended:
            return aebellError.PolicySuspended;
        case ErrorDefine.FunctionNoSupport:
            return aebellError.FunctionNoSupport;
        case ErrorDefine.AdmeasuredUser:
            return aebellError.AdmeasuredUser;
        case ErrorDefine.ExistingIP:
            return aebellError.ExistingIP;
        case ErrorDefine.ExistingPhoneNo:
            return aebellError.ExistingPhoneNo;
        case ErrorDefine.ExistingGroupNo:
            return aebellError.ExistingGroupNo;
        case ErrorDefine.ExistingName:
            return aebellError.ExistingName;
        case ErrorDefine.LicenseCodeError:
            return aebellError.LicenseCodeError;
        case ErrorDefine.LicenseIsOld:
            return aebellError.LicenseIsOld;
        case ErrorDefine.LicenseInValid:
            return aebellError.LicenseInValid;
        case ErrorDefine.FunctionRestricted:
            return aebellError.FunctionRestricted;
        default:
            return '未知错误';
    }
}


// 任务操作信息
var operInfo = {};
operInfo.loginInfo = new LoginInfo();                   // 广播服务登录信息
operInfo.broadcastInfo = new BroadcastOperInfo();       // 广播操作信息
operInfo.callInfo = new CallOperInfo();                 // 喊话操作信息
operInfo.volumeInfo = new VolumeControlInfo();          // 音量调整操作信息
operInfo.addDevInfo = new AddDevOperInfo();             // 添加/修改设备操作信息
operInfo.delDevInfo = new DelDevOperInfo();             // 删除设备操作信息
operInfo.fileUploadInfo = new UploadFileOperInfo();     // 上传文件操作信息
operInfo.addPlanInfo = new AddUpdatePlanOperInfo();     // 添加/修改方案操作信息
operInfo.delPlanInfo = new DelPlanOperInfo();           // 删除方案操作信息
operInfo.runStopTaskInfo = new TaskOperInfo();          // 执行/停止任务操作信息
operInfo.timerTaskInfo = new TimerBroadcastInfo();      // 广播定时任务信息
operInfo.sessionDevInfo = new SessionDevOperInfo();     // 添加/删除会话中设备信息

// 任务回复信息
var respondInfo = {};
respondInfo.baseInfo = new RespondBaseInfo();      // 基础回复信息
respondInfo.fileInfo = new RespondFileInfo();      // 文件信息
respondInfo.devInfo = new RespondDevInfo();        // 增/删/改设备操作回复信息
respondInfo.devStatusInfo = new AutoDeviceInfo();  // 设备状态信息


module.exports = {
    taskType: TASK_TYPE,
    devStatus: DEVICE_STATUS,
    operInfo: operInfo,
    respondInfo: respondInfo,
    taskBaseInfo: TaskBaseInfo,             // 任务基础信息
    getTaskTypeName: getTaskTypeName,
    getTaskTypeCode: getTaskTypeCode,
    getResOptType: getResOptType,
    getErrorDesc: getErrorDesc
};