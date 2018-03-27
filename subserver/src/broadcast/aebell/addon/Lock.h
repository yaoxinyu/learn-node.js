/**
* 锁基础类，跨平台
*/

#pragma once

#ifdef WIN32
#include<Windows.h>
#else
#include <pthread.h>
#endif

class CLock
{
public:
    CLock(void);
    ~CLock(void);
    void Lock();
    void UnLock();
private:
#ifdef WIN32
    CRITICAL_SECTION  m_cs;
#else
    pthread_mutex_t  m_mutex;
#endif
};

class AutoLock
{
public:
    AutoLock(CLock &lock);
    ~AutoLock();
private:
    CLock &m_lock;
};
