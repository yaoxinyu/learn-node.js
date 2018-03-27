/**
 * @file 共通协议组装
 * @author yaoxinyu
 * @date 2017/12/25
 */


/**
 * 协议组装
 * @constructor
 */
function PackProtocol() {
    /**
     * 组装II类协议头
     * @param assetNo
     * @param equipType
     * @param dataSource
     * @param optCmd
     * @param requestTime
     * @param responseTime
     * @param code
     * @param msg
     * @return {{}}
     */
    this.packProtocolHeaderII = function (assetNo, equipType, dataSource, optCmd, requestTime, responseTime, code, msg) {
        let header = {};
        header.assetNo = assetNo ? assetNo : '';
        header.equipType = equipType ? equipType : null;
        header.requestTime = requestTime ? requestTime : 0;
        header.responseTime = responseTime ? responseTime : (new Date().getTime());
        header.dataSource = dataSource ? dataSource : '0';  // 0：分控系统
        header.code = code ? code : 200;
        header.msg = msg ? msg : 'OK';
        return header;
    };

    /**
     * 组装II类告警协议数据
     * @param header 组装好的II类协议头
     * @param alarmTime
     * @param alarmList
     */
    this.packProtocolAlarmII = function (header, alarmTime, alarmList) {
        let alarmData = {};
        alarmData.header = {};
        alarmData.header = header;
        alarmData.header.optCmd = 'ad_data_9001';
        alarmData.alarmTime = alarmTime;
        alarmData.data = Array.from(alarmList);
        return alarmData;
    };

    /**
     * 组装II类设备状态数据
     * @param header 组装好的II类协议头
     * @param statusTime
     * @param deviceType
     * @param onlineType
     */
    this.packProtocolDevStatusII = function (header, statusTime, deviceType, onlineType) {
        let statusData = {};
        statusData.header = {};
        statusData.header = header;
        statusData.header.optCmd = 'ad_data_9500';
        statusData.deviceTypeTime = statusTime;
        statusData.deviceType = deviceType;
        statusData.onlineType = onlineType;
        return statusData;
    };
}


var packProtocol = new PackProtocol();
module.exports = packProtocol;