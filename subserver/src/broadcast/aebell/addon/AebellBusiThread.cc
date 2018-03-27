#include "AebellBusiThread.h"
#include "AebellBroadcast.h"
#include "AebellUploadThread.h"

bool CAEBELLBusiThread::m_bStart = false;
CLock CAEBELLBusiThread::m_instanceLock;
CAEBELLBusiThread* CAEBELLBusiThread::instance_ = NULL;

CAEBELLBusiThread& CAEBELLBusiThread::GetInstance()
{
    if (instance_ == NULL)
    {
        AutoLock lock(m_instanceLock);
        if (instance_ == NULL) {
            instance_ = new CAEBELLBusiThread();
        }
    }

    return *instance_;
}

CAEBELLBusiThread::CAEBELLBusiThread()
    : m_dwLastQueryAllDevTick(0)
    , m_dwLastGetAllDevStatTick(0)
    , m_dwLastQueryAllFileTick(0)
    , m_dwLastGetFileListTick(0)
    , m_bGetAllDevInfo(false)
    , bGetAllPolicy(false)
    , hDLL_(NULL)
    , bLogin_(false)
    , m_uMaxPhoneNum(1000)
{
    m_exitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    m_taskFinishEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    memset(m_phoneNumHash, 0, sizeof(m_phoneNumHash));
}

CAEBELLBusiThread::~CAEBELLBusiThread()
{

}

void CAEBELLBusiThread::Start()
{
    if (m_bStart)
        return;

    // 调用基类的start函数
    start();
    m_bStart = true;

    printf("美电贝尔业务线程启动!\n");
}

void CAEBELLBusiThread::Exit()
{
    if (!m_bStart)
        return;

    SetEvent(m_exitEvent);
    printf("美电贝尔业务线程退出!\n");
}

unsigned long CAEBELLBusiThread::run(void)
{
    while (true)
    {
        if (bLogin_)
        {
            // 定时获取所有的设备，更新对应map
            QueryAllDevicesTask();
            // 定时获取所有的文件，更新对应map
            QueryAllFileTask();
            // 方案状态推送监听
            RegisterPolicyStatusCB();
            // 启动时获取一次所有方案，获取到不再查询，通过方案状态推送消息维护
            if (!bGetAllPolicy)
            {
                QueryAllPolicy();
            }

            if (m_bGetAllDevInfo)
            {
                // 定时主动获取所有的设备状态信息
                GetAllDeviceStatusTask();

                // 处理任务队列
                // 等待上一个任务完成直到超时再继续下一个任务
                if (WAIT_TIMEOUT == WaitForSingleObject(m_taskFinishEvent, TASK_TIMEOUT))
                {
                    // 任务超时，回复失败
                    SetTaskTimeoutRes();
                    // 任务完成事件有效
                    SetEvent(m_taskFinishEvent);
                }
                DealTaskQueue();
            }
        }

        // 等待退出事件
        if (WAIT_OBJECT_0 == WaitForSingleObject(m_exitEvent, THREAD_SPAN))
        {
            break;
        }
    }

    printf("美电贝尔业务线程退出!");
    return 0;
}

// 处理任务队列
void CAEBELLBusiThread::DealTaskQueue()
{
    // 从任务队列取出一个任务执行
    CBroadcastTaskPtr pTask = m_threadTaskQueue.PopTask();
    if (pTask)
    {
        {
            // 当前任务信息
            AutoLock lock(reqInfoLock_);
            reqTaskInfo_ = pTask->GetReqData();
        }

        ReqTaskInfo& reqInfo = pTask->GetReqData();
        switch (reqInfo.taskType)
        {
        case TASK_TYPE::START_BROADCAST:
        {
            // 开始广播
            printf("deal start broadcast task...\n");
            BroadcastOperInfo& broadInfo = reqInfo.broadInfo;
            DealBroadcastTask(broadInfo);
        }
        break;
        case TASK_TYPE::STOP_BROADCAST:
        {
            // 停止广播
            printf("deal stop broadcast task...\n");
            StopOperInfo& stopBroadInfo = reqInfo.stopInfo;
            DealStopBroadcastTask(stopBroadInfo);
        }
        break;
        case TASK_TYPE::QUERY_FILE:
            // 查询文件
            printf("deal query all file task...\n");
            DealQueryFileTask();
            break;
        case TASK_TYPE::ADJUST_VOLUME:
        {
            // 调整音量
            printf("deal adjust volume task...\n");
            AdjustVolumeOperInfo& volumeInfo = reqInfo.adjustInfo;
            DealAdjustVolumeTask(volumeInfo);
        }
        break;
        case TASK_TYPE::DEV_STATUS:
            // 设备状态 do nothing
            break;
        case TASK_TYPE::START_CALL:
        {
            // 开始喊话
            printf("deal start call task...\n");
            CallOperInfo& callInfo = reqInfo.callInfo;
            DealCallTask(callInfo);
        }
        break;
        case TASK_TYPE::STOP_CALL:
        {
            // 停止喊话
            printf("deal stop call task...\n");
            StopOperInfo& stopCallInfo = reqInfo.stopInfo;
            DealStopCallTask(stopCallInfo);
        }
        break;
        case TASK_TYPE::ADD_DEVICE:
        case TASK_TYPE::UPDATE_DEVICE:
        {
            // 添加设备
            printf("deal add/update device task...\n");
            AddDeviceOperInfo& addDevInfo = reqInfo.addDevInfo;
            DealAddDeviceTask(addDevInfo);
        }
        break;
        case TASK_TYPE::DEL_DEVICE:
        {
            // 删除设备
            printf("deal del device task...\n");
            DelOperInfo& delDevInfo = reqInfo.delInfo;
            DealDelDeviceTask(delDevInfo);
        }
        break;
        case TASK_TYPE::ADD_PLAN:
        {
            // 添加方案
            printf("deal add plan task...\n");
            AddUpdPlanOperInfo& planInfo = reqInfo.planInfo;
            DealAddPlanTask(planInfo);
        }
        break;
        case TASK_TYPE::UPDATE_PLAN:
        {
            // 修改方案
            printf("deal update plan task...\n");
            AddUpdPlanOperInfo& planInfo = reqInfo.planInfo;
            DealUpdatePlanTask(planInfo);
        }
        break;
        case TASK_TYPE::DEL_PLAN:
        {
            // 删除方案
            printf("deal delete plan task...\n");
            DelPlanOperInfo& delInfo = reqInfo.delPlanInfo;
            DealDelPlanTask(delInfo);
        }
        break;
        case TASK_TYPE::ADD_SS_DEV:
        {
            // 添加会话设备
            printf("deal add session device task...\n");
            SessionDevOperInfo& ssDevInfo = reqInfo.ssDevInfo;
            DealAddSessionDevTask(ssDevInfo);
        }
        break;
        case TASK_TYPE::DEL_SS_DEV:
        {
            // 删除会话设备
            printf("deal delete session device task...\n");
            SessionDevOperInfo& ssDevInfo = reqInfo.ssDevInfo;
            DealDelSessionDevTask(ssDevInfo);
        }
        break;
        default:
            printf("unknown task[type=%d]!!!\n", reqInfo.taskType);
            break;
        }

        ResetEvent(m_taskFinishEvent);
    }
}

