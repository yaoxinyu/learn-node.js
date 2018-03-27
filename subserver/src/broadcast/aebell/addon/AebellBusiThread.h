/**
* 美电贝尔业务处理线程类
*/

#ifndef AEBELL_BUSI_THREAD_H
#define AEBELL_BUSI_THREAD_H

#include <map>
#include <string>
#include "CommonTypeDefine.h"
#include "BaseThread.h"
#include "TaskQueue.h"
#include "Lock.h"
#include "AebellIpcastSdk.h"

const int THREAD_SPAN = 100;     // 业务线程驱动间隔100ms;
const int TASK_TIMEOUT = 3000;   // 任务超时时间
const int QUERY_DEVICE_SPAN = 5 * 60 * 1000;    // 5分钟获取一次所有的设备并更新map
const int QUERY_DEVSTAT_SPAN = 60 * 60 * 1000;  // 每小时获取一次所有的设备状态
const int QUERY_FILE_SPAN = 5 * 60 * 1000;      // 5分钟获取一次所有的文件并更新map


class CAEBELLBusiThread : public CBaseThread
{
private:
    CAEBELLBusiThread();
    ~CAEBELLBusiThread();

public:
    // 获取唯一实例;
    static CAEBELLBusiThread& GetInstance();

    // 线程启动;
    void Start();

    // 线程退出;
    void Exit();

    // 线程执行函数;
    virtual unsigned long run(void);

    // 获取任务队列
    CTaskQueue& GetBusiThreadQueue() { return m_threadTaskQueue; }

    // 获取当前任务信息
    ReqTaskInfo getCurTaskReqInfo();
    // 设置对应taskID的任务回复信息
    void setTaskResInfo(uint64 uTaskID, ResTaskInfo& resInfo);
    // 根据taskID获取任务回复信息，没有则回复0
    ResTaskInfo getTaskResInfo(uint64 uTaskID);
    // 根据taskId获取对应任务
    CBroadcastTaskPtr getTaskPtrByID(uint64 uTaskID);
    // 根据taskId移除对应任务指针
    void removeTaskPtrByID(uint64 uTaskID);

    // 获取所有设备接口回调
    void GetAllNetDevices(const vector<NET_DEVICE>& tanDevices);
    // 获取所有设备附加信息接口回调
    void GetDeviceAttachInfo(const vector<NET_DEVICE_ATTACH>& tanAttach);
    // 获取所有文件回调
    void GetAllFileCB(const vector<NET_FILE>& tanFiles);
    // 设备状态回调
    void DeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, bool bAllStatus = false);

    /**
    * 根据设备IP获取设备通话号
    * param strDeviceIP 输入
    * param uPhoneNum 输出
    * return true：获取到 false：未获取到
    */
    bool GetPhoneNumByIP(string& strDeviceIP, unsigned short& uPhoneNum);
    /**
    * 根据设备通话号获取设备IP
    * param uPhoneNum 输入
    * param strDeviceIP 输出
    * return true：获取到 false：未获取到
    */
    bool GetIPByPhoneNum(unsigned short& uPhoneNum, string& strDeviceIP);
    /**
    * 根据设备IP获取设备ID
    * param strDeviceIP 输入
    * return 有则返回对应ID 没有返回""
    */
    std::string GetDeviceIdByIP(string& strDeviceIP);
    // 根据方案名称获取方案ID
    string GetPlanIDByName(const string& strPlanName);
    // 根据方案ID和方案任务名称获取方案任务ID
    string GetPlanTaskID(const string& strPlanID, const string& strPlanTaskName);
    /**
    * 根据文件名查询文件ID
    * param strFileName 输入
    * param iFileID 输出
    * return true：获取到 false：未获取到
    */
    bool GetIDByFileName(const string& strFileName, int& iFileID);
    // 根据通话号停止广播
    void stopBroadcast(unsigned short uSessionId);
    // 根据通话号停止喊话
    void stopCall(unsigned short uSessionId);
    // 添加方案中的任务
    void onAddPlanTask(AddUpdPlanOperInfo& info);
    // 添加设备附属信息
    void onAddDevAttachTask(AddDeviceOperInfo& info);
    // 添加一个新设备基础信息映射
    void onAddNewDevice(string& strIP, string& devID);
    // 添加一个新设备附加信息映射
    void onAddNewDeviceAttach(string& strID, unsigned short& uPhoneNum);
    // 任务完成信息
    void onCurTaskFinish(bool bRes=true);
    void onGetFileFinish(ResFileInfo fileInfos, bool bRes=true);
    void onDeviceRemoveFinish(int iErrorCode, bool bRes=true);
    void onDeviceAddFinish(int iErrorCode, bool bRes=true);
    void onAddPlanFinish(bool bRes=true);
    void onAddPlanTaskFinish(bool bRes=true);
    void onUploadSessionSuccess();

