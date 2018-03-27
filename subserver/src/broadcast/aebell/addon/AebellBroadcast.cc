/**
 * ��ģ��Ϊnode��C++��չģ�飬���ڵ������籴���㲥dll�ӿ�
 * Created by yaoxinyu on 2017/9/19.
 * modify by yaoxinyu on 2017/11/6.
 */

#include "AebellBroadcast.h"
#include "AebellBusiThread.h"
#include "AebellUploadThread.h"


/*********************************************************************************/
/********************************���⵼���ӿ�**************************************/
/*********************************************************************************/
// ����ģ��
void startModule(const FunctionCallbackInfo<Value>& args) {
    CAEBELLBusiThread::GetInstance().startModule();
}

// ֹͣģ��
void stopModule(const FunctionCallbackInfo<Value>& args) {
    CAEBELLBusiThread::GetInstance().stopModule();
}

/**
 * ��¼���籴���㲥����
 * @param args[0] ��¼��Ϣ
 */
void login(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // �ⲿ�����������Ϣ, ʹ��Cast������ת��
    Local<Object> loginInfo = Local<Object>::Cast(args[0]);
    // �û���
    Local<String> userName = Local<String>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "userName")));
    std::string strName = std::string(*(v8::String::Utf8Value(userName)));
    // ����
    Local<String> passwd = Local<String>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "passwd")));
    std::string strPasswd = std::string(*(v8::String::Utf8Value(passwd)));
    // IP
    Local<String> IP = Local<String>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "IP")));
    std::string strIP = std::string(*(v8::String::Utf8Value(IP)));
    // �˿�
    Local<Uint32> port = Local<Uint32>::Cast(loginInfo->Get(String::NewFromUtf8(isolate, "port")));
    unsigned int iPort = port->Uint32Value();

    // ����
   LOGIN_REQUEST loginReq;
   loginReq.strName = strName;
   loginReq.strPwd = strPasswd;
   loginReq.strGUID = "";
   loginReq.uID = 0;
   loginReq.bIsNewID = true;
   printf("LoginInfo:IP[%s],port[%d],userName[%s],password[%s]\n", strIP.c_str(), iPort, strName.c_str(),
        strPasswd.c_str());

    // �ⲿ�������÷���ֵ
    bool bRes = CAEBELLBusiThread::GetInstance().login(strIP, iPort, loginReq);
    args.GetReturnValue().Set(bRes);
}

/**
 * �˳�
 */
void logout(const FunctionCallbackInfo<Value>& args) {
    bool bRes = CAEBELLBusiThread::GetInstance().logout();
    args.GetReturnValue().Set(bRes);
}

/**
 * ��ѯ�ļ��б�
 * @param args[0] taskId
 */
void queryAllFile(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    printf("query file taskId[%u]\n", uTaskId->Uint32Value());
    CAEBELLBusiThread::GetInstance().queryAllFileTask(uTaskId->Uint32Value());
}

/**
 * ע���豸״̬���ͻص�����
 */
void registerDevStatusCB(const FunctionCallbackInfo<Value>& args) {
    CAEBELLBusiThread::GetInstance().registerDevStatusCB();
}

/**
 * ��ʼ�㲥
 * @param args[0] taskId
 * @param args[1] �㲥������Ϣ
 */
void startBroadcast(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // �ⲿ����Ĺ㲥��Ϣ, ʹ��Cast������ת��
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<Object> broadInfo = Local<Object>::Cast(args[1]);
    // �㲥Դ�ļ�ID
    Local<Array> arrSrcID = Local<Array>::Cast(broadInfo->Get(String::NewFromUtf8(isolate, "arraySrc")));
    // �㲥Ŀ���豸IP
    Local<Array> arrDstIP = Local<Array>::Cast(broadInfo->Get(String::NewFromUtf8(isolate, "arrayDst")));
    // �㲥����
    Local<Uint32> broadVolume = Local<Uint32>::Cast(broadInfo->Get(String::NewFromUtf8(isolate, "uVolume")));

    BroadcastOperInfo operInfo;
    operInfo.uVolume = broadVolume->Uint32Value();
    for (int i=0; i != arrSrcID->Length(); ++i)
    {
        Local<String> temp = Local<String>::Cast(arrSrcID->Get(i));
        std::string strSrcID = std::string(*(v8::String::Utf8Value(temp)));
        operInfo.arraySrc.push_back(atoll(strSrcID.c_str()));
        printf("Broadcast src fileID:%s\n", strSrcID.c_str());
    }
    for (int i=0; i != arrDstIP->Length(); ++i)
    {
        Local<String> temp = Local<String>::Cast(arrDstIP->Get(i));
        std::string strDstIP = std::string(*(v8::String::Utf8Value(temp)));
        operInfo.arrayDst.push_back(strDstIP);
        printf("Broadcast dst deviceIP:%s\n", strDstIP.c_str());
    }
    printf("BroadcastInfo:volume[%u]\n", broadVolume->Uint32Value());

    CAEBELLBusiThread::GetInstance().startBroadcastTask(uTaskId->Uint32Value(), operInfo);
}

/**
 * ��ʼ����
 * @param args[0] taskId
 * @param args[1] ����������Ϣ
 */
void startCall(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ����Ĺ㲥��Ϣ, ʹ��Cast������ת��
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<Object> callInfo = Local<Object>::Cast(args[1]);
    // ����Դ�豸IP
    Local<String> srcIP = Local<String>::Cast(callInfo->Get(String::NewFromUtf8(isolate, "src")));
    // ����Ŀ���豸IP
    Local<Array> arrDstIP = Local<Array>::Cast(callInfo->Get(String::NewFromUtf8(isolate, "dst")));
    // ��������
    Local<Uint32> callVolume = Local<Uint32>::Cast(callInfo->Get(String::NewFromUtf8(isolate, "uVolume")));

    CallOperInfo operInfo;
    std::string strSrcIP = std::string(*(v8::String::Utf8Value(srcIP)));
    operInfo.src = strSrcIP;
    printf("Call src deviceIP:%s\n", strSrcIP.c_str());
    for (int i=0; i != arrDstIP->Length(); ++i)
    {
        Local<String> temp = Local<String>::Cast(arrDstIP->Get(i));
        std::string strDstIP = std::string(*(v8::String::Utf8Value(temp)));
        operInfo.arrayDst.push_back(strDstIP);
        printf("Call dst deviceIP:%s\n", strDstIP.c_str());
    }
    printf("CallInfo:volume[%u]\n", callVolume->Uint32Value());
    operInfo.uVolume = callVolume->Uint32Value();

    CAEBELLBusiThread::GetInstance().startCallTask(uTaskId->Uint32Value(), operInfo);
}

