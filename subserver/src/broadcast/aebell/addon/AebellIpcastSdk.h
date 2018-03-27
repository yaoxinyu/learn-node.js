#pragma once

// **********************************************************************
// Copyright (C) 2004-2015, Guangzhou AEBell Electrical Technology Co.Ltd
// FileName: AebellIpcastSdk.h
// Creator: Junlin
// Version: 1.0
// Date: 2015-5-22
// Describe: Ip broadcast SDK define
// Modify record: 
// 
// **********************************************************************

#ifdef AEBELLIPCASTSDK_EXPORTS
#define IPCAST_SDK_API __declspec(dllexport)
#else
#define IPCAST_SDK_API __declspec(dllimport)
#endif

#ifdef __cplusplus
#define EXTERN_C_BEGIN_DECL  extern "C" {
#define EXTERN_C_END_DECL		 }
#else
#define EXTERN_C_BEGIN_DECL
#define EXTERN_C_END_DECL
#endif


#ifdef INVOK_C
#define decl_fun __cdecl
#define CALLBACK_FUN    
#else
#define CALLBACK_FUN   CALLBACK
#define decl_fun __stdcall
#endif

#include <string>
#include <list>
#include <vector>
using namespace std;

EXTERN_C_BEGIN_DECL

struct XMLLoginRequest;		// 1.1		EtyXmlLogin
struct XMLLoginResponse;

struct  _tagLoginRequest;
struct _tagLoginResponse;

struct XMLNetUser;				// 2.1		EtyUser
struct XMLNetUser4;				// 2.4		EtyUser
struct XMLNetUser5;				// 2.5		EtyUser
struct XMLUserType;			// 2.8		EtyUsertype
struct XMLUserAuthority;		// 2.9		EtyPurview
struct XMLNetRole;				// 2.10	EtyRole
struct XMLRoleFunction;		// 2.10
struct XMLDeviceForUser;		//			Request
struct XMLRoleForUser;			//			Request


struct _tagNetUser;
struct _tagUserType;
struct _tagUserAuthority;
struct _tagNetRole;
struct _tagRoleFunction;
struct _tagDeviceForUser;
struct _tagRoleForUser;


struct XMLConnectedDevice;	// 3.1		EtyXmlConnectDevice
struct XMLConnectedDeviceRes6;	// 7.6		EtyXmlConnectDevice
struct XMLConnectedDeviceRes7;	// 7.7		EtyXmlConnectDevice
struct XMLNetDeviceType;		// 3.2		EtyNetdevicetype
struct XMLNetDevice;			// 3.3		EtyNetDevice
struct XMLNetDevice4;
struct XMLNetDevice5678;		// 3.5		EtyNetDevice
struct XMLNetAlarmAttach;
struct XMLDefaultCallDevice;	// 3.9		EtyDefaultcalldevice
struct XMLNetDeviceAttach;	// 3.9		EtyNetdeviceattach
struct XMLChannelDevice;
struct XMLNetAlarmAttachRes;

struct _tagConnectedDevice;
struct _tagNetDeviceType;
struct _tagNetDevice;
struct _tagNetAlarmAttach;
struct _tagDefaultCallDevice;
struct _tagNetDeviceAttach;	
struct _tagChannelDevice;

struct XMLOperateDevice;		// 3.11	EtyXmlOperateWrapper
struct XMLSwitcher;
struct XMLInSwitcher;
struct XMLOutSwitcher;
struct XMLChannelStatus;
struct XMLCallDeviceWrapper;// 3.31	EtyDefaultcalldevice+
struct XMLAlarmProposal;		// 3.33	EtyAlarmproposal
struct XMLAPAlarmDevice;		// 3.33	EtyAlarmproposal_alarmdevice
struct XMLAPAlarmDeviceRes23;
struct XMLAPAlarmDeviceRes24;
struct XMLAPOutChannel;		// 3.33	EtyAlarmproposal_outchannel
struct XMLAPOutChannelWrapper; //3.33
struct XMLDeviceIDWrapper;	// 3.33
struct XMLAlarmQuery;			// 3.38	EtyAlarmQuery
struct XMLAlarmInfo;			// 3.38	EtyAlarminfo

struct _tagOperateDevice;
struct _tagCallDeviceWrapper;
struct _tagAlarmProposal;
struct _tagAPAlarmDevice;
struct _tagAPOutChannel;
struct _tagAPOutChannelWrapper;
struct _tagDeviceIDWrapper;	// 3.33
struct _tagAlarmQuery;
struct _tagAlarmInfo;

struct XMLDeviceVolume;		// 3.40	EtyXmlValueWrapper
struct XMLAlarmDeviceDetail;	// 3.42	EtyAlarmdevicedetail
struct XMLPowerDeviceDetail;// 3.09   EtyNetpowerdevice_detail
struct XMLDeviceSwitch;		// 3.48	EtyXmlValueWrapper
struct XMLDeviceText;			// 3.49	EtyXmlValueWrapper
struct XMLDeviceAudio;			// 3.51	EtyXmlValueWrapper

struct _tagDeviceVolume;
struct _tagAlarmDeviceDetail;
struct _tagPowerDeviceDetail;
struct _tagDeviceSwitch;
struct _tagDeviceText;
struct _tagDeviceAudio;

struct XMLDeviceGroup;		//	6.1	EtyDevicegroup
struct XMLDevGroupAttach;	//	6.1	EtyXmlRelatedItems<string, string>
struct XMLSessionStatus;		// 7.1		EtyXmlSessionStatus
struct XMLNetSession;			// 7.1		EtyXmlSession
struct XMLNetSessionRes;		// 7.2		EtyXmlSession
struct XMLNetResource;		// 8.1		EtyXmlResource
struct XMLNetResourceRes;	// 8.14	EtyXmlResource
struct XMLRecordFile;			// 8.6		EtyXmlRecordFile
struct XMLRecordFileRes;		// 8.10	EtyXmlRecordFile
struct XMLRecordQuery;		// 8.10	EtyXmlRecordQuery
struct XMLNetFile;				// 8.13	EtyResource

struct _tagDeviceGroup;		
struct _tagDevGroupAttach;	
struct _tagSessionStatus;		
struct _tagNetSession;			
struct _tagNetResource;		
struct _tagRecordFile;			
struct _tagRecordQuery;		
struct _tagNetFile;

struct XMLNetSpeak;			// 9.1		EtyXmlSpeak
struct XMLNetBroadcast;		// 10.1	EtyXmlBroadcast
struct XMLMediaFormat;		// 10.3	EtyXmlMediaFormat
struct XMLPlayCtrl;				// 10.7	EtyXmlPlayCtrl
struct XMLNetLicense;			// 12.2	EtyXmlLicense

struct _tagNetSpeak;			
struct _tagNetBroadcast;		
struct _tagMediaFormat;		
struct _tagPlayCtrl;				
struct _tagNetLicense;			

struct XMLBaseTask;			// 13.1	EtyBasetask
struct XMLBaseTaskRes;		// 13.4	EtyBasetask
struct XMLPlayTaskFile;			// 13.1	EtyFileplaytaskfilelist
struct XMLPlayTaskAttach;	// 13.1	EtyFileplaytaskattach
struct XMLPlayTaskAttachRes;
struct XMLLedCtrlTaskAttach;// 13.2	EtyLedctrltaskattach
struct XMLTimingTask;			// 13.2	EtyTimingtask
struct XMLTimingTaskRes;
struct XMLOperateTask;		// 13.3	EtyXmlOperateWrapper
struct XMLTaskInfoView;		// 13.6	EtyTaskinfoview

struct _tagBaseTask;
struct _tagPlayTaskFile;
struct _tagPlayTaskAttach;
struct _tagLedCtrlTaskAttach;
struct _tagTimingTask;
struct _tagOperateTask;
struct _tagTaskInfoView;


struct XMLTaskStatus;			// 13.7	EtyXmlTaskStatus
struct XMLTaskStatusRes;		// 13.7	EtyXmlTaskStatus
struct XMLBaseTaskType;		// 13.8	EtyBasetasktype
struct XMLBCTaskDevice;		// 13.13	EtyBroadcasttask_device
struct XMLPlayFile;				// 13.17	

struct _tagTaskStatus;
struct _tagBaseTaskType;
struct _tagBCTaskDevice;
struct _tagPlayFile;


struct XMLBCTaskAttach;		// 13.18 EtyAcquisbroadcasttaskattach
struct XMLTaskPolicy;			// 13.26	EtyTaskpolicy
struct XMLTaskPolicyRes;		// 13.26	EtyTaskpolicy
struct XMLPowerTaskSwitch;	// 13.35	EtyPowertaskswitch
struct XMLTaskLevel;			// 13.36	EtyLevel
struct XMLLedCtrlTaskAttachRes;
struct XMLLedCtrlTaskAttachRes28;

struct _tagBCTaskAttach;
struct _tagTaskPolicy;
struct _tagPowerTaskSwitch;
struct _tagTaskLevel;
struct _tagLedCtrlTaskAttach;

struct XMLPolicyStatus;		// 21.6	EtyXmlPolicyStatus
struct XMLDevChannelStatus;	// 21.20 EtyXmlDeviceChannelStatus
struct XMLIPAlarmChannel;		// 21.24 EtyXmlValueWrapper
struct XMLDeviceStatus;		// 21.30 EtyXmlDeviceStatus
struct XMLDeviceStatusRes;	// 21.31 EtyXmlDeviceStatus
struct XMLPowerSwitch;		// 21.33 EtyXmlValueWrapper


struct _tagPolicyStatus;		
struct _tagDevChannelStatus;	
struct _tagIPAlarmChannel;		
struct _tagDeviceStatus;		
struct _tagPowerSwitch;		

enum IPCAST_SDK_API DeviceStatus
{
	/// <summary>
	/// 未接通状态。
	/// </summary>
	Disconnect,
	/// <summary>
	/// 中断断开服务器的连接
	/// </summary>
	RelayDisconnect,
	/// <summary>
	/// 空闲状态。
	/// </summary>
	Free,
	/// <summary>
	/// 呼叫等待。
	/// </summary>
	CallWaiting,
	/// <summary>
	/// 正在响铃
	/// </summary>
	Ringing,
	/// <summary>
	/// 寻呼工作中
	/// </summary>
	Calling,
	/// <summary>
	/// 对讲工作中
	/// </summary>
	Talking,
	/// <summary>
	/// 广播工作中
	/// </summary>
	Broadcasting,
	/// <summary>
	/// 采集中
	/// </summary>
	Collecting,
	/// <summary>
	/// 监听中
	/// </summary>
	Listening,
	/// <summary>
	/// 监听播音中
	/// </summary>
	ListenBroadcasting,
	/// <summary>
	/// 采集播音中
	/// </summary>
	CollectBroadcasting,
	/// <summary>
	/// 操作结束，只一个正在进行的操作结束，结束后设备恢复空闲的状态。
	/// </summary>
	Ending,
	/// <summary>
	/// 登入，只要针对PC用户
	/// </summary>
	Login,
	/// <summary>
	/// 登出，只要针对PC用户。
	/// </summary>
	Logout,
	/// <summary>
	/// 设备被移除（指配置）
	/// </summary>
	DeviceRemove,
	/// <summary>
	/// 设备新增加
	/// </summary>
	DeviceAdd,
	/// <summary>
	/// 设备被修改
	/// </summary>
	DeviceEdit,
	///// <summary>
	///// 被监听中
	///// </summary>
	//Listeneding = 0x10000000
};

/// <summary>
/// 广播的类型。如果非PC进行广播，数据发送到服务器，收到返回成功的消息后，完成了。
/// </summary>
enum IPCAST_SDK_API BroadcastType
{
	/// <summary>
	/// PC进行广播。
	/// </summary>
	PCBroadcast,
	/// <summary>
	/// 使用PC进行寻呼，（只要是通过采集设备采集到的音频，只要有播音室）
	/// </summary>
	PCCollect,
	/// <summary>
	/// 用设备进行广播（多指喊话功能）
	/// </summary>
	DeviceBroadcast,
	/// <summary>
	/// 服务器进行广播，使用指定的文件列表。（点播、广播、定时打铃等）
	/// </summary>
	ServerBroadcast,

	/// <summary>
	/// 设备之间的寻呼
	/// </summary>
	DeviceCall,

	/// <summary>
	/// 设备之间的对讲。
	/// </summary>
	DeviceTalk,
};

//同SoundMediaUntil里的PlayCycleType保持一致。
/// <summary>
/// 播放模式。
/// </summary>
enum IPCAST_SDK_API PlayCycleType
{
	/// <summary>
	/// 单曲播放
	/// </summary>
	Single,
	/// <summary>
	/// 单曲循环
	/// </summary>
	SingleCycle,
	/// <summary>
	/// 顺序模式
	/// </summary>
	Order,
	/// <summary>
	/// 循环模式
	/// </summary>
	Recycle,
	/// <summary>
	/// 随机播放。
	/// </summary>
	Shuffle,
};

enum SessionType
{
	/// <summary>
	/// 空或临时会话
	/// </summary>
	None,
	/// <summary>
	/// 广播会话。
	/// </summary>
	Broadcast,
	/// <summary>
	/// 寻呼会话
	/// </summary>
	Call,
	/// <summary>
	/// 对讲会话
	/// </summary>
	Talk,
	/// <summary>
	/// 声音采集
	/// </summary>
	Collection,
	/// <summary>
	/// 监听
	/// </summary>
	Listen,
	/// <summary>
	/// 报警会话。
	/// </summary>
	Alarm,
	/// <summary>
	/// 资源会话。
	/// </summary>
	Resource,
	/// <summary>
	/// Led显示控制会话
	/// </summary>
	LedDisplayCtrl,
};

enum SessionState
{
	/// <summary>
	/// 表括示空，刚创建的状态
	/// </summary>
	None_,
	/// <summary>
	/// 工作中
	/// </summary>
	Working,
	/// <summary>
	/// 挂起，可能由于超时引起
	/// </summary>
	Suspend,
	/// <summary>
	/// 关闭，关闭后一般在会话列表中移除了
	/// </summary>
	Closed,
	/// <summary>
	/// 增加会话中的设备
	/// </summary>
	AddSessionDevice,
	/// <summary>
	/// 移除会话中的设备
	/// </summary>
	RemoveSessionDevice,
};

/// <summary>
/// 出错类型枚举
/// </summary>
enum ErrorType
{
	/// <summary>
	/// 未知错误
	/// </summary>
	UnknowError = -1,
	/// <summary>
	/// 成功
	/// </summary>
	Succeed,
	/// <summary>
	/// 服务未连接。
	/// </summary>
	ServerDisConnect,

