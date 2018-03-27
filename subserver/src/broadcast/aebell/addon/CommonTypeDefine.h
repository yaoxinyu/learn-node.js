/**
* 业务共通类型定义
*/

#pragma once

#include <memory.h>
#include <string>
#include <vector>

using namespace std;

// 上传文件数据时的分片大小
const int DATA_PIECE_SIZE = 6 * 1024;  // 分片大小


//*******************************
//***********类型声明*************
//*******************************
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef unsigned long DWORD;
// 定义任务类型枚举
enum TASK_TYPE {
    START_BROADCAST = 1,         // 开始广播
    STOP_BROADCAST  = 2,         // 停止广播
    QUERY_FILE      = 3,         // 查询文件列表
    ADJUST_VOLUME   = 4,         // 调整音量
    DEV_STATUS      = 5,         // 设备状态推送
    START_CALL      = 6,         // 开始喊话
    STOP_CALL       = 7,         // 停止喊话
    ADD_DEVICE      = 8,         // 添加设备
    UPDATE_DEVICE   = 9,         // 修改设备
    DEL_DEVICE      = 10,        // 删除设备
    UPLOAD_FILE     = 11,        // 上传文件
    ADD_PLAN        = 12,        // 添加方案
    UPDATE_PLAN     = 13,        // 修改方案
    DEL_PLAN        = 14,        // 删除方案
    ADD_SS_DEV      = 15,        // 添加会话中设备
    DEL_SS_DEV      = 16         // 删除会话中设备
};
// 设备状态枚举
enum DEVICE_STATE {
    DISCONNECT      = 1,     // 未接通
    FREE            = 2,     // 空闲中
    CALLWAITING     = 3,     // 喊话等待中
    RINGING         = 4,     // 正在响铃
    CALLING         = 5,     // 寻呼工作中
    TALKING         = 6,     // 对讲工作中
    BROADCASTING    = 7,     // 广播工作中
};
// 文件类型枚举
enum FILE_TYPE {
    FT_BROADCAST = 0,     // 广播文件
    FT_ALARM     = 1,     // 告警文件
};
// 设备类型枚举
enum DEV_TYPE {
    DT_MEDIA      = 1,     // 音频播放器
    DT_CALL_TALK  = 2,     // 对讲呼叫站
    DT_AID        = 3,     // 一键求助器
    DT_AID_PA     = 4,     // 平安求助器
};


//*******************************
//***********结构体声明***********
//*******************************
// 文件信息
struct FileInfo
{
    int nFileID;     // 文件ID
    string sName;    // 文件名称，需要转换为UTF-8编码

    FileInfo()
    {
        nFileID = 0;
        sName = "";
    }

    FileInfo(const FileInfo& other)
    {
        *this = other;
    }

    FileInfo& operator=(const FileInfo& other)
    {
        if (this == &other)
            return *this;

        nFileID = other.nFileID;
        sName = other.sName;

        return *this;
    }
};
// 设备状态信息
struct DeviceStatusInfo
{
    string sDeviceIP;
    uint32 uState;
    uint32 uVolume;

    DeviceStatusInfo()
    {
        uState = 0;
        sDeviceIP = "";
        uVolume = 0;
    }
};
// 新增的设备信息
struct DeviceInfo
{
    string deviceName;  // 设备名称
    string deviceCode;  // 设备资产编号
    int deviceType;     // 设备类型，参照DEVICE_TYPE枚举
    string deviceIP;    // 设备IP
    string deviceID;    // 设备ID
    unsigned short uPhoneNum; // 设备通话号

    DeviceInfo()
    {
        deviceName = "";
        deviceCode = "";
        deviceType = 0;
        deviceIP = "";
        deviceID = "";
        uPhoneNum = 0;
    }

    DeviceInfo(const DeviceInfo& other)
    {
        *this = other;
    }

    DeviceInfo& operator=(const DeviceInfo& other)
    {
        if (this == &other)
            return *this;

        deviceName = other.deviceName;
        deviceCode = other.deviceCode;
        deviceType = other.deviceType;
        deviceIP = other.deviceIP;
        deviceID = other.deviceID;
        uPhoneNum = other.uPhoneNum;

        return *this;
    }
};
// 广播操作信息
struct BroadcastOperInfo
{
    std::vector<int> arraySrc;        // 播放文件ID
    std::vector<string> arrayDst;     // 播放目标设备IP
    uint32 uVolume;

    BroadcastOperInfo()
    {
        arraySrc.clear();
        arrayDst.clear();
        uVolume = 0;
    }

    BroadcastOperInfo(const BroadcastOperInfo& other)
    {
        *this = other;
    }

    BroadcastOperInfo& operator=(const BroadcastOperInfo& other)
    {
        if (this == &other)
            return *this;

        arraySrc.clear();
        for each (auto i in other.arraySrc)
        {
            arraySrc.push_back(i);
        }
        arrayDst.clear();
        for each (auto i in other.arrayDst)
        {
            arrayDst.push_back(i);
        }
        uVolume = other.uVolume;

        return *this;
    }
};
// 喊话操作信息
struct CallOperInfo
{
    string src;  // 喊话源设备IP
    std::vector<string> arrayDst;  // 喊话目标设备IP
    uint32 uVolume;

