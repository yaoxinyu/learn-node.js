/**
 * @file 广播服务 入口
 * @author yaoxinyu
 * @date 2017/10/21
 */

var childProcessMgr = require('../src/childProcessMgr');
const constants = require('../src/commonModuleExport').constants;

/**
 * 开启服务
 */
var start = function () {
    childProcessMgr.startProcess(constants.SERVER_TYPE.BROADCAST);
};

/**
 * 停止服务
 */
var stop = function () {
    childProcessMgr.stopProcess(constants.SERVER_TYPE.BROADCAST);
}

start();
module.exports = {
    start: start,
    stop: stop
};