/**
 * �����豸IPֹͣ�㲥
 * @param args[0] taskId
 * @param args[1] ֹͣ���豸IP
 */
void stopBroadcast(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<String> dstIP = Local<String>::Cast(args[1]);
    std::string strDstIP = std::string(*(v8::String::Utf8Value(dstIP)));

    // log
    printf("stop broadcast:taskId:%u,dstIP:%s.\n", uTaskId->Uint32Value(), strDstIP.c_str());

    StopOperInfo stopInfo;
    stopInfo.dst = strDstIP;

    CAEBELLBusiThread::GetInstance().stopBroadcastTask(uTaskId->Uint32Value(), stopInfo);
}

/**
 * �����豸IPֹͣ����
 * @param args[0] taskId
 * @param args[1] ֹͣ���豸IP
 */
void stopCall(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<String> dstIP = Local<String>::Cast(args[1]);
    std::string strDstIP = std::string(*(v8::String::Utf8Value(dstIP)));

    // log
    printf("stop call:taskId:%u,dstIP:%s.\n", uTaskId->Uint32Value(), strDstIP.c_str());

    StopOperInfo stopInfo;
    stopInfo.dst = strDstIP;

    CAEBELLBusiThread::GetInstance().stopCallTask(uTaskId->Uint32Value(), stopInfo);
}

/**
 * ��������
 * @param args[0] taskId
 * @param args[1] ����������Ϣ
 */
void adjustVolume(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> volumeInfo = Local<Object>::Cast(args[1]);
    // ����Ŀ���豸IP
    Local<String> dstIP = Local<String>::Cast(volumeInfo->Get(String::NewFromUtf8(isolate, "dst")));
    std::string strDstIP = std::string(*(v8::String::Utf8Value(dstIP)));
    // ������������С
    Local<Uint32> volume = Local<Uint32>::Cast(volumeInfo->Get(String::NewFromUtf8(isolate, "uVolume")));
    int iVolume = volume->Uint32Value();

    // log
    printf("adjustVolume:taskId[%u],dstIP[%s],volume[%d].\n", uTaskId, strDstIP.c_str(), iVolume);

    AdjustVolumeOperInfo adjustInfo;
    adjustInfo.sDst = strDstIP;
    adjustInfo.volume = iVolume;

    CAEBELLBusiThread::GetInstance().adjustVolumeTask(uTaskId, adjustInfo);
}

/**
 * ����豸
 * @param args[0] taskId
 * @param args[1] ��ӵ��豸��Ϣ
 */
void addDevice(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> devInfo = Local<Object>::Cast(args[1]);
    // �豸����
    Local<String> devName = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devName")));
    std::string strDevName = std::string(*(v8::String::Utf8Value(devName)));
    // �豸�ʲ����
    Local<String> devCode = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devCode")));
    std::string strDevCode = std::string(*(v8::String::Utf8Value(devCode)));
    // �豸����
    Local<Uint32> devType = Local<Uint32>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devType")));
    int iDevType = devType->Uint32Value();
    // �豸IP
    Local<String> devIP = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));

    // log
    printf("add device:taskId:%u,name:%s,devCode:%s,type:%d,IP:%s.\n", uTaskId, strDevName.c_str(),
            strDevCode.c_str(), iDevType, strDevIP.c_str());

    string devID = CAEBELLBusiThread::GetInstance().GetDeviceIdByIP(strDevIP);
    if (!devID.empty())
    {
        // �豸�Ѵ��ڣ���ɾ��
        DelOperInfo delInfo;
        delInfo.dst = devID;

        CAEBELLBusiThread::GetInstance().delDeviceTask(0, delInfo);

        Sleep(50);
    }
    AddDeviceOperInfo info;
    info.devInfo.deviceName = strDevName.c_str();
    info.devInfo.deviceCode = strDevCode;
    ConvertDeviceType(iDevType, info.devInfo.deviceType);
    info.devInfo.deviceIP = strDevIP;

    CAEBELLBusiThread::GetInstance().addDeviceTask(uTaskId, info);
}

/**
 * �޸��豸
 * @param args[0] taskId
 * @param args[1] ��ӵ��豸��Ϣ
 */
void updateDevice(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> devInfo = Local<Object>::Cast(args[1]);
    // �豸����
    Local<String> devName = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devName")));
    std::string strDevName = std::string(*(v8::String::Utf8Value(devName)));
    // �豸�ʲ����
    Local<String> devCode = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devCode")));
    std::string strDevCode = std::string(*(v8::String::Utf8Value(devCode)));
    // �豸����
    Local<Uint32> devType = Local<Uint32>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devType")));
    int iDevType = devType->Uint32Value();
    // �豸IP
    Local<String> devIP = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));
    // �豸ID
    Local<String> devId = Local<String>::Cast(devInfo->Get(String::NewFromUtf8(isolate, "devId")));
    std::string strDevId = std::string(*(v8::String::Utf8Value(devId)));

    // log
    printf("update device:taskId=%u,name=%s,devCode=%s,type=%d,IP=%s,devId=%s.\n", uTaskId, strDevName.c_str(),
            strDevCode.c_str(), iDevType, strDevIP.c_str(), strDevId.c_str());

    if (!strDevId.empty())
    {
        // �豸�Ѵ��ڣ���ɾ��
        DelOperInfo delInfo;
        delInfo.dst = strDevId;

        CAEBELLBusiThread::GetInstance().delDeviceTask(0, delInfo);

        Sleep(50);
    }
    AddDeviceOperInfo info;
    info.devInfo.deviceName = strDevName.c_str();
    info.devInfo.deviceCode = strDevCode;
    ConvertDeviceType(iDevType, info.devInfo.deviceType);
    info.devInfo.deviceIP = strDevIP;
    info.devInfo.deviceID = strDevId; // �����豸ʱ��deviceID����

    CAEBELLBusiThread::GetInstance().updateDeviceTask(uTaskId, info);
}

/**
 * ɾ���豸
 * @param args[0] taskId
 * @param args[1] ɾ�����豸ID
 */
void delDevice(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> uTaskId = Local<Uint32>::Cast(args[0]);
    Local<String> devId = Local<String>::Cast(args[1]);
    std::string strDevId = std::string(*(v8::String::Utf8Value(devId)));

    // log
    printf("delete device:taskId:%u,devId:%s.\n", uTaskId->Uint32Value(), strDevId.c_str());

    DelOperInfo delInfo;
    delInfo.dst = strDevId;

    CAEBELLBusiThread::GetInstance().delDeviceTask(uTaskId->Uint32Value(), delInfo);
}

