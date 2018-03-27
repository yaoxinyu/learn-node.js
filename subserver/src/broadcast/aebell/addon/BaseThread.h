/**
* windows线程基础类
*/

#pragma once

#include <windows.h>
#include <process.h>

class CBaseThread
{
public:
    CBaseThread();
    virtual ~CBaseThread();
public:
    /**
    * 开启线程
    */
    void start();
    /**
    * 线程执行函数，派生类需要实现，该函数退出，线程结束
    */
    virtual unsigned long run(void) = 0;
    /**
    * 线程入口函数
    */
    static unsigned __stdcall ThreadProc(void* p);
private:
    // 线程句柄
    HANDLE m_ThreadHandle;
};