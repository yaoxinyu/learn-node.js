/**
 * 用于封装Http发送查询设备状态和回调函数
 * @author 潘翔
 * @date 2017/11/27
 */


var mqUtil = require('../activeMQMgr');
var globalCathe = require('../globalDataCache');
var httpClientUtil = require('../common/util/httpClientUtil');
var commonModule = require('../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

/**
 * getHostUrl:获得http请求中Ip地址和端口
 * @return
 *      返回IP地址和端口
 * by 潘翔 on 2018/1/10
 */

function getHostUrl() {
    let configData = globalCathe.getConfigData();
    var host = configData.httpConfig.host;
    var port = configData.httpConfig.port;
    hosturl = 'http://' + host + ':' + port;
    return hosturl;
}

/**
 * CameraEventSubHttpHandler:摄像机事件订阅的http请求处理器,
 * @constructor
 */
function CameraEventSubHttpHandler() {
    let m_hosturl = getHostUrl();
    let configData = globalCathe.getConfigData();
    let m_projectName = configData.httpConfig.projectName;

    /**
     * callback:响应事件订阅的回调函数(暂时不做处理)
     * @param
     *      error:错误对象
     *      response:应答对象
     *      body:应答对象中的body对象
     * by 潘翔 on 2018/1/10
     */
    this.callback = function(error, response, body) {

    }

    /**
     * getHttpOption:获得httpOption的格式（JSON）
     * @return
     *      返回JSON格式的HttpOption的请求格式
     * by 潘翔 on 2018/1/10
     */
    this.getHttpReqOption = function() {
        var httpOption = new httpClientUtil.httpReqOptions();
        httpOption.url = m_hosturl + m_projectName + '/services/subscribe/event';
        httpOption.method = 'POST';
        httpOption.headers = {};
        httpOption.headers['Content-Type'] = 'application/json';
        httpOption.data = {};
        httpOption.data.subscribeFlg = 1;
        httpOption.data.expires = 10;
        httpOption.data.subAddr = 'http://gw.subctrl.smartcitybase.com:9010/engima-sub/camera/push/event';
        httpOption.data.username = 'admin';
        httpOption.data.password = 'admin';
        httpOption.data.dataList = [];
        logger.info('发送视频平台事件订阅的httpOption是:[%s]', JSON.stringify(httpOption));
        return httpOption;
    }
}

/**
 * CameraEventSubHttpReq:发送事件订阅的Http请求
 * by 潘翔 on 2018/1/10
 */
function CameraEventSubHttpReq() {
    let cameraEventSubHttpHandler = {};
    let httpOption = {};
    this.sendHttpReq = function () {
        cameraEventSubHttpHandler = new CameraEventSubHttpHandler();
        httpOption = cameraEventSubHttpHandler.getHttpReqOption();
        let httpClient = new httpClientUtil.httpClient();
        httpClient.sendRequest(httpOption, cameraEventSubHttpHandler.callback);
    }
}

/**
 * CameraStatusSubHttpHandler:摄像机状态订阅的http请求处理器
 * @constructor
 */
function CameraStatusSubHttpHandler() {
    let m_hosturl = getHostUrl();
    let configData = globalCathe.getConfigData();
    let m_projectName = configData.httpConfig.projectName;

    /**
     * callback:响应状态订阅应答的回调函数(暂时不做处理)
     * @param
     *      error:错误对象
     *      response:应答对象
     *      body:应答对象中的body对象
     * by 潘翔 on 2018/1/10
     */
    this.callback = function(error, response, body) {

    }

    /**
     * getHttpOption:获得httpOption的格式（JSON）
     * @return
     *      返回JSON格式的HttpOption的请求格式
     * by 潘翔 on 2018/1/10
     */
    this.getHttpReqOption = function() {
        var httpOption = new httpClientUtil.httpReqOptions();
        httpOption.url = m_hosturl + m_projectName + '/services/subscribe/status';
        httpOption.method = 'POST';
        httpOption.headers = {};
        httpOption.headers['Content-Type'] = 'application/json';
        httpOption.data = {};
        httpOption.data.subscribeFlg = 1;
        httpOption.data.expires = 10;
        httpOption.data.subAddr = 'http://gw.subctrl.smartcitybase.com:9010/engima-sub/camera/push/status';
        httpOption.data.username = 'admin';
        httpOption.data.password = 'admin';
        httpOption.data.dataList = [];
        logger.info('发送视频平台状态订阅的httpOption是:[%s]', JSON.stringify(httpOption));
        return httpOption;
    }
}

/**
 * CameraStatusHttpReq:发送摄像机状态订阅的http请求
 * by 潘翔 on 2018/1/10
 */

function CameraStatusSubHttpReq() {
    let cameraStatusSubHttpHandler = {};
    let httpOption = {};
    this.sendHttpReq = function () {
        cameraStatusSubHttpHandler = new CameraStatusSubHttpHandler();
        httpOption = cameraStatusSubHttpHandler.getHttpReqOption();
        let httpClient = new httpClientUtil.httpClient();
        httpClient.sendRequest(httpOption, cameraStatusSubHttpHandler.callback);
    }
}

/**
 * QueryCameraStatusHttpHandler:发送查询录像机状态的http请求处理器
 * @constructor
 */

function QueryCameraStatusHttpHandler() {
    let m_hosturl = getHostUrl();
    let configData = globalCathe.getConfigData();
    let m_projectName = configData.httpConfig.projectName;

    /**
     * callback:处理请求摄像机状态的回调
     * @param
     *      error:错误对象
     *      response:应答对象
     *      body:应答中的body对象
     * by 潘翔 2018/1/10
     */
    this.callback = function(error, response, body) {
        let resultJosn = {};
        if(error) {
            logger.error('与视频平台通讯有异常[%s]', error);
            return;
        }
        if(response) {
            logger.info('视频平台有回复[%d]', response.statusCode);
            if(response.statusCode == 200) {
                logger.info('接收到摄像机状态的数据:%s', JSON.stringify(body));
                resultJosn.header = {};
                resultJosn.header.assetNo = '';
                resultJosn.header.equipType = null;
                resultJosn.header.optCmd = 'safe_data_9005';
                resultJosn.header.requestTime = 0;
                resultJosn.header.responseTime = new Date().getTime();
                resultJosn.header.dataSource = 0;
                resultJosn.header.code = 200;
                resultJosn.header.msg = '正常回复';
                resultJosn.data = body;
                mqUtil.sendBusiDataForII(resultJosn);
            } else if(response.statusCode == 500){
                logger.error('查询摄像机状态时，收到视频平台回复的是:服务器异常');
            } else if(response.statusCode == 400) {
                logger.error('查询摄像机状态时，收到视频平台回复的是:参数不正确');
            }
        }
    };

    /**
     * getHttpOption:获得httpOption的格式（JSON）
     * @return
     *      返回JSON格式的HttpOption的请求格式
     * by 潘翔 on 2018/1/10
     */
    this.getHttpReqOption = function() {
        var httpOption = new httpClientUtil.httpReqOptions();
        httpOption.url = m_hosturl + m_projectName + '/services/device/cameraStatus';
        httpOption.method = 'POST';
        httpOption.headers = {};
        httpOption.headers['Content-Type'] = 'application/json';
        httpOption.data = {};
        httpOption.data.dataCount = 0;
        httpOption.data.dataList = '';
        logger.info('发送给视频平台查询状态的httpOption是:', JSON.stringify(httpOption));
        return httpOption;
    }
}

/**
 * QueryCameraStatusHttpReq:发送查询摄像机状态的Http请求
 * by 潘翔 on 2018/1/10
 */

function QueryCameraStatusHttpReq() {
    let queryCameraStatusHttpHandler = {};
    let httpOption = {};
    this.sendHttpReq = function () {
        queryCameraStatusHttpHandler = new QueryCameraStatusHttpHandler();
        httpOption = queryCameraStatusHttpHandler.getHttpReqOption();
        let httpClient = new httpClientUtil.httpClient();
        httpClient.sendRequest(httpOption, queryCameraStatusHttpHandler.callback);
    }
}

module.exports = {
    cameareEventSubHttpReq:CameraEventSubHttpReq,
    cameraStatusSubHttpReq:CameraStatusSubHttpReq,
    queryCameraStatusHttpReq:QueryCameraStatusHttpReq
};