    CallOperInfo()
    {
        src = "";
        arrayDst.clear();
        uVolume = 0;
    }

    CallOperInfo(const CallOperInfo& other)
    {
        *this = other;
    }

    CallOperInfo& operator=(const CallOperInfo& other)
    {
        if (this == &other)
            return *this;

        src = other.src;
        arrayDst.clear();
        for each (auto i in other.arrayDst)
        {
            arrayDst.push_back(i);
        }
        uVolume = other.uVolume;

        return *this;
    }
};
// 广播/喊话停止操作信息
struct StopOperInfo
{
    string dst;  // 停止的目标设备IP
};
// 上传文件操作信息
struct UploadFileOperInfo
{
    int iSessionId;   // 上传会话ID
    int fileType;     // 文件类型，参照FILE_TYPE枚举
    uint64 fileSize;  // 文件总大小，单位字节
    string fileName;  // 文件名称（包括后缀名）
    string filePath;  // 文件绝对路径

    UploadFileOperInfo()
    {
        iSessionId = 0;
        fileType = 0;
        fileSize = 0;
        fileName = "";
        filePath = "";
    }

    UploadFileOperInfo(const UploadFileOperInfo& other)
    {
        *this = other;
    }

    UploadFileOperInfo& operator=(const UploadFileOperInfo& other)
    {
        if (this == &other)
            return *this;

        iSessionId = other.iSessionId;
        fileType = other.fileType;
        fileSize = other.fileSize;
        fileName = other.fileName;
        filePath = other.filePath;

        return *this;
    }
};
// 调整音量操作信息
struct AdjustVolumeOperInfo
{
    string sDst;
    int volume;

    AdjustVolumeOperInfo()
    {
        sDst = "";
        volume = 0;
    }

    AdjustVolumeOperInfo(const AdjustVolumeOperInfo& other)
    {
        *this = other;
    }

    AdjustVolumeOperInfo& operator=(const AdjustVolumeOperInfo& other)
    {
        if (this == &other)
            return *this;

        sDst = other.sDst;
        volume = other.volume;

        return *this;
    }
};
// 添加设备操作信息
struct AddDeviceOperInfo
{
    DeviceInfo devInfo;

    AddDeviceOperInfo() {}

    AddDeviceOperInfo(const AddDeviceOperInfo& other)
    {
        *this = other;
    }

    AddDeviceOperInfo& operator=(const AddDeviceOperInfo& other)
    {
        if (this == &other)
            return *this;

        devInfo = other.devInfo;

        return *this;
    }
};
// 删除设备操作信息
struct DelOperInfo
{
    string dst;   // 删除的目标设备ID
};
// 定时任务信息
struct TimerTaskInfo
{
    // 任务基本信息
    string taskName;                // 任务名称
    // 任务执行时间信息
    string strBeginTime;			// 定时开始日期  字符串格式
    string strEndTime;			    // 定时结束日期	字符串格式
    string strDoworkTime;		    // 每次开始的具体时间  字符串格式
    int nCycleMode;				    // 循环模式：1每天 2每周 3每月
    string strTaskRunDate;		    // 每周0到6表示周日到周六；每月为1－31天；多天使用“,”分隔
    string strTaskFinishTime;	    // 任务的具体结束时间 字符串格式
    // 设备列表信息
    std::vector<string> vDevList;   // 设备列表，数组，元素为IP
    // 文件列表信息
    std::vector<int> vFileList;     // 文件列表，数组，元素为文件ID
    // 播放信息
    int playMode;			   // 播放模式 0单曲、1单曲循环、2顺序、3循环、4随机
    int replayTimes;		   // 播放次数，0表示连续
    int playDuration;		   // 播放持续时间(秒)0表示不使用
    int volume;                // 音量

    TimerTaskInfo()
    {
        vDevList.clear();
        vFileList.clear();
        playMode = 0;
        replayTimes = 0;
        playDuration = 0;
        volume = 0;
    }

    TimerTaskInfo(const TimerTaskInfo& other)
    {
        *this = other;
    }

    TimerTaskInfo& operator=(const TimerTaskInfo& other)
    {
        if (this == &other)
            return *this;

        taskName = other.taskName;
        strBeginTime = other.strBeginTime;
        strEndTime = other.strEndTime;
        strDoworkTime = other.strDoworkTime;
        nCycleMode = other.nCycleMode;
        strTaskRunDate = other.strTaskRunDate;
        strTaskFinishTime = other.strTaskFinishTime;
        vDevList.clear();
        for each (auto i in other.vDevList)
        {
            vDevList.push_back(i);
        }
        vFileList.clear();
        for each (auto i in other.vFileList)
        {
            vFileList.push_back(i);
        }
        playMode = other.playMode;
        replayTimes = other.replayTimes;
        playDuration = other.playDuration;
        volume = other.volume;

        return *this;
    }
};
// 添加/修改方案操作信息
struct AddUpdPlanOperInfo
{
    std::string planName;                        // 方案名称
    std::string planId;                          // 方案ID
    std::vector<TimerTaskInfo> taskList;         // 任务列表信息

