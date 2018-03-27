#include "AebellUploadThread.h"
#include "AebellBusiThread.h"
#include "AebellBroadcast.h"


bool CAEBELLUploadThread::m_bStart = false;
CLock CAEBELLUploadThread::m_instanceLock;
CAEBELLUploadThread* CAEBELLUploadThread::instance_ = NULL;

CAEBELLUploadThread& CAEBELLUploadThread::GetInstance()
{
    if (instance_ == NULL)
    {
        AutoLock lock(m_instanceLock);
        if (instance_ == NULL) {
            instance_ = new CAEBELLUploadThread();
        }
    }

    return *instance_;
}

CAEBELLUploadThread::CAEBELLUploadThread()
    : m_bHasTaskRunning(false)
{
    m_exitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

CAEBELLUploadThread::~CAEBELLUploadThread()
{

}

void CAEBELLUploadThread::Start()
{
    if (m_bStart)
        return;

    // 调用基类的start函数
    start();
    m_bStart = true;

    printf("美电贝尔上传文件线程启动!\n");
}

void CAEBELLUploadThread::Exit()
{
    if (!m_bStart)
        return;

    SetEvent(m_exitEvent);
    printf("美电贝尔上传文件线程退出!\n");
}

unsigned long CAEBELLUploadThread::run(void)
{
    while (true)
    {
        // 处理任务队列
        DealTaskQueue();

        // 等待退出事件
        if (WAIT_OBJECT_0 == WaitForSingleObject(m_exitEvent, 1000))
        {
            break;
        }
    }

    printf("美电贝尔上传线程退出!");
    return 0;
}

// 处理任务队列
void CAEBELLUploadThread::DealTaskQueue()
{
    if (!m_bHasTaskRunning)
    {
        DriverNextUpload();
    }
    else
    {
        // 判断当前上传任务是否结束，未结束则继续，已完成则继续下一个任务
        if (m_curTaskPtr) {
            if (m_curTaskPtr->IsTaskTimeout())
            {
                m_curTaskPtr->onUploadTaskEnd(false);
                DriverNextUpload();
            }
            else
            {
                if (!m_curTaskPtr->IsUploaded()) {
                    m_curTaskPtr->DoUpload();
                }
                else {
                    DriverNextUpload();
                }
            }
        }
    }
}

void CAEBELLUploadThread::DriverNextUpload()
{
    m_bHasTaskRunning = false;
    // 从任务队列取出一个任务执行
    CUploadFileTaskPtr pTask = getUploadTask();
    if (pTask)
    {
        m_curTaskPtr = pTask;
        pTask->DoUpload();
        m_bHasTaskRunning = true;
    }
}

void CAEBELLUploadThread::PushUploadTask(CUploadFileTaskPtr pTask)
{
    AutoLock lock(taskListLock_);
    m_taskList.push_back(pTask);
}

CUploadFileTaskPtr CAEBELLUploadThread::getUploadTask()
{
    CUploadFileTaskPtr pTask;

    AutoLock lock(taskListLock_);
    if (!m_taskList.empty()) {
        pTask = m_taskList.front();
        m_taskList.pop_front();
    }

    return pTask;
}

void CAEBELLUploadThread::SetUploadSessionID(int iSessionID)
{
    if (m_curTaskPtr) {
        m_curTaskPtr->SetUploadSessionID(iSessionID);
    }
}

void CAEBELLUploadThread::onUploadTaskEnd(bool bRes/*=true*/)
{
    if (m_curTaskPtr) {
        m_curTaskPtr->onUploadTaskEnd(bRes);
    }
}