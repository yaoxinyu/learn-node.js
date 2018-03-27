/**
 * Created by panxiang on 2018/1/8.
 */
var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);


var mqUtil = require('../activeMQMgr');
var dbManage = require('../storageMgr');
var httpClientUtil = require('../common/util/httpClientUtil');
var globalCathe = require('../globalDataCache');

/**
 * getHostUrl: 获得hosturl
 * @return
 *      返回hostUrl
 * by 潘翔 on 2018/1/7
 */
function getHostUrl() {
    let configData = globalCathe.getConfigData();
    var host = configData.httpConfig.host;
    var port = configData.httpConfig.port;
    hosturl = 'http://' + host + ':' + port;
    return hosturl;
}

/**
 * WebBuisHttpHandler:Web业务http处理器，包括发送http请求和响应http的请求
 * @param
 *      data:业务数据
 *      httpBusiHandlers
 * by 潘翔 on 2017/12/23
 */
function WebBusiHttpHandler(data, httpBusiHandlers) {
    let m_data = data;
    let m_hosturl = getHostUrl();
    let configData = globalCathe.getConfigData();
    let m_projectName = configData.httpConfig.projectName;
    let m_httpBusiHandlers = httpBusiHandlers;

    //let m_schedule = schedule;

    /**
     * getDataOptCmd:给定param的操作码返回data的操作码
     * @param
     *      paramOptCmd : I类数据的操作码
     * @return
     *      返回的操作码
     *  by 潘翔 on 2018/1/8
     */
    function getDataOptCmd(paramOptCmd)
    {
        switch(paramOptCmd) {
            case 'safe_param_6012':
                return 'safe_data_9012';
            case 'safe_param_6013':
                return 'safe_data_9013';
            case 'safe_param_6014':
                return 'safe_data_9014';
            case 'safe_param_6015':
                return 'safe_data_9015';
            case 'safe_param_6016':
                return 'safe_data_9016';
            case 'safe_param_6017':
                return 'safe_data_9017';
            case 'safe_param_6018':
                return 'safe_data_9018';
            case 'safe_param_6019':
                return 'safe_data_9019';
            case 'safe_param_6021':
                return 'safe_data_9021';
            default:
                return '';
        }
    }

    /**
     * getBusiHttpOption: 获得业务相关的httpOption
     * @return
     *      返回业务的httpOption
     * by 潘翔 on 2018/1/7
     */
    this.getHttpReqOption = async function () {
        var httpOption = new httpClientUtil.httpReqOptions();
        var assetNo = m_data.header.assetNo;
        let deviceId = await dbManage.queryVideoIdByDeviceId(assetNo);
        if(!deviceId) {
            logger.error('没有查询到对应资产编号[%s]的摄像机Id', assetNo);
            return;
        }
        logger.info('查询到资产编号[%s]的摄像机ID是[%s]', assetNo, deviceId);
        httpOption.url = m_hosturl + m_projectName;
        httpOption.data = {};
        httpOption.headers = {};
        httpOption.headers['Content-Type'] = 'application/json';
        getHttpOptionByOptCmd(m_data.header.optCmd, httpOption, deviceId);
        logger.info('发送视频平台业务的的httpOption数据是:%s', JSON.stringify(httpOption));
        return httpOption;
    }

    /**
     * getResultBodyJson:根据业务组装获得返回结果body体(是一钟json格式)
     * @param
     *      error:错误对象
     *      response:响应对象
     *      body:响应对象的body体
     *  by 潘翔 on 2018/1/18
     */
    function getResultBodyJson(error, response, body) {
        let resultBodyJson = {};
        switch(m_data.header.optCmd) {
            case 'safe_param_6015':
            case 'safe_param_6016':
            case 'safe_param_6017':
            case 'safe_param_6018':
            case 'safe_param_6019':
                resultBodyJson = getPtzTriggerVideoResultBody(error, response, body);
                break;
            case 'safe_param_6013':
                resultBodyJson = getQueryVideoListResultBody(error, response, body);
                break;
            case 'safe_param_6021':
                resultBodyJson = getPtzTriggerVideoResultBody(error, response, body);
                break;
            default:
                resultBodyJson = null;
        }
        return resultBodyJson;
    }

    /**
     * getPtzTriggerVideoResultBody:获得云台控制、触发录像和触发截图和录像配置返回结果body体(是一种json格式)
     * @param
     *      error:错误对象
     *      response:响应对象
     *      body:响应对象的body体
     *  by 潘翔 on 2018/1/18
     */
    function getPtzTriggerVideoResultBody(error, response, body) {
        let resultBodyJson = {};
        resultBodyJson.code = 100;
        do {
            if(error) {
                logger.error('与视频平台通讯有异常[%s]', error.code);
                resultBodyJson.code = 300;
                resultBodyJson.msg = error.message;
                break;
            }
            if(response) {
                logger.info('视频平台回复状态码：', response.statusCode);
                if (response.statusCode == 200) {
                    logger.info('收到视频平台返回的录像列表是[%s]', JSON.stringify(body));
                    body = (typeof body == 'string') ? (JSON.parse(body)) : body;
                    logger.info('业务[%s]收到视频服务返回的信息body体是:[%s]', m_data.header.optCmd, JSON.stringify(body));
                    if (body.retCode == -1) {
                        resultBodyJson.msg = (body.retMsg) ? body.retMsg : '';
                    } else {
                        resultBodyJson.code = 200;
                        resultBodyJson.msg = '正常回复';
                    }
                } else if (response.statusCode == 400) {
                    resultBodyJson .msg = '参数不正确';
                } else if (response.statusCode == 500) {
                    resultBodyJson.msg = '服务器异常';
                } else {
                    resultBodyJson.msg = '其他错误';
                }
            }
        } while(false);
        logger.info('返回的录像列表内容是[%s]',JSON.stringify(resultBodyJson));
        return resultBodyJson;
    }

    /**
     * getQueryVideoListResultBody:获得查询录像列表返回结果body体(是一钟json格式)
     * @param
     *      error:错误对象
     *      response:响应对象
     *      body:响应对象的body体
     *  by 潘翔 on 2018/1/18
     */
    function getQueryVideoListResultBody(error, response, body) {
        let result = null;
        if(response) {
            logger.info('视频平台回复状态码：', response.statusCode);
            if(response.statusCode == 200) {
                logger.info('收到视频平台返回的录像列表是[%s]', JSON.stringify(body));
                if(body.retCode == 0) {
                    result = body.dataList;
                }
            }
        }
        if(error) {
            logger.error('与视频平台通讯有异常[%s]', error.code);
        }
        if(result) {
            logger.info('返回的录像列表内容是[%s]',JSON.stringify(result));
        }
        return result;
    }

    /**
     * convertVideoPlatformData:转换视频平台返回的数据为内部的数据
     * @param
     *      error:错误对象
     *      response:响应对象
     *      body:响应对象的body体对象
     * by 潘翔 on 2018/1/16
     */

    function convertVideoPlatformData(error, response, body) {
        let dataOptCmd = getDataOptCmd(m_data.header.optCmd);
        if(dataOptCmd) {
            let resultJson = {};
            resultJson.header = {};
            resultJson.header.assetNo = m_data.header.assetNo;
            resultJson.header.requestTime = m_data.header.requestTime;
            resultJson.header.equipType = m_data.header.equipType;
            resultJson.header.responseTime = new Date().getTime();
            resultJson.header.optCmd = dataOptCmd;
            resultJson.header.dataSource = m_data.header.dataSource;
            resultJson.header.code = 200;
            resultJson.header.msg = '正常回复';
            resultJson.data = getResultBodyJson(error, response, body);
            return resultJson;
        } else {
            logger.error('没有找到对应[%s]返回的操作项', m_data.header.optCmd);
            return null;
        }
    }

    /**
     * onBusiHttp:响应业务http请求返回的结果
     * @param
     *      error:错误的信息
     *      response:http请求得到的回复
     *      body:http请求得到回复的body体
     * by 潘翔 on 2018/1/7
     */
    this.callback = function(error, response, body) {
        let result = convertVideoPlatformData(error, response, body);
        if(result) {
            if(m_httpBusiHandlers) {
                m_httpBusiHandlers.addResult(result);
            } else {
                logger.info('发送给MQ的内容是[%s]', JSON.stringify(result));
                mqUtil.sendBusiDataForII(result);
            }
        } else {
            logger.error('转换的结果为空，可能是没有找到返回的操作码导致的');
        }
    }

    /**
     * getHttpOptionByOptCmd:根据optCmd获得httpOption
     * @param
     *      optCmd:业务类型
     *      httpOption:待填充的httpOption
     * @return
     *      返回组装好的httpOption
     * by 潘翔 on 2018/1/7
     */
    function getHttpOptionByOptCmd(optCmd, httpOption, deviceId) {
        switch (optCmd) {
            case 'safe_param_6010'://云台控制开始，不需要返回, Get
            case 'safe_param_6011'://云台控制结束，不需要返回, Get
            case 'safe_param_6020'://云台PTZ控制
            case 'safe_param_6021'://设置预置位
                setPTZControlBusiHttpOpt(httpOption, deviceId);
                break;
            case 'safe_param_6012'://视频播放, Get
                setPlayVideoBusiHttpOpt(httpOption, deviceId);
                break;
            case 'safe_param_6013'://录像列表查询
                setQueryRecordListBusiHttpOpt(httpOption, deviceId);
                break;
            case 'safe_param_6014'://截图列表查询
                setQueryScreenshotListBusiHttpOpt(httpOption, deviceId);
                break;
            case 'safe_param_6015'://触发录像(自动停止)
                setTriggerVideoBusiHttpOpt(httpOption, 0, 0, deviceId);
                break;
            case 'safe_param_6016'://触发录像(手动开始)
                setTriggerVideoBusiHttpOpt(httpOption, 1, 0, deviceId);
                break;
            case 'safe_param_6017'://触发录像(手动结束)
                setTriggerVideoBusiHttpOpt(httpOption, 1, 1, deviceId);
                break;
            case 'safe_param_6018'://触发截图
                setTriggerScreenshotBusiHttpOpt(httpOption, deviceId);//这个也可以合并的
                break;
            case 'safe_param_6019'://录像设置
                setRecordPlanBusiHttpOpt(httpOption, deviceId);
                break;
            default:
                break;
        }
    }

    /**
     * getHttpOption:填充云台控制的httpOption
     * @param
     *      httpOption:待填充的httpOption
     * by 潘翔 on 2018/1/7
     */
    function setPTZControlBusiHttpOpt(httpOption, deviceId) {
        httpOption.method = 'Get';
        httpOption.url += '/services/preview/ptzControl';
        httpOption.data.deviceId = deviceId;
        httpOption.data.command = m_data.body.command;
        httpOption.data.param = m_data.body.params;
        httpOption.data.orientation = m_data.body.orientation;
        httpOption.data.speed = m_data.body.speed;
    }

    /**
     * getHttpOption:填充播放视频的httpOption
     * @param
     *      httpOption:待填充的httpOption
     *      deviceId:摄像机Id
     * by 潘翔 on 2018/1/7
     */
    function setPlayVideoBusiHttpOpt(httpOption, deviceId) {
        httpOption.method = 'Get';
        httpOption.url += '/services/preview/getWsUrl';
        httpOption.data.type = m_data.body;
        httpOption.data.deviceId = deviceId;
    }

    /**
     * getHttpOption:填充查询录像列表的httpOption
     * @param
     *      httpOption:待填充的httpOption
     *      deviceId:摄像机Id
     * by 潘翔 on 2018/1/7
     */
    function setQueryRecordListBusiHttpOpt(httpOption, deviceId) {
        httpOption.method = 'POST';
        httpOption.url += '/services/record/recordFilePath';
        httpOption.data.devId = deviceId;
        httpOption.data.beginTime = m_data.body.beginTime * 1000;
        httpOption.data.endTime = m_data.body.endTime * 1000;
        httpOption.data.recordMode = '1';
    }

    /**
     * getHttpOption:填充视频截图的httpOption
     * @param
     *      httpOption:待填充的httpOption
     *      deviceId:摄像机Id
     * by 潘翔 on 2018/1/7
     */
    function setQueryScreenshotListBusiHttpOpt(httpOption, deviceId) {
        httpOption.method = 'POST';
        httpOption.url += '/services/record/searchScreenshot';
        httpOption.data.beginTime = m_data.body.beginTime * 1000;
        httpOption.data.endTime = m_data.body.endTime * 1000;
        httpOption.data.devId = deviceId;
    }

    /**
     * getHttpOption:填充触发录像的httpOption
     * @param
     *      httpOption:待填充的httpOption
     *      recordMode:录像模式
     *      command:触发命令
     *      deviceId:摄像机ID
     * by 潘翔 on 2018/1/7
     */
    function setTriggerVideoBusiHttpOpt(httpOption, recordMode, command, deviceId) {
        httpOption.method = 'POST';
        httpOption.url += '/services/record/manualRecord';
        httpOption.data.devId = deviceId;
        httpOption.data.recordMode = recordMode;
        httpOption.data.command = command;
        if (recordMode == 0) {//自动结束
            httpOption.data.duration = m_data.body.duration;
            httpOption.data.preRecTime = m_data.body.preRecTime;
            httpOption.data.streamType = m_data.body.streamType;
        } else {
            httpOption.data.duration = 0;
            if (command == 0) {//手动开始
                httpOption.data.preRecTime = m_data.body.preRecTime;
                httpOption.data.streamType = m_data.body.streamType;
            } else {//手动结束
                httpOption.data.preRecTime = 0;
                httpOption.data.streamType = 0;
            }
        }
        httpOption.interval = 0;
        httpOption.maxSnapNum = 0;
        httpOption.startOffset = 0;
    }

    /**
     * getHttpOption:填充触发截图的httpOption
     * @param
     *      httpOption:待填充的httpOption
     *      deviceId:摄像机Id
     * by 潘翔 on 2018/1/7
     */
    function setTriggerScreenshotBusiHttpOpt(httpOption, deviceId) {
        httpOption.method = 'POST';
        httpOption.url += '/services/record/manualRecord';
        httpOption.data.devId = deviceId;
        httpOption.data.recordMode = 1;
        httpOption.data.command = 0;
        httpOption.data.preRecTime = 2;
        httpOption.data.streamType = 0;
        httpOption.data.interval = m_data.body.interval;
        httpOption.data.maxSnapNum = m_data.body.maxSnapNum;
        httpOption.data.startOffset = m_data.body.startOffset;
    }

    /**
     * getHttpOption:填充录像计划的httpOption
     * @param
     *      httpOption:待填充的httpOption
     *      deviceId:摄像机Id
     * by 潘翔 on 2018/1/7
     */
    function setRecordPlanBusiHttpOpt(httpOption, deviceId) {
        httpOption.method = 'POST';
        httpOption.data.devId = deviceId;
        httpOption.url += '/services/record/recordplan';
        httpOption.data.audioRec = m_data.body.audioRec;
        httpOption.data.recordTime = m_data.body.recordTime;
        httpOption.data.preRecordTime = m_data.body.preRecordTime;
        httpOption.data.holdTime = m_data.body.holdTime;
        httpOption.data.streamType = m_data.body.streamType;
        httpOption.data.disable = m_data.body.disable;
        httpOption.data.dataList = m_data.body.dataList;
    }
}

