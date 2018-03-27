/**
 * 本模块为node中C++扩展模块，用于调用美电贝尔广播dll接口
 * Created by yaoxinyu on 2017/9/19.
 * modify by yaoxinyu on 2017/11/6.
 */

#include "AebellBroadcast.h"
#include "AebellBusiThread.h"
#include "AebellUploadThread.h"


/*********************************************************************************/
/********************************对外导出接口**************************************/
/*********************************************************************************/
// 启动模块
void startModule(const FunctionCallbackInfo<Value>& args) {
    CAEBELLBusiThread::GetInstance().startModule();
}

// 停止模块
void stopModule(const FunctionCallbackInfo<Value>& args) {
    CAEBELLBusiThread::GetInstance().stopModule();
}

/**
 * 登录美电贝尔广播服务
 * @param args[0] 登录信息
 */
void login(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // 外部传入的连接信息, 使用Cast方法来转换
    Local<Object> loginInfo = Local<Object>::Cast(args[0]);
    // 用户名
    Local<String> userName = Local<String>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "userName")));
    std::string strName = std::string(*(v8::String::Utf8Value(userName)));
    // 密码
    Local<String> passwd = Local<String>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "passwd")));
    std::string strPasswd = std::string(*(v8::String::Utf8Value(passwd)));
    // IP
    Local<String> IP = Local<String>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "IP")));
    std::string strIP = std::string(*(v8::String::Utf8Value(IP)));
    // 端口
    Local<Uint32> port = Local<Uint32>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "port")));
    unsigned int iPort = port->Uint32Value();

    // 连接
   LOGIN_REQUEST loginReq;
   loginReq.strName = strName;
   loginReq.strPwd = strPasswd;
   loginReq.strGUID = "";
   loginReq.uID = 0;
   loginReq.bIsNewID = true;
   printf("LoginInfo:IP[%s],port[%d],userName[%s],password[%s]\n", strIP.c_str(), iPort, strName.c_str(),
        strPasswd.c_str());

    // 外部函数调用返回值
    bool bRes = CAEBELLBusiThread::GetInstance().login(strIP, iPort, loginReq);
    args.GetReturnValue().Set(bRes);
}

/**
 * 退出
 */
void logout(const FunctionCallbackInfo<Value>& args) {
    bool bRes = CAEBELLBusiThread::GetInstance().logout();
    args.GetReturnValue().Set(bRes);
}

/**
 * 查询文件列表
 * @param args[0] taskId
 */
void queryAllFile(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    printf("query file taskId[%u]\n", uTaskId->Uint32Value());
    CAEBELLBusiThread::GetInstance().queryAllFileTask(uTaskId->Uint32Value());
}

/**
 * 注册设备状态推送回调函数
 */
void registerDevStatusCB(const FunctionCallbackInfo<Value>& args) {
    CAEBELLBusiThread::GetInstance().registerDevStatusCB();
}

/**
 * 开始广播
 * @param args[0] taskId
 * @param args[1] 广播操作信息
 */
void startBroadcast(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // 外部传入的广播信息, 使用Cast方法来转换
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<Object> broadInfo = Local<Object>::Cast(args[1]);
    // 广播源文件ID
    Local<Array> arrSrcID = Local<Array>::Cast(broadInfo->Get(String::NewFromUtf8(isolate, "arraySrc")));
    // 广播目标设备IP
    Local<Array> arrDstIP = Local<Array>::Cast(broadInfo->Get(String::NewFromUtf8(isolate, "arrayDst")));
    // 广播音量
    Local<Uint32> broadVolume = Local<Uint32>::Cast(broadInfo->Get(String::NewFromUtf8(isolate, "uVolume")));

    BroadcastOperInfo operInfo;
    operInfo.uVolume = broadVolume->Uint32Value();
    for (int i=0; i != arrSrcID->Length(); ++i)
    {
        Local<String> temp = Local<String>::Cast(arrSrcID->Get(i));
        std::string strSrcID = std::string(*(v8::String::Utf8Value(temp)));
        operInfo.arraySrc.push_back(atoll(strSrcID.c_str()));
        printf("Broadcast src fileID:%s\n", strSrcID.c_str());
    }
    for (int i=0; i != arrDstIP->Length(); ++i)
    {
        Local<String> temp = Local<String>::Cast(arrDstIP->Get(i));
        std::string strDstIP = std::string(*(v8::String::Utf8Value(temp)));
        operInfo.arrayDst.push_back(strDstIP);
        printf("Broadcast dst deviceIP:%s\n", strDstIP.c_str());
    }
    printf("BroadcastInfo:volume[%u]\n", broadVolume->Uint32Value());

    CAEBELLBusiThread::GetInstance().startBroadcastTask(uTaskId->Uint32Value(), operInfo);
}

/**
 * 开始喊话
 * @param args[0] taskId
 * @param args[1] 喊话操作信息
 */
void startCall(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的广播信息, 使用Cast方法来转换
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<Object> callInfo = Local<Object>::Cast(args[1]);
    // 喊话源设备IP
    Local<String> srcIP = Local<String>::Cast(callInfo->Get(String::NewFromUtf8(isolate, "src")));
    // 喊话目标设备IP
    Local<Array> arrDstIP = Local<Array>::Cast(callInfo->Get(String::NewFromUtf8(isolate, "dst")));
    // 喊话音量
    Local<Uint32> callVolume = Local<Uint32>::Cast(callInfo->Get(String::NewFromUtf8(isolate, "uVolume")));

    CallOperInfo operInfo;
    std::string strSrcIP = std::string(*(v8::String::Utf8Value(srcIP)));
    operInfo.src = strSrcIP;
    printf("Call src deviceIP:%s\n", strSrcIP.c_str());
    for (int i=0; i != arrDstIP->Length(); ++i)
    {
        Local<String> temp = Local<String>::Cast(arrDstIP->Get(i));
        std::string strDstIP = std::string(*(v8::String::Utf8Value(temp)));
        operInfo.arrayDst.push_back(strDstIP);
        printf("Call dst deviceIP:%s\n", strDstIP.c_str());
    }
    printf("CallInfo:volume[%u]\n", callVolume->Uint32Value());
    operInfo.uVolume = callVolume->Uint32Value();

    CAEBELLBusiThread::GetInstance().startCallTask(uTaskId->Uint32Value(), operInfo);
}

