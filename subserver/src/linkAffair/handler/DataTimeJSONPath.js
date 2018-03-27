/**
 * @file optCmd与表达式映射关系模块
 * @author wangWeiZHen
 * @date 2018/1/31
 */
/**
 * optCmd与表达式映射关系
 * @constructor
 */
var DataTimeJSONPath = function () {
    var JSONPathMap = {
        'ad_data_9001': '$.alarmTime',
        'ad_data_9003': '$.alarmTime',
        'ad_data_9500': '$.deviceTypeTime',
        'park_data_9011': '$.time_status',
        'manhole_data_9001': '$.dataTime'
    };
    /**
     * 通过optCmd得到表达式
     * @param optCmd
     * @return {*} 获取时间的表达式
     */
    this.getJSONPathMap = function (optCmd) {
        let JSONPath = JSONPathMap[optCmd];
        return JSONPath ? JSONPath : '$.header.responseTime';
    }
};

module.exports = new DataTimeJSONPath();

