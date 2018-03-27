/**
 * @file 错误定义
 * @author yaoxinyu
 * @date 2017/9/18
 */

const errorDefine = {
    /**
     * 文件操作
     */
    FILE_NOT_EXIST: '文件不存在',

    /**
     * 美电贝尔dll操作
     */
    AEBELL: {
        UnknowError: '未知错误',
        Succeed: '成功',
        ServerDisConnect: '服务未连接',
        DBOperateError: '数据库操作失败',
        NoPermission: '没有权限',
        CommandTimeout: '指令执行超时',
        ServerCommandTimeout: '服务器指令超时',
        SessionNotFound: '找不到会话',
        SessionClosed: '会话已终止',
        UserOrPasswordError: '用户或密码错误',
        OnLoginState: '设备已处于登录状态',
        OnLogoutState: '已登出状态',
        LoginFailed: '登录失败',
        QueryRangeError: '查询范围有误',
        RecordNotExist: '记录不存在',
        FileNotFound: '文件不存在',
        FileNumOutofRange: '文件数量超出范围',
        UploadFileExisted: '上传文件已存在',
        WriteUploadDataError: '写上传文件出错',
        WorkStatusError: '工作状态出错',
        DeviceNotFound: '没有找到设备',
        DeviceDisconnected: '设备未连接',
        DeviceTypeError: '设备类型出错或不匹配',
        CtrlDeviceBusy: '控制设备忙',
        TalkDeviceBusy: '通话设备忙',
        DeviceRestricted: '设备受限',
        NoDeviceSetting: '接入设备还没有配置',
        NoAllocDevice: '没有分配设备',
        BroadcastError: '广播出错',
        TaskError: '任务失败',
        TastNotFound: '任务不存在',
        PolicySuspended: '方案已挂起',
        FunctionNoSupport: '不支持的功能',
        AdmeasuredUser: '该角色已分配给用户',
        ExistingIP: '已分配ip',
        ExistingPhoneNo: '已分配区号',
        ExistingGroupNo: '已分配设备组号',
        ExistingName: '名称已存在',
        LicenseCodeError: '授权码有误',
        LicenseIsOld: '授权证书较旧',
        LicenseInValid: '授权证书已无效',
        FunctionRestricted: '功能受限',
    },

    DB: {
        QUERY_EXCEPTION: '查询异常:',
        INSERTION_EXCEPTION: '插入异常:',
        UPDATE_ANOMALY: '更新异常:',
        DELETE_EXCEPTION: '删除异常:',
        QUERY_ERROR: '查询错误:',
        INSERTION_ERROR: '插入错误:',
        UPDETE_ERROR: '更新错误:',
        DELETE_ERROR: '删除错误:',
        CONNECTION_FAIL: '连接失败:',
    }
};


module.exports = errorDefine;