/**
 * �ϴ��ļ�
 * @param args[0] taskId
 * @param args[1] �ļ���Ϣ
 */
void uploadFile(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> fileInfo = Local<Object>::Cast(args[1]);
    // �ļ�����
    Local<String> fileName = Local<String>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "fileName")));
    std::string strFileName = std::string(*(v8::String::Utf8Value(fileName)));
    // �ļ�����
    Local<Uint32> fileType = Local<Uint32>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "fileType")));
    int iFileType = fileType->Uint32Value();
    // �ļ���С
    Local<Uint32> fileSize = Local<Uint32>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "fileSize")));
    uint32 uFileSize = fileSize->Uint32Value();
    // �ļ�����·��
    Local<String> filePath = Local<String>::Cast(fileInfo->Get(String::NewFromUtf8(isolate, "filePath")));
    std::string strFilePath = std::string(*(v8::String::Utf8Value(filePath)));

    // log
    printf("upload file:taskId:%u,fileName:%s,fileType:%d,fileSize:%u,filePath:%s\n", uTaskId, strFileName.c_str(),
        iFileType, uFileSize, strFilePath.c_str());

    UploadFileOperInfo info;
    info.fileType = iFileType;
    info.fileSize = uFileSize;
    info.fileName = strFileName;
    info.filePath = strFilePath;

    CAEBELLBusiThread::GetInstance().uploadFileTask(uTaskId, info);
}

/**
 * ��ӷ���
 * @param args[0] taskId
 * @param args[1] ��ӵķ�����Ϣ
 */
void addPlan(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> planInfo = Local<Object>::Cast(args[1]);
    // ��������
    Local<String> planName = Local<String>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "planName")));
    std::string strPlanName = std::string(*(v8::String::Utf8Value(planName)));
    // log
    printf("add plan:taskId=%u,planName=%s\n", uTaskId, strPlanName.c_str());

    // �����б���Ϣ
    AddUpdPlanOperInfo info;
    info.planName = strPlanName;
    Local<Array> taskList = Local<Array>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "taskList")));
    for (int i=0; i != taskList->Length(); ++i)
    {
        TimerTaskInfo taskInfo;
        Local<Object> temp = Local<Object>::Cast(taskList->Get(i));
        // ��������
        Local<String> taskName = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "taskName")));
        taskInfo.taskName = std::string(*(v8::String::Utf8Value(taskName)));
        // ����ִ��ʱ����Ϣ
        Local<String> beginTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strBeginTime")));
        taskInfo.strBeginTime = std::string(*(v8::String::Utf8Value(beginTime)));
        Local<String> endTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strEndTime")));
        taskInfo.strEndTime = std::string(*(v8::String::Utf8Value(endTime)));
        Local<String> workTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strDoworkTime")));
        taskInfo.strDoworkTime = std::string(*(v8::String::Utf8Value(workTime)));
        Local<String> runDate = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskRunDate")));
        taskInfo.strTaskRunDate = std::string(*(v8::String::Utf8Value(runDate)));
        Local<String> finishTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskFinishTime")));
        taskInfo.strTaskFinishTime = std::string(*(v8::String::Utf8Value(finishTime)));
        // ѭ��ģʽ
        Local<Uint32> cycleMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "nCycleMode")));
        taskInfo.nCycleMode = cycleMode->Uint32Value();
        // �豸�б���Ϣ
        Local<Array> devList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "devList")));
        for (int j=0; j != devList->Length(); ++j) {
            Local<String> devIP = Local<String>::Cast(devList->Get(j));
            std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));
            taskInfo.vDevList.push_back(strDevIP);
        }
        // �ļ��б���Ϣ
        Local<Array> fileList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "fileList")));
        for (int k=0; k != fileList->Length(); ++k) {
            Local<Uint32> fileID = Local<Uint32>::Cast(fileList->Get(k));
            uint32 uFileID = fileID->Uint32Value();
            taskInfo.vFileList.push_back(uFileID);
        }
        // ������Ϣ
        Local<Uint32> playMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "playMode")));
        taskInfo.playMode = playMode->Uint32Value();
        Local<Uint32> playTimes = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "replayTimes")));
        taskInfo.replayTimes = playTimes->Uint32Value();
        Local<Uint32> volume = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "volume")));
        taskInfo.volume = volume->Uint32Value();

        printf("add taskInfo:taskName=%s,cycleMode=%d,playMode=%d,volume=%d\n", taskInfo.taskName.c_str(),
            taskInfo.nCycleMode, taskInfo.playMode, taskInfo.volume);

        info.taskList.push_back(taskInfo);
    }

    string strPolicyId = CAEBELLBusiThread::GetInstance().GetPlanIDByName(strPlanName);
    if (!strPolicyId.empty())
    {
        // �����Ѵ��ڣ���ɾ��
        DelPlanOperInfo delInfo;
        delInfo.planName = strPlanName;
        CAEBELLBusiThread::GetInstance().delPlanTask(0, delInfo);

        Sleep(100);
    }

    CAEBELLBusiThread::GetInstance().addPlanTask(uTaskId, info);
}

/**
 * �޸ķ���
 * @param args[0] taskId
 * @param args[1] �޸ĵķ�����Ϣ
 */
