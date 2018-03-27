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
	/// δ��ͨ״̬��
	/// </summary>
	Disconnect,
	/// <summary>
	/// �ж϶Ͽ�������������
	/// </summary>
	RelayDisconnect,
	/// <summary>
	/// ����״̬��
	/// </summary>
	Free,
	/// <summary>
	/// ���еȴ���
	/// </summary>
	CallWaiting,
	/// <summary>
	/// ��������
	/// </summary>
	Ringing,
	/// <summary>
	/// Ѱ��������
	/// </summary>
	Calling,
	/// <summary>
	/// �Խ�������
	/// </summary>
	Talking,
	/// <summary>
	/// �㲥������
	/// </summary>
	Broadcasting,
	/// <summary>
	/// �ɼ���
	/// </summary>
	Collecting,
	/// <summary>
	/// ������
	/// </summary>
	Listening,
	/// <summary>
	/// ����������
	/// </summary>
	ListenBroadcasting,
	/// <summary>
	/// �ɼ�������
	/// </summary>
	CollectBroadcasting,
	/// <summary>
	/// ����������ֻһ�����ڽ��еĲ����������������豸�ָ����е�״̬��
	/// </summary>
	Ending,
	/// <summary>
	/// ���룬ֻҪ���PC�û�
	/// </summary>
	Login,
	/// <summary>
	/// �ǳ���ֻҪ���PC�û���
	/// </summary>
	Logout,
	/// <summary>
	/// �豸���Ƴ���ָ���ã�
	/// </summary>
	DeviceRemove,
	/// <summary>
	/// �豸������
	/// </summary>
	DeviceAdd,
	/// <summary>
	/// �豸���޸�
	/// </summary>
	DeviceEdit,
	///// <summary>
	///// ��������
	///// </summary>
	//Listeneding = 0x10000000
};

/// <summary>
/// �㲥�����͡������PC���й㲥�����ݷ��͵����������յ����سɹ�����Ϣ������ˡ�
/// </summary>
enum IPCAST_SDK_API BroadcastType
{
	/// <summary>
	/// PC���й㲥��
	/// </summary>
	PCBroadcast,
	/// <summary>
	/// ʹ��PC����Ѱ������ֻҪ��ͨ���ɼ��豸�ɼ�������Ƶ��ֻҪ�в����ң�
	/// </summary>
	PCCollect,
	/// <summary>
	/// ���豸���й㲥����ָ�������ܣ�
	/// </summary>
	DeviceBroadcast,
	/// <summary>
	/// ���������й㲥��ʹ��ָ�����ļ��б����㲥���㲥����ʱ����ȣ�
	/// </summary>
	ServerBroadcast,

	/// <summary>
	/// �豸֮���Ѱ��
	/// </summary>
	DeviceCall,

	/// <summary>
	/// �豸֮��ĶԽ���
	/// </summary>
	DeviceTalk,
};

//ͬSoundMediaUntil���PlayCycleType����һ�¡�
/// <summary>
/// ����ģʽ��
/// </summary>
enum IPCAST_SDK_API PlayCycleType
{
	/// <summary>
	/// ��������
	/// </summary>
	Single,
	/// <summary>
	/// ����ѭ��
	/// </summary>
	SingleCycle,
	/// <summary>
	/// ˳��ģʽ
	/// </summary>
	Order,
	/// <summary>
	/// ѭ��ģʽ
	/// </summary>
	Recycle,
	/// <summary>
	/// ������š�
	/// </summary>
	Shuffle,
};

enum SessionType
{
	/// <summary>
	/// �ջ���ʱ�Ự
	/// </summary>
	None,
	/// <summary>
	/// �㲥�Ự��
	/// </summary>
	Broadcast,
	/// <summary>
	/// Ѱ���Ự
	/// </summary>
	Call,
	/// <summary>
	/// �Խ��Ự
	/// </summary>
	Talk,
	/// <summary>
	/// �����ɼ�
	/// </summary>
	Collection,
	/// <summary>
	/// ����
	/// </summary>
	Listen,
	/// <summary>
	/// �����Ự��
	/// </summary>
	Alarm,
	/// <summary>
	/// ��Դ�Ự��
	/// </summary>
	Resource,
	/// <summary>
	/// Led��ʾ���ƻỰ
	/// </summary>
	LedDisplayCtrl,
};

enum SessionState
{
	/// <summary>
	/// ����ʾ�գ��մ�����״̬
	/// </summary>
	None_,
	/// <summary>
	/// ������
	/// </summary>
	Working,
	/// <summary>
	/// ���𣬿������ڳ�ʱ����
	/// </summary>
	Suspend,
	/// <summary>
	/// �رգ��رպ�һ���ڻỰ�б����Ƴ���
	/// </summary>
	Closed,
	/// <summary>
	/// ���ӻỰ�е��豸
	/// </summary>
	AddSessionDevice,
	/// <summary>
	/// �Ƴ��Ự�е��豸
	/// </summary>
	RemoveSessionDevice,
};

/// <summary>
/// ��������ö��
/// </summary>
enum ErrorType
{
	/// <summary>
	/// δ֪����
	/// </summary>
	UnknowError = -1,
	/// <summary>
	/// �ɹ�
	/// </summary>
	Succeed,
	/// <summary>
	/// ����δ���ӡ�
	/// </summary>
	ServerDisConnect,

	/// <summary>
	/// ���ݿ����ʧ��
	/// </summary>
	DBOperateError,
	/// <summary>
	/// û��Ȩ�޻�Ȩ�޲�����
	/// </summary>
	NoPermission,
	/// <summary>
	/// ָ��ִ�г�ʱ��
	/// </summary>
	CommandTimeout,
	/// <summary>
	/// ������ָ�ʱ
	/// </summary>
	ServerCommandTimeout,
	/// <summary>
	/// �Ҳ����Ự��
	/// </summary>
	SessionNotFound,
	/// <summary>
	/// �Ự����ֹ��
	/// </summary>
	SessionClosed,
	/// <summary>
	/// �û����������
	/// </summary>
	UserOrPasswordError,
	/// <summary>
	/// �豸�Ѵ��ڵ�¼״̬��
	/// </summary>
	OnLoginState,
	/// <summary>
	/// �ѵǳ�״̬��
	/// </summary>
	OnLogoutState,
	/// <summary>
	/// ��¼ʧ�ܡ�
	/// </summary>
	LoginFailed,
	/// <summary>
	/// ��ѯ��Χ����̫��
	/// </summary>
	QueryRangeError,
	/// <summary>
	/// ��¼�����ڡ�
	/// </summary>
	RecordNotExist,
	/// <summary>
	/// �ļ������ڡ�
	/// </summary>
	FileNotFound,
	/// <summary>
	/// �ļ�����������Χ
	/// </summary>
	FileNumOutofRange,
	/// <summary>
	/// �ϴ��ļ��Ѵ��ڡ�
	/// </summary>
	UploadFileExisted,
	/// <summary>
	/// д�ϴ��ļ�����
	/// </summary>
	WriteUploadDataError,
	/// <summary>
	/// ����״̬����ִָ�еĹ����ڲ����ʵĹ���״̬�¡�
	/// </summary>
	WorkStatusError,
	/// <summary>
	/// û���ҵ��豸
	/// </summary>
	DeviceNotFound,
	/// <summary>
	/// �豸δ����
	/// </summary>
	DeviceDisconnected,
	/// <summary>
	/// �豸���ͳ����ƥ��
	/// </summary>
	DeviceTypeError,
	/// <summary>
	/// �����豸æ��
	/// </summary>
	CtrlDeviceBusy,
	/// <summary>
	/// ͨ���豸æ
	/// </summary>
	TalkDeviceBusy,
	/// <summary>
	/// �豸����
	/// </summary>
	DeviceRestricted,
	/// <summary>
	/// �����豸��û������
	/// </summary>
	NoDeviceSetting,
	/// <summary>
	/// û�з����豸
	/// </summary>
	NoAllocDevice,
	/// <summary>
	/// �㲥����
	/// </summary>
	BroadcastError,
	/// <summary>
	/// ����ʧ�ܡ�
	/// </summary>
	TaskError,
	/// <summary>
	/// ���񲻴���
	/// </summary>
	TastNotFound,
	/// <summary>
	/// �����ѹ���
	/// </summary>
	PolicySuspended,
	/// <summary>
	/// ��֧�ֵĹ���
	/// </summary>
	FunctionNoSupport,
	/// <summary>
	/// �ý�ɫ�ѷ�����û�
	/// </summary>
	AdmeasuredUser,
	/// <summary>
	/// �ѷ���ip
	/// </summary>
	ExistingIP,
	/// <summary>
	/// �ѷ�������
	/// </summary>
	ExistingPhoneNo,
	/// <summary>
	/// �ѷ����豸���
	/// </summary>
	ExistingGroupNo,
	/// <summary>
	/// �����Ѵ���
	/// </summary>
	ExistingName,
	/// <summary>
	/// ��Ȩ������
	/// </summary>
	LicenseCodeError,
	/// <summary>
	/// ��Ȩ֤��Ͼ�
	/// </summary>
	LicenseIsOld,
	/// <summary>
	/// ��Ȩ֤������Ч
	/// </summary>
	LicenseInValid,
	/// <summary>
	/// ��������
	/// </summary>
	FunctionRestricted,
};

enum DevicePriorityLevel
{
	Low				= 400,		// �ͼ�
	Intemediate		= 500,		// �м�
	High				= 600,		// �߼�
	Higher			= 700,		// �ϸ߼�
	Higheast			= 800,		// ��߼�
};

typedef struct IPCAST_SDK_API _tagLoginRequest
{
	string strName;				// �û���
	string strPwd;					// �û�����
	string strGUID;					// �û���GUID
	unsigned int uID;				// �û���ID
	bool bIsNewID;				// �Ƿ������û�

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
	string strID;						// �û�ID
	string strName;					// �û�����
	string strPassword;				// ��¼����
	string strUserType;				// �û�����
	int nUserTypeCode;				// �û����͵Ĵ���

	string strAddress;					// �û���ַ
	string strPhoneNum;				// ��ϵ�绰
	short nPriorityLevel;				// �������ȼ��� 50
	_tagNetUser();
	_tagNetUser(const XMLNetUser& other);
	_tagNetUser(const XMLNetUser4& other);
	_tagNetUser(const XMLNetUser5& other);
}NET_USER, *NET_USER_PTR;

// 2.8
typedef struct IPCAST_SDK_API _tagUserType
{
	string strTypeName;					// �û���������
	int nTypeCode;						// �û����ͱ��
	short nPriorityLevel;				// ���ȼ�[1-999] Ĭ��50
	_tagUserType();
	_tagUserType(const XMLUserType& other);
}USER_TYPE, *USER_TYPE_PTR;

// 2.9
typedef struct IPCAST_SDK_API _tagUserAuthority
{
	string strPurviewID;				// Ȩ��ID
	string strFunctionID;				// ���ܷ���ID
	string strOperateID;				// ����Ȩ��ID
	string strFunctionName;			// ��������(en)
	string strFunctionDesc;			// ��������

	string strOperateName;			// ����Ȩ������
	string strOperateDesc;			// ����Ȩ������
	_tagUserAuthority();
	_tagUserAuthority(const XMLUserAuthority& other);
}USER_AUTHORITY, *USER_AUTHORITY_PTR;

// 2.10
typedef struct IPCAST_SDK_API _tagNetRole
{
	string strRoleID;					// ��ɫID
	string strRoleName;				// ��ɫ����
	string strRoleDesc;				// ��ɫ����
	string strDataDefineID;			// ���ݶ���ID
	int nTypeCode;					// �û����ͱ��

	short  nPriorityLevel;				// ���ȼ�[1-999] Ĭ��50
	_tagNetRole();
	_tagNetRole(const XMLNetRole& other);
}NET_ROLE, *NET_ROLE_PTR;

typedef struct IPCAST_SDK_API _tagRoleFunction
{
	string strRoleGUID;					// ��ɫguid
	vector<string> vectFuncGUID;	// strFuncGUID
}ROLE_FUNCTION, ROLE_FUNCTION_PTR;

typedef struct IPCAST_SDK_API _tagDeviceForUser
{
	string strUserGUID;					//	�û�GUID
	vector<string> vectDeviveGUID;	// �豸GUID
}DEVICE_FOR_USER, *DEVICE_FOR_USER_PTR;

typedef struct IPCAST_SDK_API _tagRoleForUser
{
	string strUserGUID;					// �û�GUID
	vector<string> vectRoleGUID;		// ��ɫGUID
}ROLE_FOR_USER, *ROLE_FOR_USER_PTR;

// 3.1 
typedef struct IPCAST_SDK_API _tagConnectedDevice
{
	string strDisplayText;				// ��ʾ���ı����൱��Name��PC�ͻ���ʹ��IP+�û���
	string strKey;							// �豸ʹ��MAC��ַ��PC���м̡����ķ�����ֱ��ʹ��Զ��IP��ַ
	int nIdentity;							// ���Ϸ�����û����豸��Ψһ��ʶ�����Ϊ����������ʹ�û�ԭ����Id�������������Ըñ�ʶΪ����������
	unsigned short uPhoneNum;		// ���õ�ͨ���ţ�0��ʾû�����á�
	int nDeviceType;						// ���ӵ��豸���ͣ��μ�DeviceTypeö��

	int nDeviceStatus;					// �豸�Ĺ���״̬���μ�DeviceStatusö��
	string strDescription;					// �豸״̬��������
	string strRelayServerIp;				// �м̷�������IP��ַ��
	char nVolume;							// ����
	int nSoundEffect;						// ��Ч

	unsigned short uSessionId;			// ��ǰ�ĻỰ��ID��0��ʾ����
	string strSessionName;				// �Ự�����ơ�
	_tagConnectedDevice();
	_tagConnectedDevice(const XMLConnectedDevice& other);
	_tagConnectedDevice(const XMLConnectedDeviceRes6& other);
	_tagConnectedDevice(const XMLConnectedDeviceRes7& other);
}CONNECTED_DEVICE, *CONNECTED_DEVICE_PTR;

// 3.2 
typedef struct IPCAST_SDK_API _tagNetDeviceType
{
	string strID;							// �豸����ID
	int	nTypeCode;						// �豸���ͱ��
	string strTypeName;					// �豸��������
	string strDescription;					// �豸���͵�����
	_tagNetDeviceType();
	_tagNetDeviceType(const XMLNetDeviceType& other);
}NET_DEVICE_TYPE, *NET_DEVICE_TYPE_PTR;

// 3.3 
typedef struct IPCAST_SDK_API _tagNetDevice
{
	string strID;							// �豸ID
	string strName;						// �豸����
	int nDeviceTypeCode;				// �豸���ͱ��
	string strDeviceTypeName;			// �豸��������
	string strIPAddress;					// IP��ַ

	int nPort;								// �˿ں�
	string strMAC;							// MAC��ַ��IP��MAC����-����IP����.��
	string strRelayServerIP;				// �м̷�����IP
	string strAddress;						// �豸��ַ
	unsigned char  uProtocalVersion;	// Э��汾��

	string strNetPowerIP;				// IP��Դ��IP��ַ
	short nNetPowerSwitchNum;		// ��Դ�Ŀ��غ�
	_tagNetDevice();
	_tagNetDevice(const XMLNetDevice& other);
	_tagNetDevice(const XMLNetDevice4& other);
	_tagNetDevice(const XMLNetDevice5678& other);
}NET_DEVICE, *NET_DEVICE_PTR;