/**
 * 根据设备IP停止广播
 * @param args[0] taskId
 * @param args[1] 停止的设备IP
 */
void stopBroadcast(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<String> dstIP = Local<String>::Cast(args[1]);
    std::string strDstIP = std::string(*(v8::String::Utf8Value(dstIP)));

    // log
    printf("stop broadcast:taskId:%u,dstIP:%s.\n", uTaskId->Uint32Value(), strDstIP.c_str());

    StopOperInfo stopInfo;
    stopInfo.dst = strDstIP;

    CAEBELLBusiThread::GetInstance().stopBroadcastTask(uTaskId->Uint32Value(), stopInfo);
}

/**
 * 根据设备IP停止喊话
 * @param args[0] taskId
 * @param args[1] 停止的设备IP
 */
void stopCall(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<String> dstIP = Local<String>::Cast(args[1]);
    std::string strDstIP = std::string(*(v8::String::Utf8Value(dstIP)));

    // log
    printf("stop call:taskId:%u,dstIP:%s.\n", uTaskId->Uint32Value(), strDstIP.c_str());

    StopOperInfo stopInfo;
    stopInfo.dst = strDstIP;

    CAEBELLBusiThread::GetInstance().stopCallTask(uTaskId->Uint32Value(), stopInfo);
}

/**
 * 调整音量
 * @param args[0] taskId
 * @param args[1] 音量调整信息
 */
void adjustVolume(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> volumeInfo = Local<Object>::Cast(args[1]);
    // 调整目标设备IP
    Local<String> dstIP = Local<String>::Cast(volumeInfo->Get(String::NewFromUtf8(isolate, "dst")));
    std::string strDstIP = std::string(*(v8::String::Utf8Value(dstIP)));
    // 调整的音量大小
    Local<Uint32> volume = Local<Uint32>::Cast(volumeInfo->Get(String::NewFromUtf8(isolate, "uVolume")));
    int iVolume = volume->Uint32Value();

    // log
    printf("adjustVolume:taskId[%u],dstIP[%s],volume[%d].\n", uTaskId, strDstIP.c_str(), iVolume);

    AdjustVolumeOperInfo adjustInfo;
    adjustInfo.sDst = strDstIP;
    adjustInfo.volume = iVolume;

    CAEBELLBusiThread::GetInstance().adjustVolumeTask(uTaskId, adjustInfo);
}

/**
 * 添加设备
 * @param args[0] taskId
 * @param args[1] 添加的设备信息
 */
void addDevice(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> devInfo = Local<Object>::Cast(args[1]);
    // 设备名称
    Local<String> devName = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devName")));
    std::string strDevName = std::string(*(v8::String::Utf8Value(devName)));
    // 设备资产编号
    Local<String> devCode = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devCode")));
    std::string strDevCode = std::string(*(v8::String::Utf8Value(devCode)));
    // 设备类型
    Local<Uint32> devType = Local<Uint32>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devType")));
    int iDevType = devType->Uint32Value();
    // 设备IP
    Local<String> devIP = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));

    // log
    printf("add device:taskId:%u,name:%s,devCode:%s,type:%d,IP:%s.\n", uTaskId, strDevName.c_str(),
            strDevCode.c_str(), iDevType, strDevIP.c_str());

    string devID = CAEBELLBusiThread::GetInstance().GetDeviceIdByIP(strDevIP);
    if (!devID.empty())
    {
        // 设备已存在，先删除
        DelOperInfo delInfo;
        delInfo.dst = devID;

        CAEBELLBusiThread::GetInstance().delDeviceTask(0, delInfo);

        Sleep(50);
    }
    AddDeviceOperInfo info;
    info.devInfo.deviceName = strDevName.c_str();
    info.devInfo.deviceCode = strDevCode;
    ConvertDeviceType(iDevType, info.devInfo.deviceType);
    info.devInfo.deviceIP = strDevIP;

    CAEBELLBusiThread::GetInstance().addDeviceTask(uTaskId, info);
}

/**
 * 修改设备
 * @param args[0] taskId
 * @param args[1] 添加的设备信息
 */
void updateDevice(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> devInfo = Local<Object>::Cast(args[1]);
    // 设备名称
    Local<String> devName = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devName")));
    std::string strDevName = std::string(*(v8::String::Utf8Value(devName)));
    // 设备资产编号
    Local<String> devCode = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devCode")));
    std::string strDevCode = std::string(*(v8::String::Utf8Value(devCode)));
    // 设备类型
    Local<Uint32> devType = Local<Uint32>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devType")));
    int iDevType = devType->Uint32Value();
    // 设备IP
    Local<String> devIP = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));
    // 设备ID
    Local<String> devId = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devId")));
    std::string strDevId = std::string(*(v8::String::Utf8Value(devId)));

    // log
    printf("update device:taskId=%u,name=%s,devCode=%s,type=%d,IP=%s,devId=%s.\n", uTaskId, strDevName.c_str(),
            strDevCode.c_str(), iDevType, strDevIP.c_str(), strDevId.c_str());

    if (!strDevId.empty())
    {
        // 设备已存在，先删除
        DelOperInfo delInfo;
        delInfo.dst = strDevId;

        CAEBELLBusiThread::GetInstance().delDeviceTask(0, delInfo);

        Sleep(50);
    }
    AddDeviceOperInfo info;
    info.devInfo.deviceName = strDevName.c_str();
    info.devInfo.deviceCode = strDevCode;
    ConvertDeviceType(iDevType, info.devInfo.deviceType);
    info.devInfo.deviceIP = strDevIP;
    info.devInfo.deviceID = strDevId; // 更新设备时，deviceID不变

    CAEBELLBusiThread::GetInstance().updateDeviceTask(uTaskId, info);
}

/**
 * 删除设备
 * @param args[0] taskId
 * @param args[1] 删除的设备ID
 */