public:
    void startModule();
    void stopModule();
    bool login(string& strIP, int port, LOGIN_REQUEST& loginReq);
    bool logout();
    void queryAllFileTask(uint64 uTaskId);
    void registerDevStatusCB();
    void startBroadcastTask(uint64 uTaskId, BroadcastOperInfo& info);
    void stopBroadcastTask(uint64 uTaskId, StopOperInfo& info);
    void startCallTask(uint64 uTaskId, CallOperInfo& info);
    void stopCallTask(uint64 uTaskId, StopOperInfo& info);
    void adjustVolumeTask(uint64 uTaskId, AdjustVolumeOperInfo& info);
    void addDeviceTask(uint64 uTaskId, AddDeviceOperInfo& info);
    void updateDeviceTask(uint64 uTaskId, AddDeviceOperInfo& info);
    void delDeviceTask(uint64 uTaskId, DelOperInfo& info);
    void uploadFileTask(uint64 uTaskId, UploadFileOperInfo& info);
    void addPlanTask(uint64 uTaskId, AddUpdPlanOperInfo& info);
    void updatePlanTask(uint64 uTaskId, AddUpdPlanOperInfo& info);
    void delPlanTask(uint64 uTaskId, DelPlanOperInfo& info);
    void addSessionDevTask(uint64 uTaskId, SessionDevOperInfo& info);
    void delSessionDevTask(uint64 uTaskId, SessionDevOperInfo& info);
    // 获取所有的设备信息任务
    void QueryAllDevicesTask(bool bForce=false);
    // 获取所有的设备状态任务
    void GetAllDeviceStatusTask();
    // 获取文件列表任务
    void QueryAllFileTask(bool bForce=false);
    // 获取所有的方案信息
    void QueryAllPolicy();
    // 查询所有方案结果回调
    void GetAllPolicyCB(const vector<TASK_POLICY>& tanTaskPolicy);
    // 方案状态推送回调
    void AutoPolicyStatusCB(POLICY_STATUS status);
    // 查询方案的任务信息回调
    void QueryPlolicyTaskCB(const vector<TASK_INFO_VIEW>& tanTaskViews);
    // 注册方案状态推送回调
    void RegisterPolicyStatusCB();

private:
    // 处理不同类型的任务;
    void DealBroadcastTask(BroadcastOperInfo& info);
    void DealCallTask(CallOperInfo& info);
    void DealQueryFileTask();
    void DealAdjustVolumeTask(AdjustVolumeOperInfo& info);
    void DealAddDeviceTask(AddDeviceOperInfo& info);
    void DealDelDeviceTask(DelOperInfo& info);
    void DealStopBroadcastTask(StopOperInfo& info);
    void DealStopCallTask(StopOperInfo& info);
    void DealAddPlanTask(AddUpdPlanOperInfo& info);
    void DealUpdatePlanTask(AddUpdPlanOperInfo& info);
    void DealDelPlanTask(DelPlanOperInfo& info);
    void DealAddSessionDevTask(SessionDevOperInfo& info);
    void DealDelSessionDevTask(SessionDevOperInfo& info);
    // 处理任务队列
    void DealTaskQueue();
    // 设置当前任务超时回复
    void SetTaskTimeoutRes();
    // 获取最大的通话号
    unsigned short GetMaxPhoneNum();
    // 获取一个可用的通话号
    unsigned short GetUsefulPhoneNum();

    /**
    * 根据文件ID查询文件全路径
    * param iFileID 输入
    * param strFileFullName 输出
    * return true：获取到 false：未获取到
    */
    bool GetFileFullNameByID(const int iFileID, string& strFileFullName);
    // 根据通话号获取会话ID
    unsigned short GetSessionIDByPhoneNum(unsigned short uPhoneNum);
    // 根据通话号获取GUID
    string GetGuidByPhoneNum(unsigned short uPhoneNum);

