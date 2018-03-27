/**
* 广播任务类定义
*/

#ifndef BROADCAST_TASK_H
#define BROADCAST_TASK_H

#include <memory>
#include "CommonTypeDefine.h"


class CBroadcastTask
{
public:
    CBroadcastTask();
    ~CBroadcastTask();

    /**
    * 获取任务基本信息
    */
    uint64 GetTaskBaseInfo() { return m_uTaskInfo; }

    /**
    * 设置任务基本信息 强转成ReqTaskInfo获取数据
    * param: ReqTaskInfo.taskID 任务ID
    * param: ReqTaskInfo.taskType 任务类型 参照TASK_TYPE枚举
    */
    void SetTaskBaseInfo(uint64 uTaskInfo);

    /**
    * 获取请求数据
    */
    ReqTaskInfo& GetReqData() { return m_reqData; }

    /**
    * 设置任务请求数据
    */
    void SetReqData(ReqTaskInfo& reqInfo);

    /**
    * 获取响应数据
    */
    ResTaskInfo& GetRspData() { return m_rspData; }

    /**
    * 设置响应数据
    */
    void SetRspData(ResTaskInfo& resInfo);

private:
    uint64 m_uTaskInfo;         // 任务信息 强转成ReqTaskInfo获取数据
    ReqTaskInfo m_reqData;      // 请求数据
    ResTaskInfo m_rspData;      // 应答数据
};

typedef std::shared_ptr<CBroadcastTask> CBroadcastTaskPtr;        // 智能指针

#endif // BROADCAST_TASK_H