void delDevice(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<String> devId = Local<String>::Cast(args[1]);
    std::string strDevId = std::string(*(v8::String::Utf8Value(devId)));

    // log
    printf("delete device:taskId:%u,devId:%s.\n", uTaskId->Uint32Value(), strDevId.c_str());

    DelOperInfo delInfo;
    delInfo.dst = strDevId;

    CAEBELLBusiThread::GetInstance().delDeviceTask(uTaskId->Uint32Value(), delInfo);
}

/**
 * 上传文件
 * @param args[0] taskId
 * @param args[1] 文件信息
 */
void uploadFile(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> fileInfo = Local<Object>::Cast(args[1]);
    // 文件名称
    Local<String> fileName = Local<String>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "fileName")));
    std::string strFileName = std::string(*(v8::String::Utf8Value(fileName)));
    // 文件类型
    Local<Uint32> fileType = Local<Uint32>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "fileType")));
    int iFileType = fileType->Uint32Value();
    // 文件大小
    Local<Uint32> fileSize = Local<Uint32>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "fileSize")));
    uint32 uFileSize = fileSize->Uint32Value();
    // 文件本地路径
    Local<String> filePath = Local<String>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "filePath")));
    std::string strFilePath = std::string(*(v8::String::Utf8Value(filePath)));

    // log
    printf("upload file:taskId:%u,fileName:%s,fileType:%d,fileSize:%u,filePath:%s\n", uTaskId, strFileName.c_str(),
        iFileType, uFileSize, strFilePath.c_str());

    UploadFileOperInfo info;
    info.fileType = iFileType;
    info.fileSize = uFileSize;
    info.fileName = strFileName;
    info.filePath = strFilePath;

    CAEBELLBusiThread::GetInstance().uploadFileTask(uTaskId, info);
}

/**
 * 添加方案
 * @param args[0] taskId
 * @param args[1] 添加的方案信息
 */
void addPlan(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> planInfo = Local<Object>::Cast(args[1]);
    // 方案名称
    Local<String> planName = Local<String>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "planName")));
    std::string strPlanName = std::string(*(v8::String::Utf8Value(planName)));
    // log
    printf("add plan:taskId=%u,planName=%s\n", uTaskId, strPlanName.c_str());

    // 任务列表信息
    AddUpdPlanOperInfo info;
    info.planName = strPlanName;
    Local<Array> taskList = Local<Array>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "taskList")));
    for (int i=0; i != taskList->Length(); ++i)
    {
        TimerTaskInfo taskInfo;
        Local<Object> temp = Local<Object>::Cast(taskList->Get(i));
        // 任务名称
        Local<String> taskName = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "taskName")));
        taskInfo.taskName = std::string(*(v8::String::Utf8Value(taskName)));
        // 任务执行时间信息
        Local<String> beginTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strBeginTime")));
        taskInfo.strBeginTime = std::string(*(v8::String::Utf8Value(beginTime)));
        Local<String> endTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strEndTime")));
        taskInfo.strEndTime = std::string(*(v8::String::Utf8Value(endTime)));
        Local<String> workTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strDoworkTime")));
        taskInfo.strDoworkTime = std::string(*(v8::String::Utf8Value(workTime)));
        Local<String> runDate = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskRunDate")));
        taskInfo.strTaskRunDate = std::string(*(v8::String::Utf8Value(runDate)));
        Local<String> finishTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskFinishTime")));
        taskInfo.strTaskFinishTime = std::string(*(v8::String::Utf8Value(finishTime)));
        // 循环模式
        Local<Uint32> cycleMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "nCycleMode")));
        taskInfo.nCycleMode = cycleMode->Uint32Value();
        // 设备列表信息
        Local<Array> devList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "devList")));
        for (int j=0; j != devList->Length(); ++j) {
            Local<String> devIP = Local<String>::Cast(devList->Get(j));
            std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));
            taskInfo.vDevList.push_back(strDevIP);
        }
        // 文件列表信息
        Local<Array> fileList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "fileList")));
        for (int k=0; k != fileList->Length(); ++k) {
            Local<Uint32> fileID = Local<Uint32>::Cast(fileList->Get(k));
            uint32 uFileID = fileID->Uint32Value();
            taskInfo.vFileList.push_back(uFileID);
        }
        // 播放信息
        Local<Uint32> playMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "playMode")));
        taskInfo.playMode = playMode->Uint32Value();
        Local<Uint32> playTimes = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "replayTimes")));
        taskInfo.replayTimes = playTimes->Uint32Value();
        Local<Uint32> volume = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "volume")));
        taskInfo.volume = volume->Uint32Value();

        printf("add taskInfo:taskName=%s,cycleMode=%d,playMode=%d,volume=%d\n", taskInfo.taskName.c_str(),
            taskInfo.nCycleMode, taskInfo.playMode, taskInfo.volume);

        info.taskList.push_back(taskInfo);
    }

    string strPolicyId = CAEBELLBusiThread::GetInstance().GetPlanIDByName(strPlanName);
    if (!strPolicyId.empty())
    {
        // 方案已存在，先删除
        DelPlanOperInfo delInfo;
        delInfo.planName = strPlanName;
        CAEBELLBusiThread::GetInstance().delPlanTask(0, delInfo);

        Sleep(100);
    }

    CAEBELLBusiThread::GetInstance().addPlanTask(uTaskId, info);
}

/**
 * 修改方案
 * @param args[0] taskId
 * @param args[1] 修改的方案信息
 */