	/// <summary>
	/// 数据库操作失败
	/// </summary>
	DBOperateError,
	/// <summary>
	/// 没有权限或权限不够。
	/// </summary>
	NoPermission,
	/// <summary>
	/// 指令执行超时。
	/// </summary>
	CommandTimeout,
	/// <summary>
	/// 服务器指令超时
	/// </summary>
	ServerCommandTimeout,
	/// <summary>
	/// 找不到会话。
	/// </summary>
	SessionNotFound,
	/// <summary>
	/// 会话已终止。
	/// </summary>
	SessionClosed,
	/// <summary>
	/// 用户或密码错误。
	/// </summary>
	UserOrPasswordError,
	/// <summary>
	/// 设备已处于登录状态。
	/// </summary>
	OnLoginState,
	/// <summary>
	/// 已登出状态。
	/// </summary>
	OnLogoutState,
	/// <summary>
	/// 登录失败。
	/// </summary>
	LoginFailed,
	/// <summary>
	/// 查询范围有误，太大
	/// </summary>
	QueryRangeError,
	/// <summary>
	/// 记录不存在。
	/// </summary>
	RecordNotExist,
	/// <summary>
	/// 文件不存在。
	/// </summary>
	FileNotFound,
	/// <summary>
	/// 文件数量超出范围
	/// </summary>
	FileNumOutofRange,
	/// <summary>
	/// 上传文件已存在。
	/// </summary>
	UploadFileExisted,
	/// <summary>
	/// 写上传文件出错。
	/// </summary>
	WriteUploadDataError,
	/// <summary>
	/// 工作状态出错，指执行的功能在不合适的工作状态下。
	/// </summary>
	WorkStatusError,
	/// <summary>
	/// 没有找到设备
	/// </summary>
	DeviceNotFound,
	/// <summary>
	/// 设备未连接
	/// </summary>
	DeviceDisconnected,
	/// <summary>
	/// 设备类型出错或不匹配
	/// </summary>
	DeviceTypeError,
	/// <summary>
	/// 控制设备忙。
	/// </summary>
	CtrlDeviceBusy,
	/// <summary>
	/// 通话设备忙
	/// </summary>
	TalkDeviceBusy,
	/// <summary>
	/// 设备受限
	/// </summary>
	DeviceRestricted,
	/// <summary>
	/// 接入设备还没有配置
	/// </summary>
	NoDeviceSetting,
	/// <summary>
	/// 没有分配设备
	/// </summary>
	NoAllocDevice,
	/// <summary>
	/// 广播出错，
	/// </summary>
	BroadcastError,
	/// <summary>
	/// 任务失败。
	/// </summary>
	TaskError,
	/// <summary>
	/// 任务不存在
	/// </summary>
	TastNotFound,
	/// <summary>
	/// 方案已挂起
	/// </summary>
	PolicySuspended,
	/// <summary>
	/// 不支持的功能
	/// </summary>
	FunctionNoSupport,
	/// <summary>
	/// 该角色已分配给用户
	/// </summary>
	AdmeasuredUser,
	/// <summary>
	/// 已分配ip
	/// </summary>
	ExistingIP,
	/// <summary>
	/// 已分配区号
	/// </summary>
	ExistingPhoneNo,
	/// <summary>
	/// 已分配设备组号
	/// </summary>
	ExistingGroupNo,
	/// <summary>
	/// 名称已存在
	/// </summary>
	ExistingName,
	/// <summary>
	/// 授权码有误
	/// </summary>
	LicenseCodeError,
	/// <summary>
	/// 授权证书较旧
	/// </summary>
	LicenseIsOld,
	/// <summary>
	/// 授权证书已无效
	/// </summary>
	LicenseInValid,
	/// <summary>
	/// 功能受限
	/// </summary>
	FunctionRestricted,
};

enum DevicePriorityLevel
{
	Low				= 400,		// 低级
	Intemediate		= 500,		// 中级
	High				= 600,		// 高级
	Higher			= 700,		// 较高级
	Higheast			= 800,		// 最高级
};

typedef struct IPCAST_SDK_API _tagLoginRequest
{
	string strName;				// 用户名
	string strPwd;					// 用户密码
	string strGUID;					// 用户的GUID
	unsigned int uID;				// 用户的ID
	bool bIsNewID;				// 是否是新用户

	_tagLoginRequest();
	_tagLoginRequest(const XMLLoginRequest& other);
}LOGIN_REQUEST, *LOGIN_REQUEST_PTR;

typedef struct IPCAST_SDK_API _tagLoginResponse
{
	string strGUID;
	int uID;
	bool bIsNewID;

	_tagLoginResponse();
	_tagLoginResponse(const XMLLoginResponse& other);
}LOGIN_RESPONSE, *LOGIN_RESPONSE_PTR;

// 2.4 
typedef struct IPCAST_SDK_API _tagNetUser
{
	string strID;						// 用户ID
	string strName;					// 用户名称
	string strPassword;				// 登录密码
	string strUserType;				// 用户类型
	int nUserTypeCode;				// 用户类型的代号

	string strAddress;					// 用户地址
	string strPhoneNum;				// 联系电话
	short nPriorityLevel;				// 操作优先级别 50
	_tagNetUser();
	_tagNetUser(const XMLNetUser& other);
	_tagNetUser(const XMLNetUser4& other);
	_tagNetUser(const XMLNetUser5& other);
}NET_USER, *NET_USER_PTR;

// 2.8
typedef struct IPCAST_SDK_API _tagUserType
{
	string strTypeName;					// 用户类型名称
	int nTypeCode;						// 用户类型编号
	short nPriorityLevel;				// 优先级[1-999] 默认50
	_tagUserType();
	_tagUserType(const XMLUserType& other);
}USER_TYPE, *USER_TYPE_PTR;

// 2.9
typedef struct IPCAST_SDK_API _tagUserAuthority
{
	string strPurviewID;				// 权限ID
	string strFunctionID;				// 功能分类ID
	string strOperateID;				// 操作权限ID
	string strFunctionName;			// 功能名称(en)
	string strFunctionDesc;			// 功能描述

	string strOperateName;			// 操作权限名称
	string strOperateDesc;			// 操作权限描述
	_tagUserAuthority();
	_tagUserAuthority(const XMLUserAuthority& other);
}USER_AUTHORITY, *USER_AUTHORITY_PTR;

// 2.10
typedef struct IPCAST_SDK_API _tagNetRole
{
	string strRoleID;					// 角色ID
	string strRoleName;				// 角色名称
	string strRoleDesc;				// 角色描述
	string strDataDefineID;			// 数据定义ID
	int nTypeCode;					// 用户类型编号

	short  nPriorityLevel;				// 优先级[1-999] 默认50
	_tagNetRole();
	_tagNetRole(const XMLNetRole& other);
}NET_ROLE, *NET_ROLE_PTR;

typedef struct IPCAST_SDK_API _tagRoleFunction
{
	string strRoleGUID;					// 角色guid
	vector<string> vectFuncGUID;	// strFuncGUID
}ROLE_FUNCTION, ROLE_FUNCTION_PTR;

typedef struct IPCAST_SDK_API _tagDeviceForUser
{
	string strUserGUID;					//	用户GUID
	vector<string> vectDeviveGUID;	// 设备GUID
}DEVICE_FOR_USER, *DEVICE_FOR_USER_PTR;

typedef struct IPCAST_SDK_API _tagRoleForUser
{
	string strUserGUID;					// 用户GUID
	vector<string> vectRoleGUID;		// 角色GUID
}ROLE_FOR_USER, *ROLE_FOR_USER_PTR;

// 3.1 
typedef struct IPCAST_SDK_API _tagConnectedDevice
{
	string strDisplayText;				// 显示的文本，相当于Name，PC客户端使用IP+用户名
	string strKey;							// 设备使用MAC地址。PC、中继、核心服务器直接使用远程IP地址
	int nIdentity;							// 集合分配给用户或设备的唯一标识，如果为重连，必须使用回原来的Id，整个过程是以该标识为查找条件。
	unsigned short uPhoneNum;		// 配置的通话号，0表示没有配置。
	int nDeviceType;						// 连接的设备类型，参见DeviceType枚举

	int nDeviceStatus;					// 设备的工作状态，参见DeviceStatus枚举
	string strDescription;					// 设备状态工作描述
	string strRelayServerIp;				// 中继服务器的IP地址。
	char nVolume;							// 音量
	int nSoundEffect;						// 音效

	unsigned short uSessionId;			// 当前的会话的ID，0表示空闲
	string strSessionName;				// 会话的名称。
	_tagConnectedDevice();
	_tagConnectedDevice(const XMLConnectedDevice& other);
	_tagConnectedDevice(const XMLConnectedDeviceRes6& other);
	_tagConnectedDevice(const XMLConnectedDeviceRes7& other);
}CONNECTED_DEVICE, *CONNECTED_DEVICE_PTR;

// 3.2 
typedef struct IPCAST_SDK_API _tagNetDeviceType
{
	string strID;							// 设备类型ID
	int	nTypeCode;						// 设备类型编号
	string strTypeName;					// 设备类型名称
	string strDescription;					// 设备类型的描述
	_tagNetDeviceType();
	_tagNetDeviceType(const XMLNetDeviceType& other);
}NET_DEVICE_TYPE, *NET_DEVICE_TYPE_PTR;

// 3.3 
typedef struct IPCAST_SDK_API _tagNetDevice
{
	string strID;							// 设备ID
	string strName;						// 设备名称
	int nDeviceTypeCode;				// 设备类型编号
	string strDeviceTypeName;			// 设备类型名称
	string strIPAddress;					// IP地址

	int nPort;								// 端口号
	string strMAC;							// MAC地址或IP，MAC带’-’，IP带’.’
	string strRelayServerIP;				// 中继服务器IP
	string strAddress;						// 设备地址
	unsigned char  uProtocalVersion;	// 协议版本号

	string strNetPowerIP;				// IP电源的IP地址
	short nNetPowerSwitchNum;		// 电源的开关号
	_tagNetDevice();
	_tagNetDevice(const XMLNetDevice& other);
	_tagNetDevice(const XMLNetDevice4& other);
	_tagNetDevice(const XMLNetDevice5678& other);
}NET_DEVICE, *NET_DEVICE_PTR;

// 3.4 
typedef struct IPCAST_SDK_API _tagNetAlarmAttach
{
	string strDeviceID;						// 设备ID
	string strModel;							// 设备型号
	int nAlarmChannelNums;					// 报警通道总数
	unsigned short uAlarmOutChannelNums;	// 报警输出通道总数
	_tagNetAlarmAttach(){}
	_tagNetAlarmAttach(const XMLNetAlarmAttach& other);
	_tagNetAlarmAttach(const XMLNetAlarmAttachRes& other);
}NET_ALARM_ATTACH, *NET_ALARM_ATTACH_PTR;

typedef struct IPCAST_SDK_API _tagSwitcher
{
	int nIndex;									// 从 1 开始的开始序号
	int nSwitchStatus;						// 开关的状态
	unsigned char uStatus;					// 状态，为Xml传输用 ０表示开路断电，１表示闭合通电

	_tagSwitcher(){}
	_tagSwitcher(const XMLSwitcher& other);
	_tagSwitcher(const XMLInSwitcher& other);
	_tagSwitcher(const XMLOutSwitcher& other);
}SWITCHER, *SWITCHER_PTR;

typedef struct IPCAST_SDK_API _tagChannelDevice
{
	_tagNetDevice netDevice;				// 设备的实体。
	_tagNetAlarmAttach netAlarmAttach;	// 为报警设备专门配置一个该属性，因为有很多非报警设备，会带有输入，输出的功能
	vector<_tagSwitcher> InChannels;	// 设备的输入通道状态（指报警等输入）
	vector<_tagSwitcher> OutChannels;	// 设备的输出通道，指电源或报警输出
}CHANNEL_DEVICE, *CHANNEL_DEVICE_PTR;

// 3.9
typedef struct IPCAST_SDK_API _tagDefaultCallDevice
{
	unsigned short uSourcePhoneNum;	// 主呼叫IP的通话号
	unsigned short uCallButtonNum;		// 设备按键号，可以为有多个按键单独配置通话设备
	unsigned short uTargetPhoneNum;	// 目录设备的通话号
	unsigned char uActionType;			// 0寻呼 1对讲
	int nSerial;									// 序号，为每个设备关联的对话设备排序
	_tagDefaultCallDevice();
	_tagDefaultCallDevice(const XMLDefaultCallDevice& other);
}DEFAULT_CALL_DEVICE, *DEFAULT_CALL_DEVICE_PTR;

typedef struct IPCAST_SDK_API _tagDefaultCallDevices
{
	vector<_tagDefaultCallDevice> vectDevices;
}DEFAULT_CALL_DEVICES, *DEFAULT_CALL_DEVICES_PTR;

typedef struct IPCAST_SDK_API _tagNetDeviceAttach
{
	string strDeviceID;						// 设备ID
	short nDefaultVolume;					// 设备默认音量
	short nPriorityLevel;						// 优先级别[0-999]越大级别越高
	unsigned short uPhoneNum;			// 通话号
	string strScrDisplayText;				// 设备显示文本
	short nScrSaveTime;						// 屏幕保护时间，默认为30秒
	int nVideoPort;								// 实时视频端口号，默认为554
	_tagNetDeviceAttach();
	_tagNetDeviceAttach(const XMLNetDeviceAttach& other);
}NET_DEVICE_ATTACH, *NET_DEVICE_ATTACH_PTR;

// 3.11
typedef struct IPCAST_SDK_API _tagOperateDevice
{
	string strMainId;							// 操作ID
	int nOperateType;						// 操作类型
	_tagOperateDevice();
	_tagOperateDevice(const XMLOperateDevice& other);
}OPERATE_DEVICE, *OPERATE_DEVICE_PTR;

// 3.31
typedef struct IPCAST_SDK_API _tagCallDeviceWrapper
{
	int nDeviceArea;
	vector<DEFAULT_CALL_DEVICE> vectDevices;
}CALL_DEVICE_WRAPPER, *CALL_DEVICE_WRAPPER_PTR;

// 3.33
typedef struct IPCAST_SDK_API _tagAlarmProposal
{
	string strID;								// 报警预案ID
	string strName;							// 报警预案名称
	int nAlarmType;							// 报警类型
	string strSoundFileFullName;			// 报警时的声音文件
	int nAlarmDuration;						// 报警持续时间(秒)

	short nPriorityLevel;						// 优先级[1-999] 700
	unsigned char uProPowerOn;			// 是否预开电源
	unsigned char uIsSuspended;			// 是否挂起
	string strAlarmOutChannelNums;		// 报警输出通道配置，通道间用,隔开
	_tagAlarmProposal();
	_tagAlarmProposal(const XMLAlarmProposal& other);
}ALARM_PROPOSAL, *ALARM_PROPOSAL_PTR;

typedef struct IPCAST_SDK_API _tagAPAlarmDevice
{
	string strAlarmProposalID;				// 报警通道号
	string strAlarmDeviceID;				// 报警主机ID
	int nAlarmChannel;						// 报警通道号
	string strSoundFileFullName;			// 报警时的声音文件（为空时使用父级声音）
	short nDefaultVolume;					// 报警预案默认(50)的声音

	string strSoundFileAlias;					// 声音文件别名
	_tagAPAlarmDevice();
	_tagAPAlarmDevice(const XMLAPAlarmDeviceRes23& other);
	_tagAPAlarmDevice(const XMLAPAlarmDeviceRes24& other);
}AP_ALARM_DEVICE, *AP_ALARM_DEVICE_PTR;

typedef struct IPCAST_SDK_API _tagAPOutChannel
{
	string strAlarmProposalID;				// 报警预案ID
	string strAlarmOutDeviceID;			// 关联输出设备ID
	int nOutChannel;							// 关联输出设备通道号
	_tagAPOutChannel();
	_tagAPOutChannel(const XMLAPOutChannel& other);
}AP_OUT_CHANNEL, *AP_OUT_CHANNEL_PTR;

typedef struct IPCAST_SDK_API _tagAPOutChannelWrapper
{
	vector<_tagAPOutChannel> vectChannel;
}AP_OUT_CHANNEL_WRAPPER, *AP_OUT_CHANNEL_WRAPPER_PTR;

