/**
* 简单的多线程广播任务队列
*/

#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <windows.h>
#include <list>
#include <vector>
#include "BroadcastTask.h"

using namespace std;


class CTaskQueue
{
public:
    CTaskQueue();
    ~CTaskQueue();

    /**
    * @brief 加入广播任务到队尾
    * @param pTask 任务智能指针
    * @param dwMilliseconds 超时时间
    */
    void PushTask(CBroadcastTaskPtr pTask, unsigned long dwMilliseconds = INFINITE);

    /**
    * @brief 从队首弹出任务
    * @param dwMilliseconds 超时时间
    * @return 任务智能指针
    */
    CBroadcastTaskPtr PopTask(unsigned long dwMilliseconds = INFINITE);

private:
    std::list<CBroadcastTaskPtr> m_taskList;            // 保存任务链表
    HANDLE m_listMutex;                                 // 链表操作互斥量
};


#endif // TASK_QUEUE_H