void updatePlan(const FunctionCallbackInfo<Value>& args) {
     Isolate* isolate = args.GetIsolate();
     // 外部传入的信息, 使用Cast方法来转换
     Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
     uint32 uTaskId = taskId->Uint32Value();
     Local<Object> planInfo = Local<Object>::Cast(args[1]);
     // 方案名称
     Local<String> planName = Local<String>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "planName")));
     std::string strPlanName = std::string(*(v8::String::Utf8Value(planName)));
     // log
     printf("update plan:taskId=%u,planName=%s\n", uTaskId, strPlanName.c_str());

     // 任务列表信息
     AddUpdPlanOperInfo info;
     info.planName = strPlanName;
     Local<Array> taskList = Local<Array>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "taskList")));
     for (int i=0; i != taskList->Length(); ++i)
     {
         TimerTaskInfo taskInfo;
         Local<Object> temp = Local<Object>::Cast(taskList->Get(i));
         // 任务名称
         Local<String> taskName = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "taskName")));
         taskInfo.taskName = std::string(*(v8::String::Utf8Value(taskName)));
         // 任务执行时间信息
         Local<String> beginTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strBeginTime")));
         taskInfo.strBeginTime = std::string(*(v8::String::Utf8Value(beginTime)));
         Local<String> endTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strEndTime")));
         taskInfo.strEndTime = std::string(*(v8::String::Utf8Value(endTime)));
         Local<String> workTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strDoworkTime")));
         taskInfo.strDoworkTime = std::string(*(v8::String::Utf8Value(workTime)));
         Local<String> runDate = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskRunDate")));
         taskInfo.strTaskRunDate = std::string(*(v8::String::Utf8Value(runDate)));
         Local<String> finishTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskFinishTime")));
         taskInfo.strTaskFinishTime = std::string(*(v8::String::Utf8Value(finishTime)));
         // 循环模式
         Local<Uint32> cycleMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "nCycleMode")));
         taskInfo.nCycleMode = cycleMode->Uint32Value();
         // 设备列表信息
         Local<Array> devList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "devList")));
         for (int j=0; j != devList->Length(); ++j) {
             Local<String> devIP = Local<String>::Cast(devList->Get(j));
             std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));
             taskInfo.vDevList.push_back(strDevIP);
         }
         // 文件列表信息
         Local<Array> fileList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "fileList")));
         for (int k=0; k != fileList->Length(); ++k) {
             Local<Uint32> fileID = Local<Uint32>::Cast(fileList->Get(k));
             uint32 uFileID = fileID->Uint32Value();
             taskInfo.vFileList.push_back(uFileID);
         }
         // 播放信息
         Local<Uint32> playMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "playMode")));
         taskInfo.playMode = playMode->Uint32Value();
         Local<Uint32> playTimes = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "replayTimes")));
         taskInfo.replayTimes = playTimes->Uint32Value();
         Local<Uint32> volume = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "volume")));
         taskInfo.volume = volume->Uint32Value();

         printf("update taskInfo:taskName=%s,cycleMode=%d,playMode=%d,volume=%d\n", taskInfo.taskName.c_str(),
             taskInfo.nCycleMode, taskInfo.playMode, taskInfo.volume);

         info.taskList.push_back(taskInfo);
     }

    string strPolicyId = CAEBELLBusiThread::GetInstance().GetPlanIDByName(strPlanName);
    if (!strPolicyId.empty())
    {
        // 方案已存在，先删除
        DelPlanOperInfo delInfo;
        delInfo.planName = strPlanName;
        CAEBELLBusiThread::GetInstance().delPlanTask(0, delInfo);

        Sleep(100);
    }

     CAEBELLBusiThread::GetInstance().updatePlanTask(uTaskId, info);
}

/**
 * 删除方案
 * @param args[0] taskId
 * @param args[1] 删除的方案信息
 */
void delPlan(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> delPlanInfo = Local<Object>::Cast(args[1]);
    // 方案名称
    Local<String> planName = Local<String>::Cast(delPlanInfo->Get(String::NewFromUtf8(isolate, "planName")));
    std::string strPlanName = std::string(*(v8::String::Utf8Value(planName)));

    // log
    printf("delete plan:taskId=%u,planName=%s\n", uTaskId, strPlanName.c_str());

    DelPlanOperInfo info;
    info.planName = strPlanName;
    CAEBELLBusiThread::GetInstance().delPlanTask(uTaskId, info);
}

/**
 * 添加会话中设备
 * @param args[0] taskId
 * @param args[1] 操作信息
 */
void addSessionDev(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> sessionDevInfo = Local<Object>::Cast(args[1]);
    // 会话中设备IP
    Local<String> ssDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "sessionDevIP")));
    std::string strSessionDevIP = std::string(*(v8::String::Utf8Value(ssDevIP)));
    // 添加的设备IP
    Local<String> addDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strAddDevIP = std::string(*(v8::String::Utf8Value(addDevIP)));

    // log
    printf("add session device:taskId=%u,deviceIP=%s\n", uTaskId, strAddDevIP.c_str());

    SessionDevOperInfo info;
    info.sessionDevIP = strSessionDevIP;
    info.devIP = strAddDevIP;
    CAEBELLBusiThread::GetInstance().addSessionDevTask(uTaskId, info);
}

/**
 * 删除会话中设备
 * @param args[0] taskId
 * @param args[1] 操作信息
 */
void delSessionDev(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // 外部传入的信息, 使用Cast方法来转换
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> sessionDevInfo = Local<Object>::Cast(args[1]);
    // 会话中设备IP
    Local<String> ssDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "sessionDevIP")));
    std::string strSessionDevIP = std::string(*(v8::String::Utf8Value(ssDevIP)));
    // 删除的设备IP
    Local<String> delDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strDelDevIP = std::string(*(v8::String::Utf8Value(delDevIP)));

    // log
    printf("delete session device:taskId=%u,deviceIP=%s\n", uTaskId, strDelDevIP.c_str());

    SessionDevOperInfo info;
    info.sessionDevIP = strSessionDevIP;
    info.devIP = strDelDevIP;
    CAEBELLBusiThread::GetInstance().delSessionDevTask(uTaskId, info);
}

/**
 * 获取任务操作结果信息
 * @param args[0] taskId
 * @return {object} 不同任务类型回复不同数据
 */
