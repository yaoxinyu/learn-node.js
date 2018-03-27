/**
 * Created by wangweizhen on 2018/1/30.
 */
var linkAffModel = function () {
    //资产事务联动动作配置信息
    this.actionEvent = {
        'actionId': null,//动作ID
        'eventCode': null,//事件编码
        'deviceType': null//资产类型
    };

    //资产事务联动动作条件信息
    this.actionCondition = {
        'acId': null,//动作条件表主键
        'abId': null,//动作ID
        'condition': null,//JSON格式的动作条件参数
        'unitTime': null//单位时间，单位是分钟
    };

    //资产事务联动动作参数
    this.actionConditionParams = {
        'ampId': null,//动作方式参数配置自增ID
        'abId': null,//动作配置ID
        'actionCode': null,//具体动作，实时监控（1:拍照，2：录像，3：播放），广播喊话（1:音频，2：喊话）
        'actionMode': null,//1：实时监控，2：广播喊话，3：文字提示，4：GIS闪动
        'actionParam': null//以json的格式存储，动作对应的参数
    };

    //查询资产信息
    this.assetInfo = {
        'assetName': null,//资产名称
        'firstType': null,//资产大类码值含义
        'secondType': null,//资产小类码值含义
        'eventName': null//事件名称
    };

    //设备与监控参数配置信息
    this.deviceInfo = {
        'adpId': null,//设备与监控参数配置自增ID
        'ampId': null,//动作方式参数id
        'deviceId': null,//监控设备ID
        'monitorDeviceId': null,//联动设备id
        'deviceNo': null,//监控设备资产编号
        'monitorDeviceNo': null,//联动设备资产编号
        'actionCode': null,//具体动作，实时监控（1:拍照，2：录像，3：播放），广播喊话（1:音频，2：喊话）
        'actionParam': null//以json的格式存储，动作对应的参数，点击地图上的图标进行设置的
    };

    //停车被监控设备最近的联动设备
    this.parkDevice = {
        'monitorDeviceNo': null //资产编号
    };

    //联系地址
    this.concatNumber = {
        'emailAddress': null,//邮件地址
        'phoneNumber': null,//手机号码
        'orgCode': null,//地区编码
        'concatName': null//姓名
    };

    //邮件服务器配置信息
    this.emailConfig = {
        'serverConfig': null//配置项，以JSON格式存储
    };

    //有效日期
    this.actionTimeReal = {
        'abId': null,//动作ID
        'dtValidBegin': null,//有效起始日期
        'dtValidEnd': null//有效截止日期
    };

    //表达式
    this.actionEventVar = {
        'varName': null,//变量名称
        'varCode': null//变量编码
    };

    //动作ID周期设置
    this.actionCycleReal = {
        'abId': null,//动作ID
        'cycleDay': null,//日显示31个1和0组成的字符串，周显示7个0和1组成的字符串
        'cycleHour': null//小时的集合，显示24个0和1组成的字符串
    };

    //视频播放信息
    this.videoInfo = {
        'orgCode': null,//地区编码
        'usiCamId': null//国创平台摄像头ID
    };

    //最近的联动设备
    this.cameraDevice = {
        'monitorDeviceNo': null//资产编号
    };

    //服务的ip、端口
    this.serviceInfo = {
        'ip': null,//服务ip
        'port': null//服务端口
    };

    //资产数据
    this.assetData = {
        'deviceID': null,//主键
        'equipType': null,//型号
        'macAddr': null,//物理地址
        'factoryCode': null,//生产厂家编号
        'firstTypeCode': null,//大类号
        'secondTypeCode': null,//小类号
        'orgNo': null,//组织编号
        'lampID': null,//上级设备id
        'roadID': null//道路id
    };

    // 显示的大屏资产
    this.bigScreenInfo = {
        'bigScreenAssetNo': null,//大屏资产编号
        'macAddr': null,//物理地址
        'serviceId': null//服务ID
    }

    //动作日志相关参数
    this.actionLogParams = {
        'actionName': null,//动作名称
        'eventLevel': null,//事件等级
        'eventName': null,//事件名
        'orgCode': null,//地区编码
        'orgName': null,//地区名
        'deviceId': null,//设备ID
        'roadName': null//路段名
    }


};

module.exports = new linkAffModel();