void updatePlan(const FunctionCallbackInfo<Value>& args) {
     Isolate* isolate = args.GetIsolate();
     // �ⲿ�������Ϣ, ʹ��Cast������ת��
     Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
     uint32 uTaskId = taskId->Uint32Value();
     Local<Object> planInfo = Local<Object>::Cast(args[1]);
     // ��������
     Local<String> planName = Local<String>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "planName")));
     std::string strPlanName = std::string(*(v8::String::Utf8Value(planName)));
     // log
     printf("update plan:taskId=%u,planName=%s\n", uTaskId, strPlanName.c_str());

     // �����б���Ϣ
     AddUpdPlanOperInfo info;
     info.planName = strPlanName;
     Local<Array> taskList = Local<Array>::Cast(planInfo->Get(String::NewFromUtf8(isolate, "taskList")));
     for (int i=0; i != taskList->Length(); ++i)
     {
         TimerTaskInfo taskInfo;
         Local<Object> temp = Local<Object>::Cast(taskList->Get(i));
         // ��������
         Local<String> taskName = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "taskName")));
         taskInfo.taskName = std::string(*(v8::String::Utf8Value(taskName)));
         // ����ִ��ʱ����Ϣ
         Local<String> beginTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strBeginTime")));
         taskInfo.strBeginTime = std::string(*(v8::String::Utf8Value(beginTime)));
         Local<String> endTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strEndTime")));
         taskInfo.strEndTime = std::string(*(v8::String::Utf8Value(endTime)));
         Local<String> workTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strDoworkTime")));
         taskInfo.strDoworkTime = std::string(*(v8::String::Utf8Value(workTime)));
         Local<String> runDate = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskRunDate")));
         taskInfo.strTaskRunDate = std::string(*(v8::String::Utf8Value(runDate)));
         Local<String> finishTime = Local<String>::Cast(temp->Get(String::NewFromUtf8(isolate, "strTaskFinishTime")));
         taskInfo.strTaskFinishTime = std::string(*(v8::String::Utf8Value(finishTime)));
         // ѭ��ģʽ
         Local<Uint32> cycleMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "nCycleMode")));
         taskInfo.nCycleMode = cycleMode->Uint32Value();
         // �豸�б���Ϣ
         Local<Array> devList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "devList")));
         for (int j=0; j != devList->Length(); ++j) {
             Local<String> devIP = Local<String>::Cast(devList->Get(j));
             std::string strDevIP = std::string(*(v8::String::Utf8Value(devIP)));
             taskInfo.vDevList.push_back(strDevIP);
         }
         // �ļ��б���Ϣ
         Local<Array> fileList = Local<Array>::Cast(temp->Get(String::NewFromUtf8(isolate, "fileList")));
         for (int k=0; k != fileList->Length(); ++k) {
             Local<Uint32> fileID = Local<Uint32>::Cast(fileList->Get(k));
             uint32 uFileID = fileID->Uint32Value();
             taskInfo.vFileList.push_back(uFileID);
         }
         // ������Ϣ
         Local<Uint32> playMode = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "playMode")));
         taskInfo.playMode = playMode->Uint32Value();
         Local<Uint32> playTimes = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "replayTimes")));
         taskInfo.replayTimes = playTimes->Uint32Value();
         Local<Uint32> volume = Local<Uint32>::Cast(temp->Get(String::NewFromUtf8(isolate, "volume")));
         taskInfo.volume = volume->Uint32Value();

         printf("update taskInfo:taskName=%s,cycleMode=%d,playMode=%d,volume=%d\n", taskInfo.taskName.c_str(),
             taskInfo.nCycleMode, taskInfo.playMode, taskInfo.volume);

         info.taskList.push_back(taskInfo);
     }

    string strPolicyId = CAEBELLBusiThread::GetInstance().GetPlanIDByName(strPlanName);
    if (!strPolicyId.empty())
    {
        // �����Ѵ��ڣ���ɾ��
        DelPlanOperInfo delInfo;
        delInfo.planName = strPlanName;
        CAEBELLBusiThread::GetInstance().delPlanTask(0, delInfo);

        Sleep(100);
    }

     CAEBELLBusiThread::GetInstance().updatePlanTask(uTaskId, info);
}

/**
 * ɾ������
 * @param args[0] taskId
 * @param args[1] ɾ���ķ�����Ϣ
 */
void delPlan(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> delPlanInfo = Local<Object>::Cast(args[1]);
    // ��������
    Local<String> planName = Local<String>::Cast(delPlanInfo->Get(String::NewFromUtf8(isolate, "planName")));
    std::string strPlanName = std::string(*(v8::String::Utf8Value(planName)));

    // log
    printf("delete plan:taskId=%u,planName=%s\n", uTaskId, strPlanName.c_str());

    DelPlanOperInfo info;
    info.planName = strPlanName;
    CAEBELLBusiThread::GetInstance().delPlanTask(uTaskId, info);
}

/**
 * ��ӻỰ���豸
 * @param args[0] taskId
 * @param args[1] ������Ϣ
 */
void addSessionDev(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> sessionDevInfo = Local<Object>::Cast(args[1]);
    // �Ự���豸IP
    Local<String> ssDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "sessionDevIP")));
    std::string strSessionDevIP = std::string(*(v8::String::Utf8Value(ssDevIP)));
    // ��ӵ��豸IP
    Local<String> addDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strAddDevIP = std::string(*(v8::String::Utf8Value(addDevIP)));

    // log
    printf("add session device:taskId=%u,deviceIP=%s\n", uTaskId, strAddDevIP.c_str());

    SessionDevOperInfo info;
    info.sessionDevIP = strSessionDevIP;
    info.devIP = strAddDevIP;
    CAEBELLBusiThread::GetInstance().addSessionDevTask(uTaskId, info);
}

/**
 * ɾ���Ự���豸
 * @param args[0] taskId
 * @param args[1] ������Ϣ
 */
void delSessionDev(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // �ⲿ�������Ϣ, ʹ��Cast������ת��
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    Local<Object> sessionDevInfo = Local<Object>::Cast(args[1]);
    // �Ự���豸IP
    Local<String> ssDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "sessionDevIP")));
    std::string strSessionDevIP = std::string(*(v8::String::Utf8Value(ssDevIP)));
    // ɾ�����豸IP
    Local<String> delDevIP = Local<String>::Cast(sessionDevInfo->Get(String::NewFromUtf8(isolate, "devIP")));
    std::string strDelDevIP = std::string(*(v8::String::Utf8Value(delDevIP)));

    // log
    printf("delete session device:taskId=%u,deviceIP=%s\n", uTaskId, strDelDevIP.c_str());

    SessionDevOperInfo info;
    info.sessionDevIP = strSessionDevIP;
    info.devIP = strDelDevIP;
    CAEBELLBusiThread::GetInstance().delSessionDevTask(uTaskId, info);
}

/**
 * ��ȡ������������Ϣ
 * @param args[0] taskId
 * @return {object} ��ͬ�������ͻظ���ͬ����
 */