void getTaskResponse(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    // 返回信息
    Local<Object> respInfo = Object::New(isolate);

    ResTaskInfo& resInfo = CAEBELLBusiThread::GetInstance().getTaskResInfo(uTaskId);
    if (resInfo.bRespond)
    {
        printf("type:%d, taskId:%lu, operRet:%d\n", resInfo.taskType, resInfo.taskId, resInfo.operRet);
        if (resInfo.taskType == TASK_TYPE::QUERY_FILE)
        {
            // 查询文件列表的操作结果回复
            ResFileInfo& resFileInfo = resInfo.fileList;
            // C++数据结构转换为js中数据结构
            Local<Array> arrFile = Array::New(isolate);
            for (int i=0; i != resFileInfo.vFiles.size(); ++i)
            {
                FileInfo file = resFileInfo.vFiles[i];
                // Object类型的声明
                Local<Object> fileInfo = Object::New(isolate);
                // 对象的赋值
                Local<Number> temp = v8::Number::New(isolate, file.nFileID);
                Local<Uint32> fileID = Local<Uint32>::Cast(temp);
                Local<String> fileName = String::NewFromUtf8(isolate, file.sName.c_str());
                fileInfo->Set(v8::String::NewFromUtf8(isolate, "fileId"), fileID);
                fileInfo->Set(v8::String::NewFromUtf8(isolate, "fileName"), fileName);

                arrFile->Set(i, fileInfo);
            }
            respInfo->Set(v8::String::NewFromUtf8(isolate, "fileResp"), arrFile);
        }
        else if (resInfo.taskType == TASK_TYPE::ADD_DEVICE || resInfo.taskType == TASK_TYPE::UPDATE_DEVICE
                || resInfo.taskType == TASK_TYPE::DEL_DEVICE)
        {
            Local<Number> errorCode = v8::Number::New(isolate, resInfo.errorCode);
            Local<Uint32> uErrorCode = Local<Uint32>::Cast(errorCode);
            Local<Number> operRet = v8::Number::New(isolate, resInfo.operRet);
            Local<Uint32> uOperRet = Local<Uint32>::Cast(operRet);
            Local<String> devId = String::NewFromUtf8(isolate, resInfo.devId.c_str());
            respInfo->Set(v8::String::NewFromUtf8(isolate, "errCode"), uErrorCode);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "operRet"), uOperRet);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "devId"), devId);
        }
        else
        {
            // 其他任务的操作结果回复
            Local<Number> temp = v8::Number::New(isolate, resInfo.taskType);
            Local<Uint32> uTaskType = Local<Uint32>::Cast(temp);
            temp = v8::Number::New(isolate, resInfo.operRet);
            Local<Uint32> uOperRet = Local<Uint32>::Cast(temp);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "optType"), uTaskType);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "operRet"), uOperRet);
        }
        CAEBELLBusiThread::GetInstance().removeTaskPtrByID(uTaskId);
    }

    // 回调到外部
    Local<Number> temp = v8::Number::New(isolate, resInfo.bRespond);
    Local<Uint32> bRespond = Local<Uint32>::Cast(temp);
    respInfo->Set(v8::String::NewFromUtf8(isolate, "bRespond"), bRespond);
    args.GetReturnValue().Set(respInfo);
}

/**
 * 获取设备状态推送信息
 */
void getAutoDeviceStatus(const FunctionCallbackInfo<Value>& args)
{
    AutoLock lock(autoInfoLock_);

    Isolate* isolate = args.GetIsolate();
    // C++数据结构转换为js中数据结构
    Local<Array> arrDevStatus = Array::New(isolate);
    for (int i=0; i != vAutoPushData_.size(); ++i)
    {
        DeviceStatusInfo status = vAutoPushData_[i];
        // Object类型的声明
        Local<Object> statusInfo = Object::New(isolate);
        // 对象的赋值
        Local<String> sDeviceIP = String::NewFromUtf8(isolate, status.sDeviceIP.c_str());
        Local<Number> tempState = v8::Number::New(isolate, status.uState);
        Local<Uint32> uState = Local<Uint32>::Cast(tempState);
        Local<Number> tempVolume = v8::Number::New(isolate, status.uVolume*2);  // 音量返回给外部百分比
        Local<Uint32> uVolume = Local<Uint32>::Cast(tempVolume);

        statusInfo->Set(v8::String::NewFromUtf8(isolate, "deviceIP"), sDeviceIP);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uState"), uState);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uVolume"), uVolume);

        arrDevStatus->Set(i, statusInfo);
    }

    Local<Object> respInfo = Object::New(isolate);
    respInfo->Set(v8::String::NewFromUtf8(isolate, "deviceResp"), arrDevStatus);

    // 回调到外部
    args.GetReturnValue().Set(respInfo);
    vAutoPushData_.clear();
}

 /**
  * 获取所有设备状态信息
  */
void getAllDeviceStatus(const FunctionCallbackInfo<Value>& args)
{
    AutoLock lock(allDevStatusLock_);

    Isolate* isolate = args.GetIsolate();
    // C++数据结构转换为js中数据结构
    Local<Array> arrDevStatus = Array::New(isolate);
    for (int i=0; i != vAllDevStatusData_.size(); ++i)
    {
        DeviceStatusInfo status = vAllDevStatusData_[i];
        // Object类型的声明
        Local<Object> statusInfo = Object::New(isolate);
        // 对象的赋值
        Local<String> sDeviceIP = String::NewFromUtf8(isolate, status.sDeviceIP.c_str());
        Local<Number> tempState = v8::Number::New(isolate, status.uState);
        Local<Uint32> uState = Local<Uint32>::Cast(tempState);
        Local<Number> tempVolume = v8::Number::New(isolate, status.uVolume*2);  // 音量返回给外部百分比
        Local<Uint32> uVolume = Local<Uint32>::Cast(tempVolume);

        statusInfo->Set(v8::String::NewFromUtf8(isolate, "deviceIP"), sDeviceIP);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uState"), uState);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uVolume"), uVolume);

        arrDevStatus->Set(i, statusInfo);
    }

    Local<Object> respInfo = Object::New(isolate);
    respInfo->Set(v8::String::NewFromUtf8(isolate, "deviceResp"), arrDevStatus);

    // 回调到外部
    args.GetReturnValue().Set(respInfo);
    vAllDevStatusData_.clear();
}

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
// 广播的回调
void BroadcastCB(USHORT uSessionID, DWORD dwUser)
{
    printf("Establish broadcast session:[%u]\n", uSessionID);

    // 保存任务回复信息
    CAEBELLBusiThread::GetInstance().onCurTaskFinish();
}