// 3.4 
typedef struct IPCAST_SDK_API _tagNetAlarmAttach
{
	string strDeviceID;						// �豸ID
	string strModel;							// �豸�ͺ�
	int nAlarmChannelNums;					// ����ͨ������
	unsigned short uAlarmOutChannelNums;	// �������ͨ������
	_tagNetAlarmAttach(){}
	_tagNetAlarmAttach(const XMLNetAlarmAttach& other);
	_tagNetAlarmAttach(const XMLNetAlarmAttachRes& other);
}NET_ALARM_ATTACH, *NET_ALARM_ATTACH_PTR;

typedef struct IPCAST_SDK_API _tagSwitcher
{
	int nIndex;									// �� 1 ��ʼ�Ŀ�ʼ���
	int nSwitchStatus;						// ���ص�״̬
	unsigned char uStatus;					// ״̬��ΪXml������ ����ʾ��·�ϵ磬����ʾ�պ�ͨ��

	_tagSwitcher(){}
	_tagSwitcher(const XMLSwitcher& other);
	_tagSwitcher(const XMLInSwitcher& other);
	_tagSwitcher(const XMLOutSwitcher& other);
}SWITCHER, *SWITCHER_PTR;

typedef struct IPCAST_SDK_API _tagChannelDevice
{
	_tagNetDevice netDevice;				// �豸��ʵ�塣
	_tagNetAlarmAttach netAlarmAttach;	// Ϊ�����豸ר������һ�������ԣ���Ϊ�кܶ�Ǳ����豸����������룬����Ĺ���
	vector<_tagSwitcher> InChannels;	// �豸������ͨ��״̬��ָ���������룩
	vector<_tagSwitcher> OutChannels;	// �豸�����ͨ����ָ��Դ�򱨾����
}CHANNEL_DEVICE, *CHANNEL_DEVICE_PTR;

// 3.9
typedef struct IPCAST_SDK_API _tagDefaultCallDevice
{
	unsigned short uSourcePhoneNum;	// ������IP��ͨ����
	unsigned short uCallButtonNum;		// �豸�����ţ�����Ϊ�ж��������������ͨ���豸
	unsigned short uTargetPhoneNum;	// Ŀ¼�豸��ͨ����
	unsigned char uActionType;			// 0Ѱ�� 1�Խ�
	int nSerial;									// ��ţ�Ϊÿ���豸�����ĶԻ��豸����
	_tagDefaultCallDevice();
	_tagDefaultCallDevice(const XMLDefaultCallDevice& other);
}DEFAULT_CALL_DEVICE, *DEFAULT_CALL_DEVICE_PTR;

typedef struct IPCAST_SDK_API _tagDefaultCallDevices
{
	vector<_tagDefaultCallDevice> vectDevices;
}DEFAULT_CALL_DEVICES, *DEFAULT_CALL_DEVICES_PTR;

typedef struct IPCAST_SDK_API _tagNetDeviceAttach
{
	string strDeviceID;						// �豸ID
	short nDefaultVolume;					// �豸Ĭ������
	short nPriorityLevel;						// ���ȼ���[0-999]Խ�󼶱�Խ��
	unsigned short uPhoneNum;			// ͨ����
	string strScrDisplayText;				// �豸��ʾ�ı�
	short nScrSaveTime;						// ��Ļ����ʱ�䣬Ĭ��Ϊ30��
	int nVideoPort;								// ʵʱ��Ƶ�˿ںţ�Ĭ��Ϊ554
	_tagNetDeviceAttach();
	_tagNetDeviceAttach(const XMLNetDeviceAttach& other);
}NET_DEVICE_ATTACH, *NET_DEVICE_ATTACH_PTR;

// 3.11
typedef struct IPCAST_SDK_API _tagOperateDevice
{
	string strMainId;							// ����ID
	int nOperateType;						// ��������
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
	string strID;								// ����Ԥ��ID
	string strName;							// ����Ԥ������
	int nAlarmType;							// ��������
	string strSoundFileFullName;			// ����ʱ�������ļ�
	int nAlarmDuration;						// ��������ʱ��(��)

	short nPriorityLevel;						// ���ȼ�[1-999] 700
	unsigned char uProPowerOn;			// �Ƿ�Ԥ����Դ
	unsigned char uIsSuspended;			// �Ƿ����
	string strAlarmOutChannelNums;		// �������ͨ�����ã�ͨ������,����
	_tagAlarmProposal();
	_tagAlarmProposal(const XMLAlarmProposal& other);
}ALARM_PROPOSAL, *ALARM_PROPOSAL_PTR;

typedef struct IPCAST_SDK_API _tagAPAlarmDevice
{
	string strAlarmProposalID;				// ����ͨ����
	string strAlarmDeviceID;				// ��������ID
	int nAlarmChannel;						// ����ͨ����
	string strSoundFileFullName;			// ����ʱ�������ļ���Ϊ��ʱʹ�ø���������
	short nDefaultVolume;					// ����Ԥ��Ĭ��(50)������

	string strSoundFileAlias;					// �����ļ�����
	_tagAPAlarmDevice();
	_tagAPAlarmDevice(const XMLAPAlarmDeviceRes23& other);
	_tagAPAlarmDevice(const XMLAPAlarmDeviceRes24& other);
}AP_ALARM_DEVICE, *AP_ALARM_DEVICE_PTR;

typedef struct IPCAST_SDK_API _tagAPOutChannel
{
	string strAlarmProposalID;				// ����Ԥ��ID
	string strAlarmOutDeviceID;			// ��������豸ID
	int nOutChannel;							// ��������豸ͨ����
	_tagAPOutChannel();
	_tagAPOutChannel(const XMLAPOutChannel& other);
}AP_OUT_CHANNEL, *AP_OUT_CHANNEL_PTR;

typedef struct IPCAST_SDK_API _tagAPOutChannelWrapper
{
	vector<_tagAPOutChannel> vectChannel;
}AP_OUT_CHANNEL_WRAPPER, *AP_OUT_CHANNEL_WRAPPER_PTR;

typedef struct IPCAST_SDK_API _tagDeviceIDWrapper
{
	vector<string> vectID;					// �豸��GUID����
}DEVICE_ID_WRAPPER, *DEVICE_ID_WRAPPER_PTR;

// 3.38
typedef struct IPCAST_SDK_API _tagAlarmQuery
{
	string strDeviceName;					// �豸���ƣ�֧��ģ��������
	string strStartTime;						// ��ʼʱ��
	string strEndTime;						// ����ʱ��
	int nAlarmTypeCode;						// �������� 100 ����
	int nAlarmChannel;						// ����ͨ����

	string strDeviceIP;						// �豸IP��֧��ģ��������
	_tagAlarmQuery();
	_tagAlarmQuery(const XMLAlarmQuery& other);
}ALARM_QUERY, *ALARM_QUERY_PTR;

typedef struct IPCAST_SDK_API _tagAlarmInfo
{
	int nID;										// ������ϢID
	string strDeviceID;						// �����豸ID
	int nAlarmChannel;						// ����ı���ͨ��
	int nAlarmTypeCode;						// �������ͱ��
	string strAlarmDescription;				// ��������

	string strAlarmTime;						// ����ʱ��
	string strDeviceIP;						// �豸IP
	string strDeviceName;					// �豸����
	string strAlarmTypeName;				// ������������
	_tagAlarmInfo();
	_tagAlarmInfo(const XMLAlarmInfo& other);
}ALARM_INFO, *ALARM_INFO_PTR;

// 3.40
typedef struct IPCAST_SDK_API _tagDeviceVolume
{
	string strID;								// ����ID��ͨ����
	bool bIsNumber;								// Trueʱ����ʾΪͨ����
	_tagDeviceVolume();
	_tagDeviceVolume(const XMLDeviceVolume& other);
}DEVICE_VOLUME, *DEVICE_VOLUME_PTR;

// 3.42
typedef struct IPCAST_SDK_API _tagAlarmDeviceDetail
{
	string strDeviceID;						// �����豸ID
	string strName;							// �����豸����
	int nAlarmTypeCode;						// �������ͱ��
	string strAlarmDeviceTypeName;		// �豸��������
	int nAlarmChannel;						// ����ı���ͨ��

	short nPriorityLevel;						// ���ȼ���������700
	string strAddress;							// ��װ�ĵ�ַ
	string strDescription;						// ����
	string strChannelFlag;					// ͨ������OUT/IN
	_tagAlarmDeviceDetail();
	_tagAlarmDeviceDetail(const XMLAlarmDeviceDetail& other);
}ALARM_DEVICE_DETAIL, *ALARM_DEVICE_DETAIL_PTR;

typedef struct IPCAST_SDK_API _tagAlarmDeviceDetails
{
	vector<_tagAlarmDeviceDetail> vectDetails;
}ALARM_DEVICE_DETAILS, *ALARM_DEVICE_DETAILS_PTR;

typedef struct IPCAST_SDK_API  _tagPowerDeviceDetail
{
	string strID;						// �豸ID
	string strPowerDeviceID;		// 	��Դ������ID
	string strDeviceID;				// Net�豸�򱨾��豸
	int nSwitchNum;					// ���뿪�����
	string strDescription;				// 	����
}POWER_DEVICE_DETAIL, *POWER_DEVICE_DETAIL_PTR;

typedef struct IPCAST_SDK_API  _tagPowerDeviceDetails
{
	vector<_tagPowerDeviceDetail> vectDetails;
}POWER_DEVICE_DETAILS, *POWER_DEVICE_DETAILS_PTR;

// 3.48
typedef struct IPCAST_SDK_API _tagDeviceSwitch
{
	string strDeviceID;						// �豸��ID
	int nSwitch;								// ����״̬��0��ʾ�أ�1��ʾ��
	_tagDeviceSwitch();
	_tagDeviceSwitch(const XMLDeviceSwitch& other);
}DEVICE_SWITCH, *DEVICE_SWITCH_PTR;

// 3.49
typedef struct IPCAST_SDK_API _tagDeviceText
{
	string strDeviceID;						// �豸��ID
	string strText;								// �豸Ҫ��ʾ���ַ���
	_tagDeviceText();
	_tagDeviceText(const XMLDeviceText& other);
}DEVICE_TEXT, *DEVICE_TEXT_PTR;

// 3.51
typedef struct IPCAST_SDK_API _tagDeviceAudio
{
	string strValue1;							// 
	string strValue2;							// Ϊbool����
	_tagDeviceAudio();
	_tagDeviceAudio(const XMLDeviceAudio& other);
}DEVICE_AUDIO, *DEVICE_AUDIO_PTR;

// 6.1
typedef struct IPCAST_SDK_API _tagDeviceGroup
{
	string strID;							// �豸��ID
	string strName;						// �豸������
	short nSerial;							// �豸�����
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
	unsigned short nId;					// Session��ΨһID��
	string strName;						// �Ự���ơ�
	int nState;								// �Ự״̬
	int nRecState;							// ¼���״̬�� 0 ��ʾû��¼�� 1��ʾ����¼�� 2��ʾ��������ֻ���ɼ�����Ƶ�Ž���¼��
	unsigned char uVolume;				// �Ự�������ı�

	unsigned char uSoundEffect;		// ��Ч��1��ʾ
	string strDescription;					// �Ự����
	int nSessionType;						// �Ự������
	_tagSessionStatus();
	_tagSessionStatus(const XMLSessionStatus& other);
}SESSION_STATUS, *SESSION_STATUS_PTR;

typedef struct IPCAST_SDK_API _tagNetSession
{
	unsigned short uId;					// Session��ΨһID��
	string strName;						// �Ự���ơ�
	unsigned short uMainRelayId;		// ���м̷������ı�ʶ
	unsigned short uLevel;				// ϵͳ���������ȼ����������豸�ļ�����Ϊ�Ự�ļ���
	int nMainDeviceId;					// �Ự���Ự��ID

	SESSION_STATUS state;		// 
	int nSessionType;						// �Ự�����ͣ��ο�SessionTypeö��
	string strCreateTime;				// ��ȡ�Ự����ʱ�䡣��ʱ�����ͣ�
	_tagNetSession();
	_tagNetSession(const XMLNetSession& other);
	_tagNetSession(const XMLNetSessionRes& other);
}NET_SESSION, *NET_SESSION_PTR;

// 8.1
typedef struct IPCAST_SDK_API _tagNetResource
{
	int nULid;								// �û���¼Id
	int nFType;								// �ļ����͡�
	string strFName;						// �ļ�Դ���ơ�
	string strFAlais;						// �ļ�����
	_tagNetResource();
	_tagNetResource(const XMLNetResource& other);
	_tagNetResource(const XMLNetResourceRes& other);
}NET_RESOURCE, *NET_RESOURCE_PTR;

// 8.6
typedef struct IPCAST_SDK_API _tagRecordFile
{
	string strFullName;					// �ļ��ڷ�������ȫ����
	string strName;						// �ļ�������
	int nFileSize;							// �ļ��Ĵ�С�����ֽ�Ϊ��λ
	string strCreateTime;				// �ļ��Ĵ���ʱ��
	_tagRecordFile();
	_tagRecordFile(const XMLRecordFile& other);
	_tagRecordFile(const XMLRecordFileRes& other);
}RECORD_FILE, *RECORD_FILE_PTR;

// 8.10
typedef struct IPCAST_SDK_API _tagRecordQuery
{
	int nLoginId;							// ��¼�û���Id
	string strStartTime;					// ��ʼʱ��
	string strEndTime;					// ����ʱ��
	int nRecordType;						// ¼���ļ������ͣ�0 ��ʾΪ���ķ�������¼���ļ���1��ʾVOIP��¼���ļ�
	_tagRecordQuery();
	_tagRecordQuery(const XMLRecordQuery& other);
}RECORD_QUERY, *RECORD_QUERY_PTR;

// 8.13
typedef struct IPCAST_SDK_API _tagNetFile
{
	int nID;								// �ļ���¼ID
	string strAlais;						// �ļ���ʾ����
	string strFileFullName;			// �ļ�ȫ����
	string  strUpdateTime;			// �ϴ�ʱ��
	int nFileType;						// �ϴ��ļ�������
	_tagNetFile();
	_tagNetFile(const XMLNetFile& other);
}NET_FILE, *NET_FILE_PTR;

