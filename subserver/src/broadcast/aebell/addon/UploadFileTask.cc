/**
* 上传任务类实现文件
*/

#include <fstream>
#include "UploadFileTask.h"
#include "AebellBroadcast.h"
#include "AebellBusiThread.h"

CUploadFileTask::CUploadFileTask(UploadTaskInfo& taskInfo)
    : hDLL_(NULL)
    , m_bTaskRunning(false)
    , m_dwStartTick(0)
    , m_bUploaded(false)
    , m_taskInfo(taskInfo)
{
}

CUploadFileTask::~CUploadFileTask()
{
}

bool CUploadFileTask::IsTaskTimeout()
{
    if (m_dwStartTick && GetTickCount() - m_dwStartTick > UPLOAD_TIMEOUT)
    {
        return true;
    }
    return false;
}

// 上传文件
void CUploadFileTask::DealUploadFileTask()
{
    UploadFileOperInfo& fileInfo = m_taskInfo.uploadInfo;
    printf("upload thread:upload file[fileName=%s,fileSize=%lu,filePath=%s].\n", fileInfo.fileName.c_str(),
        fileInfo.fileSize, fileInfo.filePath.c_str());
    printf("upload thread:upload sessionId=%d.\n", m_taskInfo.iSessionId);

    // 将路径转换为宽字符
    int len = MultiByteToWideChar(CP_UTF8, 0, fileInfo.filePath.c_str(), fileInfo.filePath.length(), NULL, 0);
    wchar_t* wFilePath = new wchar_t[len + 1];
    MultiByteToWideChar(CP_UTF8, 0, fileInfo.filePath.c_str(), fileInfo.filePath.length(), wFilePath, len);
    wFilePath[len] = '\0';
    ifstream in(wFilePath, ios::beg | ios::binary);
    if (!in.is_open())
    {
        printf("file open fail!\n");
        in.close();
        in.open(fileInfo.filePath, ios::beg | ios::binary);
        if (!in.is_open())
        {
            printf("file retry open fail!\n");
            // 文件打开失败，设置任务失败
            onUploadTaskEnd(false);
            return;
        }
    }

    in.seekg(0, in.end);
    uint64 uFileSize = in.tellg();
    in.seekg(0, in.beg);
    uint64 uLeftSize = uFileSize;
    while (uLeftSize > 0)
    {
        string strData;
        strData.resize(DATA_PIECE_SIZE);
        int nLength = uLeftSize > DATA_PIECE_SIZE ? DATA_PIECE_SIZE : uLeftSize;
        in.read((char*)strData.c_str(), nLength);

        uploadFileData(fileInfo.iSessionId, strData);

        uLeftSize -= nLength;

        Sleep(15);
    }
    in.close();

    if (uFileSize > 0 && uLeftSize == 0)
    {
        uploadFileFinish(fileInfo.iSessionId);
    }
}

void CUploadFileTask::DoUpload()
{
    if (m_bUploaded)
        return;

    if (m_bTaskRunning) {
        // 尚未获取到上传会话ID
        if (m_taskInfo.iSessionId == 0)
            return;

        // 上传文件数据
        DealUploadFileTask();
    }
    else
    {
        // 启动任务
        m_bTaskRunning = true;
        m_dwStartTick = GetTickCount();
        printf("upload task start,taskId=%lu\n", m_taskInfo.taskId);

        GetUploadSession();
    }
}

void CUploadFileTask::GetUploadSession()
{
    if (hDLL_)
    {
//        string strFileName = getUtf8String(m_taskInfo.uploadInfo.fileName.c_str()); // 转成utf-8
        string strFileName = m_taskInfo.uploadInfo.fileName;
        NET_RESOURCE resource;
        resource.nULid = 0;
        resource.strFName = strFileName;
        resource.strFAlais = strFileName;
        resource.nFType = m_taskInfo.uploadInfo.fileType; // 0广播声音； 1报警声音

        // 判断文件是否存在
        int iFileID = 0;
        if (CAEBELLBusiThread::GetInstance().GetIDByFileName(strFileName, iFileID))
        {
            printf("need delete fileId=%d\n", iFileID);
            // 先删除文件，再上传
            DeleteFileFunc pDelFile = (DeleteFileFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_DeleteFile");
            if (pDelFile) {
                pDelFile(iFileID, OnOperateResourceCB, dwUser_);
            }
            Sleep(30);
        }

        UploadFileFunc pFunc = (UploadFileFunc)GetProcAddress(hDLL_, "AEBELL_IPCAST_UploadFile");
        if (pFunc) {
            pFunc(resource, UploadFileCB, OnOperateResourceCB, dwUser_);
        }
    }
}

void CUploadFileTask::uploadFileData(unsigned short uSessionId, string& strFileData)
{
    if (hDLL_)
    {
        UploadFileDataFunc pFunc = (UploadFileDataFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_UploadDataInFile");
        if (pFunc) {
            pFunc(uSessionId, strFileData, NULL, NULL, dwUser_);
        }
    }
}

void CUploadFileTask::uploadFileFinish(unsigned short uSessionId)
{
    if (hDLL_)
    {
        UploadFinishFunc pFinishFunc = (UploadFinishFunc)GetProcAddress(hDLL_,"AEBELL_IPCAST_FinishUploadingFile");
        if (pFinishFunc) {
            pFinishFunc(uSessionId, OnFinishUploadFileCB, NULL, dwUser_);
        }
    }
}

void CUploadFileTask::onUploadTaskEnd(bool bRes/*=true*/)
{
    // 保存任务回复信息
    if (m_taskInfo.taskId > 0)
    {
        ResTaskInfo resInfo;
        resInfo.taskType = TASK_TYPE::UPLOAD_FILE;
        resInfo.taskId = m_taskInfo.taskId;
        resInfo.operRet = bRes ? 1 : 0;
        resInfo.bRespond = true;
        CAEBELLBusiThread::GetInstance().setTaskResInfo(m_taskInfo.taskId, resInfo);
    }

    // 设置任务结束标记
    m_bUploaded = true;

    printf("upload finish[result=%d],taskId=%d\n", bRes, m_taskInfo.taskId);
}
