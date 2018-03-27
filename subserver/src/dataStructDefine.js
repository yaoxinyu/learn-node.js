/**
 * 一些共通的数据结构定义
 * @author yaoxinyu
 * @date 2017/12/1
 */


/**
 * 定义设备状态信息
 */
function DevStatusInfo() {
    this.assetNo;//资产编号
    this.onLine;//在线状态
    this.running;//运行状态
    this.onLineChanged;//在线状态变更时间
    this.runningChanged;//运行状态变更
    this.userModify;//
}

/**
 * 定义广播状态信息
 */
function BroadcastStatusInfo() {
    this.deviceId;
    this.responseTime;
    this.status;
    this.uVolume;
}

/**
 * 定义事件状态信息
 */
function EventStatusInfo() {
    this.deviceId;//设备id
    this.eventTime;//事件时间
    this.orgCode;//行政单位编号
    this.roadId;//路段id
    this.eventCode;//事件编码，对应code_type_id=1001
    this.eventSecondTypeCode;//设备小类型（具体到各类型设备的告警类型）
}


// 任务操作信息
var dataStruct = {};
dataStruct.devStatus = new DevStatusInfo();                 // 设备状态信息
dataStruct.broadcastStatus = new BroadcastStatusInfo();     // 广播状态信息
dataStruct.eventStatus = new EventStatusInfo();             // 事件状态信息


module.exports = dataStruct;