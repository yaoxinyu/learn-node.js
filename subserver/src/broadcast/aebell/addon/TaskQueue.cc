#include "TaskQueue.h"

CTaskQueue::CTaskQueue()
{
    // 创建链表互斥量
    m_listMutex = CreateMutex(NULL, FALSE, NULL);
    if (m_listMutex == NULL)
        printf("创建链表互斥量失败！\n");

    m_taskList.clear();
}

CTaskQueue::~CTaskQueue()
{
    if (m_listMutex) {
        CloseHandle(m_listMutex);
    }

    m_taskList.clear();
}

void CTaskQueue::PushTask(CBroadcastTaskPtr pTask, unsigned long dwMilliseconds /* = INFINITE */)
{
    // 获取链表互斥锁
    if (WAIT_OBJECT_0 == WaitForSingleObject(m_listMutex, dwMilliseconds))
    {
        m_taskList.push_back(pTask);
        // 释放锁
        ReleaseMutex(m_listMutex);
    }
}

CBroadcastTaskPtr CTaskQueue::PopTask(unsigned long dwMilliseconds /* = INFINITE */)
{
    CBroadcastTaskPtr pTask;
    // 获取链表互斥锁
    if (WAIT_OBJECT_0 == WaitForSingleObject(m_listMutex, dwMilliseconds))
    {
        if (!m_taskList.empty())
        {
            pTask = m_taskList.front();
            m_taskList.pop_front();
        }
        // 释放锁
        ReleaseMutex(m_listMutex);
    }

    return pTask;
}
