/**
 * @file 事件发生记录器模块
 * @author wangWeiZHen
 * @date 2018/2/1
 */
var EventRecorder = function () {
    var recordMap = {};
    /**
     * 从数组移除某个value
     * @param arr 数组
     * @param item 数组元素
     * @return {*} 移除对应元素后的数组
     */
    var removeWithoutCopy = function (arr, item) {
        for (var i = 0; i < arr.length;) {
            if (item == arr[i]) {
                arr.splice(i, 1);
            } else {
                i++;
            }
        }
        return arr;
    };
    /**
     * 记录事件
     * @param key
     * @param eventTime
     */
    this.setRecord = function (key, eventTime) {
        if (recordMap[key]) {
            recordMap[key].push(eventTime);
        } else {
            recordMap[key] = [];
            recordMap[key].push(eventTime);
        }
    };
    /**
     * 删除时间缓存
     * @param key
     * @param subList
     */
    this.removeEventTimeList = function (key, subList) {
        for (let sub of subList) {
            recordMap[key] = removeWithoutCopy(recordMap[key], sub);
        }
    };
    /**
     * 根据key获取事件暂存列表
     * @param key
     * @return {*}
     */
    this.getRecord = function (key) {
        return recordMap[key];
    };
};

module.exports = new EventRecorder();