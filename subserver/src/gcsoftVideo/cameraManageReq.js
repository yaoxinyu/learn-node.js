/**
 * 用于封装H摄像机管理(增加，修改，删除)的Http请求
 *  在返回的时候将sid返回即可
 * @author 潘翔
 * @date 2017/12/08
 */
var commonModule = require('../commonModuleExport');
var busiHttpReq = require('./httpBusiReq.js');
const logger = commonModule.logger.getLogger(0);

function CameraManageReq() {
    /**
     * addCamear:增加摄像机(可以批量增加)
     * @param
     *      data:待增加摄像机相关的信息(数组中存放若干个json对象),是JSON数组
     *      addCallback 增加设备的回调函数，将异步http的结果将调用这个回调函数
     *  by 潘翔 on 2017/12/11
     */
    this.addCamera = function (data, addDevCallback) {
        logger.info('增加摄像机,数据是[%s]', JSON.stringify(data));
        let httpReq = new busiHttpReq.assetHttpBusiReq(data, 1, addDevCallback);
        httpReq.sendHttpReq();
    };

    /**
     * modifyCamera:修改摄像机(可以批量修改)
     * @param
     *      data:待修改摄像机相关的信息
     *      modifyDevCallback:修改设备回调函数，异步http结果将调用这个回调函数
     * by 潘翔 on 2017/12/11
     */
    this.modifyCamera = function (data, modifyDevCallback) {
        logger.info('修改摄像机,数据是[%s]', JSON.stringify(data));
        let httpReq = new busiHttpReq.assetHttpBusiReq(data, 2, modifyDevCallback);
        httpReq.sendHttpReq();
    };

    /**
     * deleteCamera:删除摄像机(可以批量删除)
     * @param
     *        待删除摄像机的信息(这里就是摄像机ID即可)
     *        将异步的结果将调用这个函数
     *  by 潘翔 on 2017/12/11
     */
    this.deleteCamera = function (data, delDevCallback) {
        logger.info('删除摄像机,数据是[%s]', JSON.stringify(data));
        let httpReq = new busiHttpReq.assetHttpBusiReq(data, 3, delDevCallback);
        httpReq.sendHttpReq();
    }
}

var cameraManageReq = new CameraManageReq();
module.exports = cameraManageReq;