/**
 * HttpReq:资产同步业务的http处理器，包括发送http请求和响应http的请求
 * @param
 *      data:业务数据
 *      assetType:表示资产同步的业务类型，增加，修改和删除
 * by 潘翔 on 2017/12/23
 */
function AssetBusiHttpHandler(data, assetType, callback) {
    let m_data = data;
    let m_hosturl = getHostUrl();
    let configData = globalCathe.getConfigData();
    let m_projectName = configData.httpConfig.projectName;
    let m_assetType = assetType;
    let m_func = callback;
    let m_sidArray = [];//sid数组
    let m_length;//设备的数量
    setSidArray();

    /**
     * getAssetHttpOption: 获得资产相关的httpOption
     * @return
     *      返回资产同步的httpOption
     * by 潘翔 on 2018/1/7
     */
    this.getHttpReqOption = function () {
        var httpOption = new httpClientUtil.httpReqOptions();
        httpOption.url = m_hosturl +  m_projectName;
        httpOption.url += '/services/device';
        if(m_assetType == 1 || m_assetType == 2) {
            httpOption.method = 'Post';
        } else {
            httpOption.method = 'Delete';
        }
        httpOption.headers = {};
        httpOption.headers['Content-Type'] = 'application/json';
        httpOption.data = m_data;
        return httpOption;
    }

    /**
     * callback:资产同步的回调函数
     * @param
     *      error:错误信息
     *      response:回复信息
     *      body:回复信息中的body信息
     * by 潘翔 on 2018/1/10
     */
    this.callback = function(error, response, body) {
        if(error) {
            assembleReturnValue(error.message);
            return;
        }
        if(response) {
            logger.info('同步资产:视频平台返回状态码：', response.statusCode);
            if (response.statusCode == 200) {
                logger.info('资产同步：视频服务返回的信息[%s]', JSON.stringify(body));
                assembleReturnValue(response.statusCode, body);
            } else {
                assembleReturnValue('错误码是:' + response.statusCode);
            }
        }
    };

    /**
     * getSidArray:通过传入的body信息获得sid数组
     * param
     *      jsonBody:传入的jsonbody信息
     * return
     *      返回送body中组装的sid数组
     * by 潘翔 on 2017/12/21
     */
    function setSidArray() {
        m_length = m_data.length;
        if(m_assetType == 2 || m_assetType == 3) {
            for (var i = 0; i < m_data.length; i++) {
                m_sidArray.push(m_data[i].sid);
            }
        }
    }

    /**
     * assembleReturnValue:通过回调函数组装返回的信息
     * @param
     *      statusMsg:视频服务的返回的信息（有回复时候并且正确的时候是数字，有回复但是是错误时是字符串，有error的时候回复字符串）
     *      retBody:视频服务返回的信息
     * by 潘翔 on 2017/12/19
     */
    function assembleReturnValue(statusMsg, retBody) {
        let code = 100;
        let msg = statusMsg;
        if (statusMsg == 200) {
            if (retBody.retCode == 0) {
                code = 200;
                msg = '资产同步成功';
                if ((m_assetType == 1) || (m_assetType == 2)) {
                    console.log('处理更新资产的业务');
                    m_sidArray = [];
                    for (let i = 0; i < retBody.dataList.length; i++) {
                        m_sidArray[i] = retBody.dataList[i].sid;
                    }
                }
            }
        }
        var returnValue = [];
        if ((code == 200) || (m_assetType == 2) || (m_assetType == 3)) {
            for (let i = 0; i < m_sidArray.length; i++) {
                var temp = {};
                temp.sid = m_sidArray[i];
                temp.code = code;
                temp.msg = msg;
                returnValue.push(temp);
            }
        } else {
            for (let i = 0; i < m_length; i++) {
                var temp = {};
                temp.sid = '';
                temp.code = code;
                temp.msg = msg;
                returnValue.push(temp);
            }
        }
        logger.info('资产同步返回给socket的信息[%s]', JSON.stringify(returnValue));
        m_func(returnValue)
    }
}