private:
    static bool m_bStart;              // 线程开启标记
    CTaskQueue m_threadTaskQueue;      // 业务线程任务队列
    HANDLE m_exitEvent;                // 线程退出事件
    HANDLE m_taskFinishEvent;          // 任务结束事件

    CLock m_mapIP2IDLock; // 给m_IP2IDMap、m_ID2IPMap加锁
    std::map<std::string, std::string> m_IP2IDMap;  // 设备IP与设备ID的映射，定时更新维护
    std::map<std::string, std::string> m_ID2IPMap;  // 设备ID与设备IP的映射，定时更新维护
    CLock m_mapID2PhoneNumLock; // 给m_ID2PhoneNumMap、m_PhoneNum2IDMap加锁
    std::map<std::string, unsigned short> m_ID2PhoneNumMap;  // 设备ID与设备通话号的映射，定时更新维护
    std::map<unsigned short, std::string> m_PhoneNum2IDMap;  // 设备通话号与设备ID的映射，定时更新维护
    CLock m_arrayPhoneNumLock;  // 给m_phoneNumHash加锁
    char m_phoneNumHash[10000];
    CLock m_maxPhoneNumLock; // 给m_uMaxPhoneNum加锁
    unsigned short m_uMaxPhoneNum;

    volatile bool m_bGetAllDevInfo;   // 是否获取到所有设备信息
    DWORD m_dwLastQueryAllDevTick;    // 上一次获取所有设备信息的tick
    DWORD m_dwLastGetAllDevStatTick;  // 上一次获取所有设备状态的tick

    HINSTANCE hDLL_;        // 美电贝尔广播dll句柄
    bool bLogin_;           // 是否登录

    // 任务请求信息
    CLock reqInfoLock_;
    ReqTaskInfo reqTaskInfo_;

    CLock m_mapTaskLock;
    std::map<uint64, CBroadcastTaskPtr> m_taskMap;  // taskId与task智能指针的映射
    CLock m_mapResInfoLock;
    std::map<uint64, ResTaskInfo> m_resInfoMap;     // taskId与任务回复信息的映射

    static CLock m_instanceLock;
    static CAEBELLBusiThread* instance_;

    DWORD m_dwLastQueryAllFileTick;     // 上一次查询所有文件的tick
    DWORD m_dwLastGetFileListTick;      // 上一次获取到文件列表的tick
    CLock m_mapFileLock;
    std::map<std::string, int> m_fileNameIdMap;      // 文件名与文件ID的映射
    std::map<int, std::string> m_fileIdFullNameMap;  // 文件ID与文件全路径的映射
    std::vector<FileInfo> m_vFileList;   // 缓存文件列表信息

    volatile bool bGetAllPolicy;   // 获取到所有方案信息
    CLock m_mapPolicyLock;
    std::map<std::string, std::string> m_policyNameIdMap;   // 方案名称与方案ID的映射
    CLock m_mapPolicyTaskLock;
    std::map<std::string, map<std::string, std::string> > m_policyTaskMap;  // key为方案ID，value为任务名称与任务ID的映射

    CLock m_mapSessionId;
    std::map<unsigned short, unsigned short> m_phoneNum2SessionIdMap;   // 通话号与会话ID的映射
    std::map<unsigned short, int> m_phoneNum2IdentityMap;               // 通话号与Identity的映射
};


#endif  // AEBELL_BUSI_THREAD_H

