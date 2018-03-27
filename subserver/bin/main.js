/**
 * 本模块启动入口
 *  date : 2017-10-11
 *  author : yaoxinyu
 */

var app = require('../app');
var commonModule = require('../src/commonModuleExport');
const constants = commonModule.constants;
const logger = commonModule.logger.getLogger();

process.on('uncaughtException', function (err) {
    logger.error('主进程捕获uncaughtException: ', err);
});

logger.info('主进程启动[pid=%s]...', process.pid);
// http服务启动
app.listen(constants.HTTP_SERVER.PORT);
logger.info('http服务启动，监听端口：', constants.HTTP_SERVER.PORT);
// WebSocket服务启动
var server = require('./websocketServer');
server.start();