void getTaskResponse(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Uint32> taskId = Local<Uint32>::Cast(args[0]);
    uint32 uTaskId = taskId->Uint32Value();
    // ������Ϣ
    Local<Object> respInfo = Object::New(isolate);

    ResTaskInfo& resInfo = CAEBELLBusiThread::GetInstance().getTaskResInfo(uTaskId);
    if (resInfo.bRespond)
    {
        printf("type:%d, taskId:%lu, operRet:%d\n", resInfo.taskType, resInfo.taskId, resInfo.operRet);
        if (resInfo.taskType == TASK_TYPE::QUERY_FILE)
        {
            // ��ѯ�ļ��б�Ĳ�������ظ�
            ResFileInfo& resFileInfo = resInfo.fileList;
            // C++���ݽṹת��Ϊjs�����ݽṹ
            Local<Array> arrFile = Array::New(isolate);
            for (int i=0; i != resFileInfo.vFiles.size(); ++i)
            {
                FileInfo file = resFileInfo.vFiles[i];
                // Object���͵�����
                Local<Object> fileInfo = Object::New(isolate);
                // ����ĸ�ֵ
                Local<Number> temp = v8::Number::New(isolate, file.nFileID);
                Local<Uint32> fileID = Local<Uint32>::Cast(temp);
                Local<String> fileName = String::NewFromUtf8(isolate, file.sName.c_str());
                fileInfo->Set(v8::String::NewFromUtf8(isolate, "fileId"), fileID);
                fileInfo->Set(v8::String::NewFromUtf8(isolate, "fileName"), fileName);

                arrFile->Set(i, fileInfo);
            }
            respInfo->Set(v8::String::NewFromUtf8(isolate, "fileResp"), arrFile);
        }
        else if (resInfo.taskType == TASK_TYPE::ADD_DEVICE || resInfo.taskType == TASK_TYPE::UPDATE_DEVICE
                || resInfo.taskType == TASK_TYPE::DEL_DEVICE)
        {
            Local<Number> errorCode = v8::Number::New(isolate, resInfo.errorCode);
            Local<Uint32> uErrorCode = Local<Uint32>::Cast(errorCode);
            Local<Number> operRet = v8::Number::New(isolate, resInfo.operRet);
            Local<Uint32> uOperRet = Local<Uint32>::Cast(operRet);
            Local<String> devId = String::NewFromUtf8(isolate, resInfo.devId.c_str());
            respInfo->Set(v8::String::NewFromUtf8(isolate, "errCode"), uErrorCode);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "operRet"), uOperRet);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "devId"), devId);
        }
        else
        {
            // ��������Ĳ�������ظ�
            Local<Number> temp = v8::Number::New(isolate, resInfo.taskType);
            Local<Uint32> uTaskType = Local<Uint32>::Cast(temp);
            temp = v8::Number::New(isolate, resInfo.operRet);
            Local<Uint32> uOperRet = Local<Uint32>::Cast(temp);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "optType"), uTaskType);
            respInfo->Set(v8::String::NewFromUtf8(isolate, "operRet"), uOperRet);
        }
        CAEBELLBusiThread::GetInstance().removeTaskPtrByID(uTaskId);
    }

    // �ص����ⲿ
    Local<Number> temp = v8::Number::New(isolate, resInfo.bRespond);
    Local<Uint32> bRespond = Local<Uint32>::Cast(temp);
    respInfo->Set(v8::String::NewFromUtf8(isolate, "bRespond"), bRespond);
    args.GetReturnValue().Set(respInfo);
}

/**
 * ��ȡ�豸״̬������Ϣ
 */
void getAutoDeviceStatus(const FunctionCallbackInfo<Value>& args)
{
    AutoLock lock(autoInfoLock_);

    Isolate* isolate = args.GetIsolate();
    // C++���ݽṹת��Ϊjs�����ݽṹ
    Local<Array> arrDevStatus = Array::New(isolate);
    for (int i=0; i != vAutoPushData_.size(); ++i)
    {
        DeviceStatusInfo status = vAutoPushData_[i];
        // Object���͵�����
        Local<Object> statusInfo = Object::New(isolate);
        // ����ĸ�ֵ
        Local<String> sDeviceIP = String::NewFromUtf8(isolate, status.sDeviceIP.c_str());
        Local<Number> tempState = v8::Number::New(isolate, status.uState);
        Local<Uint32> uState = Local<Uint32>::Cast(tempState);
        Local<Number> tempVolume = v8::Number::New(isolate, status.uVolume*2);  // �������ظ��ⲿ�ٷֱ�
        Local<Uint32> uVolume = Local<Uint32>::Cast(tempVolume);

        statusInfo->Set(v8::String::NewFromUtf8(isolate, "deviceIP"), sDeviceIP);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uState"), uState);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uVolume"), uVolume);

        arrDevStatus->Set(i, statusInfo);
    }

    Local<Object> respInfo = Object::New(isolate);
    respInfo->Set(v8::String::NewFromUtf8(isolate, "deviceResp"), arrDevStatus);

    // �ص����ⲿ
    args.GetReturnValue().Set(respInfo);
    vAutoPushData_.clear();
}

 /**
  * ��ȡ�����豸״̬��Ϣ
  */
void getAllDeviceStatus(const FunctionCallbackInfo<Value>& args)
{
    AutoLock lock(allDevStatusLock_);

    Isolate* isolate = args.GetIsolate();
    // C++���ݽṹת��Ϊjs�����ݽṹ
    Local<Array> arrDevStatus = Array::New(isolate);
    for (int i=0; i != vAllDevStatusData_.size(); ++i)
    {
        DeviceStatusInfo status = vAllDevStatusData_[i];
        // Object���͵�����
        Local<Object> statusInfo = Object::New(isolate);
        // ����ĸ�ֵ
        Local<String> sDeviceIP = String::NewFromUtf8(isolate, status.sDeviceIP.c_str());
        Local<Number> tempState = v8::Number::New(isolate, status.uState);
        Local<Uint32> uState = Local<Uint32>::Cast(tempState);
        Local<Number> tempVolume = v8::Number::New(isolate, status.uVolume*2);  // �������ظ��ⲿ�ٷֱ�
        Local<Uint32> uVolume = Local<Uint32>::Cast(tempVolume);

        statusInfo->Set(v8::String::NewFromUtf8(isolate, "deviceIP"), sDeviceIP);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uState"), uState);
        statusInfo->Set(v8::String::NewFromUtf8(isolate, "uVolume"), uVolume);

        arrDevStatus->Set(i, statusInfo);
    }

    Local<Object> respInfo = Object::New(isolate);
    respInfo->Set(v8::String::NewFromUtf8(isolate, "deviceResp"), arrDevStatus);

    // �ص����ⲿ
    args.GetReturnValue().Set(respInfo);
    vAllDevStatusData_.clear();
}

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
// �㲥�Ļص�
void BroadcastCB(USHORT uSessionID, DWORD dwUser)
{
    printf("Establish broadcast session:[%u]\n", uSessionID);

    // ��������ظ���Ϣ
    CAEBELLBusiThread::GetInstance().onCurTaskFinish();
}

