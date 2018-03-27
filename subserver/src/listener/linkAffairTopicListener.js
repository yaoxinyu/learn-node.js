/**
 * @file 事务联动数据
 * @author wangweizhen
 * @date 2018/1/29
 */


var commonModule = require('../commonModuleExport');
// 日志模块
var LogicOperation = require('../linkAffair/handler/logicOperation');


function LinkAffairTopicListener() {
    /**
     * MQ消息回调并处理
     * @param msg JSON格式
     */
    this.onMessage = function (msg) {
        //
        LogicOperation.handleMessage(msg);
    };
}


var linkAffairListener = new LinkAffairTopicListener();
module.exports = linkAffairListener;