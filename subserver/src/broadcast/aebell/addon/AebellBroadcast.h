#pragma once

#ifndef AEBELL_BROADCAST_H
#define AEBELL_BROADCAST_H

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <windows.h>
#include <vector>
#include <string>
#include "AebellIpcastSdk.h"
#include "CommonTypeDefine.h"
#include "Lock.h"
using namespace v8;


//*******************************
//******导出的函数指针类型声明*****
//*******************************
// 登录
typedef BOOL(*LoginFunc)(string, UINT, LOGIN_REQUEST, FuncConnect, FuncConnectError, DWORD);
// 退出
typedef BOOL(*LogoutFunc)();
// 查询所有文件
typedef BOOL(*QueryFileFunc)(INT, FuncGetAllUploadedFiles, DWORD);
// 注册设备状态推送回调函数
typedef BOOL(*AutoDevStatusFunc)(FuncAutoGetDeviceStatus, DWORD);
// 查询所有设备状态
typedef BOOL(*QueryAllDevStatFunc)(FuncGetAllDeviceStatus, DWORD);
// 查询所有设备信息
typedef BOOL(*QueryAllDevFunc)(FuncGetAllNetDevices, DWORD);
// 查询所有设备附加信息
typedef BOOL(*QueryAllAttachFunc)(FuncGetDeviceAttachByID, DWORD);
// 开始广播
typedef BOOL(*BroadcastFunc)(NET_BROADCAST, FuncStartBroadcasting, FuncStartBroadcastingEx, DWORD);
// 开始喊话
typedef BOOL(*CallFunc)(NET_SPEAK, FuncCall, DWORD);
// 停止广播
typedef BOOL(*StopBroadcastFunc)(USHORT, FuncCancelBroadcasting, DWORD);
// 停止喊话
typedef BOOL(*StopCallFunc)(USHORT, FuncCancelCalling, DWORD);
// 根据设备IP查询单个设备状态
typedef BOOL(*QueryDevStatFunc)(string, FuncGetDevStatusByIP, DWORD);
// 添加设备基础信息
typedef BOOL(*AddDeviceFunc)(NET_DEVICE, FuncAddDeviceInfo, DWORD);
// 添加设备附加信息
typedef BOOL(*AddDeviceAttachFunc)(NET_DEVICE_ATTACH, FuncAddDeviceAttach, DWORD);
// 删除设备
typedef BOOL(*RemoveDevFunc)(OPERATE_DEVICE, FuncRemoveNetDevice, DWORD);
// 调整音量
typedef BOOL(*AdjustVolumeFunc)(DEVICE_VOLUME, INT, FuncSetDeviceVolume, DWORD);
// 上传文件
typedef BOOL(*UploadFileFunc)(NET_RESOURCE, FuncUploadFile, FuncOperateResource, DWORD);
// 上传文件数据
typedef BOOL(*UploadFileDataFunc)(USHORT, string, FuncUploadDataInFile, FuncOperateResource, DWORD);
// 上传文件数据完成
typedef BOOL(*UploadFinishFunc)(USHORT, FuncFinishUploadingFile, FuncOperateResource, DWORD);
// 删除文件
typedef BOOL(*DeleteFileFunc)(INT, FuncDeleteFile, DWORD);
// 获取所有方案
typedef BOOL(*QueryAllPolicyFunc)(FuncGetAllTaskPolicy, DWORD);
// 注册方案状态推送回调
typedef BOOL(*PolicyStatusCBFunc)(FuncAutoGetPolicyStatus, DWORD);
// 获取指定方案的所有任务
typedef BOOL(*QueryPolicyTaskFunc)(string, FuncGetAllTaskView, DWORD);
// 添加方案
typedef BOOL(*AddPlanFunc)(TASK_POLICY, INT, FuncAddTaskPolicy, DWORD);
// 添加方案中的广播定时任务
typedef BOOL(*AddPlanTaskFunc)(string, BASE_TASK, DEVICE_FOR_TASK, PLAY_TASK_ATTACH, FILE_FOR_TASK, FuncAddTaskIntoPolicy, DWORD, TIMING_TASK);
// 启动方案中的广播定时任务
typedef BOOL(*RunPlanTaskFunc)(string, FuncStartTask, DWORD, INT);
// 删除方案
typedef BOOL(*DelPlanFunc)(string, FuncRemoveTaskPolicy, DWORD);
// 增加会话中的设备
typedef BOOL(*AddSessionDevFunc)(USHORT, DEVICE_ID_WRAPPER, FuncAddDeviceIntoSession, DWORD);
// 删除会话中的设备
typedef BOOL(*DelSessionDevFunc)(USHORT, DEVICE_ID_WRAPPER, FuncRemoveDeviceFromSession, DWORD);