// �����Ļص�
void CallCB(USHORT uSessionID, DWORD dwUser)
{
    printf("Establish call session:[%u]\n", uSessionID);

    // ��������ظ���Ϣ
    CAEBELLBusiThread::GetInstance().onCurTaskFinish();
}

// ��ѯ�����ļ�����ص�
void QueryAllFileCB(const vector<NET_FILE>& tanFiles, DWORD dwUser)
{
    printf("get all file info...\n");

    CAEBELLBusiThread::GetInstance().GetAllFileCB(tanFiles);

    ResFileInfo fileInfos;
    for each (auto i in tanFiles)
    {
        FileInfo file;
        file.nFileID = i.nID;
        file.sName = getUtf8String(i.strAlais.c_str());

        fileInfos.vFiles.push_back(file);
    }

    // ��������ظ���Ϣ
    CAEBELLBusiThread::GetInstance().onGetFileFinish(fileInfos);
}

// ��ʱ��ѯ�����ļ�����ص�
void TimerQueryAllFileCB(const vector<NET_FILE>& tanFiles, DWORD dwUser)
{
    printf("timer get all file info...\n");
    CAEBELLBusiThread::GetInstance().GetAllFileCB(tanFiles);
}

// ֹͣ�㲥ʱ��ѯ�豸״̬�ص�
void QueryDevStatCB_Broadcast(DEVICE_STATUS status, DWORD dwUser)
{
    unsigned short uSessionID = status.uSessionId;
    printf("Stop broadcast:sessionID[%u]\n", uSessionID);
    if (uSessionID != 0)
    {
        CAEBELLBusiThread::GetInstance().stopBroadcast(uSessionID);
    }
    else
    {
        // ���豸�ǿ���״̬��ֱ�ӻظ������ɹ�
        // ��������ظ���Ϣ
        CAEBELLBusiThread::GetInstance().onCurTaskFinish();
    }
}

// ֹͣ����ʱ��ѯ�豸״̬�ص�
void QueryDevStatCB_Call(DEVICE_STATUS status, DWORD dwUser)
{
    unsigned short uSessionID = status.uSessionId;
    printf("Stop call:sessionID[%u]\n", uSessionID);
    if (uSessionID != 0)
    {
        CAEBELLBusiThread::GetInstance().stopCall(uSessionID);
    }
    else
    {
        // ���豸�ǿ���״̬��ֱ�ӻظ������ɹ�
        // ��������ظ���Ϣ
        CAEBELLBusiThread::GetInstance().onCurTaskFinish();
    }
}

// ֹͣ�㲥/����/�Խ�/�Ự�ص�
void StopOperationCB(INT nOperateType, DWORD dwUser)
{
    printf("StopOperationCB:result=%d\n", nOperateType);
}

// ɾ���豸�ص�
void RemoveDeviceCB(INT nOperateType, DWORD dwUser)
{
    // ��������ظ���Ϣ
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onDeviceRemoveFinish(nOperateType, bRes);
}

// �����豸�����ص�
void SetDeviceVolumeCB(INT nOperateType, DWORD dwUser)
{
    // ��������ظ���Ϣ
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onCurTaskFinish(bRes);
}

// �ϴ��ļ� �����ص�
void UploadFileCB(INT nSessionID, DWORD dwUser)
{
    printf("upload file sessionId=%d\n", nSessionID);

    // �����ϴ��Ự�ɹ�������sessionID
    CAEBELLUploadThread::GetInstance().SetUploadSessionID(nSessionID);
}

// �ϴ��ļ����ݣ������ݣ��ص�
void UploadFileDataCB(INT nOperateType, DWORD dwUser)
{
    // do nothing
    printf("uploading......\n");
}

// ��/ɾ/����Դ�ص�
void OnOperateResourceCB(INT nOperateType, DWORD dwUser)
{
    printf("nOperateType=%d.\n", nOperateType);
}

// �ϴ��ļ�������� �ص�
void OnFinishUploadFileCB(INT nFileID, DWORD dwUser)
{
    printf("upload file success: fileID[%d].\n", nFileID);

    // ��������ظ���Ϣ
    CAEBELLUploadThread::GetInstance().onUploadTaskEnd();

    // ������ѯһ�������ļ����Ӷ�����map
    CAEBELLBusiThread::GetInstance().QueryAllFileTask(true);
}

// ����豸������Ϣ�ص�
void AddDeviceCB(INT nOperateType, DWORD dwUser)
{
    printf("add device OperateResult=%d.\n", nOperateType);

    ReqTaskInfo reqInfo = CAEBELLBusiThread::GetInstance().getCurTaskReqInfo();
    // �������豸ʧ�ܣ��ظ�����ʧ��
    if (nOperateType != 0)
    {
        // ��������ظ���Ϣ
        CAEBELLBusiThread::GetInstance().onDeviceAddFinish(nOperateType, false);
    }
    else
    {
        AddDeviceOperInfo& operInfo = reqInfo.addDevInfo;
        // �������豸ӳ��
        CAEBELLBusiThread::GetInstance().onAddNewDevice(operInfo.devInfo.deviceIP, operInfo.devInfo.deviceID);
        // ����豸������Ϣ
        CAEBELLBusiThread::GetInstance().onAddDevAttachTask(operInfo);
    }
}

// ����豸������Ϣ�ص�
void AddDeviceAttachCB(INT nOperateType, DWORD dwUser)
{
    printf("add device attach OperateResult=%d.\n", nOperateType);

    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onDeviceAddFinish(nOperateType, bRes);
}

// ��ʱ��ȡ�����豸��Ϣ�ص�
void TimerGetAllNetDevicesCB(const vector<NET_DEVICE>& tanDevices, DWORD dwUser)
{
    printf("get all device info...\n");
    CAEBELLBusiThread::GetInstance().GetAllNetDevices(tanDevices);
}

// ��ʱ��ȡ�����豸������Ϣ�ص�
void TimerGetDeviceAttachInfoCB(const vector<NET_DEVICE_ATTACH>& tanAttach, DWORD dwUser)
{
    printf("get all device attach info...\n");
    CAEBELLBusiThread::GetInstance().GetDeviceAttachInfo(tanAttach);
}

