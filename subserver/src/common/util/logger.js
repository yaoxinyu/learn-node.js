/**
 * @file 导出日志类对象
 * @author yaoxinyu
 * @date 2017/9/15
 */

var log4js = require('log4js');
var fileUtils = require('./fileutil');
// 加载log4js的配置(注意log4js不同版本的配置文件写法不同)
var logConfigPath = fileUtils.path.join(fileUtils.getRootPath(), 'resource/log/log4js.json');
log4js.configure(logConfigPath);

// 导出的日志类对象
function logger() {
    /**
     * 导出日志对象
     * @param type 日志的类型
     * @return {Object} 日志对象
     */
    this.getLogger = function (type) {
        // switch (type) {
        //     case 0:
        //         return log4js.getLogger('subServer');
        //     case 1:
        //         return log4js.getLogger('request');
        //     case 2:
        //         return log4js.getLogger('db');
        //     default:
        //         return log4js.getLogger('subServer');
        // }
        return log4js.getLogger('console');
    };
}

module.exports = new logger();