/**
* 美电贝尔上传文件线程类
* 同时只支持单个文件上传，多个文件时加入队列排队上传
*/

#ifndef AEBELL_UPLOAD_THREAD_H
#define AEBELL_UPLOAD_THREAD_H


#include <string>
#include <list>
#include "CommonTypeDefine.h"
#include "BaseThread.h"
#include "Lock.h"
#include "UploadFileTask.h"


class CAEBELLUploadThread : public CBaseThread
{
private:
    CAEBELLUploadThread();
    ~CAEBELLUploadThread();

public:
    // 获取唯一实例;
    static CAEBELLUploadThread& GetInstance();

    // 线程启动;
    void Start();

    // 线程退出;
    void Exit();

    // 线程执行函数;
    virtual unsigned long run(void);

    void PushUploadTask(CUploadFileTaskPtr pTask);
    CUploadFileTaskPtr getUploadTask();

    // 保存上传会话ID
    void SetUploadSessionID(int iSessionID);

    // 上传任务结束
    void onUploadTaskEnd(bool bRes=true);

private:
    // 处理任务队列
    void DealTaskQueue();
    // 驱动下一个文件上传
    void DriverNextUpload();

private:
    static CLock m_instanceLock;
    static CAEBELLUploadThread* instance_;

    static bool m_bStart;              // 线程开启标记
    HANDLE m_exitEvent;                // 线程退出事件

    CUploadFileTaskPtr m_curTaskPtr;   // 当前上传任务

    CLock taskListLock_;
    std::list<CUploadFileTaskPtr> m_taskList;

    bool m_bHasTaskRunning;  // 是否有上传任务正在执行
};


#endif  // AEBELL_UPLOAD_THREAD_H

