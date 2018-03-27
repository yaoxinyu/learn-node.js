/**
* 上传文件任务类定义
*/

#ifndef UPLOAD_TASK_H
#define UPLOAD_TASK_H

#include <windows.h>
#include <memory>
#include "CommonTypeDefine.h"

const int UPLOAD_TIMEOUT = 300 * 1000;   // 上传文件超时时间


class CUploadFileTask
{
public:
    CUploadFileTask(UploadTaskInfo& taskInfo);
    ~CUploadFileTask();

    // 保存dll句柄
    void SetDllHandle(HINSTANCE handle) { hDLL_ = handle; }

    // 外部线程驱动
    void DoUpload();

    // 是否上传完成
    bool IsUploaded() { return m_bUploaded; }

    // 是否超时
    bool IsTaskTimeout();

    // 保存上传会话ID
    void SetUploadSessionID(int iSessionID) { m_taskInfo.iSessionId = iSessionID; }

    // 上传完成回调，保存任务回复信息
    void onUploadTaskEnd(bool bRes=true);
private:
    void DealUploadFileTask();
    void GetUploadSession();  // 获取上传会话ID
    void uploadFileData(unsigned short uSessionId, string& strFileData);
    void uploadFileFinish(unsigned short uSessionId);

    HINSTANCE hDLL_;        // 美电贝尔广播dll句柄

    UploadTaskInfo m_taskInfo;
    bool m_bTaskRunning;    // 任务是否运行
    DWORD m_dwStartTick;    // 任务开始tick
    volatile bool m_bUploaded;       // 上传完成标记
};

typedef std::shared_ptr<CUploadFileTask> CUploadFileTaskPtr;        // 智能指针

#endif // UPLOAD_TASK_H