// ��ʱ��ȡ�����豸״̬�ص�
void TimerQueryAllDeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser)
{
    printf("get all device status info...\n");
    CAEBELLBusiThread::GetInstance().DeviceStatusCB(tanStatus, true);
    AutoLock lock(allDevStatusLock_);

    vAllDevStatusData_.clear();
    for(auto device : tanStatus)
    {
        DeviceStatusInfo statusInfo;
        statusInfo.uVolume = device.uVolume;
        if (CAEBELLBusiThread::GetInstance().GetIPByPhoneNum(device.uPhoneNum, statusInfo.sDeviceIP))
        {
            ConvertDeviceStatus(device.nDeviceStatus, statusInfo.uState);
            printf("get all device status:deviceIP[%s],phoneNum[%u],devStatus[%u],volume[%u]\n",
                statusInfo.sDeviceIP.c_str(), device.uPhoneNum, statusInfo.uState, statusInfo.uVolume);

            vAllDevStatusData_.push_back(statusInfo);
        }
    }
}

// �豸״̬���ͻص�
void AutoGetDeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser)
{
    printf("auto device status...\n");
    CAEBELLBusiThread::GetInstance().DeviceStatusCB(tanStatus, false);
    AutoLock lock(autoInfoLock_);

    vAutoPushData_.clear();
    bool bDevAddOrDel = false;         // �Ƿ����豸��ӻ�ɾ��
    for(auto device : tanStatus)
    {
        DeviceStatusInfo statusInfo;
        statusInfo.uVolume = device.uVolume;

        if (CAEBELLBusiThread::GetInstance().GetIPByPhoneNum(device.uPhoneNum, statusInfo.sDeviceIP))
        {
            ConvertDeviceStatus(device.nDeviceStatus, statusInfo.uState);
            printf("auto device status:deviceIP[%s],phoneNum[%u],devStatus[%u], volume[%u]\n",
                statusInfo.sDeviceIP.c_str(), device.uPhoneNum, statusInfo.uState, statusInfo.uVolume);

            vAutoPushData_.push_back(statusInfo);
        }
        // DeviceEdit
        if (DeviceStatus::DeviceAdd == device.nDeviceStatus || DeviceStatus::DeviceRemove == device.nDeviceStatus
            || DeviceStatus::DeviceEdit == device.nDeviceStatus)
        {
            bDevAddOrDel = true;
        }
    }

    if (bDevAddOrDel)
    {
        // ������ȡһ�������豸���Ӷ�������Ϣ
        CAEBELLBusiThread::GetInstance().QueryAllDevicesTask(true);
    }
}

// ��ȡ�����з����ص�
void OnGetAllPolicyCB(const vector<TASK_POLICY>& tanTaskPolicy, DWORD dwUser)
{
    printf("GetAllPolicyInfo...\n");
    CAEBELLBusiThread::GetInstance().GetAllPolicyCB(tanTaskPolicy);
}

// ����״̬���ͻص�
void OnPolicyStatusCB(POLICY_STATUS status, DWORD dwUser)
{
    printf("auto policy status...\n");
    CAEBELLBusiThread::GetInstance().AutoPolicyStatusCB(status);
}

// ��ȡ������������Ϣ�ص�
void OnPlolicyTaskCB(const vector<TASK_INFO_VIEW>& tanTaskViews, DWORD dwUser)
{
    printf("get policy task...\n");
    CAEBELLBusiThread::GetInstance().QueryPlolicyTaskCB(tanTaskViews);
}

// ���/�޸ķ����ص�
void OnAddUpdatePlanCB(INT nOperateType, DWORD dwUser)
{
    printf("add/update policy result=%d\n", nOperateType);

    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onAddPlanFinish(bRes);
}

// ��ӷ�������ص�
void OnAddPlanTaskCB(INT nOperateType, DWORD dwUser)
{
    printf("add plan task OperateResult=%d.\n", nOperateType);

    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onAddPlanTaskFinish(bRes);
}

// ��ʼ/ֹͣ��������ص�
void OnTaskOperCB(INT nOperateType, DWORD dwUser)
{
    printf("start/stop plan task OperateResult=%d.\n", nOperateType);
}

// ɾ�������ص�
void OnDelPlanCB(INT nOperateType, DWORD dwUser)
{
    printf("delete plan OperateResult=%d.\n", nOperateType);

    // ��������ظ���Ϣ
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onCurTaskFinish(bRes);
}

// ���/ɾ���Ự�豸�ص�
void OnSessionDeviceCB(INT nOperateType, DWORD dwUser)
{
    printf("add/del session device OperateResult=%d.\n", nOperateType);

    // ��������ظ���Ϣ
    bool bRes = (nOperateType == 0) ? true : false;
    CAEBELLBusiThread::GetInstance().onCurTaskFinish(bRes);
}

// ���籴���豸״̬�뷵�ظ��ⲿ���豸״̬��Ӧ��ϵ
void ConvertDeviceStatus(const int iDevStatus, uint32& uDevStatus)
{
    switch (iDevStatus)
    {
    case DeviceStatus::Disconnect:
    case DeviceStatus::RelayDisconnect:
        uDevStatus = DEVICE_STATE::DISCONNECT;
        break;
    case DeviceStatus::Free:
        uDevStatus = DEVICE_STATE::FREE;
        break;
    case DeviceStatus::CallWaiting:   // �����ȴ���
        uDevStatus = DEVICE_STATE::CALLWAITING;
        break;
    case DeviceStatus::Ringing:       // ��������
        uDevStatus = DEVICE_STATE::RINGING;
        break;
    case DeviceStatus::Calling:       // Ѱ��������
        uDevStatus = DEVICE_STATE::CALLING;
        break;
    case DeviceStatus::Talking:       // �Խ�������
        uDevStatus = DEVICE_STATE::TALKING;
        break;
    case DeviceStatus::Broadcasting:  // �㲥������
        uDevStatus = DEVICE_STATE::BROADCASTING;
        break;
    case DeviceStatus::DeviceAdd:  // �豸�����
        uDevStatus = DEVICE_STATE::FREE;
        break;
    case DeviceStatus::DeviceRemove:  // �豸��ɾ��
        uDevStatus = DEVICE_STATE::DISCONNECT;
        break;
    default:
        uDevStatus = DEVICE_STATE::FREE;
        break;
    }
}