typedef struct IPCAST_SDK_API _tagDeviceIDWrapper
{
	vector<string> vectID;					// 设备的GUID集合
}DEVICE_ID_WRAPPER, *DEVICE_ID_WRAPPER_PTR;

// 3.38
typedef struct IPCAST_SDK_API _tagAlarmQuery
{
	string strDeviceName;					// 设备名称（支持模糊搜索）
	string strStartTime;						// 开始时间
	string strEndTime;						// 结束时间
	int nAlarmTypeCode;						// 报警类型 100 红外
	int nAlarmChannel;						// 报警通道号

	string strDeviceIP;						// 设备IP（支持模糊搜索）
	_tagAlarmQuery();
	_tagAlarmQuery(const XMLAlarmQuery& other);
}ALARM_QUERY, *ALARM_QUERY_PTR;

typedef struct IPCAST_SDK_API _tagAlarmInfo
{
	int nID;										// 报警信息ID
	string strDeviceID;						// 报警设备ID
	int nAlarmChannel;						// 接入的报警通道
	int nAlarmTypeCode;						// 报警类型编号
	string strAlarmDescription;				// 报警内容

	string strAlarmTime;						// 报警时间
	string strDeviceIP;						// 设备IP
	string strDeviceName;					// 设备名称
	string strAlarmTypeName;				// 报警类型名称
	_tagAlarmInfo();
	_tagAlarmInfo(const XMLAlarmInfo& other);
}ALARM_INFO, *ALARM_INFO_PTR;

// 3.40
typedef struct IPCAST_SDK_API _tagDeviceVolume
{
	string strID;								// 设置ID或通话号
	bool bIsNumber;								// True时，表示为通话号
	_tagDeviceVolume();
	_tagDeviceVolume(const XMLDeviceVolume& other);
}DEVICE_VOLUME, *DEVICE_VOLUME_PTR;

// 3.42
typedef struct IPCAST_SDK_API _tagAlarmDeviceDetail
{
	string strDeviceID;						// 报警设备ID
	string strName;							// 报警设备名称
	int nAlarmTypeCode;						// 报警类型编号
	string strAlarmDeviceTypeName;		// 设备类型名称
	int nAlarmChannel;						// 接入的报警通道

	short nPriorityLevel;						// 优先级别，设置在700
	string strAddress;							// 安装的地址
	string strDescription;						// 描述
	string strChannelFlag;					// 通道类型OUT/IN
	_tagAlarmDeviceDetail();
	_tagAlarmDeviceDetail(const XMLAlarmDeviceDetail& other);
}ALARM_DEVICE_DETAIL, *ALARM_DEVICE_DETAIL_PTR;

typedef struct IPCAST_SDK_API _tagAlarmDeviceDetails
{
	vector<_tagAlarmDeviceDetail> vectDetails;
}ALARM_DEVICE_DETAILS, *ALARM_DEVICE_DETAILS_PTR;

typedef struct IPCAST_SDK_API  _tagPowerDeviceDetail
{
	string strID;						// 设备ID
	string strPowerDeviceID;		// 	电源管理器ID
	string strDeviceID;				// Net设备或报警设备
	int nSwitchNum;					// 接入开关序号
	string strDescription;				// 	描述
}POWER_DEVICE_DETAIL, *POWER_DEVICE_DETAIL_PTR;

typedef struct IPCAST_SDK_API  _tagPowerDeviceDetails
{
	vector<_tagPowerDeviceDetail> vectDetails;
}POWER_DEVICE_DETAILS, *POWER_DEVICE_DETAILS_PTR;

// 3.48
typedef struct IPCAST_SDK_API _tagDeviceSwitch
{
	string strDeviceID;						// 设备的ID
	int nSwitch;								// 开关状态，0表示关，1表示开
	_tagDeviceSwitch();
	_tagDeviceSwitch(const XMLDeviceSwitch& other);
}DEVICE_SWITCH, *DEVICE_SWITCH_PTR;

// 3.49
typedef struct IPCAST_SDK_API _tagDeviceText
{
	string strDeviceID;						// 设备的ID
	string strText;								// 设备要显示的字符串
	_tagDeviceText();
	_tagDeviceText(const XMLDeviceText& other);
}DEVICE_TEXT, *DEVICE_TEXT_PTR;

// 3.51
typedef struct IPCAST_SDK_API _tagDeviceAudio
{
	string strValue1;							// 
	string strValue2;							// 为bool类型
	_tagDeviceAudio();
	_tagDeviceAudio(const XMLDeviceAudio& other);
}DEVICE_AUDIO, *DEVICE_AUDIO_PTR;

// 6.1
typedef struct IPCAST_SDK_API _tagDeviceGroup
{
	string strID;							// 设备组ID
	string strName;						// 设备组名称
	short nSerial;							// 设备组序号
	_tagDeviceGroup();
	_tagDeviceGroup(const XMLDeviceGroup& other);
}DEVICE_GROUP, *DEVICE_GROUP_PTR;

typedef struct IPCAST_SDK_API _tagDevGroupAttach
{
	string strItem;
	_tagDevGroupAttach();
	_tagDevGroupAttach(const XMLDevGroupAttach& other);
}DEVICE_GROUP_ATTACH, *DEVICE_GROUP_ATTACH_PTR;

// 7.1 
typedef struct IPCAST_SDK_API _tagSessionStatus
{
	unsigned short nId;					// Session的唯一ID。
	string strName;						// 会话名称。
	int nState;								// 会话状态
	int nRecState;							// 录像的状态。 0 表示没有录像， 1表示进行录像， 2表示出错。建议只做采集的音频才进行录像
	unsigned char uVolume;				// 会话的音量改变

	unsigned char uSoundEffect;		// 音效，1表示
	string strDescription;					// 会话描述
	int nSessionType;						// 会话的类型
	_tagSessionStatus();
	_tagSessionStatus(const XMLSessionStatus& other);
}SESSION_STATUS, *SESSION_STATUS_PTR;

typedef struct IPCAST_SDK_API _tagNetSession
{
	unsigned short uId;					// Session的唯一ID。
	string strName;						// 会话名称。
	unsigned short uMainRelayId;		// 主中继服务器的标识
	unsigned short uLevel;				// 系统操作的优先级别，以主呼设备的级别定义为会话的级别。
	int nMainDeviceId;					// 会话主会话的ID

	SESSION_STATUS state;		// 
	int nSessionType;						// 会话的类型，参考SessionType枚举
	string strCreateTime;				// 获取会话创建时间。（时间类型）
	_tagNetSession();
	_tagNetSession(const XMLNetSession& other);
	_tagNetSession(const XMLNetSessionRes& other);
}NET_SESSION, *NET_SESSION_PTR;

// 8.1
typedef struct IPCAST_SDK_API _tagNetResource
{
	int nULid;								// 用户登录Id
	int nFType;								// 文件类型。
	string strFName;						// 文件源名称。
	string strFAlais;						// 文件别名
	_tagNetResource();
	_tagNetResource(const XMLNetResource& other);
	_tagNetResource(const XMLNetResourceRes& other);
}NET_RESOURCE, *NET_RESOURCE_PTR;

// 8.6
typedef struct IPCAST_SDK_API _tagRecordFile
{
	string strFullName;					// 文件在服务器的全名称
	string strName;						// 文件的名称
	int nFileSize;							// 文件的大小，以字节为单位
	string strCreateTime;				// 文件的创建时间
	_tagRecordFile();
	_tagRecordFile(const XMLRecordFile& other);
	_tagRecordFile(const XMLRecordFileRes& other);
}RECORD_FILE, *RECORD_FILE_PTR;

// 8.10
typedef struct IPCAST_SDK_API _tagRecordQuery
{
	int nLoginId;							// 登录用户的Id
	string strStartTime;					// 开始时间
	string strEndTime;					// 结束时间
	int nRecordType;						// 录音文件的类型，0 表示为核心服务器的录音文件，1表示VOIP的录音文件
	_tagRecordQuery();
	_tagRecordQuery(const XMLRecordQuery& other);
}RECORD_QUERY, *RECORD_QUERY_PTR;

// 8.13
typedef struct IPCAST_SDK_API _tagNetFile
{
	int nID;								// 文件记录ID
	string strAlais;						// 文件显示名称
	string strFileFullName;			// 文件全名称
	string  strUpdateTime;			// 上传时间
	int nFileType;						// 上传文件的类型
	_tagNetFile();
	_tagNetFile(const XMLNetFile& other);
}NET_FILE, *NET_FILE_PTR;

// 9.1
typedef struct IPCAST_SDK_API _tagNetSpeak
{
	int nULid;								// 用户登录Id
	string strName;						// 对讲或寻呼的名称，让广播方输入
	bool bIsPhoneNum;					// 是否为通话号，如果为通话号，DeviceIds为通话号的列表，否则为设备在缓冲中分配到的ID，MainDeviceId也是一样
	int nSourceDevId;					// 原设备ID或通话号
	vector<int> vectDevIDs;		// 寻呼的列表，所有参与的会话列表。如果IsPhoneNum为真，即为用户设定的通话号，否则为设备在缓冲中分配到的ID

	int nBroadcastType;					// 广播类型，参见ProtocolXMLModel的BroadcastType 枚举
	unsigned char uVolume;				// 广播音量
	_tagNetSpeak();
	_tagNetSpeak(const XMLNetSpeak& other);
}NET_SPEAK, *NET_SPEAK_PTR;

// 10.1
typedef struct IPCAST_SDK_API _tagNetBroadcast
{
	int nULid;								// 用户登录Id
	string strName;						// 广播的名称，让广播方输入
	bool bIsPhoneNum;					// 是否为通话号，如果为通话号，DeviceIds为通话号的列表，否则为设备在缓冲中分配到的ID，MainDeviceId也是一样
	vector<int> vectDevIDs;			// 广播的列表，所有参与的会话列表。如果IsPhoneNum为真，即为用户设定的通话号，否则为设备在缓冲中分配到的ID
	vector<int> vectFileIDs;				// 文件播放列表。只有BroadcastType设置为服务器播放时才有效。

	int nMDid;								// 主广播设备。如果 为 0 即使用PC进行广播，如果指定该设备号，即使用设备号进行。
	int nBroadcastType;					// 广播类型，参见 BroadcastType 枚举
	int nPlayTime;							// 播放时间，以秒为单位，0表示不做限制。
	int nCycleCount;						// 循环次数，0 表示不做限制，非0，即播放时间无效
	int nCycleType;						// 播放模式，只有服务器播放才使用该属性

	unsigned char uVolume;				// 广播音量
	int nStartPlayIndex;					// 开始播放歌曲号。默认为0
	_tagNetBroadcast();
	_tagNetBroadcast(const XMLNetBroadcast& other);
}NET_BROADCAST, *NET_BROADCAST_PTR;

// 10.3
typedef struct IPCAST_SDK_API _tagMediaFormat
{
	string strMediaName;				// 媒体的名称
	unsigned short uPlayIndex;			// 播放的序号
	unsigned short uSessionId;			// 附加的会话Id信息，比单独处理要好
	int nMediaType;						// 音频的格式，0 为Mp3，1 为Wav，2为采集的音频格式
	unsigned short uFormatTag;		// 记录着此声音的格式代号，例如1-WAVE_FORMAT_PCM， 2-WAVE_F0RAM_ADPCM等等

	unsigned short uChannels;			// 声道数目，1--单声道；2--双声道
	unsigned int uSamlesPerSec;		// 采样频率  一般有11025Hz（11kHz）、22050Hz（22kHz）和44100Hz（44kHz）三种
	unsigned int uAvgBytesPerSec;	// 每秒所需字节数
	unsigned short uBlockAlign;		// 数据块对齐单位(每个采样需要的字节数) 声道数 * 量化数/8
	unsigned short uBitsPerSample;	// 音频采样大小 采样位数。量化数 8或16

	int nLayer;								// MP3的层数
	int nFrameSize;						// MP3的侦长度
	_tagMediaFormat();
	_tagMediaFormat(const XMLMediaFormat& other);
}MEDIA_FORMATE, *MEDIA_FORMAT_PTR;

// 10.7
typedef struct IPCAST_SDK_API _tagPlayCtrl
{
	int nULid;								// 用户登录Id
	unsigned short uSid;					// 播放会话的ID
	int nCycleType;						// 播放模式，只有服务器播放才使用该属性
	unsigned char uVolume;				// 广播音量
	int nIndex;
	_tagPlayCtrl();
	_tagPlayCtrl(const XMLPlayCtrl& other);
}PLAY_CTRL, *PLAY_CTRL_PTR;

// 12.2
typedef struct IPCAST_SDK_API _tagNetLicense
{
	int nExpireDays;						// 过期天数
	bool bIsTryVersion;					// 是否为试用版本
	string strCompanyName;			// 公司名称
	string strSetupDate;					// 安装日期
	int nDeviceCount;						// 允许设备数量

	int nOnlineUserCount;				// 在线用户数量
	string strMachineCode;				// 机器码
	string strExpireDate;					// 过期日期
	int nLicenceStatus;					// 证书状态，0 未授权 1 无效授权 2 正常使用 3 授权过期
	_tagNetLicense();
	_tagNetLicense(const XMLNetLicense& other);
}NET_LICENSE, *NET_LICENSE_PTR;


// 13.1
typedef struct IPCAST_SDK_API _tagBaseTask
{
	string strID;							// 任务ID
	string strName;						// 任务名称
	short nPriorityLevel;					// 优先级[1-999] 默认为100
	short nDefaultVolume;				// 默认音量[1-56] 50
	int nTaskTypeCode;					// 任务类型编号 广播 0, 歌曲 0, 打铃 1, 文本 10, 时钟 10, 开关 10, 亮度 10,

	string strDescription;					// 描述
	string strRecName;					// 指定的录音文件名称。
	unsigned char bIsAutoRecord;		// 是否自动录音，即任务一启动就开始录音 0表示False
	int nSoundEffect;						// 音频的播放音效
	_tagBaseTask();
	_tagBaseTask(const XMLBaseTask& other);
	_tagBaseTask(const XMLBaseTaskRes& other);
}BASE_TASK, *BASE_TASK_PTR;

typedef struct IPCAST_SDK_API _tagPlayTaskFile
{
	string strTaskID;						// 任务ID
	string strFileFullName;				// 文件全名
	int nOrderNum;						// 文件序号
	_tagPlayTaskFile();
	_tagPlayTaskFile(const XMLPlayTaskFile& other);
}PLAY_TASK_FILE, *PLAY_TASK_FILE_PTR;

typedef struct IPCAST_SDK_API _tagFileForTask
{
	vector<_tagPlayTaskFile> m_vectFiles;
}FILE_FOR_TASK, *FILE_FOR_TASK_PTR;

typedef struct IPCAST_SDK_API _tagPlayTaskAttach
{
	string strTaskID;						// 任务ID
	int nPlayMode;							// 播放模式 0单曲、1单曲循环、2顺序、3循环、4随机
	int nReplayTimes;						// 播放次数，0表示连续
	int nPlayDuration;						// 播放持续时间(秒)0表示不使用
	_tagPlayTaskAttach();
	_tagPlayTaskAttach(const XMLPlayTaskAttachRes& other);
}PLAY_TASK_ATTACH, *PLAY_TASK_ATTACH_PTR;