/**
 * HttpReq:发送Web发送业务数据
 * @param
 *      data:Web业务数据
 * by 潘翔 on 2018/1/7
 */
function WebHttpBusiReq(data, httpBusiHandlers) {
    let busiHttpHandler = {};
    let httpOption = {};
    this.sendHttpReq = async function () {
        busiHttpHandler = new WebBusiHttpHandler(data, httpBusiHandlers);
        httpOption = await busiHttpHandler.getHttpReqOption();
        let httpClient = new httpClientUtil.httpClient();
        httpClient.sendRequest(httpOption, busiHttpHandler.callback);
    }
}

/**
 * HttpReq:发送资产同步发业务数据
 * @param
 *      data:资产同步业务数据
 *      assetType:资产同步的类型 1:增加设备 2:修改设备 3:删除设备
 *      assetCallback:回调函数
 * by 潘翔 on 2018/1/7
 */
function AssetHttpBusiReq(data, assetType, assetCallback) {
    let busiHttpHandler = {};
    let httpOption = {};
    this.sendHttpReq = function () {
        busiHttpHandler = new AssetBusiHttpHandler(data, assetType, assetCallback);
        httpOption = busiHttpHandler.getHttpReqOption();
        let httpClient = new httpClientUtil.httpClient();
        httpClient.sendRequest(httpOption, busiHttpHandler.callback);

    }
}

module.exports = {
    webHttpBusiReq: WebHttpBusiReq,
    assetHttpBusiReq: AssetHttpBusiReq
};