// 设置当前任务超时结果
void CAEBELLBusiThread::SetTaskTimeoutRes()
{
    AutoLock lock(reqInfoLock_);
    uint64 uTaskID = reqTaskInfo_.taskId;
    if (uTaskID > 0)
    {
        ResTaskInfo resInfo;
        resInfo.taskType = reqTaskInfo_.taskType;
        resInfo.taskId = uTaskID;
        resInfo.operRet = 0;
        resInfo.bRespond = true;
        setTaskResInfo(uTaskID, resInfo);
    }
}

// 获取所有的设备信息任务
void CAEBELLBusiThread::QueryAllDevicesTask(bool bForce/*=false*/)
{
    if (bForce || !m_bGetAllDevInfo || m_dwLastQueryAllDevTick == 0
        || GetTickCount() - m_dwLastQueryAllDevTick > QUERY_DEVICE_SPAN)
    {
        m_dwLastQueryAllDevTick = GetTickCount();

        if (hDLL_)
        {
            // 获取设备信息
            QueryAllDevFunc pFunc = (QueryAllDevFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_GetAllNetDevices");
            if (pFunc) {
                pFunc(TimerGetAllNetDevicesCB, dwUser_);
            }
            // 获取设备附加信息
            QueryAllAttachFunc pFunc2 = (QueryAllAttachFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_GetDeviceAttachByID");
            if (pFunc2) {
                pFunc2(TimerGetDeviceAttachInfoCB, dwUser_);
            }
        }
    }
}

// 获取所有文件任务
void CAEBELLBusiThread::QueryAllFileTask(bool bForce/*=false*/)
{
    if (bForce || m_dwLastGetFileListTick == 0 || m_dwLastQueryAllFileTick == 0
        || GetTickCount() - m_dwLastQueryAllFileTick > QUERY_FILE_SPAN)
    {
        m_dwLastQueryAllFileTick = GetTickCount();

        if (hDLL_)
        {
            // 获取文件列表
            QueryFileFunc pFunc = (QueryFileFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_GetAllUploadedFiles");
            if (pFunc) {
                pFunc(-1, TimerQueryAllFileCB, dwUser_);
            }
        }
    }
}

// 获取所有的设备状态任务
void CAEBELLBusiThread::GetAllDeviceStatusTask()
{
    if (m_dwLastGetAllDevStatTick == 0 || GetTickCount() - m_dwLastGetAllDevStatTick > QUERY_DEVSTAT_SPAN)
    {
        m_dwLastGetAllDevStatTick = GetTickCount();

        if (hDLL_)
        {
            // 获取所有设备状态信息
            QueryAllDevStatFunc pFunc = (QueryAllDevStatFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_GetAllDeviceStatus");
            if (pFunc) {
                pFunc(TimerQueryAllDeviceStatusCB, dwUser_);
            }
        }
    }
}

// 开始广播
void CAEBELLBusiThread::DealBroadcastTask(BroadcastOperInfo& info)
{
    NET_BROADCAST broadcast;
    broadcast.bIsPhoneNum = true;
    broadcast.strName = "";
    broadcast.nMDid = 0;
    broadcast.nBroadcastType = BroadcastType::ServerBroadcast;
    broadcast.nPlayTime = 0;
    broadcast.nCycleCount = 0;
    broadcast.nCycleType = PlayCycleType::Recycle;  // 播放模式 循环
    broadcast.uVolume = info.uVolume / 2;
    broadcast.nStartPlayIndex = 0;

    for each (auto i in info.arraySrc)
        broadcast.vectFileIDs.push_back(i);

    for each (auto i in info.arrayDst)
    {
        unsigned short uPhoneNum = 0;
        if (GetPhoneNumByIP(i, uPhoneNum)) {
            broadcast.vectDevIDs.push_back(uPhoneNum);
        }
    }

    if (hDLL_)
    {
        // 开始广播
        BroadcastFunc pFunc = (BroadcastFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_StartBroadcasting");
        if (pFunc) {
            pFunc(broadcast, NULL, BroadcastCB, dwUser_);
        }
    }
}

// 开始喊话
void CAEBELLBusiThread::DealCallTask(CallOperInfo& info)
{
    NET_SPEAK speak;
    speak.strName = "";
    speak.bIsPhoneNum = true;
    speak.nBroadcastType = BroadcastType::DeviceCall;
    speak.uVolume = info.uVolume / 2;
    if (!info.src.empty())
    {
        unsigned short uPhoneNum = 0;
        if (GetPhoneNumByIP(info.src, uPhoneNum)) {
            speak.nSourceDevId = uPhoneNum;
        }
    }
    for each (auto i in info.arrayDst)
    {
        unsigned short uPhoneNum = 0;
        if (GetPhoneNumByIP(i, uPhoneNum)) {
            speak.vectDevIDs.push_back(uPhoneNum);
        }
    }

    if (hDLL_)
    {
        CallFunc pCallFunc = (CallFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_Call");
        if (pCallFunc) {
            pCallFunc(speak, CallCB, dwUser_);
        }
    }
}

// 查询文件列表
void CAEBELLBusiThread::DealQueryFileTask()
{
    if (hDLL_)
    {
        QueryFileFunc pQueryFileFunc = (QueryFileFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_GetAllUploadedFiles");
        if (pQueryFileFunc) {
            pQueryFileFunc(-1, QueryAllFileCB, dwUser_);
        }
    }
}

// 调整音量
void CAEBELLBusiThread::DealAdjustVolumeTask(AdjustVolumeOperInfo& info)
{
    if (hDLL_)
    {
        AdjustVolumeFunc pFunc = (AdjustVolumeFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_SetDeviceVolume");
        if (pFunc) {
            unsigned short uPhoneNum = 0;
            if (GetPhoneNumByIP(info.sDst, uPhoneNum)) {
                printf("adjust device volume：IP:%s,phoneNum:%u,volume:%d\n", info.sDst.c_str(),
                    uPhoneNum, info.volume);

                DEVICE_VOLUME vol;
                vol.bIsNumber = true;
                char cBuf[32] = { 0 };
                sprintf(cBuf, "%d", uPhoneNum);
                vol.strID = cBuf;
                INT iVolume = info.volume / 2;
                pFunc(vol, iVolume, SetDeviceVolumeCB, dwUser_);
            }
        }
    }
}

// 添加设备
void CAEBELLBusiThread::DealAddDeviceTask(AddDeviceOperInfo& info)
{
    NET_DEVICE device;
    device.strID = info.devInfo.deviceID;
    device.nDeviceTypeCode = info.devInfo.deviceType;
    device.strIPAddress = info.devInfo.deviceIP;
    device.strAddress = info.devInfo.deviceCode;
//    device.strName = getGBKString(info.devInfo.deviceName.c_str());
    device.strName = info.devInfo.deviceName.c_str();
    device.strRelayServerIP = "";
    device.nPort = 0;
    device.uProtocalVersion = 0;
    device.nNetPowerSwitchNum = 0;
    device.strDeviceTypeName = GetDeviceTypeName(info.devInfo.deviceType);

    if (hDLL_)
    {
        // 添加设备基础信息
        AddDeviceFunc pFunc = (AddDeviceFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_AddBaseDeviceInfo");
        if (pFunc) {
            pFunc(device, AddDeviceCB, dwUser_);
        }
    }
}

void CAEBELLBusiThread::onAddDevAttachTask(AddDeviceOperInfo& info)
{
    NET_DEVICE_ATTACH attach;
    attach.strDeviceID = info.devInfo.deviceID;
    attach.nPriorityLevel = DevicePriorityLevel::Low;  // 低级400 中级500 较高级600 高级700 最高级800
    attach.nDefaultVolume = 25;
    attach.uPhoneNum = info.devInfo.uPhoneNum;

    if (hDLL_)
    {
        // 添加设备附加信息
        AddDeviceAttachFunc pFunc2 = (AddDeviceAttachFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_AddDeviceAttach");
        if (pFunc2) {
            pFunc2(attach, AddDeviceAttachCB, dwUser_);
        }
    }
}

// 删除设备
void CAEBELLBusiThread::DealDelDeviceTask(DelOperInfo& info)
{
    if (hDLL_)
    {
        RemoveDevFunc pFunc = (RemoveDevFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_RemoveNetDevice");
        if (pFunc) {
            std::string devID = info.dst;
            printf("remove device:ID=%s\n", devID.c_str());

            if (!devID.empty()) {
                OPERATE_DEVICE operateDev;
                operateDev.nOperateType = 0;
                operateDev.strMainId = devID;
                pFunc(operateDev, RemoveDeviceCB, dwUser_);

                unsigned short uPhoneNum = 0;
                // 删除设备的映射
                {
                    AutoLock lock(m_mapIP2IDLock);
                    std::map<std::string, std::string>::iterator iterIP = m_ID2IPMap.find(devID);
                    if (iterIP != m_ID2IPMap.end()) {
                        m_IP2IDMap.erase(iterIP->second);
                        m_ID2IPMap.erase(iterIP);
                    }
                }
                {
                    AutoLock lock(m_mapID2PhoneNumLock);
                    std::map<std::string, unsigned short>::iterator iter = m_ID2PhoneNumMap.find(devID);
                    if (iter != m_ID2PhoneNumMap.end()) {
                        uPhoneNum = iter->second;
                        m_ID2PhoneNumMap.erase(iter);
                    }
                }
                {
                    // 设置该通话号为可用
                    AutoLock lock(m_arrayPhoneNumLock);
                    m_phoneNumHash[uPhoneNum] = 0;
                }
            }
        }
    }
}

// 停止广播
void CAEBELLBusiThread::DealStopBroadcastTask(StopOperInfo& info)
{
    printf("stop broadcast:IP:%s\n", info.dst.c_str());
    if (hDLL_)
    {
        // 根据IP查询对应设备状态信息，从中取出通话号然后停止该广播会话
        QueryDevStatFunc pFunc = (QueryDevStatFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_GetDevStatusByIP");
        if (pFunc) {
            pFunc(info.dst, QueryDevStatCB_Broadcast, dwUser_);
        }
    }
}

// 停止喊话
void CAEBELLBusiThread::DealStopCallTask(StopOperInfo& info)
{
    printf("stop call:IP:%s\n", info.dst.c_str());
    if (hDLL_)
    {
        // 根据IP查询对应设备状态信息，从中取出通话号然后停止该喊话会话
        QueryDevStatFunc pFunc = (QueryDevStatFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_GetDevStatusByIP");
        if (pFunc) {
            pFunc(info.dst, QueryDevStatCB_Call, dwUser_);
        }
    }
}

// 添加方案中的任务
void CAEBELLBusiThread::onAddPlanTask(AddUpdPlanOperInfo& info)
{
    if (hDLL_)
    {
        TimerTaskInfo timerInfo = info.taskList[0];
        // 方案ID
//        string strPolicyId = GetPlanIDByName(info.planName);
        string strPolicyId = info.planId;
        printf("add plan task,strPolicyId=%s\n", strPolicyId.c_str());
        if (strPolicyId.empty()) {
            return;
        }
        // 任务基本信息
        BASE_TASK task;
        task.strID = GenerateGUID();
        task.strName = timerInfo.taskName;
        task.nDefaultVolume = timerInfo.volume / 2;
        task.nTaskTypeCode = 0; // 广播 0
        task.nPriorityLevel = DevicePriorityLevel::Low;

        // 设备列表信息
        DEVICE_FOR_TASK device;
        for each(auto i in timerInfo.vDevList)
        {
            string strDeviceID = GetDeviceIdByIP(i);
            if (!strDeviceID.empty()) {
                device.vectDeviceID.push_back(strDeviceID);
            }
        }

        // 播放模式信息
        PLAY_TASK_ATTACH attach;
        attach.strTaskID = task.strID;
        attach.nPlayMode = timerInfo.playMode;
        attach.nReplayTimes = timerInfo.replayTimes;
        attach.nPlayDuration = timerInfo.playDuration;

        // 播放文件列表信息
        FILE_FOR_TASK files;
        PLAY_TASK_FILE file;
        file.strTaskID = task.strID;
        int index = 0;
        for each(auto i in timerInfo.vFileList)
        {
            string strFileFullName;
            if (GetFileFullNameByID(i, strFileFullName)) {
                file.strFileFullName = strFileFullName;
                file.nOrderNum = i;
                files.m_vectFiles.push_back(file);
            }
        }

        // 定时信息
        TIMING_TASK tmTask;
        tmTask.strTaskID = task.strID;
        tmTask.strTaskRunDate = timerInfo.strTaskRunDate;
        tmTask.nCycleMode = timerInfo.nCycleMode;
        tmTask.strBeginTime = timerInfo.strBeginTime;
        tmTask.strDoworkTime = timerInfo.strDoworkTime;
        tmTask.strTaskRunTime = timerInfo.strTaskFinishTime;
        tmTask.strEndTime = timerInfo.strEndTime;

        // 添加方案任务
        AddPlanTaskFunc pFunc = (AddPlanTaskFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_AddBCTaskIntoPolicy");
        bool success = false;
        if (pFunc) {
            success = pFunc(strPolicyId, task, device, attach, files, OnAddPlanTaskCB, dwUser_, tmTask);
        }

        Sleep(100);
        // 启动方案任务
        RunPlanTaskFunc pFunc2 = (RunPlanTaskFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_StartTask");
        if (pFunc2 && success) {
            pFunc2(task.strID, OnTaskOperCB, dwUser_, -1);
        }
    }
}

// 添加方案
void CAEBELLBusiThread::DealAddPlanTask(AddUpdPlanOperInfo& info)
{
    if (hDLL_)
    {
        TASK_POLICY policy;
        policy.strID = info.planId;
        policy.strName = info.planName;
        policy.nPriorityLevel = DevicePriorityLevel::Low;
        policy.nPolicyType = 0; // 0普通方案，1电源方案，2为Led屏显控制方案
        policy.strTempResumeTime = "";
        policy.strTempSuspendedTime = "";
        policy.nPolicyStatus = 0;
        policy.bProPowerOn = 1;
        {
            AutoLock lock(m_mapPolicyLock);
            m_policyNameIdMap[policy.strName] = policy.strID;
        }
        // 添加方案
        AddPlanFunc pFunc = (AddPlanFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_AddTaskPolicy");
        if (pFunc)
        {
            pFunc(policy, 0, OnAddUpdatePlanCB, dwUser_);
        }
    }
}

// 修改方案
void CAEBELLBusiThread::DealUpdatePlanTask(AddUpdPlanOperInfo& info)
{
    // 操作同添加方案
    DealAddPlanTask(info);
}

// 删除方案
void CAEBELLBusiThread::DealDelPlanTask(DelPlanOperInfo& info)
{
    if (hDLL_)
    {
        string strPolicyId = GetPlanIDByName(info.planName);
        if (!strPolicyId.empty())
        {
            DelPlanFunc pFunc = (DelPlanFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_RemoveTaskPolicy");
            if (pFunc) {
                pFunc(strPolicyId, OnDelPlanCB, dwUser_);
            }
        }
    }
}

// 添加会话中的设备
void CAEBELLBusiThread::DealAddSessionDevTask(SessionDevOperInfo& info)
{
    if (hDLL_)
    {
        unsigned short uPhoneNum = 0;
        if (GetPhoneNumByIP(info.sessionDevIP, uPhoneNum))
        {
            unsigned short uSessionId = GetSessionIDByPhoneNum(uPhoneNum);
            uPhoneNum = 0;
            if (GetPhoneNumByIP(info.devIP, uPhoneNum)) {
                string& strGuid = GetGuidByPhoneNum(uPhoneNum);
                AddSessionDevFunc pFunc = (AddSessionDevFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_AddDeviceIntoSession");
                if (pFunc) {
                    DEVICE_ID_WRAPPER devIDs;
                    devIDs.vectID.push_back(strGuid);
                    pFunc(uSessionId, devIDs, OnSessionDeviceCB, dwUser_);
                }
            }
        }
    }
}

// 删除会话中的设备
void CAEBELLBusiThread::DealDelSessionDevTask(SessionDevOperInfo& info)
{
    if (hDLL_)
    {
        unsigned short uPhoneNum = 0;
        if (GetPhoneNumByIP(info.sessionDevIP, uPhoneNum))
        {
            unsigned short uSessionId = GetSessionIDByPhoneNum(uPhoneNum);
            uPhoneNum = 0;
            if (GetPhoneNumByIP(info.devIP, uPhoneNum)) {
                string& strGuid = GetGuidByPhoneNum(uPhoneNum);
                DelSessionDevFunc pFunc = (DelSessionDevFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_RemoveDeviceFromSession");
                if (pFunc) {
                    DEVICE_ID_WRAPPER devIDs;
                    devIDs.vectID.push_back(strGuid);
                    pFunc(uSessionId, devIDs, OnSessionDeviceCB, dwUser_);
                }
            }
        }
    }
}

void CAEBELLBusiThread::onCurTaskFinish(bool bRes/*=true*/)
{
    // 任务完成事件有效
    SetEvent(m_taskFinishEvent);

    AutoLock lock(reqInfoLock_);
    // 保存任务回复信息
    if (reqTaskInfo_.taskId > 0) {
        ResTaskInfo resInfo;
        resInfo.taskType = reqTaskInfo_.taskType;
        resInfo.taskId = reqTaskInfo_.taskId;
        resInfo.operRet = bRes ? 1 : 0;
        resInfo.bRespond = true;
        setTaskResInfo(reqTaskInfo_.taskId, resInfo);
    }
}

void CAEBELLBusiThread::onGetFileFinish(ResFileInfo fileInfos, bool bRes/*=true*/)
{
    // 任务完成事件有效
    SetEvent(m_taskFinishEvent);

    AutoLock lock(reqInfoLock_);
    if (reqTaskInfo_.taskId > 0) {
        ResTaskInfo resInfo;
        resInfo.taskType = reqTaskInfo_.taskType;
        resInfo.taskId = reqTaskInfo_.taskId;
        resInfo.operRet = bRes ? 1 : 0;
        resInfo.bRespond = true;
        resInfo.fileList = fileInfos;
        setTaskResInfo(reqTaskInfo_.taskId, resInfo);
    }
}

void CAEBELLBusiThread::onDeviceRemoveFinish(int iErrorCode, bool bRes/*=true*/)
{
    // 任务完成事件有效
    SetEvent(m_taskFinishEvent);

    AutoLock lock(reqInfoLock_);
    if (reqTaskInfo_.taskId > 0) {
        ResTaskInfo resInfo;
        resInfo.taskType = reqTaskInfo_.taskType;
        resInfo.taskId = reqTaskInfo_.taskId;
        resInfo.operRet = bRes ? 1 : 0;
        resInfo.errorCode = iErrorCode;
        resInfo.bRespond = true;
        setTaskResInfo(reqTaskInfo_.taskId, resInfo);
    }
}

void CAEBELLBusiThread::onDeviceAddFinish(int iErrorCode, bool bRes/*=true*/)
{
    // 任务完成事件有效
    SetEvent(m_taskFinishEvent);

    AutoLock lock(reqInfoLock_);
    // 保存任务回复信息
    string strDevID = reqTaskInfo_.addDevInfo.devInfo.deviceID;
    if (reqTaskInfo_.taskId > 0) {
        ResTaskInfo resInfo;
        resInfo.taskType = reqTaskInfo_.taskType;
        resInfo.taskId = reqTaskInfo_.taskId;
        resInfo.operRet = bRes ? 1 : 0;
        resInfo.devId = bRes ? strDevID : "";
        resInfo.errorCode = iErrorCode;
        resInfo.bRespond = true;
        setTaskResInfo(reqTaskInfo_.taskId, resInfo);
    }

    // 如果添加设备失败，将其删除掉
    if (iErrorCode != 0)
    {
        if (!strDevID.empty()) {
            DelOperInfo delInfo;
            delInfo.dst = strDevID;
            delDeviceTask(0, delInfo);
        }
    }
    else
    {
        if (!strDevID.empty()) {
            unsigned short uPhoneNum = reqTaskInfo_.addDevInfo.devInfo.uPhoneNum;
            onAddNewDeviceAttach(strDevID, uPhoneNum);
        }
    }
}

void CAEBELLBusiThread::onAddPlanFinish(bool bRes/*=true*/)
{
    AddUpdPlanOperInfo planInfo;
    {
        AutoLock lock(reqInfoLock_);
        planInfo = reqTaskInfo_.planInfo;
    }
    // 方案添加成功后给方案添加任务
    if (bRes)
    {
        onAddPlanTask(planInfo);
    }
    else
    {
        onCurTaskFinish(false);

        // 操作失败时将方案删除
        DelPlanOperInfo delInfo;
        delInfo.planName = planInfo.planName;
        CAEBELLBusiThread::GetInstance().delPlanTask(0, delInfo);
    }
}

void CAEBELLBusiThread::onAddPlanTaskFinish(bool bRes/*=true*/)
{
    onCurTaskFinish(bRes);
    // 操作失败时将方案删除
    if (!bRes)
    {
        AutoLock lock(reqInfoLock_);
        DelPlanOperInfo delInfo;
        delInfo.planName = reqTaskInfo_.planInfo.planName;
        CAEBELLBusiThread::GetInstance().delPlanTask(0, delInfo);
    }
}

void CAEBELLBusiThread::onUploadSessionSuccess()
{
    // 任务完成事件有效
    SetEvent(m_taskFinishEvent);
}

void CAEBELLBusiThread::setTaskResInfo(uint64 uTaskID, ResTaskInfo& resInfo)
{
    // 涉及到多线程操作，需要加锁
    AutoLock lock(m_mapResInfoLock);
    m_resInfoMap[uTaskID] = resInfo;
}

ResTaskInfo CAEBELLBusiThread::getTaskResInfo(uint64 uTaskID)
{
    // 涉及到多线程操作，需要加锁
    AutoLock lock(m_mapResInfoLock);
    ResTaskInfo resInfo;
    std::map<uint64, ResTaskInfo>::iterator iter = m_resInfoMap.find(uTaskID);
    if (iter != m_resInfoMap.end()) {
        resInfo = iter->second;
        m_resInfoMap.erase(iter);
    }

    return resInfo;
}

void CAEBELLBusiThread::removeTaskPtrByID(uint64 uTaskID)
{
    // 涉及到多线程操作，需要加锁
    AutoLock lock(m_mapTaskLock);

    std::map<uint64, CBroadcastTaskPtr>::iterator iter = m_taskMap.find(uTaskID);
    if (iter != m_taskMap.end()) {
        m_taskMap.erase(iter);
    }
}

void CAEBELLBusiThread::GetAllNetDevices(const vector<NET_DEVICE>& tanDevices)
{
    // 涉及到多线程操作，需要加锁
    AutoLock lock(m_mapIP2IDLock);

    m_IP2IDMap.clear();
    m_ID2IPMap.clear();
    for each(auto i in tanDevices) {
        printf("devIP:%s,devId:%s\n", i.strIPAddress.c_str(), i.strID.c_str());
        m_IP2IDMap.insert(make_pair(i.strIPAddress, i.strID));
        m_ID2IPMap.insert(make_pair(i.strID, i.strIPAddress));
    }
}

void CAEBELLBusiThread::GetDeviceAttachInfo(const vector<NET_DEVICE_ATTACH>& tanAttach)
{
    m_bGetAllDevInfo = true;
    // 涉及到多线程操作，需要加锁
    std:vector<unsigned short> phoneNums;
    {
        AutoLock lock(m_mapID2PhoneNumLock);

        m_ID2PhoneNumMap.clear();
        for each(auto i in tanAttach) {
            printf("devId:%s,phoneNum:%u\n", i.strDeviceID.c_str(), i.uPhoneNum);
            m_ID2PhoneNumMap.insert(make_pair(i.strDeviceID, i.uPhoneNum));
            m_PhoneNum2IDMap.insert(make_pair(i.uPhoneNum, i.strDeviceID));
            phoneNums.push_back(i.uPhoneNum);
        }
    }

    {
        // 设置该通话号为已用
        AutoLock lock(m_arrayPhoneNumLock);
        for each(auto i in phoneNums) {
            m_phoneNumHash[i] = 1;
        }
    }

    {
        // 更新最大通话号
        AutoLock lock(m_maxPhoneNumLock);
        m_uMaxPhoneNum = 1000;
        for each(auto i in phoneNums) {
            if (i > m_uMaxPhoneNum) {
                m_uMaxPhoneNum = i;
            }
        }
    }
}

bool CAEBELLBusiThread::GetPhoneNumByIP(string& strDeviceIP, unsigned short& uPhoneNum)
{
    bool bRes = false;
    // 涉及到多线程操作，需要加锁
    string strDevID = "";
    {
        AutoLock lock(m_mapIP2IDLock);
        std::map<std::string, std::string>::iterator iterID = m_IP2IDMap.find(strDeviceIP);
        if (iterID != m_IP2IDMap.end()) {
            strDevID = iterID->second;
        }
    }
    if (!strDevID.empty()) {
        AutoLock lock(m_mapID2PhoneNumLock);
        std::map<std::string, unsigned short>::iterator iterPhoneNum = m_ID2PhoneNumMap.find(strDevID);
        if (iterPhoneNum != m_ID2PhoneNumMap.end()) {
            uPhoneNum = iterPhoneNum->second;
            bRes = true;
        }
    }

    return bRes;
}

bool CAEBELLBusiThread::GetIPByPhoneNum(unsigned short& uPhoneNum, string& strDeviceIP)
{
    bool bRes = false;
    // 涉及到多线程操作，需要加锁
    string strDevID = "";
    {
        AutoLock lock(m_mapID2PhoneNumLock);
        std::map<unsigned short, std::string>::iterator iterPhoneNum = m_PhoneNum2IDMap.find(uPhoneNum);
        if (iterPhoneNum != m_PhoneNum2IDMap.end()) {
            strDevID = iterPhoneNum->second;
        }
    }

    if (!strDevID.empty()) {
        AutoLock lock(m_mapIP2IDLock);
        std::map<std::string, std::string>::iterator iterIP = m_ID2IPMap.find(strDevID);
        if (iterIP != m_ID2IPMap.end()) {
            strDeviceIP = iterIP->second;
            bRes = true;
        }
    }

    return bRes;
}

std::string CAEBELLBusiThread::GetDeviceIdByIP(string& strDeviceIP)
{
    // 涉及到多线程操作，需要加锁
    AutoLock lock(m_mapIP2IDLock);
    std::map<std::string, std::string>::iterator iterID = m_IP2IDMap.find(strDeviceIP);
    if (iterID != m_IP2IDMap.end()) {
        return iterID->second;
    }

    return "";
}

void CAEBELLBusiThread::startModule()
{
    if (!hDLL_)
    {
        hDLL_ = LoadLibrary("AebellIpcastSdk.dll");
        if (hDLL_)
        {
            printf("load dll success.\n");
            // 启动业务线程
            Start();
            // 启动上传线程
            CAEBELLUploadThread::GetInstance().Start();
        }
        else
        {
            printf("load dll failure, errCode:%d\n", GetLastError());
        }
    }
    else
    {
        printf("dll is load already...\n");
    }
}

void CAEBELLBusiThread::stopModule()
{
    if (hDLL_)
    {
        FreeLibrary(hDLL_);
        hDLL_ = NULL;
        printf("free dll.\n");
    }
}

bool CAEBELLBusiThread::login(string& strIP, int port, LOGIN_REQUEST& loginReq)
{
    if (hDLL_ && !bLogin_)
    {
        LoginFunc pLoginFunc = (LoginFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_Connect");
        if (pLoginFunc)
        {
            bLogin_ = pLoginFunc(strIP, port, loginReq, NULL, NULL, dwUser_);
            printf("login result[%d].\n", bLogin_);
        }
    }

    return bLogin_;
}

bool CAEBELLBusiThread::logout()
{
    bool bRes = true;
    if (hDLL_)
    {
        LogoutFunc pLogoutFunc = (LogoutFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_DisConnect");
        if (pLogoutFunc) {
            bRes = pLogoutFunc();
            bLogin_ = !bRes;
        }
    }

    return bRes;
}

void CAEBELLBusiThread::queryAllFileTask(uint64 uTaskId)
{
    if (m_dwLastGetFileListTick && GetTickCount() - m_dwLastGetFileListTick < QUERY_FILE_SPAN)
    {
        // 5分钟之内的查询文件列表任务直接用缓存数据回复
        AutoLock lock(m_mapFileLock);
        ResTaskInfo resInfo;
        resInfo.taskType = TASK_TYPE::QUERY_FILE;
        resInfo.taskId = uTaskId;
        resInfo.operRet = 1;
        resInfo.bRespond = true;
        ResFileInfo fileInfos;
        fileInfos.vFiles = m_vFileList;
        resInfo.fileList = fileInfos;
        setTaskResInfo(uTaskId, resInfo);
    }
    else
    {
        ReqTaskInfo taskInfo;
        taskInfo.taskType = TASK_TYPE::QUERY_FILE;
        taskInfo.taskId = uTaskId;
        // 新建一个查询文件列表任务
        CBroadcastTask* tmpTask = new CBroadcastTask();
        tmpTask->SetReqData(taskInfo);
        CBroadcastTaskPtr pTask(tmpTask);
        m_threadTaskQueue.PushTask(pTask);
    }
}

void CAEBELLBusiThread::registerDevStatusCB()
{
    if (hDLL_)
    {
        AutoDevStatusFunc pFunc = (AutoDevStatusFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_AutoGetDeviceStatus");
        if (pFunc) {
            pFunc(AutoGetDeviceStatusCB, dwUser_);
        }
    }
}

void CAEBELLBusiThread::startBroadcastTask(uint64 uTaskId, BroadcastOperInfo& info)
{
    // 新建一个开始广播任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::START_BROADCAST;
    taskInfo.taskId = uTaskId;
    taskInfo.broadInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::startCallTask(uint64 uTaskId, CallOperInfo& info)
{
    // 新建一个开始喊话任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::START_CALL;
    taskInfo.taskId = uTaskId;
    taskInfo.callInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::stopBroadcastTask(uint64 uTaskId, StopOperInfo& info)
{
    // 新建一个停止广播任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::STOP_BROADCAST;
    taskInfo.taskId = uTaskId;
    taskInfo.stopInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::stopCallTask(uint64 uTaskId, StopOperInfo& info)
{
    // 新建一个停止喊话任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::STOP_CALL;
    taskInfo.taskId = uTaskId;
    taskInfo.stopInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::adjustVolumeTask(uint64 uTaskId, AdjustVolumeOperInfo& info)
{
    // 新建一个调整音量任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::ADJUST_VOLUME;
    taskInfo.taskId = uTaskId;
    taskInfo.adjustInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::addDeviceTask(uint64 uTaskId, AddDeviceOperInfo& info)
{
    // 新建一个添加设备任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::ADD_DEVICE;
    taskInfo.taskId = uTaskId;
    taskInfo.addDevInfo = info;
    taskInfo.addDevInfo.devInfo.deviceID = GenerateGUID();
    unsigned short uPhoneNum = GetMaxPhoneNum();
    if (uPhoneNum > 9999) {
        uPhoneNum = GetUsefulPhoneNum();
    }
    taskInfo.addDevInfo.devInfo.uPhoneNum = uPhoneNum;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::updateDeviceTask(uint64 uTaskId, AddDeviceOperInfo& info)
{
    // 新建一个修改设备任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::UPDATE_DEVICE;
    taskInfo.taskId = uTaskId;
    taskInfo.addDevInfo = info;
    if (info.devInfo.deviceID.empty()) {
        taskInfo.addDevInfo.devInfo.deviceID = GenerateGUID();
    }
    // taskInfo.addDevInfo.devInfo.deviceID = GenerateGUID();
    unsigned short uPhoneNum = GetMaxPhoneNum();
    if (uPhoneNum > 9999) {
        uPhoneNum = GetUsefulPhoneNum();
    }
    taskInfo.addDevInfo.devInfo.uPhoneNum = uPhoneNum;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::delDeviceTask(uint64 uTaskId, DelOperInfo& info)
{
    // 新建一个删除设备任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::DEL_DEVICE;
    taskInfo.taskId = uTaskId;
    taskInfo.delInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::uploadFileTask(uint64 uTaskId, UploadFileOperInfo& info)
{
    // 新建一个上传文件任务，加入到上传线程中
    UploadTaskInfo taskInfo;
    taskInfo.taskId = uTaskId;
    taskInfo.uploadInfo = info;
    CUploadFileTaskPtr pTask(new CUploadFileTask(taskInfo));
    pTask->SetDllHandle(hDLL_);
    CAEBELLUploadThread::GetInstance().PushUploadTask(pTask);
}

void CAEBELLBusiThread::addPlanTask(uint64 uTaskId, AddUpdPlanOperInfo& info)
{
    // 新建一个添加方案任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::ADD_PLAN;
    taskInfo.taskId = uTaskId;
    taskInfo.planInfo = info;
    taskInfo.planInfo.planId = GenerateGUID();
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::updatePlanTask(uint64 uTaskId, AddUpdPlanOperInfo& info)
{
    // 新建一个修改方案任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::UPDATE_PLAN;
    taskInfo.taskId = uTaskId;
    taskInfo.planInfo = info;
    taskInfo.planInfo.planId = GenerateGUID();
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::delPlanTask(uint64 uTaskId, DelPlanOperInfo& info)
{
    // 新建一个删除方案任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::DEL_PLAN;
    taskInfo.taskId = uTaskId;
    taskInfo.delPlanInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::addSessionDevTask(uint64 uTaskId, SessionDevOperInfo& info)
{
    // 新建一个添加会话设备任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::ADD_SS_DEV;
    taskInfo.taskId = uTaskId;
    taskInfo.ssDevInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::delSessionDevTask(uint64 uTaskId, SessionDevOperInfo& info)
{
    // 新建一个删除会话设备任务
    ReqTaskInfo taskInfo;
    taskInfo.taskType = TASK_TYPE::DEL_SS_DEV;
    taskInfo.taskId = uTaskId;
    taskInfo.ssDevInfo = info;
    CBroadcastTask* tmpTask = new CBroadcastTask();
    tmpTask->SetReqData(taskInfo);
    CBroadcastTaskPtr pTask(tmpTask);
    m_threadTaskQueue.PushTask(pTask);
}

void CAEBELLBusiThread::stopBroadcast(unsigned short uSessionId)
{
    if (hDLL_)
    {
        StopBroadcastFunc pFunc = (StopBroadcastFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_CancelBroadcasting");
        if (pFunc) {
            pFunc(uSessionId, StopOperationCB, dwUser_);

            // 保存任务回复信息
            onCurTaskFinish();
        }
    }
}
void CAEBELLBusiThread::stopCall(unsigned short uSessionId)
{
    if (hDLL_)
    {
        StopCallFunc pFunc = (StopCallFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_CancelCalling");
        if (pFunc) {
            pFunc(uSessionId, StopOperationCB, dwUser_);

            // 保存任务回复信息
            onCurTaskFinish();
        }
    }
}

CBroadcastTaskPtr CAEBELLBusiThread::getTaskPtrByID(uint64 uTaskID)
{
    AutoLock lock(m_mapTaskLock);
    CBroadcastTaskPtr pTask;
    std::map<uint64, CBroadcastTaskPtr>::iterator iter = m_taskMap.find(uTaskID);
    if (iter != m_taskMap.end()) {
        pTask = iter->second;
    }

    return pTask;
}

void CAEBELLBusiThread::GetAllFileCB(const vector<NET_FILE>& tanFiles)
{
    AutoLock lock(m_mapFileLock);

    m_dwLastGetFileListTick = GetTickCount();
    m_fileNameIdMap.clear();
    m_fileIdFullNameMap.clear();
    m_vFileList.clear();
    FileInfo file;
    for each(auto i in tanFiles) {
        string name = getUtf8String(i.strAlais.c_str());
        string fullName = getUtf8String(i.strFileFullName.c_str());
        printf("fileName:%s,fullName:%s,fileId:%d\n", name.c_str(), fullName.c_str(), i.nID);
        m_fileNameIdMap.insert(make_pair(name, i.nID));
        m_fileIdFullNameMap.insert(make_pair(i.nID, fullName));

        // 缓存文件列表信息
        file.nFileID = i.nID;
        file.sName = name;
        m_vFileList.push_back(file);
    }
}

bool CAEBELLBusiThread::GetIDByFileName(const string& strFileName, int& iFileID)
{
    bool bRes = false;
    // 涉及到多线程操作，需要加锁
    AutoLock lock(m_mapFileLock);
    std::map<std::string, int>::iterator iter = m_fileNameIdMap.find(strFileName);
    if (iter != m_fileNameIdMap.end()) {
        iFileID = iter->second;
        bRes = true;
    }

    return bRes;
}

bool CAEBELLBusiThread::GetFileFullNameByID(const int iFileID, string& strFileFullName)
{
    bool bRes = false;
    // 涉及到多线程操作，需要加锁
    AutoLock lock(m_mapFileLock);
    std::map<int, std::string>::iterator iter = m_fileIdFullNameMap.find(iFileID);
    if (iter != m_fileIdFullNameMap.end()) {
        strFileFullName = iter->second;
        bRes = true;
    }

    return bRes;
}

unsigned short CAEBELLBusiThread::GetMaxPhoneNum()
{
    // 涉及到多线程操作，需要加锁
//    AutoLock lock(m_mapID2PhoneNumLock);
//
//    unsigned short uMaxPhoneNum = 0;
//    std::map<std::string, unsigned short>::iterator iter = m_ID2PhoneNumMap.begin();
//    for (iter; iter != m_ID2PhoneNumMap.end(); ++iter) {
//        if (iter->second > uMaxPhoneNum) {
//            uMaxPhoneNum = iter->second;
//        }
//    }
//    ++uMaxPhoneNum;
//
//    return uMaxPhoneNum;
    AutoLock lock(m_maxPhoneNumLock);
    return ++m_uMaxPhoneNum;
}

unsigned short CAEBELLBusiThread::GetUsefulPhoneNum()
{
    // 当通话号超过9999时，需要重新查找可用的通话号
    AutoLock lock(m_arrayPhoneNumLock);
    unsigned short uPhoneNum = 0;
    for (int i=1001; i != 9999; ++i) {
        if (m_phoneNumHash[i] == 0) {
            uPhoneNum = i;
            m_phoneNumHash[i] = 1;
            break;
        }
    }

    return uPhoneNum;
}

// 获取所有方案
void CAEBELLBusiThread::QueryAllPolicy()
{
    if (hDLL_)
    {
        QueryAllPolicyFunc pFunc = (QueryAllPolicyFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_GetAllTaskPolicy");
        if (pFunc) {
            pFunc(OnGetAllPolicyCB, dwUser_);
        }
    }
}

// 注册方案状态推送回调
void CAEBELLBusiThread::RegisterPolicyStatusCB()
{
    if (hDLL_)
    {
        PolicyStatusCBFunc pFunc = (PolicyStatusCBFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_AutoGetPolicyStatus");
        if (pFunc) {
            pFunc(OnPolicyStatusCB, dwUser_);
        }
    }
}

// 查询所有方案结果回调
void CAEBELLBusiThread::GetAllPolicyCB(const vector<TASK_POLICY>& tanTaskPolicy)
{
    bGetAllPolicy = true;
    {
        AutoLock lock(m_mapPolicyLock);
        m_policyNameIdMap.clear();
        for each (auto i in tanTaskPolicy)
        {
            string policyName = getUtf8String(i.strName.c_str());
            m_policyNameIdMap.insert(make_pair(policyName, i.strID));
            printf("policyName=%s,policyId=%s\n", policyName.c_str(), i.strID.c_str());
        }
    }

    // 获取每个方案的任务列表信息 目前不做 TODO
//    QueryPolicyTaskFunc pFunc2 = NULL;
//    if (hDLL_)
//    {
//        pFunc2 = (QueryPolicyTaskFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_GetAllTaskView");
//    }
//
//    for each (auto i in tanTaskPolicy)
//    {
//        // 根据方案ID查询其所有任务
//        if (pFunc2) {
//            pFunc2(i.strID, OnPlolicyTaskCB, (DWORD)&reqInfo_);
//        }
//    }
}

// 方案状态推送回调
void CAEBELLBusiThread::AutoPolicyStatusCB(POLICY_STATUS status)
{
    bool bQueryTask = false;
    std::string strPolicyId = status.strId;
    std::string strPolicyName = status.strName;
    if (status.nStatus == 2) {
        // 方案状态为添加
        AutoLock lock(m_mapPolicyLock);
        m_policyNameIdMap[strPolicyName] = strPolicyId;
    }
    else if (status.nStatus == 3) {
        // 方案状态为删除
        {
            AutoLock lock(m_mapPolicyLock);
            m_policyNameIdMap.erase(strPolicyName);
        }
//        {
//            AutoLock lock(m_mapPolicyTaskLock);
//            m_policyTaskMap.erase(strPolicyId);
//        }
    } else if (status.nStatus == 4) {
        // 方案状态为更新
        bQueryTask = true;
    } else {
        // 不处理
    }

    // 获取方案的任务列表信息 目前不做 TODO
//    if (bQueryTask && hDLL_)
//    {
//        QueryPolicyTaskFunc pFunc = (QueryPolicyTaskFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_GetAllTaskView");
//        // 根据方案ID查询其所有任务
//        if (pFunc) {
//            pFunc(strPolicyId, OnPlolicyTaskCB, (DWORD)&reqInfo_);
//        }
//    }
}

// 查询方案的任务信息回调
void CAEBELLBusiThread::QueryPlolicyTaskCB(const vector<TASK_INFO_VIEW>& tanTaskViews)
{
    AutoLock lock(m_mapPolicyTaskLock);
    // 更新对应方案的任务列表信息
    std::string strPolicyId = "";
    map<std::string, std::string> tempMap;  // 任务名称与任务ID的映射
    for each (auto i in tanTaskViews)
    {
        tempMap.insert(make_pair(i.strName, i.strTaskID));
        if (strPolicyId.empty()) {
            strPolicyId = i.strTaskPolicyID;
        }
    }
    if (!strPolicyId.empty()) {
        m_policyTaskMap[strPolicyId] = tempMap;
    }
}

void CAEBELLBusiThread::DeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, bool bAllStatus)
{
    AutoLock lock(m_mapSessionId);
    if (bAllStatus)
    {
        m_phoneNum2SessionIdMap.clear();
        m_phoneNum2IdentityMap.clear();
    }
    for each (auto i in tanStatus)
    {
        m_phoneNum2SessionIdMap[i.uPhoneNum] = i.uSessionId;
        m_phoneNum2IdentityMap[i.uPhoneNum] = i.nIdentity;
    }
}

unsigned short CAEBELLBusiThread::GetSessionIDByPhoneNum(unsigned short uPhoneNum)
{
    AutoLock lock(m_mapSessionId);
    unsigned short uSessionId = 0;
    std::map<unsigned short, unsigned short>::iterator iter = m_phoneNum2SessionIdMap.find(uPhoneNum);
    if (iter != m_phoneNum2SessionIdMap.end()) {
        uSessionId = iter->second;
    }
    return uSessionId;
}

string CAEBELLBusiThread::GetGuidByPhoneNum(unsigned short uPhoneNum)
{
    AutoLock lock(m_mapSessionId);
    char guid[32] = {0};
    std::map<unsigned short, int>::iterator iter = m_phoneNum2IdentityMap.find(uPhoneNum);
    if (iter != m_phoneNum2IdentityMap.end()) {
        sprintf(guid, "%d", iter->second);
    }
    return string(guid);
}

string CAEBELLBusiThread::GetPlanIDByName(const string& strPlanName)
{
    AutoLock lock(m_mapPolicyLock);
    string strPolicyId = "";
    std::map<std::string, std::string>::iterator iter = m_policyNameIdMap.find(strPlanName);
    if (iter != m_policyNameIdMap.end()) {
        strPolicyId = iter->second;
    }
    return strPolicyId;
}

string CAEBELLBusiThread::GetPlanTaskID(const string& strPlanID, const string& strPlanTaskName)
{
    AutoLock lock(m_mapPolicyLock);
    string strPlanTaskId = "";
    std::map<std::string, map<std::string, std::string> >::iterator iter = m_policyTaskMap.find(strPlanID);
    if (iter != m_policyTaskMap.end()) {
        map<std::string, std::string> tmpMap = iter->second;
        map<std::string, std::string>::iterator iterTask = tmpMap.find(strPlanTaskName);
        if (iterTask != tmpMap.end()) {
            strPlanTaskId = iterTask->second;
        }
    }
    return strPlanTaskId;
}

void CAEBELLBusiThread::onAddNewDevice(string& strIP, string& devID)
{
    // 添加一个新设备IP与ID的映射
    AutoLock lock(m_mapIP2IDLock);
    m_IP2IDMap[strIP] = devID;
    m_ID2IPMap[devID] = strIP;
}

void CAEBELLBusiThread::onAddNewDeviceAttach(string& strID, unsigned short& uPhoneNum)
{
    {
        // 添加一个新设备ID与通话号的映射
        AutoLock lock(m_mapID2PhoneNumLock);
        m_ID2PhoneNumMap[strID] = uPhoneNum;
    }
    {
        // 设置该通话号为已用
        AutoLock lock(m_arrayPhoneNumLock);
        m_phoneNumHash[uPhoneNum] = 1;
    }
}

ReqTaskInfo CAEBELLBusiThread::getCurTaskReqInfo()
{
    AutoLock lock(reqInfoLock_);
    return reqTaskInfo_;
}