// 喊话的回调
void CallCB(USHORT uSessionID, DWORD dwUser)
{
    printf("Establish call session:[%u]\n", uSessionID);

    // 保存任务回复信息
    CAEBELLBusiThread::GetInstance().onCurTaskFinish();
}

// 查询所有文件结果回调
void QueryAllFileCB(const vector<NET_FILE>& tanFiles, DWORD dwUser)
{
    printf("get all file info...\n");

    CAEBELLBusiThread::GetInstance().GetAllFileCB(tanFiles);

    ResFileInfo fileInfos;
    for each (auto i in tanFiles)
    {
        FileInfo file;
        file.nFileID = i.nID;
        file.sName = getUtf8String(i.strAlais.c_str());

        fileInfos.vFiles.push_back(file);
    }

    // 保存任务回复信息
    CAEBELLBusiThread::GetInstance().onGetFileFinish(fileInfos);
}

// 定时查询所有文件结果回调
void TimerQueryAllFileCB(const vector<NET_FILE>& tanFiles, DWORD dwUser)
{
    printf("timer get all file info...\n");
    CAEBELLBusiThread::GetInstance().GetAllFileCB(tanFiles);
}

// 停止广播时查询设备状态回调
void QueryDevStatCB_Broadcast(DEVICE_STATUS status, DWORD dwUser)
{
    unsigned short uSessionID = status.uSessionId;
    printf("Stop broadcast:sessionID[%u]\n", uSessionID);
    if (uSessionID != 0)
    {
        CAEBELLBusiThread::GetInstance().stopBroadcast(uSessionID);
    }
    else
    {
        // 该设备是空闲状态，直接回复操作成功
        // 保存任务回复信息
        CAEBELLBusiThread::GetInstance().onCurTaskFinish();
    }
}

// 停止喊话时查询设备状态回调
void QueryDevStatCB_Call(DEVICE_STATUS status, DWORD dwUser)
{
    unsigned short uSessionID = status.uSessionId;
    printf("Stop call:sessionID[%u]\n", uSessionID);
    if (uSessionID != 0)
    {
        CAEBELLBusiThread::GetInstance().stopCall(uSessionID);
    }
    else
    {
        // 该设备是空闲状态，直接回复操作成功
        // 保存任务回复信息
        CAEBELLBusiThread::GetInstance().onCurTaskFinish();
    }
}

// 停止广播/喊话/对讲/会话回调
void StopOperationCB(INT nOperateType, DWORD dwUser)
{
    printf("StopOperationCB:result=%d\n", nOperateType);
}

// 删除设备回调
void RemoveDeviceCB(INT nOperateType, DWORD dwUser)
{
    // 保存任务回复信息
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onDeviceRemoveFinish(nOperateType, bRes);
}

// 调整设备音量回调
void SetDeviceVolumeCB(INT nOperateType, DWORD dwUser)
{
    // 保存任务回复信息
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onCurTaskFinish(bRes);
}

// 上传文件 操作回调
void UploadFileCB(INT nSessionID, DWORD dwUser)
{
    printf("upload file sessionId=%d\n", nSessionID);

    // 创建上传会话成功，保存sessionID
    CAEBELLUploadThread::GetInstance().SetUploadSessionID(nSessionID);
}

// 上传文件数据（纯数据）回调
void UploadFileDataCB(INT nOperateType, DWORD dwUser)
{
    // do nothing
    printf("uploading......\n");
}

// 增/删/改资源回调
void OnOperateResourceCB(INT nOperateType, DWORD dwUser)
{
    printf("nOperateType=%d.\n", nOperateType);
}

// 上传文件数据完成 回调
void OnFinishUploadFileCB(INT nFileID, DWORD dwUser)
{
    printf("upload file success: fileID[%d].\n", nFileID);

    // 保存任务回复信息
    CAEBELLUploadThread::GetInstance().onUploadTaskEnd();

    // 立即查询一次所有文件，从而更新map
    CAEBELLBusiThread::GetInstance().QueryAllFileTask(true);
}

// 添加设备基础信息回调
void AddDeviceCB(INT nOperateType, DWORD dwUser)
{
    printf("add device OperateResult=%d.\n", nOperateType);

    ReqTaskInfo reqInfo = CAEBELLBusiThread::GetInstance().getCurTaskReqInfo();
    // 如果添加设备失败，回复操作失败
    if (nOperateType != 0)
    {
        // 保存任务回复信息
        CAEBELLBusiThread::GetInstance().onDeviceAddFinish(nOperateType, false);
    }
    else
    {
        AddDeviceOperInfo& operInfo = reqInfo.addDevInfo;
        // 保存新设备映射
        CAEBELLBusiThread::GetInstance().onAddNewDevice(operInfo.devInfo.deviceIP, operInfo.devInfo.deviceID);
        // 添加设备附属信息
        CAEBELLBusiThread::GetInstance().onAddDevAttachTask(operInfo);
    }
}

// 添加设备附加信息回调
void AddDeviceAttachCB(INT nOperateType, DWORD dwUser)
{
    printf("add device attach OperateResult=%d.\n", nOperateType);

    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onDeviceAddFinish(nOperateType, bRes);
}

// 定时获取所有设备信息回调
void TimerGetAllNetDevicesCB(const vector<NET_DEVICE>& tanDevices, DWORD dwUser)
{
    printf("get all device info...\n");
    CAEBELLBusiThread::GetInstance().GetAllNetDevices(tanDevices);
}

// 定时获取所有设备附加信息回调
void TimerGetDeviceAttachInfoCB(const vector<NET_DEVICE_ATTACH>& tanAttach, DWORD dwUser)
{
    printf("get all device attach info...\n");
    CAEBELLBusiThread::GetInstance().GetDeviceAttachInfo(tanAttach);
}