// 13.2 
typedef struct IPCAST_SDK_API _tagLedCtrlTaskAttach
{
	string strTaskId;						// 任务Id
	int nCtrlType;							// 0文本，1数字时钟，2开关屏控制，3亮度控制
	int nFontSize;							// 8x8,16x16,32x32
	string strDisplayText;				// 显示文本
	int nDisplayStyle;						// 具体看SDK的定义 上移:30 下移:31 左移:32 右移:33
	int nDisplaySpeed;					// 显示的速度或开关屏控制或亮度（0-15）

	int nPosLeft;							// 显示的左边距8的倍数
	int nPosTop;							// 显示的上边距8的倍数
	int nDisplayWidth;					// 显示宽度
	int nDisplayHeight;					// 显示高度
	int nTextAlign;							// 居中，居右，全屏，居上，居下等
	_tagLedCtrlTaskAttach();
	_tagLedCtrlTaskAttach(const XMLLedCtrlTaskAttachRes& other);
	_tagLedCtrlTaskAttach(const XMLLedCtrlTaskAttachRes28& other);
}LED_CTRL_TASK_ATTACH, *LED_CTRL_TASK_ATTACH_PTR;

typedef struct IPCAST_SDK_API _tagTimingTask
{
	string strTaskID;						// 任务ID
	string strBeginTime;					// 定时开始日期  ? time_t
	string strEndTime;					// 定时结束日期	 ? time_t
	string strDoworkTime;				// 每次开始的具体时间  ? time_t
	int nCycleMode;						// 循环模式1每天、2每周、3每月、4定义

	string strTaskRunDate;				// 每周0到6表示周日到周六，每月为1－31天，指定日期为具体的时间字符串，多天使用“,”分隔。? time_t
	string strTaskRunTime;				// 任务的具体执行时长时间 ? time_t
	_tagTimingTask();
	_tagTimingTask(const XMLTimingTask& other);
	_tagTimingTask(const XMLTimingTaskRes& other);
	bool operator==(const _tagTimingTask& other);
}TIMING_TASK, *TIMING_TASK_PTR;

// 13.3
typedef struct IPCAST_SDK_API _tagOperateTask
{
	string strMainId;						// 主表记录的Id。
	int nOperateType;					// 相关属性类型。
	_tagOperateTask();
	_tagOperateTask(const XMLOperateTask& other);
}OPERATE_TASK, *OPERATE_TASK_PTR;

// 13.6
typedef struct IPCAST_SDK_API _tagTaskInfoView
{
	string strTaskPolicyID;				// 方案ID
	string strTaskID;						// 任务Id
	string strName;						// 任务名称
	short nPriorityLevel;					// 优先级[1-999] 默认为100
	short nDefaultVolume;				// 默认音量[1-56] 50

	int nTaskTypeCode;					// 任务类型编号
	string strDescription;					// 描述
	string strBeginTime;					// 定时开始时间 ? time_t
	string strEndTime;					// 	定时结束时间	 ? time_t	
	string strDoworkTime;				// 	每次开始的具体时间	 ? time_t

	int nCycleMode;						// 循环模式1每天、2每周、3每月、4定义
	string strTaskRunDate;				// 每周0到6表示周日到周六，每月为1－31天，指定日期为具体的时间字符串，多天使用“,”分隔 ? time_t
	string strTaskRunTime;				// 任务的具体执行时间 ? time_t
	int nTaskStatus;						// 任务状态 0 表示停止状态，1表示执行状态, 2表示任务新增加， 3 任务被删除
	_tagTaskInfoView();
	_tagTaskInfoView(const XMLTaskInfoView& other);
}TASK_INFO_VIEW, *TASK_INFO_VIEW_PTR;

// 13.7
typedef struct IPCAST_SDK_API _tagTaskStatus
{
	string strTaskId;						// 任务Id
	string strTaskName;					// 任务名称
	unsigned short uSessionId;			// 会话Id
	int nTaskStatus;						// 任务状态 0 表示停止状态，1表示执行状态, 2表示任务新增加， 3 任务被删除
	_tagTaskStatus();
	_tagTaskStatus(const XMLTaskStatus& other);
	_tagTaskStatus(const XMLTaskStatusRes& other);
}TASK_STATUS, *TASK_STATUS_PTR;

// 13.8
typedef struct IPCAST_SDK_API _tagBaseTaskType
{
	int nTaskTypeCode;					// 任务类型编号
	string strTaskTypeName;			// 任务类型名称
	string strDescription;					// 描述
	_tagBaseTaskType();
	_tagBaseTaskType(const XMLBaseTaskType& other);
}BASE_TASK_TYPE, *BASE_TASK_TYPE_PTR;


// 13.13
typedef struct IPCAST_SDK_API _tagBCTaskDevice
{
	string strTaskID;						// 任务ID
	string strDeviceID;					// 设备ID
	_tagBCTaskDevice();
	_tagBCTaskDevice(const XMLBCTaskDevice& other);
}BC_TASK_DEVICE, *BC_TASK_DEVICE_PTR;

// 13.17
typedef struct IPCAST_SDK_API _tagPlayFile
{

}PALY_FILE, *PLAY_FILE_PTR;

// 13.18
typedef struct IPCAST_SDK_API _tagBCTaskAttach
{
	string strTaskID;						// 任务ID
	int nSourceInputCode;				// 采集源区号
	string strSourceInputName;		// 采集源名称
	short nRecVolume;					// 录音音量
	string strRecSaveFile;				// 录音保存文件名，不使用（转为使用Task中的RecName）

	int nInputChannel;					// 采集的通道号
	_tagBCTaskAttach();
	_tagBCTaskAttach(const XMLBCTaskAttach& other);
}BC_TASK_ATTACH, *BC_TASK_ATTACH_PTR;

// 13.26
typedef struct IPCAST_SDK_API _tagTaskPolicy
{
	int nPolicyStatus;						// 方案的状态。
	string strID;							// 方案ID
	string strName;						// 方案名称
	short nPriorityLevel;					// 优先级[1-999] 默认100
	short nDefaultVolume;				// 默认音量[1-56]50

	string strTempSuspendedTime = "0001-01-01T00:00:00";	// 临时挂起时间 ? time_t
	string strTempResumeTime = "0001-01-01T00:00:00";		// 临时挂起的恢复时间 ? time_t
	unsigned char bProPowerOn;		// 是否预开电源
	int nPolicyType;						// 方案类型0普通方案，1电源方案，2为Led屏显控制方案

	_tagTaskPolicy();
	_tagTaskPolicy(const XMLTaskPolicy& other);
	_tagTaskPolicy(const XMLTaskPolicyRes& other);
}TASK_POLICY, *TASK_POLICY_PTR;

typedef struct IPCAST_SDK_API _tagDeviceForTask
{
	vector<string> vectDeviceID;
}DEVICE_FOR_TASK, *DEVICE_FOR_TASK_PTR;


// 13.35
typedef struct IPCAST_SDK_API _tagPowerTaskSwitch
{
	string strTaskID;						// 任务ID
	unsigned char uSwitchStatus;	// 开关状态0表示关，1表示开
	int nSwitchCode;						// 开关号
	string strDeviceId;					//	电源设备的ID
	_tagPowerTaskSwitch();
	_tagPowerTaskSwitch(const XMLPowerTaskSwitch& other);
}POWER_TASK_SWITCH, *POWER_TASK_SWITCH_PTR;

typedef struct IPCAST_SDK_API _tagSwitchForTask
{
	vector<POWER_TASK_SWITCH> vectSwitch;
}SWITCH_FOR_TASK, SWITCH_FOR_TASK_PTR;

// 13.36
typedef struct IPCAST_SDK_API _tagTaskLevel
{
	int nLevelCode;						// 级别数值
	string strLevelName;					// 级别名称
	_tagTaskLevel();
	_tagTaskLevel(const XMLTaskLevel& other);
}TASK_LEVEL, *TASK_LEVEL_PTR;

// 21.6
typedef struct IPCAST_SDK_API _tagPolicyStatus
{
	string strId;								// 方案ID或电源任务Id（状态为6），如果为空，且状态为5，即为全部更新。
	string strName;						// 名称
	int nStatus;							// 方案状态 0 表示正常，1表示挂起状态, 2表示增加， 3被删除，4更新（包括任务等）， 5更新全部（指在方案外删除任务，比较少发生）
	short  nDefaultVolume;				// 默认音量[1-50]50
	string  strSuspendedTime;			// 临时挂起时间

	string strResumeTime;				// 临时挂起的恢复时间
	unsigned char  uProPowerOn;		// 是否预开电源
	int nPolicyType;						// 方案类型，0表示普通方案，1表示电源方案。
	_tagPolicyStatus();
	_tagPolicyStatus(const XMLPolicyStatus& other);
}POLICY_STATUS, *POLICY_STATUS_PTR;

// 21.20
//typedef struct IPCAST_SDK_API _tagSwitcher
//{
//	int nIndex;								// 从 1 开始的开始序号
//	int nSwitchStatus;					// 开关的状态
//	unsigned char uStatus;				// 状态，为Xml传输用
//}SWITCHER, *SWITCHER_PTR;

typedef struct IPCAST_SDK_API _tagDevChannelStatus
{
	string strDeviceIp;					// 设备IP。
	int nIdentity;							// 设置在集合（缓存）中的Id
	unsigned char uDeviceType;		// 设备类型，参考DeviceType枚举。
	vector<SWITCHER> InChannels;	
	vector<SWITCHER> OutChannels;

	_tagDevChannelStatus(){}
	_tagDevChannelStatus(const XMLChannelStatus& other);

	unsigned char uChannelType;		// 通道类型， 0 表示输入，1 表示输出，2表示输出为警示灯之类，使用OutChannels
}DEV_CHANNEL_STATUS, *DEV_CHANNEL_STATUS_PTR;

// 21.24
typedef struct IPCAST_SDK_API _tagIPAlarmChannel
{
	string strDeviceIP;					// 设备IP
	int nIndex;								// 电源设备输出通道号
	_tagIPAlarmChannel();
	_tagIPAlarmChannel(const XMLIPAlarmChannel& other);
}IP_ALARM_CHANNEL, *IP_ALARM_CHANNEL_PTR;

// 21.30
typedef struct IPCAST_SDK_API _tagDeviceStatus
{
	string strKey;							// 设备使用MAC地址。PC、中继、核心服务器直接使用远程IP地址
	string strDeviceName;				// 设备的名称
	int nIdentity;							// 集合分配给用户或设备的唯一标识，如果为重连，必须使用回原来的Id，整个过程是以该标识为查找条件
	unsigned short uPhoneNum;		// 配置的通话号，0表示没有配置
	unsigned char uDeviceType;		// 连接的设备类型，参见DeviceType枚举

	int nDeviceStatus;					// 设备的工作状态，参见DeviceStatus枚举
	unsigned char uVolume;				// 音量
	unsigned char uSoundEffect;		// 音效，1表示
	unsigned short uSessionId;			// 当前的会话的ID，0表示空闲
	string strSessionName;				// 当前的会话的名称

	string strDescription;					// 当前状态描述
	string strRelayServerIp;				// 中继服务器的IP地址
	bool bIsListened;						// 是否被监听
	string strScreenDisplayText;		// 屏幕显示文本
	short nScreenSaveTime;			// 屏保时间
	_tagDeviceStatus();
	_tagDeviceStatus(const XMLDeviceStatus& other);
	_tagDeviceStatus(const XMLDeviceStatusRes& other);
}DEVICE_STATUS, *DEVICE_STATUS_PTR;

// 31.33
typedef struct IPCAST_SDK_API _tagPowerSwitch
{
	string strDeviceID;				// 设备ID
	int nSwitch;							// 控制状态，0断开 1闭合
	_tagPowerSwitch();
	_tagPowerSwitch(const XMLPowerSwitch& other);
}POWER_STATUS, POWER_STATUS_PTR;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 1. 网络连接与登录回调函数定义
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1.1 连接到服务器
typedef void(CALLBACK *FuncConnect)(bool bSuccessful, DWORD dwUser);
typedef void(CALLBACK *FuncConnectError)(int nErrorCode, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 2. 用户管理回调函数定义
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2.0 增删改操作返回（SubCmd = 0）
typedef void(CALLBACK *FuncOperateUser)(INT nOperateType, DWORD dwUser);

// 2.1	增加用户 0x0001
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddUser)(INT nOperateType, DWORD dwUser);

// 2.2	更新用户 0x0002
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateUser)(INT nOperateType, DWORD dwUser);

// 2.3	删除用户信息 0x0003
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteUser)(INT nOperateType, DWORD dwUser);

// 2.4 获取所有的用户信息
typedef void(CALLBACK *FuncGetAllUsers)(const vector<NET_USER>& tanNetUsers, DWORD dwUser);

// 2.5  通过用户的GUID获取用户信息
typedef void(CALLBACK *FuncGetUserInfo)(const NET_USER& stuNetUser, DWORD dwUser);

// 2.6 通过用户的GUID获取分配给用户的设备
typedef void(CALLBACK *FuncGetAllocatedDevicesByGUID)(const vector<NET_DEVICE>& tanNetDevices, DWORD dwUser);

// 2.7 增加或删除用户分配的设备
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncManageAllocatedDevices)(INT nOperateType, DWORD dwUser);

// 2.8 获取所有用户类型信息表
typedef void(CALLBACK *FuncGetAllUserTypes)(const vector<USER_TYPE>& tanUserTypes, DWORD dwUser);

// 2.9 获取用户权限列表
typedef void(CALLBACK *FuncGetUserAuthorities)(const vector<USER_AUTHORITY>& tanUserAuthorities, DWORD dwUser);

// 2.10	获取所有角色 0x000A
typedef void(CALLBACK *FuncGetAllRoles)(const vector<NET_ROLE> tanRoles, DWORD dwUser);

// 2.11	增删改用户关联角色 0x000B
//typedef void(CALLBACK *FuncManageAssociatedRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncManageAssociatedRole)(INT nOperateType, DWORD dwUser);

// 2.12	增加角色 0x000C
//typedef void(CALLBACK *FuncAddRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddRole)(INT nOperateType, DWORD dwUser);

// 2.13	更新角色 0x000D
//typedef void(CALLBACK *FuncUpdateRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateRole)(INT nOperateType, DWORD dwUser);

// 2.14	删除角色 0x000E
//typedef void(CALLBACK *FuncDeleteRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteRole)(INT nOperateType, DWORD dwUser);

//// 
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 3. 设备管理回调函数定义
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3.0 增删改设备返回
typedef void(CALLBACK *FuncOperateDevice)(INT nOperateType, DWORD dwUser);

// 3.1	获取所有的新接入的设备 0x0001
typedef void(CALLBACK *FuncGetNewConnectedDevices)(const vector<CONNECTED_DEVICE>& tanDevices, DWORD dwUser);

// 3.2	获取所有的设备类型列表 0x0002
typedef void(CALLBACK *FuncGetAllNetDeviceTypes)(const vector<NET_DEVICE_TYPE>& tanDeviceTypes, DWORD dwUser);

