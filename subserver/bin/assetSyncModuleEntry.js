/**
 * @file 资产同步服务 入口
 * @author yaoxinyu
 * @date 2017/10/23
 */

var childProcessMgr = require('../src/childProcessMgr');
const constants = require('../src/commonModuleExport').constants;

/**
 * 开启服务
 */
var start = function () {
    childProcessMgr.startProcess(constants.SERVER_TYPE.ASSETSYNC);
};

/**
 * 停止服务
 */
var stop = function () {
    childProcessMgr.stopProcess(constants.SERVER_TYPE.ASSETSYNC);
}

start();
module.exports = {
    start: start,
    stop: stop
};