// 9.1
typedef struct IPCAST_SDK_API _tagNetSpeak
{
	int nULid;								// �û���¼Id
	string strName;						// �Խ���Ѱ�������ƣ��ù㲥������
	bool bIsPhoneNum;					// �Ƿ�Ϊͨ���ţ����Ϊͨ���ţ�DeviceIdsΪͨ���ŵ��б�����Ϊ�豸�ڻ����з��䵽��ID��MainDeviceIdҲ��һ��
	int nSourceDevId;					// ԭ�豸ID��ͨ����
	vector<int> vectDevIDs;		// Ѱ�����б����в���ĻỰ�б����IsPhoneNumΪ�棬��Ϊ�û��趨��ͨ���ţ�����Ϊ�豸�ڻ����з��䵽��ID

	int nBroadcastType;					// �㲥���ͣ��μ�ProtocolXMLModel��BroadcastType ö��
	unsigned char uVolume;				// �㲥����
	_tagNetSpeak();
	_tagNetSpeak(const XMLNetSpeak& other);
}NET_SPEAK, *NET_SPEAK_PTR;

// 10.1
typedef struct IPCAST_SDK_API _tagNetBroadcast
{
	int nULid;								// �û���¼Id
	string strName;						// �㲥�����ƣ��ù㲥������
	bool bIsPhoneNum;					// �Ƿ�Ϊͨ���ţ����Ϊͨ���ţ�DeviceIdsΪͨ���ŵ��б�����Ϊ�豸�ڻ����з��䵽��ID��MainDeviceIdҲ��һ��
	vector<int> vectDevIDs;			// �㲥���б����в���ĻỰ�б����IsPhoneNumΪ�棬��Ϊ�û��趨��ͨ���ţ�����Ϊ�豸�ڻ����з��䵽��ID
	vector<int> vectFileIDs;				// �ļ������б�ֻ��BroadcastType����Ϊ����������ʱ����Ч��

	int nMDid;								// ���㲥�豸����� Ϊ 0 ��ʹ��PC���й㲥�����ָ�����豸�ţ���ʹ���豸�Ž��С�
	int nBroadcastType;					// �㲥���ͣ��μ� BroadcastType ö��
	int nPlayTime;							// ����ʱ�䣬����Ϊ��λ��0��ʾ�������ơ�
	int nCycleCount;						// ѭ��������0 ��ʾ�������ƣ���0��������ʱ����Ч
	int nCycleType;						// ����ģʽ��ֻ�з��������Ų�ʹ�ø�����

	unsigned char uVolume;				// �㲥����
	int nStartPlayIndex;					// ��ʼ���Ÿ����š�Ĭ��Ϊ0
	_tagNetBroadcast();
	_tagNetBroadcast(const XMLNetBroadcast& other);
}NET_BROADCAST, *NET_BROADCAST_PTR;

// 10.3
typedef struct IPCAST_SDK_API _tagMediaFormat
{
	string strMediaName;				// ý�������
	unsigned short uPlayIndex;			// ���ŵ����
	unsigned short uSessionId;			// ���ӵĻỰId��Ϣ���ȵ�������Ҫ��
	int nMediaType;						// ��Ƶ�ĸ�ʽ��0 ΪMp3��1 ΪWav��2Ϊ�ɼ�����Ƶ��ʽ
	unsigned short uFormatTag;		// ��¼�Ŵ������ĸ�ʽ���ţ�����1-WAVE_FORMAT_PCM�� 2-WAVE_F0RAM_ADPCM�ȵ�

	unsigned short uChannels;			// ������Ŀ��1--��������2--˫����
	unsigned int uSamlesPerSec;		// ����Ƶ��  һ����11025Hz��11kHz����22050Hz��22kHz����44100Hz��44kHz������
	unsigned int uAvgBytesPerSec;	// ÿ�������ֽ���
	unsigned short uBlockAlign;		// ���ݿ���뵥λ(ÿ��������Ҫ���ֽ���) ������ * ������/8
	unsigned short uBitsPerSample;	// ��Ƶ������С ����λ���������� 8��16

	int nLayer;								// MP3�Ĳ���
	int nFrameSize;						// MP3���쳤��
	_tagMediaFormat();
	_tagMediaFormat(const XMLMediaFormat& other);
}MEDIA_FORMATE, *MEDIA_FORMAT_PTR;

// 10.7
typedef struct IPCAST_SDK_API _tagPlayCtrl
{
	int nULid;								// �û���¼Id
	unsigned short uSid;					// ���ŻỰ��ID
	int nCycleType;						// ����ģʽ��ֻ�з��������Ų�ʹ�ø�����
	unsigned char uVolume;				// �㲥����
	int nIndex;
	_tagPlayCtrl();
	_tagPlayCtrl(const XMLPlayCtrl& other);
}PLAY_CTRL, *PLAY_CTRL_PTR;

// 12.2
typedef struct IPCAST_SDK_API _tagNetLicense
{
	int nExpireDays;						// ��������
	bool bIsTryVersion;					// �Ƿ�Ϊ���ð汾
	string strCompanyName;			// ��˾����
	string strSetupDate;					// ��װ����
	int nDeviceCount;						// �����豸����

	int nOnlineUserCount;				// �����û�����
	string strMachineCode;				// ������
	string strExpireDate;					// ��������
	int nLicenceStatus;					// ֤��״̬��0 δ��Ȩ 1 ��Ч��Ȩ 2 ����ʹ�� 3 ��Ȩ����
	_tagNetLicense();
	_tagNetLicense(const XMLNetLicense& other);
}NET_LICENSE, *NET_LICENSE_PTR;


// 13.1
typedef struct IPCAST_SDK_API _tagBaseTask
{
	string strID;							// ����ID
	string strName;						// ��������
	short nPriorityLevel;					// ���ȼ�[1-999] Ĭ��Ϊ100
	short nDefaultVolume;				// Ĭ������[1-56] 50
	int nTaskTypeCode;					// �������ͱ�� �㲥 0, ���� 0, ���� 1, �ı� 10, ʱ�� 10, ���� 10, ���� 10,

	string strDescription;					// ����
	string strRecName;					// ָ����¼���ļ����ơ�
	unsigned char bIsAutoRecord;		// �Ƿ��Զ�¼����������һ�����Ϳ�ʼ¼�� 0��ʾFalse
	int nSoundEffect;						// ��Ƶ�Ĳ�����Ч
	_tagBaseTask();
	_tagBaseTask(const XMLBaseTask& other);
	_tagBaseTask(const XMLBaseTaskRes& other);
}BASE_TASK, *BASE_TASK_PTR;

typedef struct IPCAST_SDK_API _tagPlayTaskFile
{
	string strTaskID;						// ����ID
	string strFileFullName;				// �ļ�ȫ��
	int nOrderNum;						// �ļ����
	_tagPlayTaskFile();
	_tagPlayTaskFile(const XMLPlayTaskFile& other);
}PLAY_TASK_FILE, *PLAY_TASK_FILE_PTR;

typedef struct IPCAST_SDK_API _tagFileForTask
{
	vector<_tagPlayTaskFile> m_vectFiles;
}FILE_FOR_TASK, *FILE_FOR_TASK_PTR;

typedef struct IPCAST_SDK_API _tagPlayTaskAttach
{
	string strTaskID;						// ����ID
	int nPlayMode;							// ����ģʽ 0������1����ѭ����2˳��3ѭ����4���
	int nReplayTimes;						// ���Ŵ�����0��ʾ����
	int nPlayDuration;						// ���ų���ʱ��(��)0��ʾ��ʹ��
	_tagPlayTaskAttach();
	_tagPlayTaskAttach(const XMLPlayTaskAttachRes& other);
}PLAY_TASK_ATTACH, *PLAY_TASK_ATTACH_PTR;

// 13.2 
typedef struct IPCAST_SDK_API _tagLedCtrlTaskAttach
{
	string strTaskId;						// ����Id
	int nCtrlType;							// 0�ı���1����ʱ�ӣ�2���������ƣ�3���ȿ���
	int nFontSize;							// 8x8,16x16,32x32
	string strDisplayText;				// ��ʾ�ı�
	int nDisplayStyle;						// ���忴SDK�Ķ��� ����:30 ����:31 ����:32 ����:33
	int nDisplaySpeed;					// ��ʾ���ٶȻ򿪹������ƻ����ȣ�0-15��

	int nPosLeft;							// ��ʾ����߾�8�ı���
	int nPosTop;							// ��ʾ���ϱ߾�8�ı���
	int nDisplayWidth;					// ��ʾ���
	int nDisplayHeight;					// ��ʾ�߶�
	int nTextAlign;							// ���У����ң�ȫ�������ϣ����µ�
	_tagLedCtrlTaskAttach();
	_tagLedCtrlTaskAttach(const XMLLedCtrlTaskAttachRes& other);
	_tagLedCtrlTaskAttach(const XMLLedCtrlTaskAttachRes28& other);
}LED_CTRL_TASK_ATTACH, *LED_CTRL_TASK_ATTACH_PTR;

typedef struct IPCAST_SDK_API _tagTimingTask
{
	string strTaskID;						// ����ID
	string strBeginTime;					// ��ʱ��ʼ����  ? time_t
	string strEndTime;					// ��ʱ��������	 ? time_t
	string strDoworkTime;				// ÿ�ο�ʼ�ľ���ʱ��  ? time_t
	int nCycleMode;						// ѭ��ģʽ1ÿ�졢2ÿ�ܡ�3ÿ�¡�4����

	string strTaskRunDate;				// ÿ��0��6��ʾ���յ�������ÿ��Ϊ1��31�죬ָ������Ϊ�����ʱ���ַ���������ʹ�á�,���ָ���? time_t
	string strTaskRunTime;				// ����ľ���ִ��ʱ��ʱ�� ? time_t
	_tagTimingTask();
	_tagTimingTask(const XMLTimingTask& other);
	_tagTimingTask(const XMLTimingTaskRes& other);
	bool operator==(const _tagTimingTask& other);
}TIMING_TASK, *TIMING_TASK_PTR;

// 13.3
typedef struct IPCAST_SDK_API _tagOperateTask
{
	string strMainId;						// �����¼��Id��
	int nOperateType;					// ����������͡�
	_tagOperateTask();
	_tagOperateTask(const XMLOperateTask& other);
}OPERATE_TASK, *OPERATE_TASK_PTR;

// 13.6
typedef struct IPCAST_SDK_API _tagTaskInfoView
{
	string strTaskPolicyID;				// ����ID
	string strTaskID;						// ����Id
	string strName;						// ��������
	short nPriorityLevel;					// ���ȼ�[1-999] Ĭ��Ϊ100
	short nDefaultVolume;				// Ĭ������[1-56] 50

	int nTaskTypeCode;					// �������ͱ��
	string strDescription;					// ����
	string strBeginTime;					// ��ʱ��ʼʱ�� ? time_t
	string strEndTime;					// 	��ʱ����ʱ��	 ? time_t	
	string strDoworkTime;				// 	ÿ�ο�ʼ�ľ���ʱ��	 ? time_t

	int nCycleMode;						// ѭ��ģʽ1ÿ�졢2ÿ�ܡ�3ÿ�¡�4����
	string strTaskRunDate;				// ÿ��0��6��ʾ���յ�������ÿ��Ϊ1��31�죬ָ������Ϊ�����ʱ���ַ���������ʹ�á�,���ָ� ? time_t
	string strTaskRunTime;				// ����ľ���ִ��ʱ�� ? time_t
	int nTaskStatus;						// ����״̬ 0 ��ʾֹͣ״̬��1��ʾִ��״̬, 2��ʾ���������ӣ� 3 ����ɾ��
	_tagTaskInfoView();
	_tagTaskInfoView(const XMLTaskInfoView& other);
}TASK_INFO_VIEW, *TASK_INFO_VIEW_PTR;

// 13.7
typedef struct IPCAST_SDK_API _tagTaskStatus
{
	string strTaskId;						// ����Id
	string strTaskName;					// ��������
	unsigned short uSessionId;			// �ỰId
	int nTaskStatus;						// ����״̬ 0 ��ʾֹͣ״̬��1��ʾִ��״̬, 2��ʾ���������ӣ� 3 ����ɾ��
	_tagTaskStatus();
	_tagTaskStatus(const XMLTaskStatus& other);
	_tagTaskStatus(const XMLTaskStatusRes& other);
}TASK_STATUS, *TASK_STATUS_PTR;

// 13.8
typedef struct IPCAST_SDK_API _tagBaseTaskType
{
	int nTaskTypeCode;					// �������ͱ��
	string strTaskTypeName;			// ������������
	string strDescription;					// ����
	_tagBaseTaskType();
	_tagBaseTaskType(const XMLBaseTaskType& other);
}BASE_TASK_TYPE, *BASE_TASK_TYPE_PTR;


// 13.13
typedef struct IPCAST_SDK_API _tagBCTaskDevice
{
	string strTaskID;						// ����ID
	string strDeviceID;					// �豸ID
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
	string strTaskID;						// ����ID
	int nSourceInputCode;				// �ɼ�Դ����
	string strSourceInputName;		// �ɼ�Դ����
	short nRecVolume;					// ¼������
	string strRecSaveFile;				// ¼�������ļ�������ʹ�ã�תΪʹ��Task�е�RecName��

	int nInputChannel;					// �ɼ���ͨ����
	_tagBCTaskAttach();
	_tagBCTaskAttach(const XMLBCTaskAttach& other);
}BC_TASK_ATTACH, *BC_TASK_ATTACH_PTR;

// 13.26
typedef struct IPCAST_SDK_API _tagTaskPolicy
{
	int nPolicyStatus;						// ������״̬��
	string strID;							// ����ID
	string strName;						// ��������
	short nPriorityLevel;					// ���ȼ�[1-999] Ĭ��100
	short nDefaultVolume;				// Ĭ������[1-56]50

	string strTempSuspendedTime = "0001-01-01T00:00:00";	// ��ʱ����ʱ�� ? time_t
	string strTempResumeTime = "0001-01-01T00:00:00";		// ��ʱ����Ļָ�ʱ�� ? time_t
	unsigned char bProPowerOn;		// �Ƿ�Ԥ����Դ
	int nPolicyType;						// ��������0��ͨ������1��Դ������2ΪLed���Կ��Ʒ���

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
	string strTaskID;						// ����ID
	unsigned char uSwitchStatus;	// ����״̬0��ʾ�أ�1��ʾ��
	int nSwitchCode;						// ���غ�
	string strDeviceId;					//	��Դ�豸��ID
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
	int nLevelCode;						// ������ֵ
	string strLevelName;					// ��������
	_tagTaskLevel();
	_tagTaskLevel(const XMLTaskLevel& other);
}TASK_LEVEL, *TASK_LEVEL_PTR;

// 21.6
typedef struct IPCAST_SDK_API _tagPolicyStatus
{
	string strId;								// ����ID���Դ����Id��״̬Ϊ6�������Ϊ�գ���״̬Ϊ5����Ϊȫ�����¡�
	string strName;						// ����
	int nStatus;							// ����״̬ 0 ��ʾ������1��ʾ����״̬, 2��ʾ���ӣ� 3��ɾ����4���£���������ȣ��� 5����ȫ����ָ�ڷ�����ɾ�����񣬱Ƚ��ٷ�����
	short  nDefaultVolume;				// Ĭ������[1-50]50
	string  strSuspendedTime;			// ��ʱ����ʱ��

	string strResumeTime;				// ��ʱ����Ļָ�ʱ��
	unsigned char  uProPowerOn;		// �Ƿ�Ԥ����Դ
	int nPolicyType;						// �������ͣ�0��ʾ��ͨ������1��ʾ��Դ������
	_tagPolicyStatus();
	_tagPolicyStatus(const XMLPolicyStatus& other);
}POLICY_STATUS, *POLICY_STATUS_PTR;