    AddUpdPlanOperInfo()
    {
        taskList.clear();
    }

    AddUpdPlanOperInfo(const AddUpdPlanOperInfo& other)
    {
        *this = other;
    }

    AddUpdPlanOperInfo& operator=(const AddUpdPlanOperInfo& other)
    {
        if (this == &other)
            return *this;

        planName = other.planName;
        planId = other.planId;
        taskList.clear();
        for each (auto i in other.taskList)
        {
            taskList.push_back(i);
        }

        return *this;
    }
};
// 删除方案操作信息
struct DelPlanOperInfo
{
    string planName;  // 方案名称
};
// 添加/删除会话中的设备操作信息
struct SessionDevOperInfo
{
    string sessionDevIP;   // 会话中的设备IP
    string devIP;          // 添加/删除的设备IP
};
// 任务请求信息
struct ReqTaskInfo
{
    int taskType;   // 请求任务类型，参照TASK_TYPE
    uint64 taskId;  // 请求任务ID
    // 请求任务数据
    BroadcastOperInfo broadInfo;        // 广播操作信息
    CallOperInfo callInfo;              // 喊话操作信息
    StopOperInfo stopInfo;              // 停止操作信息
    AdjustVolumeOperInfo adjustInfo;    // 调整音量操作信息
    AddDeviceOperInfo addDevInfo;       // 添加设备操作信息
    DelOperInfo delInfo;                // 删除设备操作信息
    UploadFileOperInfo uploadInfo;      // 上传文件操作信息
    AddUpdPlanOperInfo planInfo;        // 添加/修改方案操作信息
    DelPlanOperInfo delPlanInfo;        // 删除方案操作信息
    SessionDevOperInfo ssDevInfo;       // 添加/删除会话中的设备操作信息

    ReqTaskInfo()
    {
        taskType = 0;
        taskId = 0;
    }

    ReqTaskInfo(const ReqTaskInfo& other)
    {
        *this = other;
    }

    ReqTaskInfo& operator=(const ReqTaskInfo& other)
    {
        if (this == &other)
            return *this;

        taskType = other.taskType;
        taskId = other.taskId;
        broadInfo = other.broadInfo;
        callInfo = other.callInfo;
        stopInfo = other.stopInfo;
        adjustInfo = other.adjustInfo;
        addDevInfo = other.addDevInfo;
        delInfo = other.delInfo;
        uploadInfo = other.uploadInfo;
        planInfo = other.planInfo;
        delPlanInfo = other.delPlanInfo;
        ssDevInfo = other.ssDevInfo;

        return *this;
    }
};
// 查询文件列表回复信息
struct ResFileInfo
{
    std::vector<FileInfo> vFiles;
    ResFileInfo()
    {
        vFiles.clear();
    }

    ResFileInfo(const ResFileInfo& other)
    {
        *this = other;
    }

    ResFileInfo& operator=(const ResFileInfo& other)
    {
        if (this == &other)
            return *this;

        for each (auto i in other.vFiles)
        {
            vFiles.push_back(i);
        }

        return *this;
    }
};
// 任务回复信息
struct ResTaskInfo
{
    uint64 taskType;        // 任务类型，参照TASK_TYPE
    uint64 taskId;          // 任务ID
    uint64 operRet;         // 操作结果 0失败 1成功
    int errorCode;          // 美电贝尔dll操作错误码
    bool bRespond;          // 是否已响应
    ResFileInfo fileList;   // 文件列表
    string devId;           // 设备ID（添加/修改设备时返回）

    ResTaskInfo()
    {
        taskType = 0;
        taskId = 0;
        operRet = 0;
        errorCode = 0;
        bRespond = false;
        devId = "";
    }

    ResTaskInfo(const ResTaskInfo& other)
    {
        *this = other;
    }

    ResTaskInfo& operator=(const ResTaskInfo& other)
    {
        if (this == &other)
            return *this;

        taskType = other.taskType;
        taskId = other.taskId;
        operRet = other.operRet;
        errorCode = other.errorCode;
        bRespond = other.bRespond;
        fileList = other.fileList;
        devId = other.devId;

        return *this;
    }
};

// 上传任务信息
struct UploadTaskInfo
{
    uint64 taskId;                   // 任务ID
    int iSessionId;                  // 上传会话ID
    UploadFileOperInfo uploadInfo;   // 文件信息

    UploadTaskInfo()
    {
        taskId = 0;
        iSessionId = 0;
    }

    UploadTaskInfo(const UploadTaskInfo& other)
    {
        *this = other;
    }

    UploadTaskInfo& operator=(const UploadTaskInfo& other)
    {
        if (this == &other)
            return *this;

        taskId = other.taskId;
        iSessionId = other.iSessionId;
        uploadInfo = other.uploadInfo;

        return *this;
    }
};