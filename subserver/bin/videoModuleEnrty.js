/**
 * @file 视频服务 入口
 * @author 潘翔
 * @date 2017/11/24
 */

var childProcessMgr = require('../src/childProcessMgr');
const constants = require('../src/commonModuleExport').constants;

/**
 * 开启服务
 */
var start = function () {
    childProcessMgr.startProcess(constants.SERVER_TYPE.VIDEO);
};

/**
 * 停止服务
 */
var stop = function () {
    childProcessMgr.stopProcess(constants.SERVER_TYPE.VIDEO);
}

start();
module.exports = {
    start: start,
    stop: stop
};