// 21.20
//typedef struct IPCAST_SDK_API _tagSwitcher
//{
//	int nIndex;								// �� 1 ��ʼ�Ŀ�ʼ���
//	int nSwitchStatus;					// ���ص�״̬
//	unsigned char uStatus;				// ״̬��ΪXml������
//}SWITCHER, *SWITCHER_PTR;

typedef struct IPCAST_SDK_API _tagDevChannelStatus
{
	string strDeviceIp;					// �豸IP��
	int nIdentity;							// �����ڼ��ϣ����棩�е�Id
	unsigned char uDeviceType;		// �豸���ͣ��ο�DeviceTypeö�١�
	vector<SWITCHER> InChannels;	
	vector<SWITCHER> OutChannels;

	_tagDevChannelStatus(){}
	_tagDevChannelStatus(const XMLChannelStatus& other);

	unsigned char uChannelType;		// ͨ�����ͣ� 0 ��ʾ���룬1 ��ʾ�����2��ʾ���Ϊ��ʾ��֮�࣬ʹ��OutChannels
}DEV_CHANNEL_STATUS, *DEV_CHANNEL_STATUS_PTR;

// 21.24
typedef struct IPCAST_SDK_API _tagIPAlarmChannel
{
	string strDeviceIP;					// �豸IP
	int nIndex;								// ��Դ�豸���ͨ����
	_tagIPAlarmChannel();
	_tagIPAlarmChannel(const XMLIPAlarmChannel& other);
}IP_ALARM_CHANNEL, *IP_ALARM_CHANNEL_PTR;

// 21.30
typedef struct IPCAST_SDK_API _tagDeviceStatus
{
	string strKey;							// �豸ʹ��MAC��ַ��PC���м̡����ķ�����ֱ��ʹ��Զ��IP��ַ
	string strDeviceName;				// �豸������
	int nIdentity;							// ���Ϸ�����û����豸��Ψһ��ʶ�����Ϊ����������ʹ�û�ԭ����Id�������������Ըñ�ʶΪ��������
	unsigned short uPhoneNum;		// ���õ�ͨ���ţ�0��ʾû������
	unsigned char uDeviceType;		// ���ӵ��豸���ͣ��μ�DeviceTypeö��

	int nDeviceStatus;					// �豸�Ĺ���״̬���μ�DeviceStatusö��
	unsigned char uVolume;				// ����
	unsigned char uSoundEffect;		// ��Ч��1��ʾ
	unsigned short uSessionId;			// ��ǰ�ĻỰ��ID��0��ʾ����
	string strSessionName;				// ��ǰ�ĻỰ������

	string strDescription;					// ��ǰ״̬����
	string strRelayServerIp;				// �м̷�������IP��ַ
	bool bIsListened;						// �Ƿ񱻼���
	string strScreenDisplayText;		// ��Ļ��ʾ�ı�
	short nScreenSaveTime;			// ����ʱ��
	_tagDeviceStatus();
	_tagDeviceStatus(const XMLDeviceStatus& other);
	_tagDeviceStatus(const XMLDeviceStatusRes& other);
}DEVICE_STATUS, *DEVICE_STATUS_PTR;

// 31.33
typedef struct IPCAST_SDK_API _tagPowerSwitch
{
	string strDeviceID;				// �豸ID
	int nSwitch;							// ����״̬��0�Ͽ� 1�պ�
	_tagPowerSwitch();
	_tagPowerSwitch(const XMLPowerSwitch& other);
}POWER_STATUS, POWER_STATUS_PTR;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 1. �����������¼�ص���������
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1.1 ���ӵ�������
typedef void(CALLBACK *FuncConnect)(bool bSuccessful, DWORD dwUser);
typedef void(CALLBACK *FuncConnectError)(int nErrorCode, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 2. �û�����ص���������
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2.0 ��ɾ�Ĳ������أ�SubCmd = 0��
typedef void(CALLBACK *FuncOperateUser)(INT nOperateType, DWORD dwUser);

// 2.1	�����û� 0x0001
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddUser)(INT nOperateType, DWORD dwUser);

// 2.2	�����û� 0x0002
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateUser)(INT nOperateType, DWORD dwUser);

// 2.3	ɾ���û���Ϣ 0x0003
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteUser)(INT nOperateType, DWORD dwUser);

// 2.4 ��ȡ���е��û���Ϣ
typedef void(CALLBACK *FuncGetAllUsers)(const vector<NET_USER>& tanNetUsers, DWORD dwUser);

// 2.5  ͨ���û���GUID��ȡ�û���Ϣ
typedef void(CALLBACK *FuncGetUserInfo)(const NET_USER& stuNetUser, DWORD dwUser);

// 2.6 ͨ���û���GUID��ȡ������û����豸
typedef void(CALLBACK *FuncGetAllocatedDevicesByGUID)(const vector<NET_DEVICE>& tanNetDevices, DWORD dwUser);

// 2.7 ���ӻ�ɾ���û�������豸
//typedef void(CALLBACK *FuncDeleteUser)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncManageAllocatedDevices)(INT nOperateType, DWORD dwUser);

// 2.8 ��ȡ�����û�������Ϣ��
typedef void(CALLBACK *FuncGetAllUserTypes)(const vector<USER_TYPE>& tanUserTypes, DWORD dwUser);

// 2.9 ��ȡ�û�Ȩ���б�
typedef void(CALLBACK *FuncGetUserAuthorities)(const vector<USER_AUTHORITY>& tanUserAuthorities, DWORD dwUser);

// 2.10	��ȡ���н�ɫ 0x000A
typedef void(CALLBACK *FuncGetAllRoles)(const vector<NET_ROLE> tanRoles, DWORD dwUser);

// 2.11	��ɾ���û�������ɫ 0x000B
//typedef void(CALLBACK *FuncManageAssociatedRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncManageAssociatedRole)(INT nOperateType, DWORD dwUser);

// 2.12	���ӽ�ɫ 0x000C
//typedef void(CALLBACK *FuncAddRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddRole)(INT nOperateType, DWORD dwUser);

// 2.13	���½�ɫ 0x000D
//typedef void(CALLBACK *FuncUpdateRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateRole)(INT nOperateType, DWORD dwUser);

// 2.14	ɾ����ɫ 0x000E
//typedef void(CALLBACK *FuncDeleteRole)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteRole)(INT nOperateType, DWORD dwUser);

//// 
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 3. �豸����ص���������
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3.0 ��ɾ���豸����
typedef void(CALLBACK *FuncOperateDevice)(INT nOperateType, DWORD dwUser);

// 3.1	��ȡ���е��½�����豸 0x0001
typedef void(CALLBACK *FuncGetNewConnectedDevices)(const vector<CONNECTED_DEVICE>& tanDevices, DWORD dwUser);

// 3.2	��ȡ���е��豸�����б� 0x0002
typedef void(CALLBACK *FuncGetAllNetDeviceTypes)(const vector<NET_DEVICE_TYPE>& tanDeviceTypes, DWORD dwUser);

// 3.3	��ȡ���е��豸�������������͵�Դ�� 0x0003
typedef void(CALLBACK *FuncGetAllNetDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.4	��ȡ���а������ݻ����ͨ���������߶����ڣ����豸 0x0004
typedef void(CALLBACK *FuncGetAllChannelDevices)(const vector<CHANNEL_DEVICE>& tanDevices, DWORD dwUser);

// 3.5	ͨ���豸GUID��ȡ�豸��Ϣ 0x0005
typedef void(CALLBACK *FuncGetDeviceInfoByGUID)(NET_DEVICE device, DWORD dwUser);

// 3.6	ͨ���豸ID��ȡ�豸��Ϣ 0x0006
typedef void(CALLBACK *FuncGetDeviceInfoByID)(NET_DEVICE device, DWORD dwUser);

// 3.7	ͨ���豸IP��ȡ�豸��Ϣ 0x0007
typedef void(CALLBACK *FuncGetDeviceInfoByIP)(NET_DEVICE device, DWORD dwUser);

// 3.8	ͨ���豸ͨ���ţ����ţ���ȡ�豸ʵ�� 0x0008
typedef void(CALLBACK *FuncGetDeviceInfoByArea)(NET_DEVICE device, DWORD dwUser);

// 3.9	����һ���豸�Ļ������� 0x0009
typedef void(CALLBACK *FuncAddDeviceInfo)(INT nOperateType, DWORD dwUser);

// 3.10�޸�һ���豸�Ļ������� 0x000A
typedef void(CALLBACK *FuncModifyDeviceInfo)(INT nOperateType, DWORD dwUser);

// 3.11	�Ƴ��豸���� 0x000B
typedef void(CALLBACK *FuncRemoveNetDevice)(INT nOperateType, DWORD dwUser);

// 3.12	�����豸�������� 0x000C
typedef void(CALLBACK *FuncAddDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.13	�����豸ID��ȡ�����豸������Ϣ 0x000D
typedef void(CALLBACK *FuncGetDeviceAttachByID)(const vector<NET_DEVICE_ATTACH>& tanAttach, DWORD dwUser);

// 3.14	�����豸GUID��ȡ�����豸������Ϣ 0x000E
typedef void(CALLBACK *FuncGetDeviceAttachByGUID)(NET_DEVICE_ATTACH attach, DWORD dwUser);

// 3.15	�����豸������Ϣ 0x000F
typedef void(CALLBACK *FuncUpdateDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.16	�����豸Guidɾ���豸�ĸ�������ʵ�� 0x0010
typedef void(CALLBACK *FuncRemoveDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.17	��ȡ���еı����豸�б�ָ�豸����Ϊ�����豸�� 0x0011
typedef void(CALLBACK *FuncGetAllAlarmDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.18	��ȡ���еĴ�����ͨ���豸�б������������豸 0x0012
typedef void(CALLBACK *FuncGetAllInputChannelDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.19	��ȡ���б����豸�ĸ�����Ϣ�� 0x0013
typedef void(CALLBACK *FuncGetAllNetAlarmDevicesAttach)(const vector<NET_ALARM_ATTACH>& tanAttach, DWORD dwUser);

// 3.20	�����豸GUID��ȡ�豸ʵ�帽����Ϣ 0x0014
typedef void(CALLBACK *FuncGetNetAlarmDevicesAttach)(NET_ALARM_ATTACH attach, DWORD dwUser);

// 3.21	���ӱ����豸�ĸ�����Ϣ0x0015
typedef void(CALLBACK *FuncAddNetAlarmDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.22	���ı����豸�ĸ�����Ϣ 0x0016
typedef void(CALLBACK *FuncModifyNetAlarmDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.23	�����豸Guidɾ�������豸��������Ϣ 0x0017
typedef void(CALLBACK *FuncRemoveNetAlarmDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.24	��ȡ���еĵ�Դ�豸�б�ָ�豸����Ϊ�����豸�� 0x0018
typedef void(CALLBACK *FuncGetAllNetAlarmDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.25	��ȡ���еĴ����ͨ���豸�б� 0x0019
typedef void(CALLBACK *FuncGetAllOutputChannelDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 3.26	��ȡ���е�Դ�豸�ĸ�����Ϣ�� 0x001A
typedef void(CALLBACK *FuncGetAllPowerDeviceAttach)(const vector<NET_ALARM_ATTACH>& tanAttach, DWORD dwUser);

// 3.27	�����豸GUID��ȡ��Դʵ�帽����Ϣ 0x001B
typedef void(CALLBACK *FuncGetPowerDeviceAttach)(NET_ALARM_ATTACH attach, DWORD dwUser);

// 3.28	���ӵ�Դ�豸�ĸ�����Ϣ 0x001C
typedef void(CALLBACK *FuncAddPowerDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.29	���ĵ�Դ�豸�ĸ�����Ϣ 0x001D
typedef void(CALLBACK *FuncModifyPowerDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.30	�����豸Guidɾ����Դ�豸��������Ϣ 0x001E
typedef void(CALLBACK *FuncRemovePowerDeviceAttach)(INT nOperateType, DWORD dwUser);

// 3.31	���ӻ�ɾ���Խ����豸���� 0x001F
typedef void(CALLBACK *FuncManageSpeakDeviceConfig)(INT nOperateType, DWORD dwUser);

// 3.32	�������Ż�ȡ�Խ������豸 0x0020
typedef void(CALLBACK *FuncGetSpeakDevice)(const vector<DEFAULT_CALL_DEVICE>& tanDevices, DWORD dwUser);

// 3.33	���ӱ���Ԥ�� 0x0021
typedef void(CALLBACK *FuncAddAlarmProposal)(INT nOperateType, DWORD dwUser);

// 3.34	�Ƴ�����Ԥ�� 0x0022
typedef void(CALLBACK *FuncRemoveAlarmProposal)(INT nOperateType, DWORD dwUser);

// 3.35	�ݱ�������Id��ͨ���Ż�ȡ����Ԥ������ʵ�� 0x0023
typedef void(CALLBACK *FuncGetAlarmProposalByDevice)(AP_ALARM_DEVICE device, DWORD dwUser);

// 3.36	��ȡ���б�������Ԥ��ʵ�� 0x0024
typedef void(CALLBACK *FuncGetAllAlarmProposals)(const vector<AP_ALARM_DEVICE>& tanDevices, DWORD dwUser);

// 3.37	����Ԥ��Id��ȡԤ��ʵ�� 0x0025
typedef void(CALLBACK *FuncGetAlarmProposalByPolicy)(ALARM_PROPOSAL proposal, DWORD dwUser);

// 3.38	���ݲ�ѯ������ȡ������Ϣ 0x0026
typedef void(CALLBACK *FuncQueryAlarmInfo)(const vector<ALARM_INFO>& tanInfo, DWORD dwUser);

// 3.39	���ݲ�ѯ������ȡ��Ϣ���� 0x0027
typedef void(CALLBACK *FuncQueryInfoWrapper)(INT nRecord, DWORD dwUser);

// 3.40	�����豸������ 0x0028
typedef void(CALLBACK *FuncSetDeviceVolume)(INT nOperateType, DWORD dwUser);

// 3.41	��ȡ�豸������ 0x0029
typedef void(CALLBACK *FuncGetDeviceVolume)(INT nVolume, DWORD dwUser);

// 3.42	��ȡ�������뼰�������豸 0x002A
typedef void(CALLBACK *FuncGetAllAlarmDeviceDetail)(const vector<ALARM_DEVICE_DETAIL>& tanDevDetail, DWORD dwUser);

// 3.43	�����豸GUID��ȡ��������豸 0x002B
typedef void(CALLBACK *FuncGetAlarmDeviceDetail)(const vector<ALARM_DEVICE_DETAIL>& tanDevDetail, DWORD dwUser);

// 3.44	��ȡ�������� 0x002C
typedef void(CALLBACK *FuncGetAlarmType)(const vector<ALARM_DEVICE_DETAIL>& tanDevDetail, DWORD dwUser);

// 3.45	����Ԥ��ID��ȡ��������豸 0x002D
typedef void(CALLBACK *FuncGetAPOutChannel)(const vector<AP_OUT_CHANNEL>& tanDevDetail, DWORD dwUser);

// 3.46	��ȡ�������ͨ���Ĺ����豸 0x002E
//typedef void(CALLBACK *FuncGetAllAPOutChannel)(int, DWORD dwUser);

// 3.47	�����豸ID�����豸 0x002F
typedef void(CALLBACK *FuncRestartDevice)(INT nOperateType, DWORD dwUser);

// 3.48	�����豸��Ļ�Ŀ���� 0x0030
typedef void(CALLBACK *FuncSetScreenSwitch)(INT nOperateType, DWORD dwUser);

// 3.49	�����豸��Ļ��ʱ��ʾ���ı� 0x0031
typedef void(CALLBACK *FuncSetScreenText)(INT nOperateType, DWORD dwUser);

// 3.50	�����豸��ĻĬ���ı� 0x0032
typedef void(CALLBACK *FuncSetScreenDefaultText)(INT nOperateType, DWORD dwUser);

// 3.51	�����豸��Ч 0x0033
typedef void(CALLBACK *FuncSetDeviceAudio)(INT nOperateType, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 6. ����Ϣ����(ManageGroup) 0x06
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 6.0 ��ɾ������Ϣ 0x0000
typedef void(CALLBACK *FuncOperateGroup)(INT nOperateType, DWORD dwUser);

// 6.1	��������Ϣ 0x0001
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddGroup)(INT nOperateType, DWORD dwUser);

// 6.2	��������Ϣ 0x0002
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateGroup)(INT nOperateType, DWORD dwUser);

// 6.3	ɾ������Ϣ 0x0003
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteGroup)(INT nOperateType, DWORD dwUser);

// 6.4	��ȡ��������Ϣ 0x0004
typedef void(CALLBACK *FuncGetAllGroupInfo)(const vector<DEVICE_GROUP>& tanGroups, DWORD dwUser);

// 6.5	������ID��ȡ���豸��Ϣ 0x0005
typedef void(CALLBACK *FuncGetGroupDevices)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 6.6	��ɾ������豸 0x0006
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncManageGroupDevice)(INT nOperateType, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 7.�Ự����(ManageSession) 0x07
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 7.0 ��ɾ�ĻỰ
typedef void(CALLBACK *FuncOperateSession)(INT nOperateType, DWORD dwUser);

// 7.1 ���ݻỰID��ȡ�Ự��ϢParaId=0x0001
typedef void(CALLBACK *FuncGetSessionByID)(NET_SESSION session, DWORD dwUser);

// 7.2 ��ȡ���лỰ��ϢParaId=0x0002
typedef void(CALLBACK *FuncGetAllSessions)(const vector<NET_SESSION>& tanSession, DWORD dwUser);

// 7.3 ���ݻỰID��ֹ�ỰParaId=0x0003
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncTerminateSession)(INT nOperateType, DWORD dwUser);

// 7.4 ���ӻỰ�е��豸ParaId=0x0004
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncAddDeviceIntoSession)(INT nOperateType, DWORD dwUser);

// 7.5 ɾ���Ự�е��豸ParaId=0x0005
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncRemoveDeviceFromSession)(INT nOperateType, DWORD dwUser);

// 7.6 ��ȡ�Ự���������豸ParaId=0x0006
typedef void(CALLBACK *FuncGetLeadingDevice)(CONNECTED_DEVICE device, DWORD dwUser);

// 7.7 ���ݻỰID��ȡ���������豸��ParaId=0x0007��
typedef void(CALLBACK *FuncGetDevicesInSession)(const vector<CONNECTED_DEVICE>& tanDevice, DWORD dwUser);

// 7.7 ��ȡ�����������豸ParaId=0x0009
typedef void(CALLBACK *FuncGetAllConnectedDevices)(const vector<CONNECTED_DEVICE>& tanDevice, DWORD dwUser);

// 7.8 ��ʼ¼��ParaId=0x000A
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncStartRecording)(INT nOperateType, DWORD dwUser);

// 7.9 ֹͣ¼��ParaId=0x000B
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncStopRecording)(INT nOperateType, DWORD dwUser);

// 7.10 ���ûỰ����ParaId=0x000C
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSetVolume)(INT nOperateType, DWORD dwUser);

// 7.11 ���û���ЧParaId=0x000D
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSetAudio)(INT nOperateType, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 8.��Դ���ݹ���(ManageResource) 0x08
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 8.0 ��ɾ����Դ 0x0000
typedef void(CALLBACK *FuncOperateResource)(INT nOperateType, DWORD dwUser);

// 8.1	�ϴ��ļ� 0x0001
typedef void(CALLBACK *FuncUploadFile)(INT nSessionID, DWORD dwUser);

// 8.2	�ϴ��ļ����ݣ������ݣ� 0x0002
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUploadDataInFile)(INT nOperateType, DWORD dwUser);

// 8.3	�ϴ��ļ�������� 0x0003
typedef void(CALLBACK *FuncFinishUploadingFile)(INT nFileID, DWORD dwUser);

// 8.4	ȡ���ϴ��ļ� 0x0004
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCancelUploadingFile)(INT nOperateType, DWORD dwUser);

// 8.5	���ϴ�����ļ�λ�� 0x0005
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncGetPosOfUploadedFile)(INT nOperateType, DWORD dwUser);

// 8.6	�����ļ� 0x0006
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDownloadFile)(INT nOperateType, DWORD dwUser);

// 8.7	�����������ļ����� 0x0007
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSendFileByServer)(string strText, DWORD dwUser);
typedef void(CALLBACK *FuncRecvDataFromServer)(char* pData, int nLength, DWORD dwUser);