// 3.3	获取所有的设备（不包含报警和电源） 0x0003
typedef void(CALLBACK *FuncGetAllNetDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.4	获取所有包含数据或输出通道（或两者都存在）的设备 0x0004
typedef void(CALLBACK *FuncGetAllChannelDevices)(const vector<CHANNEL_DEVICE>& tanDevices, DWORD dwUser);

// 3.5	通过设备GUID获取设备信息 0x0005
typedef void(CALLBACK *FuncGetDeviceInfoByGUID)(NET_DEVICE device, DWORD dwUser);

// 3.6	通过设备ID获取设备信息 0x0006
typedef void(CALLBACK *FuncGetDeviceInfoByID)(NET_DEVICE device, DWORD dwUser);

// 3.7	通过设备IP获取设备信息 0x0007
typedef void(CALLBACK *FuncGetDeviceInfoByIP)(NET_DEVICE device, DWORD dwUser);

// 3.8	通过设备通话号（区号）获取设备实体 0x0008
typedef void(CALLBACK *FuncGetDeviceInfoByArea)(NET_DEVICE device, DWORD dwUser);

// 3.9	增加一个设备的基础数据 0x0009
typedef void(CALLBACK *FuncAddDeviceInfo)(INT nOperateType, DWORD dwUser);

// 3.10修改一个设备的基础数据 0x000A
typedef void(CALLBACK *FuncModifyDeviceInfo)(INT nOperateType, DWORD dwUser);

// 3.11	移除设备数据 0x000B
typedef void(CALLBACK *FuncRemoveNetDevice)(INT nOperateType, DWORD dwUser);

// 3.12	增加设备附加属性 0x000C
typedef void(CALLBACK *FuncAddDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.13	根据设备ID获取所有设备附加信息 0x000D
typedef void(CALLBACK *FuncGetDeviceAttachByID)(const vector<NET_DEVICE_ATTACH>& tanAttach, DWORD dwUser);

// 3.14	根据设备GUID获取所有设备附加信息 0x000E
typedef void(CALLBACK *FuncGetDeviceAttachByGUID)(NET_DEVICE_ATTACH attach, DWORD dwUser);

// 3.15	更新设备附加信息 0x000F
typedef void(CALLBACK *FuncUpdateDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.16	根据设备Guid删除设备的附加属性实体 0x0010
typedef void(CALLBACK *FuncRemoveDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.17	获取所有的报警设备列表，指设备类型为报警设备的 0x0011
typedef void(CALLBACK *FuncGetAllAlarmDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.18	获取所有的带输入通道设备列表，即带报警的设备 0x0012
typedef void(CALLBACK *FuncGetAllInputChannelDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.19	获取所有报警设备的附属信息表 0x0013
typedef void(CALLBACK *FuncGetAllNetAlarmDevicesAttach)(const vector<NET_ALARM_ATTACH>& tanAttach, DWORD dwUser);

// 3.20	根据设备GUID获取设备实体附属信息 0x0014
typedef void(CALLBACK *FuncGetNetAlarmDevicesAttach)(NET_ALARM_ATTACH attach, DWORD dwUser);

// 3.21	增加报警设备的附属信息0x0015
typedef void(CALLBACK *FuncAddNetAlarmDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.22	更改报警设备的附属信息 0x0016
typedef void(CALLBACK *FuncModifyNetAlarmDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.23	根据设备Guid删除报警设备附属表信息 0x0017
typedef void(CALLBACK *FuncRemoveNetAlarmDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.24	获取所有的电源设备列表，指设备类型为报警设备的 0x0018
typedef void(CALLBACK *FuncGetAllNetAlarmDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.25	获取所有的带输出通道设备列表 0x0019
typedef void(CALLBACK *FuncGetAllOutputChannelDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.26	获取所有电源设备的附属信息表 0x001A
typedef void(CALLBACK *FuncGetAllPowerDeviceAttach)(const vector<NET_ALARM_ATTACH>& tanAttach, DWORD dwUser);

// 3.27	根据设备GUID获取电源实体附属信息 0x001B
typedef void(CALLBACK *FuncGetPowerDeviceAttach)(NET_ALARM_ATTACH attach, DWORD dwUser);

// 3.28	增加电源设备的附属信息 0x001C
typedef void(CALLBACK *FuncAddPowerDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.29	更改电源设备的附属信息 0x001D
typedef void(CALLBACK *FuncModifyPowerDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.30	根据设备Guid删除电源设备附属表信息 0x001E
typedef void(CALLBACK *FuncRemovePowerDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.31	增加或删除对讲的设备配置 0x001F
typedef void(CALLBACK *FuncManageSpeakDeviceConfig)(INT nOperateType, DWORD dwUser);

// 3.32	根据区号获取对讲配置设备 0x0020
typedef void(CALLBACK *FuncGetSpeakDevice)(const vector<DEFAULT_CALL_DEVICE>& tanDevices, DWORD dwUser);

// 3.33	增加报警预案 0x0021
typedef void(CALLBACK *FuncAddAlarmProposal)(INT nOperateType, DWORD dwUser);

// 3.34	移除报警预案 0x0022
typedef void(CALLBACK *FuncRemoveAlarmProposal)(INT nOperateType, DWORD dwUser);

// 3.35	据报警主机Id和通道号获取报警预案基础实体 0x0023
typedef void(CALLBACK *FuncGetAlarmProposalByDevice)(AP_ALARM_DEVICE device, DWORD dwUser);

// 3.36	获取所有报警基础预案实体 0x0024
typedef void(CALLBACK *FuncGetAllAlarmProposals)(const vector<AP_ALARM_DEVICE>& tanDevices, DWORD dwUser);

// 3.37	根据预案Id获取预案实体 0x0025
typedef void(CALLBACK *FuncGetAlarmProposalByPolicy)(ALARM_PROPOSAL proposal, DWORD dwUser);

// 3.38	根据查询条件获取报警信息 0x0026
typedef void(CALLBACK *FuncQueryAlarmInfo)(const vector<ALARM_INFO>& tanInfo, DWORD dwUser);

// 3.39	根据查询条件获取信息总数 0x0027
typedef void(CALLBACK *FuncQueryInfoWrapper)(INT nRecord, DWORD dwUser);

// 3.40	设置设备的音量 0x0028
typedef void(CALLBACK *FuncSetDeviceVolume)(INT nOperateType, DWORD dwUser);

// 3.41	获取设备的音量 0x0029
typedef void(CALLBACK *FuncGetDeviceVolume)(INT nVolume, DWORD dwUser);

// 3.42	获取所有输入及输出外接设备 0x002A
typedef void(CALLBACK *FuncGetAllAlarmDeviceDetail)(const vector<ALARM_DEVICE_DETAIL>& tanDevDetail, DWORD dwUser);

// 3.43	根据设备GUID获取报警外接设备 0x002B
typedef void(CALLBACK *FuncGetAlarmDeviceDetail)(const vector<ALARM_DEVICE_DETAIL>& tanDevDetail, DWORD dwUser);

// 3.44	获取报警类型 0x002C
typedef void(CALLBACK *FuncGetAlarmType)(const vector<ALARM_DEVICE_DETAIL>& tanDevDetail, DWORD dwUser);

// 3.45	根据预案ID获取关联输出设备 0x002D
typedef void(CALLBACK *FuncGetAPOutChannel)(const vector<AP_OUT_CHANNEL>& tanDevDetail, DWORD dwUser);

// 3.46	获取所有输出通道的关联设备 0x002E
//typedef void(CALLBACK *FuncGetAllAPOutChannel)(int, DWORD dwUser);

// 3.47	根据设备ID重启设备 0x002F
typedef void(CALLBACK *FuncRestartDevice)(INT nOperateType, DWORD dwUser);

// 3.48	设置设备屏幕的开与关 0x0030
typedef void(CALLBACK *FuncSetScreenSwitch)(INT nOperateType, DWORD dwUser);

// 3.49	设置设备屏幕即时显示的文本 0x0031
typedef void(CALLBACK *FuncSetScreenText)(INT nOperateType, DWORD dwUser);

// 3.50	设置设备屏幕默认文本 0x0032
typedef void(CALLBACK *FuncSetScreenDefaultText)(INT nOperateType, DWORD dwUser);

// 3.51	设置设备音效 0x0033
typedef void(CALLBACK *FuncSetDeviceAudio)(INT nOperateType, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 6. 组信息管理(ManageGroup) 0x06
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 6.0 增删改组信息 0x0000
typedef void(CALLBACK *FuncOperateGroup)(INT nOperateType, DWORD dwUser);

// 6.1	增加组信息 0x0001
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddGroup)(INT nOperateType, DWORD dwUser);

// 6.2	更新组信息 0x0002
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateGroup)(INT nOperateType, DWORD dwUser);

// 6.3	删除组信息 0x0003
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteGroup)(INT nOperateType, DWORD dwUser);

// 6.4	获取所有组信息 0x0004
typedef void(CALLBACK *FuncGetAllGroupInfo)(const vector<DEVICE_GROUP>& tanGroups, DWORD dwUser);

// 6.5	根据组ID获取组设备信息 0x0005
typedef void(CALLBACK *FuncGetGroupDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 6.6	增删改组的设备 0x0006
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncManageGroupDevice)(INT nOperateType, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 7.会话管理(ManageSession) 0x07
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 7.0 增删改会话
typedef void(CALLBACK *FuncOperateSession)(INT nOperateType, DWORD dwUser);

// 7.1 根据会话ID获取会话信息ParaId=0x0001
typedef void(CALLBACK *FuncGetSessionByID)(NET_SESSION session, DWORD dwUser);

// 7.2 获取所有会话信息ParaId=0x0002
typedef void(CALLBACK *FuncGetAllSessions)(const vector<NET_SESSION>& tanSession, DWORD dwUser);

// 7.3 根据会话ID终止会话ParaId=0x0003
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncTerminateSession)(INT nOperateType, DWORD dwUser);

// 7.4 增加会话中的设备ParaId=0x0004
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddDeviceIntoSession)(INT nOperateType, DWORD dwUser);

// 7.5 删除会话中的设备ParaId=0x0005
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncRemoveDeviceFromSession)(INT nOperateType, DWORD dwUser);

// 7.6 获取会话的主发起设备ParaId=0x0006
typedef void(CALLBACK *FuncGetLeadingDevice)(CONNECTED_DEVICE device, DWORD dwUser);

// 7.7 根据会话ID获取所有连接设备（ParaId=0x0007）
typedef void(CALLBACK *FuncGetDevicesInSession)(const vector<CONNECTED_DEVICE>& tanDevice, DWORD dwUser);

// 7.7 获取的所有连接设备ParaId=0x0009
typedef void(CALLBACK *FuncGetAllConnectedDevices)(const vector<CONNECTED_DEVICE>& tanDevice, DWORD dwUser);

// 7.8 开始录音ParaId=0x000A
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncStartRecording)(INT nOperateType, DWORD dwUser);

// 7.9 停止录音ParaId=0x000B
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncStopRecording)(INT nOperateType, DWORD dwUser);

// 7.10 设置会话音量ParaId=0x000C
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSetVolume)(INT nOperateType, DWORD dwUser);

// 7.11 设置会音效ParaId=0x000D
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSetAudio)(INT nOperateType, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 8.资源数据管理(ManageResource) 0x08
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 8.0 增删改资源 0x0000
typedef void(CALLBACK *FuncOperateResource)(INT nOperateType, DWORD dwUser);

// 8.1	上传文件 0x0001
typedef void(CALLBACK *FuncUploadFile)(INT nSessionID, DWORD dwUser);

// 8.2	上传文件数据（纯数据） 0x0002
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUploadDataInFile)(INT nOperateType, DWORD dwUser);

// 8.3	上传文件数据完成 0x0003
typedef void(CALLBACK *FuncFinishUploadingFile)(INT nFileID, DWORD dwUser);

// 8.4	取消上传文件 0x0004
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCancelUploadingFile)(INT nOperateType, DWORD dwUser);

// 8.5	已上传完成文件位置 0x0005
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncGetPosOfUploadedFile)(INT nOperateType, DWORD dwUser);

// 8.6	下载文件 0x0006
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDownloadFile)(INT nOperateType, DWORD dwUser);

// 8.7	服务器发送文件数据 0x0007
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSendFileByServer)(string strText, DWORD dwUser);
typedef void(CALLBACK *FuncRecvDataFromServer)(char* pData, int nLength, DWORD dwUser);

// 8.8	服务器发送下载文件结束 0x0008
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncFinishSendingFileByServer)(USHORT uSessionID, DWORD dwUser);

// 8.9	取消上传下载 0x0009
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCancelUploadOrDownload)(INT nOperateType, DWORD dwUser);

// 8.10 查找录音文件 0x000A
typedef void(CALLBACK *FuncFindRecordedFile)(const vector<RECORD_FILE>& tanFiles, DWORD dwUser);

// 8.11 下载文件 0x000B
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
//typedef void(CALLBACK *FuncGetPosOfDownload)(INT nOperateType, DWORD dwUser);

// 8.12 请求下载的位置 0x000C
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncGetPosOfDownload)(INT nOperateType, DWORD dwUser);

// 8.13 获取所有的上传资源文件 0x000D
typedef void(CALLBACK *FuncGetAllUploadedFiles)(const vector<NET_FILE>& tanFiles, DWORD dwUser);

// 8.14 根据文件ID获取文件信息 0x000E
typedef void(CALLBACK *FuncGetFileInfo)(NET_FILE resource, DWORD dwUser);

// 8.15 根据文件ID删除文件 0x000F
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteFile)(INT nOperateType, DWORD dwUser);

// 8.16 更新文件信息 0x0010
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateFile)(INT nOperateType, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 9.寻呼、对讲(ManageSpeaking) 0x09
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 9.0
typedef void(CALLBACK *FuncOperateSpeak)(INT nOperateType, DWORD dwUser);

// 9.1	寻呼 0x0001
typedef void(CALLBACK *FuncCall)(USHORT uSessionID, DWORD dwUser);

// 9.2	对讲 0x0002
typedef void(CALLBACK *FuncSpeak)(USHORT uSessionID, DWORD dwUser);

// 9.3	停止寻呼 0x0003
typedef void(CALLBACK *FuncCancelCalling)(INT nOperateType, DWORD dwUser);

// 9.4	停止对讲 0x0004
typedef void(CALLBACK *FuncCancelSpeaking)(INT nOperateType, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 10.广播(ManageBroadcast) 0x0A
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 9.0
typedef void(CALLBACK *FuncOperateBroadcast)(INT nOperateType, DWORD dwUser);

// 10.1 广播开始 0x0001
typedef void(CALLBACK *FuncStartBroadcasting)(INT nSessionID, DWORD dwUser);
typedef void(CALLBACK *FuncStartBroadcastingEx)(USHORT nSessionID, DWORD dwUser);


// 10.3 广播的音频格式数据 0x0003
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncBroadcastAudio)(INT nOperateType, DWORD dwUser);

// 10.5 传送音频数据 0x0005
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncTransmitAudio)(string strText, DWORD dwUser);

// 10.6 停止广播 0x0006
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCancelBroadcasting)(INT nOperateType, DWORD dwUser);

// 10.7 切歌操作 0x0007
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSwitchSong)(INT nOperateType, DWORD dwUser);

// 10.8 广播临时文件 0x0008
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncBroadcastTempFile)(INT nOperateType, DWORD dwUser);
// 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 12. 授权管理(ManageAuthority) 0x0C
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12.1 获取注册码 0x0001
typedef void(CALLBACK *FuncGetMachineCode)(string strRegisterCode, DWORD dwUser);

// 12.2 获取证书信息 0x0002
typedef void(CALLBACK *FuncGetLicenseInfo)(NET_LICENSE license, DWORD dwUser);

// 12.3 证书有效性验证 0x0003
typedef void(CALLBACK *FuncVerifyLicense)(NET_LICENSE license, DWORD dwUser);