// ���洫���豸����ת��Ϊ���籴���ڲ��豸����
void ConvertDeviceType(const int srcType, int& destType)
{
    // ���籴���ڲ�codeֵ��1��Ƶ������ 2��Ƶ������ 3IP���� 4�Խ�����վ 5������ 6�������� 7��Դ������ 8��Ƶ�ɼ��� 10ƽ��������
    switch (srcType)
    {
    case DEV_TYPE::DT_MEDIA:
        destType = 1;   // ��Ƶ������
        break;
    case DEV_TYPE::DT_CALL_TALK:
        destType = 4;   // �Խ�����վ
        break;
    case DEV_TYPE::DT_AID:
        destType = 5;   // һ��������
        break;
    case DEV_TYPE::DT_AID_PA:
        destType = 10;  // ƽ��������
        break;
    default:
        destType = 0;
        break;
    }
}

// ת��UTF-8������ַ���
string getUtf8String(const char* pSrc)
{
    string result = "";
    do
    {
        wchar_t* pWideText = NULL;
        int size = MultiByteToWideChar(CP_ACP, 0, pSrc, -1, NULL, 0);
        if (size > 0)
        {
            pWideText = new wchar_t[size + 1];
            memset(pWideText, 0, size);
            if (MultiByteToWideChar(CP_ACP, 0, pSrc, -1, (LPWSTR)pWideText, size) == 0)
            {
                delete []pWideText;
                pWideText = NULL;
                break;
            }
            else
            {
                int size = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pWideText, -1, NULL, 0, NULL, NULL);
                if (size > 0)
                {
                    char* pText = new char[size + 1];
                    memset(pText, 0, size);
                    if (WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pWideText, -1, pText, size, NULL, NULL) == 0)
                    {
                        delete[] pText;
                        pText = NULL;
                        break;
                    }
                    result = pText;
                }
            }
        }
    } while (false);

    return result;
}

// ת��GBK������ַ���
string getGBKString(const char* pSrc)
{
    string result = "";
    do
    {
        wchar_t* pWideText = NULL;
        int size = MultiByteToWideChar(CP_UTF8, 0, pSrc, -1, NULL, 0);
        if (size > 0)
        {
            pWideText = new wchar_t[size + 1];
            memset(pWideText, 0, size);
            if (MultiByteToWideChar(CP_UTF8, 0, pSrc, -1, (LPWSTR)pWideText, size) == 0)
            {
                delete []pWideText;
                pWideText = NULL;
                break;
            }
            else
            {
                int size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pWideText, -1, NULL, 0, NULL, NULL);
                if (size > 0)
                {
                    char* pText = new char[size + 1];
                    memset(pText, 0, size);
                    if (WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pWideText, -1, pText, size, NULL, NULL) == 0)
                    {
                        delete[] pText;
                        pText = NULL;
                        break;
                    }
                    result = pText;
                }
            }
        }
    } while (false);

    return result;
}

// �����豸ʱ�������豸ID
string GenerateGUID()
{
    // ��ʼ��COM
    CoInitialize(NULL);

    char buf[64] = { 0 };
    GUID guid;
    if (S_OK == ::CoCreateGuid(&guid))
    {
        _snprintf_s(buf, sizeof(buf)
            , "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"
            , guid.Data1
            , guid.Data2
            , guid.Data3
            , guid.Data4[0], guid.Data4[1]
            , guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
            , guid.Data4[6], guid.Data4[7]
            );
    }

    // ж��COM
    CoUninitialize();

    string result = buf;
    return result;
}

// ��ȡ��Ӧ�豸���͵��豸��������
string GetDeviceTypeName(int devType)
{
    switch (devType)
    {
    case DEV_TYPE::DT_MEDIA:
        return getUtf8String("��Ƶ������");
    case DEV_TYPE::DT_CALL_TALK:
        return getUtf8String("�Խ�����վ");
    case DEV_TYPE::DT_AID:
        return getUtf8String("һ��������");
    default:
        return "";
    }
}

// ģ���ʼ��������ע��ģ�鹦�ܣ������ӿڹ��ⲿ����
void RegisterModule(Local<Object> exports) {
    NODE_SET_METHOD(exports, "startModule", startModule);                        // ����ģ��ӿ�
    NODE_SET_METHOD(exports, "stopModule", stopModule);                          // ֹͣģ��ӿ�
    NODE_SET_METHOD(exports, "login", login);                                    // ��¼�ӿ�
    NODE_SET_METHOD(exports, "logout", logout);                                  // �˳��ӿ�
    NODE_SET_METHOD(exports, "queryAllFile", queryAllFile);                      // ��ѯ�����ļ��ӿ�
    NODE_SET_METHOD(exports, "registerDeviceStatusCB", registerDevStatusCB);     // ע���豸״̬���ͻص��ӿ�
    NODE_SET_METHOD(exports, "startBroadcast", startBroadcast);                  // ��ʼ�㲥
    NODE_SET_METHOD(exports, "startCall", startCall);                            // ��ʼѰ��
    NODE_SET_METHOD(exports, "stopBroadcast", stopBroadcast);                    // ֹͣ�㲥
    NODE_SET_METHOD(exports, "adjustVolume", adjustVolume);                      // ��������
    NODE_SET_METHOD(exports, "stopCall", stopCall);                              // ֹͣѰ��
    NODE_SET_METHOD(exports, "addDevice", addDevice);                            // �����豸
    NODE_SET_METHOD(exports, "updateDevice", updateDevice);                      // �޸��豸
    NODE_SET_METHOD(exports, "delDevice", delDevice);                            // ɾ���豸
    NODE_SET_METHOD(exports, "uploadFile", uploadFile);                          // �ϴ��ļ�
    NODE_SET_METHOD(exports, "addPlan", addPlan);                                // ��ӷ���
    NODE_SET_METHOD(exports, "delPlan", delPlan);                                // ɾ������
    NODE_SET_METHOD(exports, "updatePlan", updatePlan);                          // �޸ķ���
    NODE_SET_METHOD(exports, "addSessionDev", addSessionDev);                    // ��ӻỰ���豸
    NODE_SET_METHOD(exports, "delSessionDev", delSessionDev);                    // ɾ���Ự���豸
    NODE_SET_METHOD(exports, "getTaskResponse", getTaskResponse);                // ��ȡ����ظ���Ϣ
    NODE_SET_METHOD(exports, "getAutoDeviceStatus", getAutoDeviceStatus);        // ��ȡ���͵��豸״̬��Ϣ
    NODE_SET_METHOD(exports, "getAllDeviceStatus", getAllDeviceStatus);          // ������ȡ�����豸״̬��Ϣ
}


/**
 * ���屾ģ������ֺͳ�ʼ������
 * @param aebellBroadcast ģ������
 * @param RegisterModule ��ʼ������
 */
NODE_MODULE(aebellBroadcast, RegisterModule)