// 定时获取所有设备状态回调
void TimerQueryAllDeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser)
{
    printf("get all device status info...\n");
    CAEBELLBusiThread::GetInstance().DeviceStatusCB(tanStatus, true);
    AutoLock lock(allDevStatusLock_);

    vAllDevStatusData_.clear();
    for(auto device : tanStatus)
    {
        DeviceStatusInfo statusInfo;
        statusInfo.uVolume = device.uVolume;
        if (CAEBELLBusiThread::GetInstance().GetIPByPhoneNum(device.uPhoneNum, statusInfo.sDeviceIP))
        {
            ConvertDeviceStatus(device.nDeviceStatus, statusInfo.uState);
            printf("get all device status:deviceIP[%s],phoneNum[%u],devStatus[%u],volume[%u]\n",
                statusInfo.sDeviceIP.c_str(), device.uPhoneNum, statusInfo.uState, statusInfo.uVolume);

            vAllDevStatusData_.push_back(statusInfo);
        }
    }
}

// 设备状态推送回调
void AutoGetDeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser)
{
    printf("auto device status...\n");
    CAEBELLBusiThread::GetInstance().DeviceStatusCB(tanStatus, false);
    AutoLock lock(autoInfoLock_);

    vAutoPushData_.clear();
    bool bDevAddOrDel = false;         // 是否有设备添加或删除
    for(auto device : tanStatus)
    {
        DeviceStatusInfo statusInfo;
        statusInfo.uVolume = device.uVolume;

        if (CAEBELLBusiThread::GetInstance().GetIPByPhoneNum(device.uPhoneNum, statusInfo.sDeviceIP))
        {
            ConvertDeviceStatus(device.nDeviceStatus, statusInfo.uState);
            printf("auto device status:deviceIP[%s],phoneNum[%u],devStatus[%u], volume[%u]\n",
                statusInfo.sDeviceIP.c_str(), device.uPhoneNum, statusInfo.uState, statusInfo.uVolume);

            vAutoPushData_.push_back(statusInfo);
        }
        // DeviceEdit
        if (DeviceStatus::DeviceAdd == device.nDeviceStatus || DeviceStatus::DeviceRemove == device.nDeviceStatus
            || DeviceStatus::DeviceEdit == device.nDeviceStatus)
        {
            bDevAddOrDel = true;
        }
    }

    if (bDevAddOrDel)
    {
        // 立即获取一次所有设备，从而更新信息
        CAEBELLBusiThread::GetInstance().QueryAllDevicesTask(true);
    }
}

// 获取到所有方案回调
void OnGetAllPolicyCB(const vector<TASK_POLICY>& tanTaskPolicy, DWORD dwUser)
{
    printf("GetAllPolicyInfo...\n");
    CAEBELLBusiThread::GetInstance().GetAllPolicyCB(tanTaskPolicy);
}

// 方案状态推送回调
void OnPolicyStatusCB(POLICY_STATUS status, DWORD dwUser)
{
    printf("auto policy status...\n");
    CAEBELLBusiThread::GetInstance().AutoPolicyStatusCB(status);
}

// 获取方案的任务信息回调
void OnPlolicyTaskCB(const vector<TASK_INFO_VIEW>& tanTaskViews, DWORD dwUser)
{
    printf("get policy task...\n");
    CAEBELLBusiThread::GetInstance().QueryPlolicyTaskCB(tanTaskViews);
}

// 添加/修改方案回调
void OnAddUpdatePlanCB(INT nOperateType, DWORD dwUser)
{
    printf("add/update policy result=%d\n", nOperateType);

    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onAddPlanFinish(bRes);
}

// 添加方案任务回调
void OnAddPlanTaskCB(INT nOperateType, DWORD dwUser)
{
    printf("add plan task OperateResult=%d.\n", nOperateType);

    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onAddPlanTaskFinish(bRes);
}

// 开始/停止方案任务回调
void OnTaskOperCB(INT nOperateType, DWORD dwUser)
{
    printf("start/stop plan task OperateResult=%d.\n", nOperateType);
}

// 删除方案回调
void OnDelPlanCB(INT nOperateType, DWORD dwUser)
{
    printf("delete plan OperateResult=%d.\n", nOperateType);

    // 保存任务回复信息
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onCurTaskFinish(bRes);
}

// 添加/删除会话设备回调
void OnSessionDeviceCB(INT nOperateType, DWORD dwUser)
{
    printf("add/del session device OperateResult=%d.\n", nOperateType);

    // 保存任务回复信息
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onCurTaskFinish(bRes);
}

// 美电贝尔设备状态与返回给外部的设备状态对应关系
void ConvertDeviceStatus(const int iDevStatus, uint32& uDevStatus)
{
    switch (iDevStatus)
    {
    case DeviceStatus::Disconnect:
    case DeviceStatus::RelayDisconnect:
        uDevStatus = DEVICE_STATE::DISCONNECT;
        break;
    case DeviceStatus::Free:
        uDevStatus = DEVICE_STATE::FREE;
        break;
    case DeviceStatus::CallWaiting:   // 喊话等待中
        uDevStatus = DEVICE_STATE::CALLWAITING;
        break;
    case DeviceStatus::Ringing:       // 正在响铃
        uDevStatus = DEVICE_STATE::RINGING;
        break;
    case DeviceStatus::Calling:       // 寻呼工作中
        uDevStatus = DEVICE_STATE::CALLING;
        break;
    case DeviceStatus::Talking:       // 对讲工作中
        uDevStatus = DEVICE_STATE::TALKING;
        break;
    case DeviceStatus::Broadcasting:  // 广播工作中
        uDevStatus = DEVICE_STATE::BROADCASTING;
        break;
    case DeviceStatus::DeviceAdd:  // 设备被添加
        uDevStatus = DEVICE_STATE::FREE;
        break;
    case DeviceStatus::DeviceRemove:  // 设备被删除
        uDevStatus = DEVICE_STATE::DISCONNECT;
        break;
    default:
        uDevStatus = DEVICE_STATE::FREE;
        break;
    }
}

// 外面传的设备类型转换为美电贝尔内部设备类型
void ConvertDeviceType(const int srcType, int& destType)
{
    // 美电贝尔内部code值：1音频播放器 2音频解码器 3IP功放 4对讲呼叫站 5求助器 6消防主机 7电源控制器 8音频采集器 10平安求助器
    switch (srcType)
    {
    case DEV_TYPE::DT_MEDIA:
        destType = 1;   // 音频播放器
        break;
    case DEV_TYPE::DT_CALL_TALK:
        destType = 4;   // 对讲呼叫站
        break;
    case DEV_TYPE::DT_AID:
        destType = 5;   // 一键求助器
        break;
    case DEV_TYPE::DT_AID_PA:
        destType = 10;  // 平安求助器
        break;
    default:
        destType = 0;
        break;
    }
}

