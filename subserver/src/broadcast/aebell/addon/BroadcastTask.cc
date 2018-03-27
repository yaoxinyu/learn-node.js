/**
* 广播任务类实现文件
*/

#include "BroadcastTask.h"

CBroadcastTask::CBroadcastTask()
{
}

CBroadcastTask::~CBroadcastTask()
{
}

void CBroadcastTask::SetTaskBaseInfo(uint64 uTaskInfo)
{
    m_uTaskInfo = uTaskInfo;
}

void CBroadcastTask::SetReqData(ReqTaskInfo& reqInfo)
{
    m_reqData = reqInfo;
}

void CBroadcastTask::SetRspData(ResTaskInfo& resInfo)
{
    m_rspData = resInfo;
}