//*******************************
//***********回调函数*************
//*******************************
// 查询所有文件回调
void QueryAllFileCB(const vector<NET_FILE>& tanFiles, DWORD dwUser);
// 定时查询所有文件回调
void TimerQueryAllFileCB(const vector<NET_FILE>& tanFiles, DWORD dwUser);
// 设备状态推送回调
void AutoGetDeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);
// 查询所有设备状态回调
void TimerQueryAllDeviceStatusCB(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);
// 停止广播时查询设备状态回调
void QueryDevStatCB_Broadcast(DEVICE_STATUS status, DWORD dwUser);
// 停止喊话时查询设备状态回调
void QueryDevStatCB_Call(DEVICE_STATUS status, DWORD dwUser);
// 停止操作回调（停止会话/广播/寻呼/对讲使用同一个回调函数）
void StopOperationCB(INT nOperateType, DWORD dwUser);
// 广播的回调
void BroadcastCB(USHORT uSessionID, DWORD dwUser);
// 寻呼的回调
void CallCB(USHORT uSessionID, DWORD dwUser);
// 定时获取所有设备信息回调
void TimerGetAllNetDevicesCB(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);
// 定时获取所有设备附加信息回调
void TimerGetDeviceAttachInfoCB(const vector<NET_DEVICE_ATTACH>& tanAttach, DWORD dwUser);
// 删除设备回调
void RemoveDeviceCB(INT nOperateType, DWORD dwUser);
// 调整设备音量回调
void SetDeviceVolumeCB(INT nOperateType, DWORD dwUser);
// 上传文件 操作回调
void UploadFileCB(INT nSessionID, DWORD dwUser);
// 上传文件数据（纯数据）回调
void UploadFileDataCB(INT nOperateType, DWORD dwUser);
// 上传文件数据完成 回调
void OnFinishUploadFileCB(INT nFileID, DWORD dwUser);
// 增删改资源回调
void OnOperateResourceCB(INT nOperateType, DWORD dwUser);
// 添加设备基础信息回调
void AddDeviceCB(INT nOperateType, DWORD dwUser);
// 添加设备附加信息回调
void AddDeviceAttachCB(INT nOperateType, DWORD dwUser);
// 获取到所有方案回调
void OnGetAllPolicyCB(const vector<TASK_POLICY>& tanTaskPolicy, DWORD dwUser);
// 方案状态推送回调
void OnPolicyStatusCB(POLICY_STATUS status, DWORD dwUser);
// 获取方案的任务信息回调
void OnPlolicyTaskCB(const vector<TASK_INFO_VIEW>& tanTaskViews, DWORD dwUser);
// 添加/修改方案回调
void OnAddUpdatePlanCB(INT nOperateType, DWORD dwUser);
// 添加任务回调
void OnAddPlanTaskCB(INT nOperateType, DWORD dwUser);
// 删除方案回调
void OnDelPlanCB(INT nOperateType, DWORD dwUser);
// 添加/删除会话中的设备回调
void OnSessionDeviceCB(INT nOperateType, DWORD dwUser);
// 启动/停止任务回调
void OnTaskOperCB(INT nOperateType, DWORD dwUser);




//*******************************
//***********共通函数*************
//*******************************
// 编码转成UTF-8
string getUtf8String(const char* pSrc);
// 转成GBK编码的字符串
string getGBKString(const char* pSrc);
// 设备状态值对应转换
void ConvertDeviceStatus(const int iDevStatus, uint32& uDevStatus);
// 设备类型值转换
void ConvertDeviceType(const int srcType, int& destType);
// 创建设备时，生成设备ID
string GenerateGUID();
// 获取对应设备类型的设备类型名称
string GetDeviceTypeName(int devType);




//*******************************
//***********数据成员*************
//*******************************
// 设备状态推送信息
static CLock autoInfoLock_;
static vector<DeviceStatusInfo> vAutoPushData_;
// 所有设备状态信息
static CLock allDevStatusLock_;
static vector<DeviceStatusInfo> vAllDevStatusData_;
// 调用美电贝尔dll接口的dwUser
static DWORD dwUser_ = 17788;


#endif