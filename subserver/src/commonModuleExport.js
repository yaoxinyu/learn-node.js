/**
 * @file 对外提供统一的公共组件引入服务
 * @author yaoxinyu
 * @date 2017/10/21
 */


// 常量定义组件
const constants = require('./common/constant');
// 错误定义组件
const errDef = require('./common/errorDefine');
// 日志组件
const logger = require('./common/util/logger');
// 文件工具类组件
const fileUtil = require('./common/util/fileUtil');
// 阻塞sleep
const sleep = require('./common/util/sleep');

module.exports = {
    constants: constants,
    errDef: errDef,
    logger: logger,
    fileUtil: fileUtil,
    sleep: sleep
};