// 转成UTF-8编码的字符串
string getUtf8String(const char* pSrc)
{
    string result = "";
    do
    {
        wchar_t* pWideText = NULL;
        int size = MultiByteToWideChar(CP_ACP, 0, pSrc, -1, NULL, 0);
        if (size > 0)
        {
            pWideText = new wchar_t[size + 1];
            memset(pWideText, 0, size);
            if (MultiByteToWideChar(CP_ACP, 0, pSrc, -1, (LPWSTR)pWideText, size) == 0)
            {
                delete []pWideText;
                pWideText = NULL;
                break;
            }
            else
            {
                int size = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pWideText, -1, NULL, 0, NULL, NULL);
                if (size > 0)
                {
                    char* pText = new char[size + 1];
                    memset(pText, 0, size);
                    if (WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pWideText, -1, pText, size, NULL, NULL) == 0)
                    {
                        delete[] pText;
                        pText = NULL;
                        break;
                    }
                    result = pText;
                }
            }
        }
    } while (false);

    return result;
}

// 转成GBK编码的字符串
string getGBKString(const char* pSrc)
{
    string result = "";
    do
    {
        wchar_t* pWideText = NULL;
        int size = MultiByteToWideChar(CP_UTF8, 0, pSrc, -1, NULL, 0);
        if (size > 0)
        {
            pWideText = new wchar_t[size + 1];
            memset(pWideText, 0, size);
            if (MultiByteToWideChar(CP_UTF8, 0, pSrc, -1, (LPWSTR)pWideText, size) == 0)
            {
                delete []pWideText;
                pWideText = NULL;
                break;
            }
            else
            {
                int size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pWideText, -1, NULL, 0, NULL, NULL);
                if (size > 0)
                {
                    char* pText = new char[size + 1];
                    memset(pText, 0, size);
                    if (WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pWideText, -1, pText, size, NULL, NULL) == 0)
                    {
                        delete[] pText;
                        pText = NULL;
                        break;
                    }
                    result = pText;
                }
            }
        }
    } while (false);

    return result;
}

// 创建设备时，生成设备ID
string GenerateGUID()
{
    // 初始化COM
    CoInitialize(NULL);

    char buf[64] = { 0 };
    GUID guid;
    if (S_OK == ::CoCreateGuid(&guid))
    {
        _snprintf_s(buf, sizeof(buf)
            , "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"
            , guid.Data1
            , guid.Data2
            , guid.Data3
            , guid.Data4[0], guid.Data4[1]
            , guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
            , guid.Data4[6], guid.Data4[7]
            );
    }

    // 卸载COM
    CoUninitialize();

    string result = buf;
    return result;
}

// 获取对应设备类型的设备类型名称
string GetDeviceTypeName(int devType)
{
    switch (devType)
    {
    case DEV_TYPE::DT_MEDIA:
        return getUtf8String("音频播放器");
    case DEV_TYPE::DT_CALL_TALK:
        return getUtf8String("对讲呼叫站");
    case DEV_TYPE::DT_AID:
        return getUtf8String("一键求助器");
    default:
        return "";
    }
}

// 模块初始化函数，注册模块功能，导出接口供外部调用
void RegisterModule(Local<Object> exports) {
    NODE_SET_METHOD(exports, "startModule", startModule);                        // 启动模块接口
    NODE_SET_METHOD(exports, "stopModule", stopModule);                          // 停止模块接口
    NODE_SET_METHOD(exports, "login", login);                                    // 登录接口
    NODE_SET_METHOD(exports, "logout", logout);                                  // 退出接口
    NODE_SET_METHOD(exports, "queryAllFile", queryAllFile);                      // 查询所有文件接口
    NODE_SET_METHOD(exports, "registerDeviceStatusCB", registerDevStatusCB);     // 注册设备状态推送回调接口
    NODE_SET_METHOD(exports, "startBroadcast", startBroadcast);                  // 开始广播
    NODE_SET_METHOD(exports, "startCall", startCall);                            // 开始寻呼
    NODE_SET_METHOD(exports, "stopBroadcast", stopBroadcast);                    // 停止广播
    NODE_SET_METHOD(exports, "adjustVolume", adjustVolume);                      // 调整音量
    NODE_SET_METHOD(exports, "stopCall", stopCall);                              // 停止寻呼
    NODE_SET_METHOD(exports, "addDevice", addDevice);                            // 增加设备
    NODE_SET_METHOD(exports, "updateDevice", updateDevice);                      // 修改设备
    NODE_SET_METHOD(exports, "delDevice", delDevice);                            // 删除设备
    NODE_SET_METHOD(exports, "uploadFile", uploadFile);                          // 上传文件
    NODE_SET_METHOD(exports, "addPlan", addPlan);                                // 添加方案
    NODE_SET_METHOD(exports, "delPlan", delPlan);                                // 删除方案
    NODE_SET_METHOD(exports, "updatePlan", updatePlan);                          // 修改方案
    NODE_SET_METHOD(exports, "addSessionDev", addSessionDev);                    // 添加会话中设备
    NODE_SET_METHOD(exports, "delSessionDev", delSessionDev);                    // 删除会话中设备
    NODE_SET_METHOD(exports, "getTaskResponse", getTaskResponse);                // 获取任务回复信息
    NODE_SET_METHOD(exports, "getAutoDeviceStatus", getAutoDeviceStatus);        // 获取推送的设备状态信息
    NODE_SET_METHOD(exports, "getAllDeviceStatus", getAllDeviceStatus);          // 主动获取所有设备状态信息
}


/**
 * 定义本模块的名字和初始化函数
 * @param aebellBroadcast 模块名称
 * @param RegisterModule 初始化函数
 */
NODE_MODULE(aebellBroadcast, RegisterModule)
