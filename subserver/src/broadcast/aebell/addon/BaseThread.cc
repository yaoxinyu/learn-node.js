#include "BaseThread.h"


CBaseThread::CBaseThread()
    : m_ThreadHandle(NULL)
{
}

CBaseThread::~CBaseThread()
{
    if (WaitForSingleObject(m_ThreadHandle, 5000) != WAIT_OBJECT_0)
    {
        // 线程退出失败，强杀线程.
        TerminateThread(m_ThreadHandle, 0);
    }

    if (m_ThreadHandle)
    {
        CloseHandle(m_ThreadHandle);
        m_ThreadHandle = NULL;
    }
}

void CBaseThread::start()
{
    unsigned int threadId = 0;
    m_ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, true, &threadId);
}

unsigned __stdcall CBaseThread::ThreadProc(void* p)
{
    CBaseThread* pThis = (CBaseThread*)p;
    if (pThis)
    {
        return pThis->run();
    }

    return 0;
}