// 12.4 注册证书 0x0004
typedef void(CALLBACK *FuncRegisterLicense)(NET_LICENSE license, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 13. 任务和方案管理回调函数
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3.0 增删改任务返回
typedef void(CALLBACK *FuncOperateTask)(INT nOperateType, DWORD dwUser);

// 13.1	增加任务 0x0001
typedef void(CALLBACK *FuncAddTask)(INT nOperateType, DWORD dwUser);

// 13.2	更新任务 0x0002
typedef void(CALLBACK *FuncUpdateTask)(INT nOperateType, DWORD dwUser);

// 13.3	删除任务 0x0003
typedef void(CALLBACK *FuncRemoveTask)(INT nOperateType, DWORD dwUser);

// 13.4	根据任务ID获取任务信息 0x0004
typedef void(CALLBACK *FuncGetTaskInfo)(BASE_TASK task, DWORD dwUser);

// 13.5	获取所有任务信息 0x0005
typedef void(CALLBACK *FuncGetAllTaskInfo)(const vector<BASE_TASK>& tanTasks, DWORD dwUser);

// 13.6	根据方案ID获取所有任务信息 0x0006
typedef void(CALLBACK *FuncGetAllTaskView)(const vector<TASK_INFO_VIEW>& tanTaskViews, DWORD dwUser);

// 13.7	获取所有执行任务的状态 0x0007
typedef void(CALLBACK *FuncGetAllTaskStatus)(const vector<TASK_STATUS>& tanTaskStatus, DWORD dwUser);

// 13.8	获取所有任务类型s 0x00013
typedef void(CALLBACK *FuncGetAllTaskTypes)(const vector<BASE_TASK_TYPE>& tanTaskTypes, DWORD dwUser);

// 13.9	 0x0009

// 13.10 根据任务ID获取文件播放任务列表 0x000A
typedef void(CALLBACK *FuncGetPlayTask)(PLAY_TASK_ATTACH attach, DWORD dwUser);

// 13.11 增加文件播放附加属性 0x000B
typedef void(CALLBACK *FuncAddPlayTaskAttach)(INT nOperateType, DWORD dwUser);

// 13.12 更新文件播放附加属性 0x000C
typedef void(CALLBACK *FuncUpdatePlayTaskAttach)(INT nOperateType, DWORD dwUser);

// 13.13 删除文件播放附加属性 0x000D
typedef void(CALLBACK *FuncRemovePlayTaskAttach)(INT nOperateType, DWORD dwUser);

// 13.14 根据任务ID获取设备关联 0x000E
typedef void(CALLBACK *FuncGetBCDeviceByTaskID)(const vector<BC_TASK_DEVICE>& tanDevices, DWORD dwUser);

// 13.15 根据任务ID获取关联设备信息 0x000F
typedef void(CALLBACK *FuncGetDeiveByTaskID)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 13.16 增加或删除播放任务的设备 0x0010
typedef void(CALLBACK *FuncAddOrDelPlayingDevice)(const vector<PLAY_TASK_FILE>& tanFiles, DWORD dwUser);

// 13.17 根据任务Id获取播放任务中的文件列表 0x00011
typedef void(CALLBACK *FuncGetPlayingFilesByTaskID)(const vector<PLAY_TASK_FILE>& tanFiles, DWORD dwUser);

// 13.18 增加或删除播放任务中的文件列表 0x00012
typedef void(CALLBACK *FuncAddOrDelPlayingFiles)(INT nOperateType, DWORD dwUser);

// 13.19 根据任务Id获取采播附加属性信息 0x00013
typedef void(CALLBACK *FuncGetAcquicastAttach)(BC_TASK_ATTACH attach, DWORD dwUser);

// 13.20 增加采播任务属性 0x0014
typedef void(CALLBACK *FuncAddAcquicastAttach)(INT nOperateType, DWORD dwUser);

// 13.21 修改采播任务属性(ParaId=0x0015)
typedef void(CALLBACK *FuncModifyAcquicastAttach)(INT nOperateType, DWORD dwUser);

// 13.22 删除采播任务属性(ParaId=0x0016)
typedef void(CALLBACK *FuncRemoveAcquicastAttach)(INT nOperateType, DWORD dwUser);

// 13.23 获取定时设置(ParaId=0x0017)
typedef void(CALLBACK *FuncGetTimingConfig)(TIMING_TASK task, DWORD dwUser);

// 13.24 增加定时设置(ParaId=0x0018)
typedef void(CALLBACK *FuncAddTimingConfig)(INT nOperateType, DWORD dwUser);

// 13.25 // 重复了

// 13.26 删除定时设置(ParaId=0x001A)
typedef void(CALLBACK *FuncRemoveTimingConfig)(INT nOperateType, DWORD dwUser);

// 13.27 获取所有任务方案(ParaId=0x001B)
typedef void(CALLBACK *FuncGetAllTaskPolicy)(const vector<TASK_POLICY>& m_tanTaskPolicy, DWORD dwUser);

// 13.28 根据方案ID获取方案实体(ParaId=0x001C)
typedef void(CALLBACK *FuncGetTaskPolicy)(TASK_POLICY policy, DWORD dwUser);

// 13.29 增加任务方案(ParaId=0x001D)
typedef void(CALLBACK *FuncAddTaskPolicy)(INT nOperateType, DWORD dwUser);

// 13.30 更新任务方案(ParaId=0x001E)
typedef void(CALLBACK *FuncModifyTaskPolicy)(INT nOperateType, DWORD dwUser);

// 13.31 删除任务方案(ParaId=0x001F)
typedef void(CALLBACK *FuncRemoveTaskPolicy)(INT nOperateType, DWORD dwUser);

// 13.32 增加方案中的任务(ParaId=0x0020)
typedef void(CALLBACK *FuncAddTaskIntoPolicy)(INT nOperateType, DWORD dwUser);

// 13.33 从方案中删除任务(ParaId=0x0021)
typedef void(CALLBACK *FuncRemoveTaskFromPolicy)(INT nOperateType, DWORD dwUser);

// 13.34 启动任务(ParaId=0x0023)
typedef void(CALLBACK *FuncStartTask)(INT nOperateType, DWORD dwUser);

// 13.35 停止任务(ParaId=0x0024)
typedef void(CALLBACK *FuncStopTask)(INT nOperateType, DWORD dwUser);

// 13.36 获取电源开关任务信息(ParaId=0x0025)
typedef void(CALLBACK *FuncGetPowerSwithTask)(const vector<POWER_TASK_SWITCH>& tanInfo, DWORD dwUser);

// 13.37 获取所有级别信息(ParaId=0x0026)
typedef void(CALLBACK *FuncGetAllTaskLevels)(const vector<TASK_LEVEL>& tanLevels, DWORD dwUser);

// 13.38 获取全部或指定方案ID的LED控制任务信息(ParaId=0x0027)
typedef void(CALLBACK *FuncGetAllLedCtrlTaskAttach)(const vector<LED_CTRL_TASK_ATTACH>& tanTaskInfo, DWORD dwUser);

// 13.39 根据任务ID获取LED控制任务信息(ParaId=0x0028)
typedef void(CALLBACK *FuncGetLedCtrlTaskAttach)(LED_CTRL_TASK_ATTACH info, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 14.客户端获取状态指令(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 14.0
typedef void(CALLBACK *FuncOperateStatus)(INT nOperateType, DWORD dwUser);

// 14.1 获取所有报警设备状态信息(ParaId=0x0014)
typedef void(CALLBACK *FuncGetAllAlarmDevStatus)(const vector<DEV_CHANNEL_STATUS>& tanStatus, DWORD dwUser);

// 14.2 根据IP获取报警设备状态信息(ParaId=0x0015)
typedef void(CALLBACK *FuncGetAlarmDevStatus)(DEV_CHANNEL_STATUS status, DWORD dwUser);

// 14.3 根据IP和报警通道确认报警(ParaId=0x0018)
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncConfirmAlarm)(INT nOperateType, DWORD dwUser);

// 14.4 获取所有电源的状态信息(ParaId=0x0019)
typedef void(CALLBACK *FuncGetAllPowerStatus)(const vector<DEV_CHANNEL_STATUS>& tanStatus, DWORD dwUser);

// 14.5 根据IP获取电源设备状态信息(ParaId=0x001A)
typedef void(CALLBACK *FuncGetPowerStatus)(DEV_CHANNEL_STATUS status, DWORD dwUser);

// 14.6 客户端控制电源的开或关(ParaId=0x001D)
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCtrlPowerSwitchByIP)(INT nOperateType, DWORD dwUser);

// 14.7 获取所有接入设备的状态信息(ParaId=0x001E)
typedef void(CALLBACK *FuncGetAllDeviceStatus)(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);

// 14.8 根据设备ID获取设备的状态信息(ParaId=0x001F)
typedef void(CALLBACK *FuncGetDevStatusByID)(DEVICE_STATUS status, DWORD dwUser);

// 14.9 根据设备IP获取设备的状态信息(ParaId=0x0020)
typedef void(CALLBACK *FuncGetDevStatusByIP)(DEVICE_STATUS status, DWORD dwUser);

// 14.10 控制电源的开或关(ParaId=0x0021)
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCtrlPowerSwitchByID)(INT nOperateType, DWORD dwUser);

// 14.11 获取所有警示灯状态信息(ParaId=0x0022)
typedef void(CALLBACK *FuncGetAllAlarmLightStatus)(const vector<DEV_CHANNEL_STATUS>& tanStatus, DWORD dwUser);

