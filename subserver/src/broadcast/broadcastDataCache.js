/**
 * @file 广播服务全局数据缓存
 * @author yaoxinyu
 * @date 2017/11/12
 */

// 共通函数模块
var commonFunc = require('../common/commonFunction');

function BroadcastDataCache() {
    // 任务协议头数据缓存
    var taskHeaderInfoMap = new Map();

    /**
     * 保存协议头数据
     * @param taskId
     * @param header 协议头JSON数据
     */
    this.setTaskHeadInfo = function (taskId, header) {
        taskHeaderInfoMap.set(taskId, commonFunc.clone(header));
    };

    /**
     * 获取对应任务的协议头数据
     * @param taskId
     * @return {object} 协议头JSON数据
     */
    this.getTaskHeadInfo = function (taskId) {
        return taskHeaderInfoMap.get(taskId);
    };

    /**
     * 移除协议头信息，任务处理完之后调用
     * @param taskId
     */
    this.removeTaskHeadInfo = function (taskId) {
        if (taskHeaderInfoMap.has(taskId)) {
            taskHeaderInfoMap.delete(taskId);
        }
    };
}


// 单例
var broadcastData = new BroadcastDataCache();
module.exports = broadcastData;