// 8.8	���������������ļ����� 0x0008
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncFinishSendingFileByServer)(USHORT uSessionID, DWORD dwUser);

// 8.9	ȡ���ϴ����� 0x0009
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCancelUploadOrDownload)(INT nOperateType, DWORD dwUser);

// 8.10 ����¼���ļ� 0x000A
typedef void(CALLBACK *FuncFindRecordedFile)(const vector<RECORD_FILE>& tanFiles, DWORD dwUser);

// 8.11 �����ļ� 0x000B
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
//typedef void(CALLBACK *FuncGetPosOfDownload)(INT nOperateType, DWORD dwUser);

// 8.12 �������ص�λ�� 0x000C
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncGetPosOfDownload)(INT nOperateType, DWORD dwUser);

// 8.13 ��ȡ���е��ϴ���Դ�ļ� 0x000D
typedef void(CALLBACK *FuncGetAllUploadedFiles)(const vector<NET_FILE>& tanFiles, DWORD dwUser);

// 8.14 �����ļ�ID��ȡ�ļ���Ϣ 0x000E
typedef void(CALLBACK *FuncGetFileInfo)(NET_FILE resource, DWORD dwUser);

// 8.15 �����ļ�IDɾ���ļ� 0x000F
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncDeleteFile)(INT nOperateType, DWORD dwUser);

// 8.16 �����ļ���Ϣ 0x0010
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncUpdateFile)(INT nOperateType, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 9.Ѱ�����Խ�(ManageSpeaking) 0x09
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 9.0
typedef void(CALLBACK *FuncOperateSpeak)(INT nOperateType, DWORD dwUser);

// 9.1	Ѱ�� 0x0001
typedef void(CALLBACK *FuncCall)(USHORT uSessionID, DWORD dwUser);

// 9.2	�Խ� 0x0002
typedef void(CALLBACK *FuncSpeak)(USHORT uSessionID, DWORD dwUser);

// 9.3	ֹͣѰ�� 0x0003
typedef void(CALLBACK *FuncCancelCalling)(INT nOperateType, DWORD dwUser);

// 9.4	ֹͣ�Խ� 0x0004
typedef void(CALLBACK *FuncCancelSpeaking)(INT nOperateType, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 10.�㲥(ManageBroadcast) 0x0A
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 9.0
typedef void(CALLBACK *FuncOperateBroadcast)(INT nOperateType, DWORD dwUser);

// 10.1 �㲥��ʼ 0x0001
typedef void(CALLBACK *FuncStartBroadcasting)(INT nSessionID, DWORD dwUser);
typedef void(CALLBACK *FuncStartBroadcastingEx)(USHORT nSessionID, DWORD dwUser);


// 10.3 �㲥����Ƶ��ʽ���� 0x0003
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncBroadcastAudio)(INT nOperateType, DWORD dwUser);

// 10.5 ������Ƶ���� 0x0005
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncTransmitAudio)(string strText, DWORD dwUser);

// 10.6 ֹͣ�㲥 0x0006
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCancelBroadcasting)(INT nOperateType, DWORD dwUser);

// 10.7 �и���� 0x0007
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncSwitchSong)(INT nOperateType, DWORD dwUser);

// 10.8 �㲥��ʱ�ļ� 0x0008
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncBroadcastTempFile)(INT nOperateType, DWORD dwUser);
// 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 12. ��Ȩ����(ManageAuthority) 0x0C
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12.1 ��ȡע���� 0x0001
typedef void(CALLBACK *FuncGetMachineCode)(string strRegisterCode, DWORD dwUser);

// 12.2 ��ȡ֤����Ϣ 0x0002
typedef void(CALLBACK *FuncGetLicenseInfo)(NET_LICENSE license, DWORD dwUser);

// 12.3 ֤����Ч����֤ 0x0003
typedef void(CALLBACK *FuncVerifyLicense)(NET_LICENSE license, DWORD dwUser);