// 14.12 根据设备ID获取警示灯状态信息(ParaId=0x0023)
typedef void(CALLBACK *FuncGetAlarmLightStatus)(DEV_CHANNEL_STATUS status, DWORD dwUser);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 15.服务器推送设备状态(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 15.1	服务器推送设备状态变化(ParaId=0x0001)
typedef void(CALLBACK *FuncAutoGetDeviceStatus)(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);

// 15.2	服务器推送会话状态变化(ParaId=0x0002)
typedef void(CALLBACK *FuncAutoGetSessionStatus)(SESSION_STATUS status, DWORD dwUser);

// 15.3	服务器推送会话终止消息(ParaId=0x0003)
typedef void(CALLBACK *FuncAutoGetSessionTerminal)(INT nSessionID, DWORD dwUser);

// 15.4	服务器推送在线用户状态变化(ParaId=0x0004)
typedef void(CALLBACK *FuncAutoGetUserStatus)(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);

// 15.5	服务器推送任务状态变化(ParaId=0x0005)
typedef void(CALLBACK *FuncAutoGetTaskStatus)(TASK_STATUS status, DWORD dwUser);

// 15.6	服务器推送方案状态变化(ParaId=0x0005)
typedef void(CALLBACK *FuncAutoGetPolicyStatus)(POLICY_STATUS status, DWORD dwUser);

// 15.17 服务器推送设备的通道状态变化(ParaId=0x0017)
typedef void(CALLBACK *FuncAutoGetChannelStatus)(DEV_CHANNEL_STATUS tanStatus, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 1. 网络连接与登录接口
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1.1 连接到服务器
//IPCAST_SDK_API BOOL __stdcall AEBELL_IPCAST_Connect(string strIP, UINT uPort, LOGIN_REQUEST stuLoginRequest);
//IPCAST_SDK_API BOOL __stdcall AEBELL_IPCAST_Connect(string strIP, UINT uPort, LOGIN_REQUEST stuLoginRequest, FuncConnect cbConnect, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_Connect(string strIP, UINT uPort, LOGIN_REQUEST stuLoginRequest, FuncConnect cbConnect, FuncConnectError cbConnectError, DWORD dwUser);
// 1.2 断开连接
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DisConnect();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 2. 用户管理接口
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2.1	增加用户 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddUser(NET_USER user, FuncAddUser cbAddUser, DWORD dwUser, DEVICE_FOR_USER device = DEVICE_FOR_USER());
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddUser(NET_USER user, ROLE_FOR_USER role, FuncAddUser cbAddUser, DWORD dwUser, DEVICE_FOR_USER device = DEVICE_FOR_USER());

// 2.2	更新用户 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateUser(NET_USER user, FuncUpdateUser cbUpdateUser, DWORD dwUser);

// 2.3	删除用户信息 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteUser(string strUserGUID, FuncDeleteUser cbDeleteUser, DWORD dwUser);

// 2.4 获取所有的用户信息
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllUsers(FuncGetAllUsers cbGetAllUser, DWORD dwUser);

// 2.5  通过用户的GUID获取用户信息
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetUserInfo(FuncGetUserInfo cbGetUserInfo, DWORD dwUser);

// 2.6 通过用户的GUID获取分配给用户的设备
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllocatedDevicesByGUID(FuncGetAllocatedDevicesByGUID cbGetAllocatedDevicesByGUID, DWORD dwUser);

// 2.7 增加或删除用户分配的设备
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageAllocatedDevices(DEVICE_FOR_USER device, FuncManageAllocatedDevices cbManageAllocatedDevices, DWORD dwUser);

// 2.8 获取所有用户类型信息表
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllUserTypes(FuncGetAllUserTypes cbGetAllUserTypes, DWORD dwUser);

// 2.9 获取用户权限列表
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetUserAuthorities(INT nOperateType, string strGUID, FuncGetUserAuthorities cbGetUserAuthorities, DWORD dwUser);

// 2.10	获取所有角色 0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllRoles(FuncGetAllRoles cbGetAllRoles, DWORD dwUser);

// 2.11	增删改用户关联角色 0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageAssociatedRole(string strUserID, ROLE_FOR_USER role, FuncManageAssociatedRole cbManageAssociatedRole, DWORD dwUser);

// 2.12	增加角色 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddRole(NET_ROLE role, ROLE_FUNCTION function, FuncAddRole cbAddRole, DWORD dwUser);

// 2.13	更新角色 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateRole(NET_ROLE role, ROLE_FUNCTION function, FuncUpdateRole cbUpdateRole, DWORD dwUser);

// 2.14	删除角色 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteRole(string strRoleGUID, FuncDeleteRole cbDeleteRole, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 3.设备管理
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3.1	获取所有的新接入的设备 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetNewConnectedDevices(FuncGetNewConnectedDevices cbGetNewConnectedDevices, DWORD dwUser);

// 3.2	获取所有的设备类型列表 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetDeviceTypes(FuncGetAllNetDeviceTypes cbGetAllNetDeviceTypes, DWORD dwUser);

// 3.3	获取所有的设备（不包含报警和电源） 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetDevices(FuncGetAllNetDevices cbGetAllNetDevices, DWORD dwUser);

// 3.4	获取所有包含数据或输出通道（或两者都存在）的设备 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllChannelDevices(FuncGetAllChannelDevices cbGetAllChannelDevices, DWORD dwUser);

// 3.5	通过设备GUID获取设备信息 0x0005(针对硬件设备，针对pc端无数据)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByGUID(FuncGetDeviceInfoByGUID cbGetDeviceInfoByGUID, DWORD dwUser);

// 3.6	通过设备ID获取设备信息 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByID(string strDeviceID, FuncGetDeviceInfoByID cbGetDeviceInfoByID, DWORD dwUser);

// 3.7	通过设备IP获取设备信息 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByIP(string strDeviceIP, FuncGetDeviceInfoByIP cbGetDeviceInfoByIP, DWORD dwUser);

// 3.8	通过设备通话号（区号）获取设备实体 0x0008
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByArea(WORD nAreaNum, FuncGetDeviceInfoByArea cbGetDeviceInfoByArea, DWORD dwUser);

// 3.9	增加一个设备的基础数据 0x0009
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddDeviceInfo(NET_DEVICE device, INT nOperateType, const list<NET_DEVICE_ATTACH>& tanAttach, const list<DEFAULT_CALL_DEVICE>& tanCallDevices, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddBaseDeviceInfo(NET_DEVICE device, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAudioDeviceInfo(NET_DEVICE netDevice, NET_DEVICE_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, DEFAULT_CALL_DEVICES callDevices = DEFAULT_CALL_DEVICES());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAlarmDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, ALARM_DEVICE_DETAILS devDetails = ALARM_DEVICE_DETAILS());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPowerDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, POWER_DEVICE_DETAILS devDetails = POWER_DEVICE_DETAILS());

// 3.10修改一个设备的基础数据 0x000A
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyDeviceInfo(NET_DEVICE device, INT nOperateType, const list<NET_DEVICE_ATTACH>& tanAttach, const list<DEFAULT_CALL_DEVICE>& tanCallDevices, FuncModifyDeviceInfo cbModifyDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyBaseDeviceInfo(NET_DEVICE device, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyAudioDeviceInfo(NET_DEVICE netDevice, NET_DEVICE_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, DEFAULT_CALL_DEVICES callDevices = DEFAULT_CALL_DEVICES());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyAlarmDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, ALARM_DEVICE_DETAILS devDetails = ALARM_DEVICE_DETAILS());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyPowerDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, POWER_DEVICE_DETAILS devDetails = POWER_DEVICE_DETAILS());

// 3.11	移除设备数据 0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveNetDevice(OPERATE_DEVICE operateDev, FuncRemoveNetDevice cbRemoveNetDevice, DWORD dwUser);

// 3.12	增加设备附加属性 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddDeviceAttach(NET_DEVICE_ATTACH devAttach, FuncAddDeviceAttach cbAddDeviceAttach, DWORD dwUser);

// 3.13	根据设备ID获取所有设备附加信息 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceAttachByID(FuncGetDeviceAttachByID cbGetDeviceAttachByID, DWORD dwUser);

// 3.14	根据设备GUID获取所有设备附加信息 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceAttachByGUID(string strGUID, FuncGetDeviceAttachByGUID cbGetDeviceAttachByGUID, DWORD dwUser);

// 3.15	更新设备附加信息 0x000F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateDeviceAttach(NET_DEVICE_ATTACH devAttach, FuncUpdateDeviceAttach cbUpdateDeviceAttach, DWORD dwUser);

// 3.16	根据设备Guid删除设备的附加属性实体 0x0010
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveDeviceAttach(FuncRemoveDeviceAttach cbRemoveDeviceAttach, DWORD dwUser);

// 3.17	获取所有的报警设备列表，指设备类型为报警设备的 0x0011
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmDevices(FuncGetAllAlarmDevices cbGetAllAlarmDevices, DWORD dwUser);

// 3.18	获取所有的带输入通道设备列表，即带报警的设备 0x0012
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllInputChannelDevices(FuncGetAllInputChannelDevices cbGetAllInputChannelDevices, DWORD dwUser);

// 3.19	获取所有报警设备的附属信息表 0x0013
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetAlarmDevicesAttach(FuncGetAllNetAlarmDevicesAttach cbGetAllNetAlarmDevicesAttach, DWORD dwUser);

// 3.20	根据设备GUID获取设备实体附属信息 0x0014
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetNetAlarmDevicesAttach(string strGUID, FuncGetNetAlarmDevicesAttach cbGetNetAlarmDevicesAttach, DWORD dwUser);

// 3.21	增加报警设备的附属信息0x0015
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddNetAlarmDeviceAttach(NET_ALARM_ATTACH alarmAttach, FuncAddNetAlarmDeviceAttach cbAddNetAlarmDeviceAttach, DWORD dwUser);

// 3.22	更改报警设备的附属信息 0x0016
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyNetAlarmDeviceAttach(NET_ALARM_ATTACH alarmAttach, FuncModifyNetAlarmDeviceAttach cbModifyNetAlarmDeviceAttach, DWORD dwUser);

// 3.23	根据设备Guid删除报警设备附属表信息 0x0017
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveNetAlarmDeviceAttach(string strDeviceGUID, FuncRemoveNetAlarmDeviceAttach cbRemoveNetAlarmDeviceAttach, DWORD dwUser);

// 3.24	获取所有的电源设备列表，指设备类型为报警设备的 0x0018
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetAlarmDevices(FuncGetAllNetAlarmDevices cbGetAllNetAlarmDevices, DWORD dwUser);

// 3.25	获取所有的带输出通道设备列表 0x0019
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllOutputChannelDevices(FuncGetAllOutputChannelDevices cbGetAllOutputChannelDevices, DWORD dwUser);

// 3.26	获取所有电源设备的附属信息表 0x001A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllPowerDeviceAttach(FuncGetAllPowerDeviceAttach cbGetAllPowerDeviceAttach, DWORD dwUser);

// 3.27	根据设备GUID获取电源实体附属信息 0x001B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPowerDeviceAttach(FuncGetPowerDeviceAttach cbGetPowerDeviceAttach, DWORD dwUser);

// 3.28	增加电源设备的附属信息 0x001C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPowerDeviceAttach(NET_ALARM_ATTACH attach, FuncAddPowerDeviceAttach cbAddPowerDeviceAttach, DWORD dwUser);

// 3.29	更改电源设备的附属信息 0x001D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyPowerDeviceAttach(NET_ALARM_ATTACH attach, FuncModifyPowerDeviceAttach cbModifyPowerDeviceAttach, DWORD dwUser);

// 3.30	根据设备Guid删除电源设备附属表信息 0x001E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemovePowerDeviceAttach(string strDeviceGUID, FuncRemovePowerDeviceAttach cbRemovePowerDeviceAttach, DWORD dwUser);

// 3.31	增加或删除对讲的设备配置 0x001F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageSpeakDeviceConfig(CALL_DEVICE_WRAPPER device, FuncManageSpeakDeviceConfig cbManageSpeakDeviceConfig, DWORD dwUser);

// 3.32	根据区号获取对讲配置设备 0x0020
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetSpeakDevice(WORD nAreaNum, FuncGetSpeakDevice cbGetSpeakDevice, DWORD dwUser);

// 3.33	增加报警预案 0x0021
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAlarmProposal(AP_ALARM_DEVICE device, ALARM_PROPOSAL proposal, DEVICE_ID_WRAPPER devIDs, AP_OUT_CHANNEL_WRAPPER channels, FuncAddAlarmProposal cbAddAlarmProposal, DWORD dwUser);

// 3.34	移除报警预案 0x0022
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveAlarmProposal(string strProposalGUID, INT nAlarmChannelNo, FuncRemoveAlarmProposal cbRemoveAlarmProposal, DWORD dwUser);

// 3.35	据报警主机Id和通道号获取报警预案基础实体 0x0023
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmProposalByDevice(string strDeviceID, INT nAlarmChannelNo, FuncGetAlarmProposalByDevice cbGetAlarmProposalByDevice, DWORD dwUser);

// 3.36	获取所有报警基础预案实体 0x0024
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmProposals(FuncGetAllAlarmProposals cbGetAllAlarmProposals, DWORD dwUser);

// 3.37	根据预案Id获取预案实体 0x0025
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmProposalByPolicy(string strProposalGUID, FuncGetAlarmProposalByPolicy cbGetAlarmProposalByPolicy, DWORD dwUser);

// 3.38	根据查询条件获取报警信息 0x0026
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_QueryAlarmInfo(ALARM_QUERY query, INT nPage, INT nRecordsPerPage, FuncQueryAlarmInfo cbQueryAlarmInfo, DWORD dwUser);

// 3.39	根据查询条件获取信息总数 0x0027
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_QueryInfoWrapper(ALARM_QUERY query, FuncQueryInfoWrapper cbQueryInfoWrapper, DWORD dwUser);

// 3.40	设置设备的音量 0x0028
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetDeviceVolume(DEVICE_VOLUME volume, INT nVolume, FuncSetDeviceVolume cbSetDeviceVolume, DWORD dwUser);

// 3.41	获取设备的音量 0x0029
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceVolume(DEVICE_VOLUME volume, FuncGetDeviceVolume cbGetDeviceVolume, DWORD dwUser);

// 3.42	获取所有输入及输出外接设备 0x002A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmDeviceDetail(FuncGetAllAlarmDeviceDetail cbGetAllAlarmDeviceDetail, DWORD dwUser);

// 3.43	根据设备GUID获取报警外接设备 0x002B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmDeviceDetail(string strAlarmDeviceGUID, FuncGetAlarmDeviceDetail cbGetAlarmDeviceDetail, DWORD dwUser);

// 3.44	获取报警类型 0x002C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmType(FuncGetAlarmType cbGetAlarmType, DWORD dwUser);

// 3.45	根据预案ID获取关联输出设备 0x002D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAPOutChannel(string strProposalGUID, FuncGetAPOutChannel cbGetAPOutChannel, DWORD dwUser);

// 3.46	获取所有输出通道的关联设备 0x002E
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAPOutChannel(FuncGetAllAPOutChannel cbGetAllAPOutChannel, DWORD dwUser);

// 3.47	根据设备ID重启设备 0x002F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RestartDevice(INT nDeviceID, FuncRestartDevice cbRestartDevice, DWORD dwUser);

// 3.48	设置设备屏幕的开与关 0x0030
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetScreenSwitch(DEVICE_SWITCH devSwitch, FuncSetScreenSwitch cbSetScreenSwitch, DWORD dwUser);

// 3.49	设置设备屏幕即时显示的文本 0x0031
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetScreenText(DEVICE_TEXT devText, FuncSetScreenText cbSetScreenText, DWORD dwUser);

// 3.50	设置设备屏幕默认文本 0x0032
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetScreenDefaultText(INT nDeviceID, FuncSetScreenDefaultText cbSetScreenDefaultText, DWORD dwUser);

// 3.51	设置设备音效 0x0033
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetDeviceAudio(DEVICE_AUDIO devAudio, FuncSetDeviceAudio cbSetDeviceAudio, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 6. 组信息管理(ManageGroup) 0x06
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 6.1	增加组信息 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddGroup(DEVICE_GROUP group, FuncAddGroup cbAddGroup, DWORD dwUser, DEVICE_GROUP_ATTACH attach = {});

// 6.2	更新组信息 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateGroup(DEVICE_GROUP group, FuncUpdateGroup cbUpdateGroup, DWORD dwUser, DEVICE_GROUP_ATTACH attach = {});

// 6.3	删除组信息 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteGroup(string strGroupGUID, FuncDeleteGroup cbDeleteGroup, DWORD dwUser);

// 6.4	获取所有组信息 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllGroupInfo(FuncGetAllGroupInfo cbGetAllGroupInfo, DWORD dwUser);

// 6.5	根据组ID获取组设备信息 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetGroupDevices(string strGroupGUID, FuncGetGroupDevices cbGetGroupDevices, DWORD dwUser);

// 6.6	增删改组的设备 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageGroupDevice(DEVICE_ID_WRAPPER devIDs, FuncManageGroupDevice cbManageGroupDevice, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 7.会话管理(ManageSession) 0x07
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 7.1 根据会话ID获取会话信息ParaId=0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetSessionByID(USHORT uSessionID, FuncGetSessionByID cbGetSessionByID, DWORD dwUser);

// 7.2 获取所有会话信息ParaId=0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllSessions(FuncGetAllSessions cbGetAllSessions, DWORD dwUser);

// 7.3 根据会话ID终止会话ParaId=0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_TerminateSession(USHORT uSessionID, FuncTerminateSession cbTerminateSession, DWORD dwUser);

// 7.4 增加会话中的设备ParaId=0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddDeviceIntoSession(USHORT uSessionID, DEVICE_ID_WRAPPER devIDs, FuncAddDeviceIntoSession cbAddDeviceIntoSession, DWORD dwUser);

// 7.5 删除会话中的设备ParaId=0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveDeviceFromSession(USHORT uSessionID, DEVICE_ID_WRAPPER devIDs, FuncRemoveDeviceFromSession cbRemoveDeviceFromSession, DWORD dwUser);

// 7.6 获取会话的主发起设备ParaId=0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetLeadingDevice(USHORT uSessionID, FuncGetLeadingDevice cbGetLeadingDevice, DWORD dwUser);

// 7.7 获取会话中的设备
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDevicesInSession(USHORT uSessionID, FuncGetAllConnectedDevices cbGetAllConnectedDevices, DWORD dwUser);

// 7.7 获取的所有连接设备ParaId=0x0009
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllConnectedDevices(FuncGetAllConnectedDevices cbGetAllConnectedDevices, DWORD dwUser);

// 7.8 开始录音ParaId=0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StartRecording(USHORT uSessionID, FuncStartRecording cbStartRecording, DWORD dwUser, string strFileName = "");

// 7.9 停止录音ParaId=0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StopRecording(USHORT uSessionID, FuncStopRecording cbStopRecording, DWORD dwUser);

// 7.10 设置会话音量ParaId=0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetVolume(USHORT uSessionID, BYTE nVolume, FuncSetVolume cbSetVolume, DWORD dwUser);

// 7.11 设置会音效ParaId=0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetAudio(USHORT uSessionID, INT nAudio, FuncSetAudio cbSetAudio, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 8.资源数据管理(ManageResource) 0x08
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 8.1	上传文件 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UploadFile(NET_RESOURCE resource, FuncUploadFile cbUploadFile, FuncOperateResource cbOperateResource, DWORD dwUser);

// 8.2	上传文件数据（纯数据） 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UploadDataInFile(USHORT uSesionID, string strData, FuncUploadDataInFile cbUploadDataInFile, FuncOperateResource cbOperateResource, DWORD dwUser);

// 8.3	上传文件数据完成 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_FinishUploadingFile(USHORT uSessionID, FuncFinishUploadingFile cbFinishUploadingFile, FuncOperateResource cbOperateResource, DWORD dwUser);

// 8.4	取消上传文件 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelUploadingFile(USHORT uSessionID, FuncCancelUploadingFile cbCancelUploadingFile, DWORD dwUser);

// 8.5	已上传完成文件位置 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPosOfUploadedFile(USHORT uSessionID, FuncGetPosOfUploadedFile cbGetPosOfUploadedFile, DWORD dwUser);

// 8.6	下载文件 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DownloadFile(RECORD_FILE file, FuncDownloadFile cbDownloadFile, DWORD dwUser);

// 8.7	服务器发送文件数据 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SendFileByServer(/*string strData,*/ FuncSendFileByServer cbSendFileByServer, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RecvDataFromServer(FuncRecvDataFromServer cbRecvDataFromServer, DWORD dwUser);

// 8.8	服务器发送下载文件结束 0x0008
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_FinishSendingFileByServer(/*USHORT uSessionID,*/ FuncFinishSendingFileByServer cbFinishSendingFileByServer, DWORD dwUser);

// 8.9	取消上传下载 0x0009
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelUploadOrDownload(USHORT uSessionID, FuncCancelUploadOrDownload cbCancelUploadOrDownload, DWORD dwUser);

// 8.10 查找录音文件 0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_FindRecordedFile(RECORD_QUERY query, FuncFindRecordedFile cbFindRecordedFile, DWORD dwUser);

// 8.11 下载文件 0x000B
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 8.12 请求下载的位置 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPosOfDownload(USHORT uSessionID, INT nDownloadPos, FuncGetPosOfDownload cbGetPosOfDownload, DWORD dwUser);

// 8.13 获取所有的上传资源文件 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllUploadedFiles(INT nFileType, FuncGetAllUploadedFiles cbGetAllUploadedFiles, DWORD dwUser);

// 8.14 根据文件ID获取文件信息 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetFileInfo(INT nFileID, FuncGetFileInfo cbGetFileInfo, DWORD dwUser);

// 8.15 根据文件ID删除文件 0x000F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteFile(INT nFileID, FuncDeleteFile cbDeleteFile, DWORD dwUser);

// 8.16 更新文件信息 0x0010
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateFile(NET_FILE file, FuncUpdateFile cbUpdateFile, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 9.寻呼、对讲(ManageSpeaking) 0x09
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 9.1	寻呼 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_Call(NET_SPEAK speak, FuncCall cbCall, DWORD dwUser);

// 9.2	对讲 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_Speak(NET_SPEAK speak, FuncSpeak cbSpeak, DWORD dwUser);

// 9.3	停止寻呼 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelCalling(USHORT uSessionID, FuncCancelCalling cbCancelCalling, DWORD dwUser);

// 9.4	停止对讲 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelSpeaking(USHORT uSessionID, FuncCancelSpeaking cbCancelSpeaking, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 10.广播(ManageBroadcast) 0x0A
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 10.1 广播开始 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StartBroadcasting(NET_BROADCAST broadcast, FuncStartBroadcasting cbStartBroadcasting, FuncStartBroadcastingEx cbStartBroadcastingEx, DWORD dwUser);

// 10.2 0x0002
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 10.3 广播的音频格式数据 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_BroadcastAudio(MEDIA_FORMATE format, FuncBroadcastAudio cbBroadcastAudio, DWORD dwUser, string strHeadFormat);

// 10.4 0x0004
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 10.5 传送音频数据 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_TransmitAudio(string strData, FuncTransmitAudio cbTransmitAudio, DWORD dwUser);

// 10.6 停止广播 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelBroadcasting(USHORT uSessionID, FuncCancelBroadcasting cbCancelBroadcasting, DWORD dwUser);

// 10.7 切歌操作 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SwitchSong(PLAY_CTRL ctrl, FuncSwitchSong cbSwitchSong, DWORD dwUser);

// 10.8 广播临时文件 0x0008
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_BroadcastTempFile(FuncBroadcastTempFile cbBroadcastTempFile, DWORD dwUser);

// 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 12. 授权管理(ManageAuthority) 0x0C
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12.1 获取注册码 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetMachineCode(FuncGetMachineCode cbGetMachineCode, DWORD dwUser);

// 12.2 获取证书信息 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetLicenseInfo(FuncGetLicenseInfo cbGetLicenseInfo, DWORD dwUser);

// 12.3 证书有效性验证 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_VerifyLicense(string strLicense, FuncVerifyLicense cbVerifyLicense, DWORD dwUser);

// 12.4 注册证书 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RegisterLicense(string strLicense, FuncRegisterLicense cbRegisterLicense, DWORD dwUser);




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 13. 任务和方案管理
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 13.1	增加任务 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddTask(BASE_TASK task, INT nOperateType, FuncAddTask cbAddTask, DWORD dwUser);

// 13.2	更新任务 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateTask(BASE_TASK task, INT nOperateType, DEVICE_ID_WRAPPER devIDs, LED_CTRL_TASK_ATTACH attach, FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.3	删除任务 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTask(OPERATE_TASK oprTask, FuncRemoveTask cbRemoveTask, DWORD dwUser);

// 13.4	根据任务ID获取任务信息 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetTaskInfo(string strTaskID, FuncGetTaskInfo cbGetTaskInfo, DWORD dwUser);

// 13.5	获取所有任务信息 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskInfo(FuncGetAllTaskInfo cbGetAllTaskInfo, DWORD dwUser);

// 13.6	根据方案ID获取所有任务信息 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskView(string strPolicyID, FuncGetAllTaskView cbGetAllTaskView, DWORD dwUser);

// 13.7	获取所有执行任务的状态 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskStatus(FuncGetAllTaskStatus cbGetAllTaskStatus, DWORD dwUser);

// 13.8	获取所有任务类型s 0x00013
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskTypes(FuncGetAllTaskTypes cbGetAllTaskTypes, DWORD dwUser);

// 13.9	 0x0009
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 13.10 根据任务ID获取文件播放任务列表 0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPlayTask(string strTaskID, FuncGetPlayTask cbGetPlayTask, DWORD dwUser);

// 13.11 增加文件播放附加属性 0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPlayTaskAttach(PLAY_TASK_ATTACH attach, FuncAddPlayTaskAttach cbAddPlayTaskAttach, DWORD dwUser);

// 13.12 更新文件播放附加属性 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdatePlayTaskAttach(PLAY_TASK_ATTACH attach, FuncUpdatePlayTaskAttach cbUpdatePlayTaskAttach, DWORD dwUser);

// 13.13 删除文件播放附加属性 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemovePlayTaskAttach(string strTaskID, FuncRemovePlayTaskAttach cbRemovePlayTaskAttach, DWORD dwUser);

// 13.14 根据任务ID获取设备关联 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetBCDeviceByTaskID(string strTaskID, FuncGetBCDeviceByTaskID cbGetBCDeviceByTaskID, DWORD dwUser);

// 13.15 根据任务ID获取关联设备信息 0x000F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceByTaskID(string strTaskID, FuncGetDeiveByTaskID cbGetDeiveByTaskID, DWORD dwUser);

// 13.16 增加或删除播放任务的设备 0x0010
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddOrDelPlayingDevice(string strDeviceID, FuncAddOrDelPlayingDevice cbAddOrDelPlayingDevice, DWORD dwUser);

// 13.17 根据任务Id获取播放任务中的文件列表 0x00011
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPlayingFilesByTaskID(string strTaskID, FuncGetPlayingFilesByTaskID cbGetPlayingFilesByTaskID, DWORD dwUser);

// 13.18 增加或删除播放任务中的文件列表 0x00012
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddOrDelPlayingFiles(string strAbsoluteFilePath, FuncAddOrDelPlayingFiles cbAddOrDelPlayingFiles, DWORD dwUser);

// 13.19 根据任务Id获取采播附加属性信息 0x00013
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAcquicastAttach(string strTaskID, FuncGetAcquicastAttach cbGetAcquicastAttach, DWORD dwUser);

// 13.20 增加采播任务属性 0x0014
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAcquicastAttach(BC_TASK_ATTACH attach, FuncAddAcquicastAttach cbAddAcquicastAttach, DWORD dwUser);

// 13.21 修改采播任务属性(ParaId=0x0015)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyAcquicastAttach(BC_TASK_ATTACH attach, FuncModifyAcquicastAttach cbModifyAcquicastAttach, DWORD dwUser);

// 13.22 删除采播任务属性(ParaId=0x0016)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveAcquicastAttach(string strTaskID, FuncRemoveAcquicastAttach cbRemoveAcquicastAttach, DWORD dwUser);

// 13.23 获取定时设置(ParaId=0x0017)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetTimingConfig(string strTaskID, FuncGetTimingConfig cbGetTimingConfig, DWORD dwUser);

// 13.24 增加定时设置(ParaId=0x0018)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddTimingConfig(TIMING_TASK task, FuncAddTimingConfig cbAddTimingConfig, DWORD dwUser);

// 13.25 // 重复了

// 13.26 删除定时设置(ParaId=0x001A)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTimingConfig(string strTaskID, FuncRemoveTimingConfig cbRemoveTimingConfig, DWORD dwUser);

// 13.27 获取所有任务方案(ParaId=0x001B)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskPolicy(FuncGetAllTaskPolicy cbGetAllTaskPolicy, DWORD dwUser);

// 13.28 根据方案ID获取方案实体(ParaId=0x001C)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetTaskPolicy(string strPolicyID, FuncGetTaskPolicy cbGetTaskPolicy, DWORD dwUser);

// 13.29 增加任务方案(ParaId=0x001D)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddTaskPolicy(TASK_POLICY policy, INT nOperateType, FuncAddTaskPolicy cbAddTaskPolicy, DWORD dwUser);

// 13.30 更新任务方案(ParaId=0x001E)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyTaskPolicy(TASK_POLICY policy, INT nOperateType, FuncModifyTaskPolicy cbModifyTaskPolicy, DWORD dwUser);

// 13.31 删除任务方案(ParaId=0x001F)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTaskPolicy(string strPolicyID, FuncRemoveTaskPolicy cbRemoveTaskPolicy, DWORD dwUser);

// 13.32 增加方案中的任务(ParaId=0x0020) 增加广播任务
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddBCTaskIntoPolicy(string strPolicyID, BASE_TASK task, DEVICE_FOR_TASK device, PLAY_TASK_ATTACH attach, 
	FILE_FOR_TASK file,FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 增加方案中的任务(ParaId=0x0020) 增加电源任务
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPowerTaskIntoPolicy(string strDeviceID, BASE_TASK task, SWITCH_FOR_TASK switcher,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 增加方案中的任务(ParaId=0x0020) 增加采集任务 
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddACTaskIntoPolicy(string strPolicyID, BASE_TASK task, DEVICE_FOR_TASK device, BC_TASK_ATTACH attach,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 增加方案中的任务(ParaId=0x0020) 增加LED控制任务
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddLEDTaskIntoPolicy(string strPolicyID, BASE_TASK task, DEVICE_FOR_TASK device, LED_CTRL_TASK_ATTACH attach,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 修改方案中的任务(ParaId=0x0020) 修改广播任务和打铃
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyBCTask(/*string strPolicyID, */BASE_TASK task, DEVICE_FOR_TASK device, PLAY_TASK_ATTACH attach, FILE_FOR_TASK file,
	FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 修改方案中的任务(ParaId=0x0020) 修改电源任务
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyPowerTask(string strDeviceID, BASE_TASK task, SWITCH_FOR_TASK switcher,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 修改方案中的任务(ParaId=0x0020) 修改采集任务 
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyACTask(/*string strPolicyID,*/ BASE_TASK task, DEVICE_FOR_TASK device, BC_TASK_ATTACH attach,
	FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 修改方案中的任务(ParaId=0x0020) 修改LED控制任务
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyLEDTask(/*string strPolicyID, */BASE_TASK task, DEVICE_FOR_TASK device, LED_CTRL_TASK_ATTACH attach,
	FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.33 从方案中删除任务(ParaId=0x0021)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTaskFromPolicy(string strPolicyID, string strTaskID, FuncRemoveTaskFromPolicy cbRemoveTaskFromPolicy, DWORD dwUser);

// 13.34 启动任务(ParaId=0x0023)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StartTask(string strTaskID, FuncStartTask cbStartTask, DWORD dwUser, INT nTaskType = -1);

// 13.35 停止任务(ParaId=0x0024)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StopTask(string strTaskID, FuncStopTask cbStopTask, DWORD dwUser);

// 13.36 获取电源开关任务信息(ParaId=0x0025)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPowerSwithTask(string strTaskID, FuncGetPowerSwithTask cbGetPowerSwithTask, DWORD dwUser);

// 13.37 获取所有级别信息(ParaId=0x0026)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskLevels(FuncGetAllTaskLevels cbGetAllTaskLevels, DWORD dwUser);

// 13.38 获取全部或指定方案ID的LED控制任务信息(ParaId=0x0027)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllLedCtrlTaskAttach(OPERATE_TASK oprTask, FuncGetAllLedCtrlTaskAttach cbGetAllLedCtrlTaskAttach, DWORD dwUser);

// 13.39 根据任务ID获取LED控制任务信息(ParaId=0x0028)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetLedCtrlTaskAttach(string strTaskID, FuncGetLedCtrlTaskAttach cbGetLedCtrlTaskAttach, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 14.客户端获取状态指令(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 14.1 获取所有报警设备状态信息(ParaId=0x0014)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmDevStatus(FuncGetAllAlarmDevStatus cbGetAllAlarmDevStatus, DWORD dwUser);

// 14.2 根据IP获取报警设备状态信息(ParaId=0x0015)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmDevStatus(string strDeviceIP, FuncGetAlarmDevStatus cbGetAlarmDevStatus, DWORD dwUser);

// 14.3 根据IP和报警通道确认报警(ParaId=0x0018)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ConfirmAlarm(IP_ALARM_CHANNEL channel, FuncConfirmAlarm cbConfirmAlarm, DWORD dwUser);

// 14.4 获取所有电源的状态信息(ParaId=0x0019)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllPowerStatus(FuncGetAllPowerStatus cbGetAllPowerStatus, DWORD dwUser);

// 14.5 根据IP获取电源设备状态信息(ParaId=0x001A)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPowerStatus(string strDeviceIP, FuncGetPowerStatus cbGetPowerStatus, DWORD dwUser);

// 14.6 客户端控制电源的开或关(ParaId=0x001D)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CtrlPowerSwitchByIP(IP_ALARM_CHANNEL channel, INT nCtrlStatus, FuncCtrlPowerSwitchByIP cbCtrlPowerSwitchByIP, DWORD dwUser);

// 14.7 获取所有接入设备的状态信息(ParaId=0x001E)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllDeviceStatus(FuncGetAllDeviceStatus cbGetAllDeviceStatus, DWORD dwUser);

// 14.8 根据设备ID获取设备的状态信息(ParaId=0x001F)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDevStatusByID(INT nDeviceID, FuncGetDevStatusByID cbGetDevStatusByID, DWORD dwUser);

// 14.9 根据设备IP获取设备的状态信息(ParaId=0x0020)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDevStatusByIP(string strDeviceIP, FuncGetDevStatusByIP cbGetDevStatusByIP, DWORD dwUser);

// 14.10 控制电源的开或关(ParaId=0x0021)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CtrlPowerSwitchByID(IP_ALARM_CHANNEL channel, INT nCtrlStatus, FuncCtrlPowerSwitchByID cbCtrlPowerSwitchByID, DWORD dwUser);

// 14.11 获取所有警示灯状态信息(ParaId=0x0022)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmLightStatus(FuncGetAllAlarmLightStatus cbGetAllAlarmLightStatus, DWORD dwUser);

// 14.12 根据设备ID获取警示灯状态信息(ParaId=0x0023)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmLightStatus(int nDeviceID, FuncGetAlarmLightStatus cbGetAlarmLightStatus, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 15.服务器推送设备状态(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 15.1	服务器推送设备状态变化(ParaId=0x0001)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetDeviceStatus(FuncAutoGetDeviceStatus cbAutoGetDeviceStatus, DWORD dwUser);

// 15.2	服务器推送会话状态变化(ParaId=0x0002)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetSessionStatus(FuncAutoGetSessionStatus cbAutoGetSessionStatus, DWORD dwUser);

// 15.3	服务器推送会话终止消息(ParaId=0x0003)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetSessionTerminal(FuncAutoGetSessionTerminal cbAutoGetSessionTerminal, DWORD dwUser);

// 15.4	服务器推送在线用户状态变化(ParaId=0x0004)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetUserStatus(FuncAutoGetUserStatus cbAutoGetUserStatus, DWORD dwUser);

// 15.5	服务器推送任务状态变化(ParaId=0x0005)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetTaskStatus(FuncAutoGetTaskStatus cbAutoGetTaskStatus, DWORD dwUser);

// 15.6	服务器推送方案状态变化(ParaId=0x0005)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetPolicyStatus(FuncAutoGetPolicyStatus cbAutoGetPolicyStatus, DWORD dwUser);

// 15.17	服务器推送设备的通道状态变化(ParaId=0x0017)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetChannelStatus(FuncAutoGetChannelStatus cbAutoGetChannelStatus, DWORD dwUser);

EXTERN_C_END_DECL