// 12.4 ע��֤�� 0x0004
typedef void(CALLBACK *FuncRegisterLicense)(NET_LICENSE license, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 13. ����ͷ�������ص�����
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3.0 ��ɾ�����񷵻�
typedef void(CALLBACK *FuncOperateTask)(INT nOperateType, DWORD dwUser);

// 13.1	�������� 0x0001
typedef void(CALLBACK *FuncAddTask)(INT nOperateType, DWORD dwUser);

// 13.2	�������� 0x0002
typedef void(CALLBACK *FuncUpdateTask)(INT nOperateType, DWORD dwUser);

// 13.3	ɾ������ 0x0003
typedef void(CALLBACK *FuncRemoveTask)(INT nOperateType, DWORD dwUser);

// 13.4	��������ID��ȡ������Ϣ 0x0004
typedef void(CALLBACK *FuncGetTaskInfo)(BASE_TASK task, DWORD dwUser);

// 13.5	��ȡ����������Ϣ 0x0005
typedef void(CALLBACK *FuncGetAllTaskInfo)(const vector<BASE_TASK>& tanTasks, DWORD dwUser);

// 13.6	���ݷ���ID��ȡ����������Ϣ 0x0006
typedef void(CALLBACK *FuncGetAllTaskView)(const vector<TASK_INFO_VIEW>& tanTaskViews, DWORD dwUser);

// 13.7	��ȡ����ִ�������״̬ 0x0007
typedef void(CALLBACK *FuncGetAllTaskStatus)(const vector<TASK_STATUS>& tanTaskStatus, DWORD dwUser);

// 13.8	��ȡ������������s 0x00013
typedef void(CALLBACK *FuncGetAllTaskTypes)(const vector<BASE_TASK_TYPE>& tanTaskTypes, DWORD dwUser);

// 13.9	 0x0009

// 13.10 ��������ID��ȡ�ļ����������б� 0x000A
typedef void(CALLBACK *FuncGetPlayTask)(PLAY_TASK_ATTACH attach, DWORD dwUser);

// 13.11 �����ļ����Ÿ������� 0x000B
typedef void(CALLBACK *FuncAddPlayTaskAttach)(INT nOperateType, DWORD dwUser);

// 13.12 �����ļ����Ÿ������� 0x000C
typedef void(CALLBACK *FuncUpdatePlayTaskAttach)(INT nOperateType, DWORD dwUser);

// 13.13 ɾ���ļ����Ÿ������� 0x000D
typedef void(CALLBACK *FuncRemovePlayTaskAttach)(INT nOperateType, DWORD dwUser);

// 13.14 ��������ID��ȡ�豸���� 0x000E
typedef void(CALLBACK *FuncGetBCDeviceByTaskID)(const vector<BC_TASK_DEVICE>& tanDevices, DWORD dwUser);

// 13.15 ��������ID��ȡ�����豸��Ϣ 0x000F
typedef void(CALLBACK *FuncGetDeiveByTaskID)(const vector<NET_DEVICE>& tanDevices, DWORD dwUser);

// 13.16 ���ӻ�ɾ������������豸 0x0010
typedef void(CALLBACK *FuncAddOrDelPlayingDevice)(const vector<PLAY_TASK_FILE>& tanFiles, DWORD dwUser);

// 13.17 ��������Id��ȡ���������е��ļ��б� 0x00011
typedef void(CALLBACK *FuncGetPlayingFilesByTaskID)(const vector<PLAY_TASK_FILE>& tanFiles, DWORD dwUser);

// 13.18 ���ӻ�ɾ�����������е��ļ��б� 0x00012
typedef void(CALLBACK *FuncAddOrDelPlayingFiles)(INT nOperateType, DWORD dwUser);

// 13.19 ��������Id��ȡ�ɲ�����������Ϣ 0x00013
typedef void(CALLBACK *FuncGetAcquicastAttach)(BC_TASK_ATTACH attach, DWORD dwUser);

// 13.20 ���Ӳɲ��������� 0x0014
typedef void(CALLBACK *FuncAddAcquicastAttach)(INT nOperateType, DWORD dwUser);

// 13.21 �޸Ĳɲ���������(ParaId=0x0015)
typedef void(CALLBACK *FuncModifyAcquicastAttach)(INT nOperateType, DWORD dwUser);

// 13.22 ɾ���ɲ���������(ParaId=0x0016)
typedef void(CALLBACK *FuncRemoveAcquicastAttach)(INT nOperateType, DWORD dwUser);

// 13.23 ��ȡ��ʱ����(ParaId=0x0017)
typedef void(CALLBACK *FuncGetTimingConfig)(TIMING_TASK task, DWORD dwUser);

// 13.24 ���Ӷ�ʱ����(ParaId=0x0018)
typedef void(CALLBACK *FuncAddTimingConfig)(INT nOperateType, DWORD dwUser);

// 13.25 // �ظ���

// 13.26 ɾ����ʱ����(ParaId=0x001A)
typedef void(CALLBACK *FuncRemoveTimingConfig)(INT nOperateType, DWORD dwUser);

// 13.27 ��ȡ�������񷽰�(ParaId=0x001B)
typedef void(CALLBACK *FuncGetAllTaskPolicy)(const vector<TASK_POLICY>& m_tanTaskPolicy, DWORD dwUser);

// 13.28 ���ݷ���ID��ȡ����ʵ��(ParaId=0x001C)
typedef void(CALLBACK *FuncGetTaskPolicy)(TASK_POLICY policy, DWORD dwUser);

// 13.29 �������񷽰�(ParaId=0x001D)
typedef void(CALLBACK *FuncAddTaskPolicy)(INT nOperateType, DWORD dwUser);

// 13.30 �������񷽰�(ParaId=0x001E)
typedef void(CALLBACK *FuncModifyTaskPolicy)(INT nOperateType, DWORD dwUser);

// 13.31 ɾ�����񷽰�(ParaId=0x001F)
typedef void(CALLBACK *FuncRemoveTaskPolicy)(INT nOperateType, DWORD dwUser);

// 13.32 ���ӷ����е�����(ParaId=0x0020)
typedef void(CALLBACK *FuncAddTaskIntoPolicy)(INT nOperateType, DWORD dwUser);

// 13.33 �ӷ�����ɾ������(ParaId=0x0021)
typedef void(CALLBACK *FuncRemoveTaskFromPolicy)(INT nOperateType, DWORD dwUser);

// 13.34 ��������(ParaId=0x0023)
typedef void(CALLBACK *FuncStartTask)(INT nOperateType, DWORD dwUser);

// 13.35 ֹͣ����(ParaId=0x0024)
typedef void(CALLBACK *FuncStopTask)(INT nOperateType, DWORD dwUser);

// 13.36 ��ȡ��Դ����������Ϣ(ParaId=0x0025)
typedef void(CALLBACK *FuncGetPowerSwithTask)(const vector<POWER_TASK_SWITCH>& tanInfo, DWORD dwUser);

// 13.37 ��ȡ���м�����Ϣ(ParaId=0x0026)
typedef void(CALLBACK *FuncGetAllTaskLevels)(const vector<TASK_LEVEL>& tanLevels, DWORD dwUser);

// 13.38 ��ȡȫ����ָ������ID��LED����������Ϣ(ParaId=0x0027)
typedef void(CALLBACK *FuncGetAllLedCtrlTaskAttach)(const vector<LED_CTRL_TASK_ATTACH>& tanTaskInfo, DWORD dwUser);

// 13.39 ��������ID��ȡLED����������Ϣ(ParaId=0x0028)
typedef void(CALLBACK *FuncGetLedCtrlTaskAttach)(LED_CTRL_TASK_ATTACH info, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 14.�ͻ��˻�ȡ״ָ̬��(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 14.0
typedef void(CALLBACK *FuncOperateStatus)(INT nOperateType, DWORD dwUser);

// 14.1 ��ȡ���б����豸״̬��Ϣ(ParaId=0x0014)
typedef void(CALLBACK *FuncGetAllAlarmDevStatus)(const vector<DEV_CHANNEL_STATUS>& tanStatus, DWORD dwUser);

// 14.2 ����IP��ȡ�����豸״̬��Ϣ(ParaId=0x0015)
typedef void(CALLBACK *FuncGetAlarmDevStatus)(DEV_CHANNEL_STATUS status, DWORD dwUser);

// 14.3 ����IP�ͱ���ͨ��ȷ�ϱ���(ParaId=0x0018)
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncConfirmAlarm)(INT nOperateType, DWORD dwUser);

// 14.4 ��ȡ���е�Դ��״̬��Ϣ(ParaId=0x0019)
typedef void(CALLBACK *FuncGetAllPowerStatus)(const vector<DEV_CHANNEL_STATUS>& tanStatus, DWORD dwUser);

// 14.5 ����IP��ȡ��Դ�豸״̬��Ϣ(ParaId=0x001A)
typedef void(CALLBACK *FuncGetPowerStatus)(DEV_CHANNEL_STATUS status, DWORD dwUser);

// 14.6 �ͻ��˿��Ƶ�Դ�Ŀ����(ParaId=0x001D)
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCtrlPowerSwitchByIP)(INT nOperateType, DWORD dwUser);

// 14.7 ��ȡ���н����豸��״̬��Ϣ(ParaId=0x001E)
typedef void(CALLBACK *FuncGetAllDeviceStatus)(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);

// 14.8 �����豸ID��ȡ�豸��״̬��Ϣ(ParaId=0x001F)
typedef void(CALLBACK *FuncGetDevStatusByID)(DEVICE_STATUS status, DWORD dwUser);

// 14.9 �����豸IP��ȡ�豸��״̬��Ϣ(ParaId=0x0020)
typedef void(CALLBACK *FuncGetDevStatusByIP)(DEVICE_STATUS status, DWORD dwUser);

// 14.10 ���Ƶ�Դ�Ŀ����(ParaId=0x0021)
//typedef void(CALLBACK *Func)(INT, DWORD dwUser);
typedef void(CALLBACK *FuncCtrlPowerSwitchByID)(INT nOperateType, DWORD dwUser);

// 14.11 ��ȡ���о�ʾ��״̬��Ϣ(ParaId=0x0022)
typedef void(CALLBACK *FuncGetAllAlarmLightStatus)(const vector<DEV_CHANNEL_STATUS>& tanStatus, DWORD dwUser);

// 14.12 �����豸ID��ȡ��ʾ��״̬��Ϣ(ParaId=0x0023)
typedef void(CALLBACK *FuncGetAlarmLightStatus)(DEV_CHANNEL_STATUS status, DWORD dwUser);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 15.�����������豸״̬(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 15.1	�����������豸״̬�仯(ParaId=0x0001)
typedef void(CALLBACK *FuncAutoGetDeviceStatus)(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);

// 15.2	���������ͻỰ״̬�仯(ParaId=0x0002)
typedef void(CALLBACK *FuncAutoGetSessionStatus)(SESSION_STATUS status, DWORD dwUser);

// 15.3	���������ͻỰ��ֹ��Ϣ(ParaId=0x0003)
typedef void(CALLBACK *FuncAutoGetSessionTerminal)(INT nSessionID, DWORD dwUser);

// 15.4	���������������û�״̬�仯(ParaId=0x0004)
typedef void(CALLBACK *FuncAutoGetUserStatus)(const vector<DEVICE_STATUS>& tanStatus, DWORD dwUser);

// 15.5	��������������״̬�仯(ParaId=0x0005)
typedef void(CALLBACK *FuncAutoGetTaskStatus)(TASK_STATUS status, DWORD dwUser);

// 15.6	���������ͷ���״̬�仯(ParaId=0x0005)
typedef void(CALLBACK *FuncAutoGetPolicyStatus)(POLICY_STATUS status, DWORD dwUser);

// 15.17 �����������豸��ͨ��״̬�仯(ParaId=0x0017)
typedef void(CALLBACK *FuncAutoGetChannelStatus)(DEV_CHANNEL_STATUS tanStatus, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 1. �����������¼�ӿ�
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1.1 ���ӵ�������
//IPCAST_SDK_API BOOL __stdcall AEBELL_IPCAST_Connect(string strIP, UINT uPort, LOGIN_REQUEST stuLoginRequest);
//IPCAST_SDK_API BOOL __stdcall AEBELL_IPCAST_Connect(string strIP, UINT uPort, LOGIN_REQUEST stuLoginRequest, FuncConnect cbConnect, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_Connect(string strIP, UINT uPort, LOGIN_REQUEST stuLoginRequest, FuncConnect cbConnect, FuncConnectError cbConnectError, DWORD dwUser);
// 1.2 �Ͽ�����
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DisConnect();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 2. �û�����ӿ�
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2.1	�����û� 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddUser(NET_USER user, FuncAddUser cbAddUser, DWORD dwUser, DEVICE_FOR_USER device = DEVICE_FOR_USER());
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddUser(NET_USER user, ROLE_FOR_USER role, FuncAddUser cbAddUser, DWORD dwUser, DEVICE_FOR_USER device = DEVICE_FOR_USER());

// 2.2	�����û� 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateUser(NET_USER user, FuncUpdateUser cbUpdateUser, DWORD dwUser);

// 2.3	ɾ���û���Ϣ 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteUser(string strUserGUID, FuncDeleteUser cbDeleteUser, DWORD dwUser);

// 2.4 ��ȡ���е��û���Ϣ
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllUsers(FuncGetAllUsers cbGetAllUser, DWORD dwUser);

// 2.5  ͨ���û���GUID��ȡ�û���Ϣ
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetUserInfo(FuncGetUserInfo cbGetUserInfo, DWORD dwUser);

// 2.6 ͨ���û���GUID��ȡ������û����豸
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllocatedDevicesByGUID(FuncGetAllocatedDevicesByGUID cbGetAllocatedDevicesByGUID, DWORD dwUser);

// 2.7 ���ӻ�ɾ���û�������豸
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageAllocatedDevices(DEVICE_FOR_USER device, FuncManageAllocatedDevices cbManageAllocatedDevices, DWORD dwUser);

// 2.8 ��ȡ�����û�������Ϣ��
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllUserTypes(FuncGetAllUserTypes cbGetAllUserTypes, DWORD dwUser);

// 2.9 ��ȡ�û�Ȩ���б�
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetUserAuthorities(INT nOperateType, string strGUID, FuncGetUserAuthorities cbGetUserAuthorities, DWORD dwUser);

// 2.10	��ȡ���н�ɫ 0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllRoles(FuncGetAllRoles cbGetAllRoles, DWORD dwUser);

// 2.11	��ɾ���û�������ɫ 0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageAssociatedRole(string strUserID, ROLE_FOR_USER role, FuncManageAssociatedRole cbManageAssociatedRole, DWORD dwUser);

// 2.12	���ӽ�ɫ 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddRole(NET_ROLE role, ROLE_FUNCTION function, FuncAddRole cbAddRole, DWORD dwUser);

// 2.13	���½�ɫ 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateRole(NET_ROLE role, ROLE_FUNCTION function, FuncUpdateRole cbUpdateRole, DWORD dwUser);

// 2.14	ɾ����ɫ 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteRole(string strRoleGUID, FuncDeleteRole cbDeleteRole, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 3.�豸����
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3.1	��ȡ���е��½�����豸 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetNewConnectedDevices(FuncGetNewConnectedDevices cbGetNewConnectedDevices, DWORD dwUser);

// 3.2	��ȡ���е��豸�����б� 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetDeviceTypes(FuncGetAllNetDeviceTypes cbGetAllNetDeviceTypes, DWORD dwUser);

// 3.3	��ȡ���е��豸�������������͵�Դ�� 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetDevices(FuncGetAllNetDevices cbGetAllNetDevices, DWORD dwUser);

// 3.4	��ȡ���а������ݻ����ͨ���������߶����ڣ����豸 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllChannelDevices(FuncGetAllChannelDevices cbGetAllChannelDevices, DWORD dwUser);

// 3.5	ͨ���豸GUID��ȡ�豸��Ϣ 0x0005(���Ӳ���豸�����pc��������)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByGUID(FuncGetDeviceInfoByGUID cbGetDeviceInfoByGUID, DWORD dwUser);

// 3.6	ͨ���豸ID��ȡ�豸��Ϣ 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByID(string strDeviceID, FuncGetDeviceInfoByID cbGetDeviceInfoByID, DWORD dwUser);

// 3.7	ͨ���豸IP��ȡ�豸��Ϣ 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByIP(string strDeviceIP, FuncGetDeviceInfoByIP cbGetDeviceInfoByIP, DWORD dwUser);

// 3.8	ͨ���豸ͨ���ţ����ţ���ȡ�豸ʵ�� 0x0008
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceInfoByArea(WORD nAreaNum, FuncGetDeviceInfoByArea cbGetDeviceInfoByArea, DWORD dwUser);

// 3.9	����һ���豸�Ļ������� 0x0009
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddDeviceInfo(NET_DEVICE device, INT nOperateType, const list<NET_DEVICE_ATTACH>& tanAttach, const list<DEFAULT_CALL_DEVICE>& tanCallDevices, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddBaseDeviceInfo(NET_DEVICE device, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAudioDeviceInfo(NET_DEVICE netDevice, NET_DEVICE_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, DEFAULT_CALL_DEVICES callDevices = DEFAULT_CALL_DEVICES());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAlarmDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, ALARM_DEVICE_DETAILS devDetails = ALARM_DEVICE_DETAILS());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPowerDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, POWER_DEVICE_DETAILS devDetails = POWER_DEVICE_DETAILS());

// 3.10�޸�һ���豸�Ļ������� 0x000A
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyDeviceInfo(NET_DEVICE device, INT nOperateType, const list<NET_DEVICE_ATTACH>& tanAttach, const list<DEFAULT_CALL_DEVICE>& tanCallDevices, FuncModifyDeviceInfo cbModifyDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyBaseDeviceInfo(NET_DEVICE device, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyAudioDeviceInfo(NET_DEVICE netDevice, NET_DEVICE_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, DEFAULT_CALL_DEVICES callDevices = DEFAULT_CALL_DEVICES());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyAlarmDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, ALARM_DEVICE_DETAILS devDetails = ALARM_DEVICE_DETAILS());
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyPowerDeviceInfo(NET_DEVICE netDevice, NET_ALARM_ATTACH attach, FuncAddDeviceInfo cbAddDeviceInfo, DWORD dwUser, POWER_DEVICE_DETAILS devDetails = POWER_DEVICE_DETAILS());

// 3.11	�Ƴ��豸���� 0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveNetDevice(OPERATE_DEVICE operateDev, FuncRemoveNetDevice cbRemoveNetDevice, DWORD dwUser);

// 3.12	�����豸�������� 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddDeviceAttach(NET_DEVICE_ATTACH devAttach, FuncAddDeviceAttach cbAddDeviceAttach, DWORD dwUser);

// 3.13	�����豸ID��ȡ�����豸������Ϣ 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceAttachByID(FuncGetDeviceAttachByID cbGetDeviceAttachByID, DWORD dwUser);

// 3.14	�����豸GUID��ȡ�����豸������Ϣ 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceAttachByGUID(string strGUID, FuncGetDeviceAttachByGUID cbGetDeviceAttachByGUID, DWORD dwUser);

// 3.15	�����豸������Ϣ 0x000F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateDeviceAttach(NET_DEVICE_ATTACH devAttach, FuncUpdateDeviceAttach cbUpdateDeviceAttach, DWORD dwUser);

// 3.16	�����豸Guidɾ���豸�ĸ�������ʵ�� 0x0010
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveDeviceAttach(FuncRemoveDeviceAttach cbRemoveDeviceAttach, DWORD dwUser);

// 3.17	��ȡ���еı����豸�б�ָ�豸����Ϊ�����豸�� 0x0011
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmDevices(FuncGetAllAlarmDevices cbGetAllAlarmDevices, DWORD dwUser);

// 3.18	��ȡ���еĴ�����ͨ���豸�б������������豸 0x0012
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllInputChannelDevices(FuncGetAllInputChannelDevices cbGetAllInputChannelDevices, DWORD dwUser);

// 3.19	��ȡ���б����豸�ĸ�����Ϣ�� 0x0013
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetAlarmDevicesAttach(FuncGetAllNetAlarmDevicesAttach cbGetAllNetAlarmDevicesAttach, DWORD dwUser);

// 3.20	�����豸GUID��ȡ�豸ʵ�帽����Ϣ 0x0014
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetNetAlarmDevicesAttach(string strGUID, FuncGetNetAlarmDevicesAttach cbGetNetAlarmDevicesAttach, DWORD dwUser);

// 3.21	���ӱ����豸�ĸ�����Ϣ0x0015
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddNetAlarmDeviceAttach(NET_ALARM_ATTACH alarmAttach, FuncAddNetAlarmDeviceAttach cbAddNetAlarmDeviceAttach, DWORD dwUser);

// 3.22	���ı����豸�ĸ�����Ϣ 0x0016
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyNetAlarmDeviceAttach(NET_ALARM_ATTACH alarmAttach, FuncModifyNetAlarmDeviceAttach cbModifyNetAlarmDeviceAttach, DWORD dwUser);

// 3.23	�����豸Guidɾ�������豸��������Ϣ 0x0017
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveNetAlarmDeviceAttach(string strDeviceGUID, FuncRemoveNetAlarmDeviceAttach cbRemoveNetAlarmDeviceAttach, DWORD dwUser);

// 3.24	��ȡ���еĵ�Դ�豸�б�ָ�豸����Ϊ�����豸�� 0x0018
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllNetAlarmDevices(FuncGetAllNetAlarmDevices cbGetAllNetAlarmDevices, DWORD dwUser);

// 3.25	��ȡ���еĴ����ͨ���豸�б� 0x0019
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllOutputChannelDevices(FuncGetAllOutputChannelDevices cbGetAllOutputChannelDevices, DWORD dwUser);

// 3.26	��ȡ���е�Դ�豸�ĸ�����Ϣ�� 0x001A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllPowerDeviceAttach(FuncGetAllPowerDeviceAttach cbGetAllPowerDeviceAttach, DWORD dwUser);

// 3.27	�����豸GUID��ȡ��Դʵ�帽����Ϣ 0x001B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPowerDeviceAttach(FuncGetPowerDeviceAttach cbGetPowerDeviceAttach, DWORD dwUser);

// 3.28	���ӵ�Դ�豸�ĸ�����Ϣ 0x001C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPowerDeviceAttach(NET_ALARM_ATTACH attach, FuncAddPowerDeviceAttach cbAddPowerDeviceAttach, DWORD dwUser);

// 3.29	���ĵ�Դ�豸�ĸ�����Ϣ 0x001D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyPowerDeviceAttach(NET_ALARM_ATTACH attach, FuncModifyPowerDeviceAttach cbModifyPowerDeviceAttach, DWORD dwUser);

// 3.30	�����豸Guidɾ����Դ�豸��������Ϣ 0x001E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemovePowerDeviceAttach(string strDeviceGUID, FuncRemovePowerDeviceAttach cbRemovePowerDeviceAttach, DWORD dwUser);

// 3.31	���ӻ�ɾ���Խ����豸���� 0x001F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageSpeakDeviceConfig(CALL_DEVICE_WRAPPER device, FuncManageSpeakDeviceConfig cbManageSpeakDeviceConfig, DWORD dwUser);

// 3.32	�������Ż�ȡ�Խ������豸 0x0020
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetSpeakDevice(WORD nAreaNum, FuncGetSpeakDevice cbGetSpeakDevice, DWORD dwUser);

// 3.33	���ӱ���Ԥ�� 0x0021
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAlarmProposal(AP_ALARM_DEVICE device, ALARM_PROPOSAL proposal, DEVICE_ID_WRAPPER devIDs, AP_OUT_CHANNEL_WRAPPER channels, FuncAddAlarmProposal cbAddAlarmProposal, DWORD dwUser);

// 3.34	�Ƴ�����Ԥ�� 0x0022
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveAlarmProposal(string strProposalGUID, INT nAlarmChannelNo, FuncRemoveAlarmProposal cbRemoveAlarmProposal, DWORD dwUser);

// 3.35	�ݱ�������Id��ͨ���Ż�ȡ����Ԥ������ʵ�� 0x0023
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmProposalByDevice(string strDeviceID, INT nAlarmChannelNo, FuncGetAlarmProposalByDevice cbGetAlarmProposalByDevice, DWORD dwUser);

// 3.36	��ȡ���б�������Ԥ��ʵ�� 0x0024
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmProposals(FuncGetAllAlarmProposals cbGetAllAlarmProposals, DWORD dwUser);

// 3.37	����Ԥ��Id��ȡԤ��ʵ�� 0x0025
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmProposalByPolicy(string strProposalGUID, FuncGetAlarmProposalByPolicy cbGetAlarmProposalByPolicy, DWORD dwUser);

// 3.38	���ݲ�ѯ������ȡ������Ϣ 0x0026
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_QueryAlarmInfo(ALARM_QUERY query, INT nPage, INT nRecordsPerPage, FuncQueryAlarmInfo cbQueryAlarmInfo, DWORD dwUser);

// 3.39	���ݲ�ѯ������ȡ��Ϣ���� 0x0027
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_QueryInfoWrapper(ALARM_QUERY query, FuncQueryInfoWrapper cbQueryInfoWrapper, DWORD dwUser);

// 3.40	�����豸������ 0x0028
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetDeviceVolume(DEVICE_VOLUME volume, INT nVolume, FuncSetDeviceVolume cbSetDeviceVolume, DWORD dwUser);

// 3.41	��ȡ�豸������ 0x0029
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceVolume(DEVICE_VOLUME volume, FuncGetDeviceVolume cbGetDeviceVolume, DWORD dwUser);

// 3.42	��ȡ�������뼰�������豸 0x002A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmDeviceDetail(FuncGetAllAlarmDeviceDetail cbGetAllAlarmDeviceDetail, DWORD dwUser);

// 3.43	�����豸GUID��ȡ��������豸 0x002B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmDeviceDetail(string strAlarmDeviceGUID, FuncGetAlarmDeviceDetail cbGetAlarmDeviceDetail, DWORD dwUser);

// 3.44	��ȡ�������� 0x002C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmType(FuncGetAlarmType cbGetAlarmType, DWORD dwUser);

// 3.45	����Ԥ��ID��ȡ��������豸 0x002D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAPOutChannel(string strProposalGUID, FuncGetAPOutChannel cbGetAPOutChannel, DWORD dwUser);

// 3.46	��ȡ�������ͨ���Ĺ����豸 0x002E
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAPOutChannel(FuncGetAllAPOutChannel cbGetAllAPOutChannel, DWORD dwUser);

// 3.47	�����豸ID�����豸 0x002F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RestartDevice(INT nDeviceID, FuncRestartDevice cbRestartDevice, DWORD dwUser);

// 3.48	�����豸��Ļ�Ŀ���� 0x0030
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetScreenSwitch(DEVICE_SWITCH devSwitch, FuncSetScreenSwitch cbSetScreenSwitch, DWORD dwUser);

// 3.49	�����豸��Ļ��ʱ��ʾ���ı� 0x0031
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetScreenText(DEVICE_TEXT devText, FuncSetScreenText cbSetScreenText, DWORD dwUser);

// 3.50	�����豸��ĻĬ���ı� 0x0032
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetScreenDefaultText(INT nDeviceID, FuncSetScreenDefaultText cbSetScreenDefaultText, DWORD dwUser);

// 3.51	�����豸��Ч 0x0033
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetDeviceAudio(DEVICE_AUDIO devAudio, FuncSetDeviceAudio cbSetDeviceAudio, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 6. ����Ϣ����(ManageGroup) 0x06
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 6.1	��������Ϣ 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddGroup(DEVICE_GROUP group, FuncAddGroup cbAddGroup, DWORD dwUser, DEVICE_GROUP_ATTACH attach = {});

// 6.2	��������Ϣ 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateGroup(DEVICE_GROUP group, FuncUpdateGroup cbUpdateGroup, DWORD dwUser, DEVICE_GROUP_ATTACH attach = {});

// 6.3	ɾ������Ϣ 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteGroup(string strGroupGUID, FuncDeleteGroup cbDeleteGroup, DWORD dwUser);

// 6.4	��ȡ��������Ϣ 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllGroupInfo(FuncGetAllGroupInfo cbGetAllGroupInfo, DWORD dwUser);

// 6.5	������ID��ȡ���豸��Ϣ 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetGroupDevices(string strGroupGUID, FuncGetGroupDevices cbGetGroupDevices, DWORD dwUser);

// 6.6	��ɾ������豸 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ManageGroupDevice(DEVICE_ID_WRAPPER devIDs, FuncManageGroupDevice cbManageGroupDevice, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 7.�Ự����(ManageSession) 0x07
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 7.1 ���ݻỰID��ȡ�Ự��ϢParaId=0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetSessionByID(USHORT uSessionID, FuncGetSessionByID cbGetSessionByID, DWORD dwUser);

// 7.2 ��ȡ���лỰ��ϢParaId=0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllSessions(FuncGetAllSessions cbGetAllSessions, DWORD dwUser);

// 7.3 ���ݻỰID��ֹ�ỰParaId=0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_TerminateSession(USHORT uSessionID, FuncTerminateSession cbTerminateSession, DWORD dwUser);

// 7.4 ���ӻỰ�е��豸ParaId=0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddDeviceIntoSession(USHORT uSessionID, DEVICE_ID_WRAPPER devIDs, FuncAddDeviceIntoSession cbAddDeviceIntoSession, DWORD dwUser);

// 7.5 ɾ���Ự�е��豸ParaId=0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveDeviceFromSession(USHORT uSessionID, DEVICE_ID_WRAPPER devIDs, FuncRemoveDeviceFromSession cbRemoveDeviceFromSession, DWORD dwUser);

// 7.6 ��ȡ�Ự���������豸ParaId=0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetLeadingDevice(USHORT uSessionID, FuncGetLeadingDevice cbGetLeadingDevice, DWORD dwUser);

// 7.7 ��ȡ�Ự�е��豸
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDevicesInSession(USHORT uSessionID, FuncGetAllConnectedDevices cbGetAllConnectedDevices, DWORD dwUser);

// 7.7 ��ȡ�����������豸ParaId=0x0009
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllConnectedDevices(FuncGetAllConnectedDevices cbGetAllConnectedDevices, DWORD dwUser);

// 7.8 ��ʼ¼��ParaId=0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StartRecording(USHORT uSessionID, FuncStartRecording cbStartRecording, DWORD dwUser, string strFileName = "");

// 7.9 ֹͣ¼��ParaId=0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StopRecording(USHORT uSessionID, FuncStopRecording cbStopRecording, DWORD dwUser);

// 7.10 ���ûỰ����ParaId=0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetVolume(USHORT uSessionID, BYTE nVolume, FuncSetVolume cbSetVolume, DWORD dwUser);

// 7.11 ���û���ЧParaId=0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SetAudio(USHORT uSessionID, INT nAudio, FuncSetAudio cbSetAudio, DWORD dwUser);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 8.��Դ���ݹ���(ManageResource) 0x08
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 8.1	�ϴ��ļ� 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UploadFile(NET_RESOURCE resource, FuncUploadFile cbUploadFile, FuncOperateResource cbOperateResource, DWORD dwUser);

// 8.2	�ϴ��ļ����ݣ������ݣ� 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UploadDataInFile(USHORT uSesionID, string strData, FuncUploadDataInFile cbUploadDataInFile, FuncOperateResource cbOperateResource, DWORD dwUser);

// 8.3	�ϴ��ļ�������� 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_FinishUploadingFile(USHORT uSessionID, FuncFinishUploadingFile cbFinishUploadingFile, FuncOperateResource cbOperateResource, DWORD dwUser);

// 8.4	ȡ���ϴ��ļ� 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelUploadingFile(USHORT uSessionID, FuncCancelUploadingFile cbCancelUploadingFile, DWORD dwUser);

// 8.5	���ϴ�����ļ�λ�� 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPosOfUploadedFile(USHORT uSessionID, FuncGetPosOfUploadedFile cbGetPosOfUploadedFile, DWORD dwUser);

// 8.6	�����ļ� 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DownloadFile(RECORD_FILE file, FuncDownloadFile cbDownloadFile, DWORD dwUser);

// 8.7	�����������ļ����� 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SendFileByServer(/*string strData,*/ FuncSendFileByServer cbSendFileByServer, DWORD dwUser);
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RecvDataFromServer(FuncRecvDataFromServer cbRecvDataFromServer, DWORD dwUser);

// 8.8	���������������ļ����� 0x0008
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_FinishSendingFileByServer(/*USHORT uSessionID,*/ FuncFinishSendingFileByServer cbFinishSendingFileByServer, DWORD dwUser);

// 8.9	ȡ���ϴ����� 0x0009
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelUploadOrDownload(USHORT uSessionID, FuncCancelUploadOrDownload cbCancelUploadOrDownload, DWORD dwUser);

// 8.10 ����¼���ļ� 0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_FindRecordedFile(RECORD_QUERY query, FuncFindRecordedFile cbFindRecordedFile, DWORD dwUser);

// 8.11 �����ļ� 0x000B
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 8.12 �������ص�λ�� 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPosOfDownload(USHORT uSessionID, INT nDownloadPos, FuncGetPosOfDownload cbGetPosOfDownload, DWORD dwUser);

// 8.13 ��ȡ���е��ϴ���Դ�ļ� 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllUploadedFiles(INT nFileType, FuncGetAllUploadedFiles cbGetAllUploadedFiles, DWORD dwUser);

// 8.14 �����ļ�ID��ȡ�ļ���Ϣ 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetFileInfo(INT nFileID, FuncGetFileInfo cbGetFileInfo, DWORD dwUser);

// 8.15 �����ļ�IDɾ���ļ� 0x000F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_DeleteFile(INT nFileID, FuncDeleteFile cbDeleteFile, DWORD dwUser);

// 8.16 �����ļ���Ϣ 0x0010
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateFile(NET_FILE file, FuncUpdateFile cbUpdateFile, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 9.Ѱ�����Խ�(ManageSpeaking) 0x09
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 9.1	Ѱ�� 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_Call(NET_SPEAK speak, FuncCall cbCall, DWORD dwUser);

// 9.2	�Խ� 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_Speak(NET_SPEAK speak, FuncSpeak cbSpeak, DWORD dwUser);

// 9.3	ֹͣѰ�� 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelCalling(USHORT uSessionID, FuncCancelCalling cbCancelCalling, DWORD dwUser);

// 9.4	ֹͣ�Խ� 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelSpeaking(USHORT uSessionID, FuncCancelSpeaking cbCancelSpeaking, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 10.�㲥(ManageBroadcast) 0x0A
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 10.1 �㲥��ʼ 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StartBroadcasting(NET_BROADCAST broadcast, FuncStartBroadcasting cbStartBroadcasting, FuncStartBroadcastingEx cbStartBroadcastingEx, DWORD dwUser);

// 10.2 0x0002
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 10.3 �㲥����Ƶ��ʽ���� 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_BroadcastAudio(MEDIA_FORMATE format, FuncBroadcastAudio cbBroadcastAudio, DWORD dwUser, string strHeadFormat);

// 10.4 0x0004
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 10.5 ������Ƶ���� 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_TransmitAudio(string strData, FuncTransmitAudio cbTransmitAudio, DWORD dwUser);

// 10.6 ֹͣ�㲥 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CancelBroadcasting(USHORT uSessionID, FuncCancelBroadcasting cbCancelBroadcasting, DWORD dwUser);

// 10.7 �и���� 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_SwitchSong(PLAY_CTRL ctrl, FuncSwitchSong cbSwitchSong, DWORD dwUser);

// 10.8 �㲥��ʱ�ļ� 0x0008
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_BroadcastTempFile(FuncBroadcastTempFile cbBroadcastTempFile, DWORD dwUser);

// 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 12. ��Ȩ����(ManageAuthority) 0x0C
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12.1 ��ȡע���� 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetMachineCode(FuncGetMachineCode cbGetMachineCode, DWORD dwUser);

// 12.2 ��ȡ֤����Ϣ 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetLicenseInfo(FuncGetLicenseInfo cbGetLicenseInfo, DWORD dwUser);

// 12.3 ֤����Ч����֤ 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_VerifyLicense(string strLicense, FuncVerifyLicense cbVerifyLicense, DWORD dwUser);

// 12.4 ע��֤�� 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RegisterLicense(string strLicense, FuncRegisterLicense cbRegisterLicense, DWORD dwUser);




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 13. ����ͷ�������
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 13.1	�������� 0x0001
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddTask(BASE_TASK task, INT nOperateType, FuncAddTask cbAddTask, DWORD dwUser);

// 13.2	�������� 0x0002
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdateTask(BASE_TASK task, INT nOperateType, DEVICE_ID_WRAPPER devIDs, LED_CTRL_TASK_ATTACH attach, FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.3	ɾ������ 0x0003
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTask(OPERATE_TASK oprTask, FuncRemoveTask cbRemoveTask, DWORD dwUser);

// 13.4	��������ID��ȡ������Ϣ 0x0004
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetTaskInfo(string strTaskID, FuncGetTaskInfo cbGetTaskInfo, DWORD dwUser);

// 13.5	��ȡ����������Ϣ 0x0005
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskInfo(FuncGetAllTaskInfo cbGetAllTaskInfo, DWORD dwUser);

// 13.6	���ݷ���ID��ȡ����������Ϣ 0x0006
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskView(string strPolicyID, FuncGetAllTaskView cbGetAllTaskView, DWORD dwUser);

// 13.7	��ȡ����ִ�������״̬ 0x0007
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskStatus(FuncGetAllTaskStatus cbGetAllTaskStatus, DWORD dwUser);

// 13.8	��ȡ������������s 0x00013
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskTypes(FuncGetAllTaskTypes cbGetAllTaskTypes, DWORD dwUser);

// 13.9	 0x0009
//IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_XXX(Func cb, DWORD dwUser);

// 13.10 ��������ID��ȡ�ļ����������б� 0x000A
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPlayTask(string strTaskID, FuncGetPlayTask cbGetPlayTask, DWORD dwUser);

// 13.11 �����ļ����Ÿ������� 0x000B
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPlayTaskAttach(PLAY_TASK_ATTACH attach, FuncAddPlayTaskAttach cbAddPlayTaskAttach, DWORD dwUser);

// 13.12 �����ļ����Ÿ������� 0x000C
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_UpdatePlayTaskAttach(PLAY_TASK_ATTACH attach, FuncUpdatePlayTaskAttach cbUpdatePlayTaskAttach, DWORD dwUser);

// 13.13 ɾ���ļ����Ÿ������� 0x000D
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemovePlayTaskAttach(string strTaskID, FuncRemovePlayTaskAttach cbRemovePlayTaskAttach, DWORD dwUser);

// 13.14 ��������ID��ȡ�豸���� 0x000E
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetBCDeviceByTaskID(string strTaskID, FuncGetBCDeviceByTaskID cbGetBCDeviceByTaskID, DWORD dwUser);

// 13.15 ��������ID��ȡ�����豸��Ϣ 0x000F
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDeviceByTaskID(string strTaskID, FuncGetDeiveByTaskID cbGetDeiveByTaskID, DWORD dwUser);

// 13.16 ���ӻ�ɾ������������豸 0x0010
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddOrDelPlayingDevice(string strDeviceID, FuncAddOrDelPlayingDevice cbAddOrDelPlayingDevice, DWORD dwUser);

// 13.17 ��������Id��ȡ���������е��ļ��б� 0x00011
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPlayingFilesByTaskID(string strTaskID, FuncGetPlayingFilesByTaskID cbGetPlayingFilesByTaskID, DWORD dwUser);

// 13.18 ���ӻ�ɾ�����������е��ļ��б� 0x00012
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddOrDelPlayingFiles(string strAbsoluteFilePath, FuncAddOrDelPlayingFiles cbAddOrDelPlayingFiles, DWORD dwUser);

// 13.19 ��������Id��ȡ�ɲ�����������Ϣ 0x00013
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAcquicastAttach(string strTaskID, FuncGetAcquicastAttach cbGetAcquicastAttach, DWORD dwUser);

// 13.20 ���Ӳɲ��������� 0x0014
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddAcquicastAttach(BC_TASK_ATTACH attach, FuncAddAcquicastAttach cbAddAcquicastAttach, DWORD dwUser);

// 13.21 �޸Ĳɲ���������(ParaId=0x0015)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyAcquicastAttach(BC_TASK_ATTACH attach, FuncModifyAcquicastAttach cbModifyAcquicastAttach, DWORD dwUser);

// 13.22 ɾ���ɲ���������(ParaId=0x0016)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveAcquicastAttach(string strTaskID, FuncRemoveAcquicastAttach cbRemoveAcquicastAttach, DWORD dwUser);

// 13.23 ��ȡ��ʱ����(ParaId=0x0017)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetTimingConfig(string strTaskID, FuncGetTimingConfig cbGetTimingConfig, DWORD dwUser);

// 13.24 ���Ӷ�ʱ����(ParaId=0x0018)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddTimingConfig(TIMING_TASK task, FuncAddTimingConfig cbAddTimingConfig, DWORD dwUser);

// 13.25 // �ظ���

// 13.26 ɾ����ʱ����(ParaId=0x001A)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTimingConfig(string strTaskID, FuncRemoveTimingConfig cbRemoveTimingConfig, DWORD dwUser);

// 13.27 ��ȡ�������񷽰�(ParaId=0x001B)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskPolicy(FuncGetAllTaskPolicy cbGetAllTaskPolicy, DWORD dwUser);

// 13.28 ���ݷ���ID��ȡ����ʵ��(ParaId=0x001C)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetTaskPolicy(string strPolicyID, FuncGetTaskPolicy cbGetTaskPolicy, DWORD dwUser);

// 13.29 �������񷽰�(ParaId=0x001D)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddTaskPolicy(TASK_POLICY policy, INT nOperateType, FuncAddTaskPolicy cbAddTaskPolicy, DWORD dwUser);

// 13.30 �������񷽰�(ParaId=0x001E)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyTaskPolicy(TASK_POLICY policy, INT nOperateType, FuncModifyTaskPolicy cbModifyTaskPolicy, DWORD dwUser);

// 13.31 ɾ�����񷽰�(ParaId=0x001F)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTaskPolicy(string strPolicyID, FuncRemoveTaskPolicy cbRemoveTaskPolicy, DWORD dwUser);

// 13.32 ���ӷ����е�����(ParaId=0x0020) ���ӹ㲥����
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddBCTaskIntoPolicy(string strPolicyID, BASE_TASK task, DEVICE_FOR_TASK device, PLAY_TASK_ATTACH attach, 
	FILE_FOR_TASK file,FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 ���ӷ����е�����(ParaId=0x0020) ���ӵ�Դ����
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddPowerTaskIntoPolicy(string strDeviceID, BASE_TASK task, SWITCH_FOR_TASK switcher,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 ���ӷ����е�����(ParaId=0x0020) ���Ӳɼ����� 
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddACTaskIntoPolicy(string strPolicyID, BASE_TASK task, DEVICE_FOR_TASK device, BC_TASK_ATTACH attach,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 ���ӷ����е�����(ParaId=0x0020) ����LED��������
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AddLEDTaskIntoPolicy(string strPolicyID, BASE_TASK task, DEVICE_FOR_TASK device, LED_CTRL_TASK_ATTACH attach,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 �޸ķ����е�����(ParaId=0x0020) �޸Ĺ㲥����ʹ���
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyBCTask(/*string strPolicyID, */BASE_TASK task, DEVICE_FOR_TASK device, PLAY_TASK_ATTACH attach, FILE_FOR_TASK file,
	FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 �޸ķ����е�����(ParaId=0x0020) �޸ĵ�Դ����
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyPowerTask(string strDeviceID, BASE_TASK task, SWITCH_FOR_TASK switcher,
	FuncAddTaskIntoPolicy cbAddTaskIntoPolicy, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 �޸ķ����е�����(ParaId=0x0020) �޸Ĳɼ����� 
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyACTask(/*string strPolicyID,*/ BASE_TASK task, DEVICE_FOR_TASK device, BC_TASK_ATTACH attach,
	FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.32 �޸ķ����е�����(ParaId=0x0020) �޸�LED��������
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ModifyLEDTask(/*string strPolicyID, */BASE_TASK task, DEVICE_FOR_TASK device, LED_CTRL_TASK_ATTACH attach,
	FuncUpdateTask cbUpdateTask, DWORD dwUser, TIMING_TASK tmTask = {});

// 13.33 �ӷ�����ɾ������(ParaId=0x0021)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_RemoveTaskFromPolicy(string strPolicyID, string strTaskID, FuncRemoveTaskFromPolicy cbRemoveTaskFromPolicy, DWORD dwUser);

// 13.34 ��������(ParaId=0x0023)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StartTask(string strTaskID, FuncStartTask cbStartTask, DWORD dwUser, INT nTaskType = -1);

// 13.35 ֹͣ����(ParaId=0x0024)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_StopTask(string strTaskID, FuncStopTask cbStopTask, DWORD dwUser);

// 13.36 ��ȡ��Դ����������Ϣ(ParaId=0x0025)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPowerSwithTask(string strTaskID, FuncGetPowerSwithTask cbGetPowerSwithTask, DWORD dwUser);

// 13.37 ��ȡ���м�����Ϣ(ParaId=0x0026)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllTaskLevels(FuncGetAllTaskLevels cbGetAllTaskLevels, DWORD dwUser);

// 13.38 ��ȡȫ����ָ������ID��LED����������Ϣ(ParaId=0x0027)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllLedCtrlTaskAttach(OPERATE_TASK oprTask, FuncGetAllLedCtrlTaskAttach cbGetAllLedCtrlTaskAttach, DWORD dwUser);

// 13.39 ��������ID��ȡLED����������Ϣ(ParaId=0x0028)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetLedCtrlTaskAttach(string strTaskID, FuncGetLedCtrlTaskAttach cbGetLedCtrlTaskAttach, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 14.�ͻ��˻�ȡ״ָ̬��(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 14.1 ��ȡ���б����豸״̬��Ϣ(ParaId=0x0014)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmDevStatus(FuncGetAllAlarmDevStatus cbGetAllAlarmDevStatus, DWORD dwUser);

// 14.2 ����IP��ȡ�����豸״̬��Ϣ(ParaId=0x0015)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmDevStatus(string strDeviceIP, FuncGetAlarmDevStatus cbGetAlarmDevStatus, DWORD dwUser);

// 14.3 ����IP�ͱ���ͨ��ȷ�ϱ���(ParaId=0x0018)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_ConfirmAlarm(IP_ALARM_CHANNEL channel, FuncConfirmAlarm cbConfirmAlarm, DWORD dwUser);

// 14.4 ��ȡ���е�Դ��״̬��Ϣ(ParaId=0x0019)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllPowerStatus(FuncGetAllPowerStatus cbGetAllPowerStatus, DWORD dwUser);

// 14.5 ����IP��ȡ��Դ�豸״̬��Ϣ(ParaId=0x001A)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetPowerStatus(string strDeviceIP, FuncGetPowerStatus cbGetPowerStatus, DWORD dwUser);

// 14.6 �ͻ��˿��Ƶ�Դ�Ŀ����(ParaId=0x001D)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CtrlPowerSwitchByIP(IP_ALARM_CHANNEL channel, INT nCtrlStatus, FuncCtrlPowerSwitchByIP cbCtrlPowerSwitchByIP, DWORD dwUser);

// 14.7 ��ȡ���н����豸��״̬��Ϣ(ParaId=0x001E)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllDeviceStatus(FuncGetAllDeviceStatus cbGetAllDeviceStatus, DWORD dwUser);

// 14.8 �����豸ID��ȡ�豸��״̬��Ϣ(ParaId=0x001F)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDevStatusByID(INT nDeviceID, FuncGetDevStatusByID cbGetDevStatusByID, DWORD dwUser);

// 14.9 �����豸IP��ȡ�豸��״̬��Ϣ(ParaId=0x0020)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetDevStatusByIP(string strDeviceIP, FuncGetDevStatusByIP cbGetDevStatusByIP, DWORD dwUser);

// 14.10 ���Ƶ�Դ�Ŀ����(ParaId=0x0021)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_CtrlPowerSwitchByID(IP_ALARM_CHANNEL channel, INT nCtrlStatus, FuncCtrlPowerSwitchByID cbCtrlPowerSwitchByID, DWORD dwUser);

// 14.11 ��ȡ���о�ʾ��״̬��Ϣ(ParaId=0x0022)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAllAlarmLightStatus(FuncGetAllAlarmLightStatus cbGetAllAlarmLightStatus, DWORD dwUser);

// 14.12 �����豸ID��ȡ��ʾ��״̬��Ϣ(ParaId=0x0023)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_GetAlarmLightStatus(int nDeviceID, FuncGetAlarmLightStatus cbGetAlarmLightStatus, DWORD dwUser);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 15.�����������豸״̬(Status) 0x21
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 15.1	�����������豸״̬�仯(ParaId=0x0001)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetDeviceStatus(FuncAutoGetDeviceStatus cbAutoGetDeviceStatus, DWORD dwUser);

// 15.2	���������ͻỰ״̬�仯(ParaId=0x0002)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetSessionStatus(FuncAutoGetSessionStatus cbAutoGetSessionStatus, DWORD dwUser);

// 15.3	���������ͻỰ��ֹ��Ϣ(ParaId=0x0003)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetSessionTerminal(FuncAutoGetSessionTerminal cbAutoGetSessionTerminal, DWORD dwUser);

// 15.4	���������������û�״̬�仯(ParaId=0x0004)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetUserStatus(FuncAutoGetUserStatus cbAutoGetUserStatus, DWORD dwUser);

// 15.5	��������������״̬�仯(ParaId=0x0005)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetTaskStatus(FuncAutoGetTaskStatus cbAutoGetTaskStatus, DWORD dwUser);

// 15.6	���������ͷ���״̬�仯(ParaId=0x0005)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetPolicyStatus(FuncAutoGetPolicyStatus cbAutoGetPolicyStatus, DWORD dwUser);

// 15.17	�����������豸��ͨ��״̬�仯(ParaId=0x0017)
IPCAST_SDK_API BOOL decl_fun AEBELL_IPCAST_AutoGetChannelStatus(FuncAutoGetChannelStatus cbAutoGetChannelStatus, DWORD dwUser);

EXTERN_C_END_DECL