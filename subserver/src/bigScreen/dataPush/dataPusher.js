/**
 * @file 大屏数据推送模块
 * @author yaoxinyu
 * @date 2018/1/29
 */

/**
 * 大屏数据格式
 * 停车：{"js":"receiver({\"dataType\":\"park\",\"num\":-1,\"assetNo\":36})","type":"invokeJs"}
 * RFID：{"js":"receiver({\"dataType\":\"rfid\",\"data\":[{\"rfidCode\":\"123213\",\"interval\":20049}]})","type":"invokeJs"}
 * 环境：{"js":"receiver({\"dataType\":\"env\",\"temperature\":12.0,\"humidity\":20.0})","type":"invokeJs"}
 */

var logger = require('../../common/util/logger').getLogger(0);
var httpClient = require('../../common/util/httpClientUtil');
var linkAffairDao = require('../../linkAffair/DB/linkAffairDao');
var parkParser = require('./parkDataParser');
var rfidParser = require('./rfidDataParser');
var envParser = require('./envDataParser');
const PUSH_SPAN = 5000;  // 定时任务间隔

function DataPusher() {
    // 大屏数据缓存，结构为map<大屏数据类型, map<资产编号, 推送数据> >
    var dataCache = new Map();

    this.init = function () {
        // 启动定时推送任务，从缓存去数据，调用http模块推送
        logger.info('启动大屏推送定时任务.');
        setInterval(schedulePushTask, PUSH_SPAN);
    };

    /**
     * 定时推送任务
     */
    var schedulePushTask = async function () {
        // 遍历缓存
        for (let [dataType, dataList] of dataCache.entries()) {
            for (let [assetNo, data] of dataList.entries()) {
                // 查询大屏服务
                let pushData = buildReqData(data);
                let urlList = await getBigScreenUrl(dataType, assetNo);
                if (urlList && urlList.length > 0) {
                    urlList.forEach(function (url) {
                        pushData2Service(url, pushData);
                    });
                }
            }
            // 移除缓存
            dataCache.delete(dataType);
        }
    };

    /**
     * 推送大屏数据，对外接口
     * @param data JSON数据
     */
    this.pushScreenData = function (data) {
        // 调用数据解析模块，解析出数据，加入缓存
        if (!data || !data.header) {
            // 数据格式错误
            logger.error('数据格式错误，不做大屏推送！');
            return;
        }
        parseData(data);
    };

    /**
     * 解析数据
     * @param data
     */
    var parseData = function (data) {
        // 根据类型调用不用解析函数
        let optCmd = data.header.optCmd;
        switch (optCmd) {
            case 'rfid_data_9003':
            // RFID数据
                parseRfidData(data);
                break;
            case 'park_data_9011':
            // 停车数据
                parseParkData(data);
                break;
            case 'senset_data_9001':
            // 环境数据
                parseEnvData(data);
                break;
            case 'manhole_data_9017':
            // 水位数据 TODO
                break;
            default:
                logger.error('无法处理的待推送数据：', data);
                break;
        }
    };

    /**
     * 解析停车数据
     * @param data JSON
     */
    var parseParkData = async function (data) {
        try {
            // 对原始数据进行过滤，推送车位变化.
            // 状态类型（001：车位心跳，002：车位状态,003：基站状态,004：检测器校准）
            let statusType = data.statusType;
            // 车位状态（100-无车，200-有车（正常），300-异常（故障））
            let status = data.status;
            if ('002' === statusType && '300' != status) {
                // 筛选出车位状态类型+车位状态非异常的数据
                let freeSpotCnt = ('100' == status) ? 1 : -1;   // 空闲车位数量
                // 根据资产编号查询停车场信息
                let assetNo = data.header.assetNo;
                let placeInfo = await linkAffairDao.getSpotPlaceIdByAssetNo(assetNo);
                if (!placeInfo || !placeInfo.placeID) {
                    logger.error('大屏推送-停车场查询，根据编号[%s]未查询到配置的停车场！', assetNo);
                    return;
                }
                let pushParkData = {};
                pushParkData.assetNo = placeInfo.placeID; // 停车场ID
                pushParkData.dataType = 'park';
                pushParkData.num = freeSpotCnt;
                // 将待推送停车数据加入缓存
                logger.info('大屏推送-待推送停车数据：', pushParkData);
                addCache(pushParkData);
            }
        } catch (exception) {
            logger.error('解析停车数据异常：', exception);
        }
    };

    /**
     * 解析环境/气象数据
     * @param data JSON
     */
    var parseEnvData = function (data) {
        try {
            let jsonArray = data.data;
            if (jsonArray && jsonArray.length > 0) {
                let pushEnvData = {};
                for (let item of jsonArray) {
                    let code = item.code;
                    let value = item.value;  // 注意这里应该是double类型
                    envParser.addParam(code, value, pushEnvData);
                }
                if (JSON.stringify(pushEnvData) !== '{}') {
                    pushEnvData.dataType = 'env';
                    pushEnvData.assetNo = data.header.assetNo;
                    // 将待推送环境/气象数据加入缓存
                    logger.info('大屏推送-待推送环境/气象数据：', pushEnvData);
                    addCache(pushEnvData);
                }
            }

        } catch (exception) {
            logger.error('解析环境/气象数据异常：', exception);
        }
    };

    /**
     * 解析RFID数据
     * @param data JSON
     * @return {object} 返回推送数据
     */
    var parseRfidData = function (data) {
        try {
            let header = data.header;
            let assetNo = header.assetNo;
            let dtData = data.dataTime;  // long类型
            let jsonArray = data.data;
            if (jsonArray && jsonArray.length > 0) {
                jsonArray.forEach(function (item) {
                    let pushRfidData = {};
                    pushRfidData.rssi = item['lfrssi'];
                    pushRfidData.dtTime = dtData;
                    pushRfidData.rfidCode = item['tagId'];
                    pushRfidData.assetNo = assetNo;
                    pushRfidData.dataType = 'rfid';
                    // 将待推送RFID数据加入缓存
                    logger.info('大屏推送-待推送RFID数据：', pushRfidData);
                    addCache(pushRfidData);
                });
            }

        } catch (exception) {
            logger.error('解析RFID数据异常：', exception);
        }
    };

    /**
     * 将待推送数据加入缓存
     * @param pushData 待推送数据 JSON格式
     */
    var addCache = function (pushData) {
        if (pushData && (JSON.stringify(pushData) !== '{}')) {
            if (!pushData.dataType || !pushData.assetNo) {
                // dataType和assetNo值必须设置
                logger.error('大屏推送数据[%s]-dataType和assetNo值必须设置！', pushData);
                return;
            }
            // 合并同一个dataType的缓存数据
            let assetNo = pushData.assetNo;
            let dataType = pushData.dataType;
            let cacheData = dataCache.get(dataType);
            if (cacheData) {
                switch (dataType) {
                    case 'park':
                        parkParser.mergeCacheParkData(cacheData.get(assetNo), pushData);
                        break;
                    case 'rfid':
                        rfidParser.mergeCacheRfidData(cacheData.get(assetNo), pushData);
                        break;
                    case 'env':
                        break;
                    default:
                        break;
                }
                if (pushData && (JSON.stringify(pushData) !== '{}')) {
                    cacheData.set(assetNo, pushData);
                }
            } else {
                let tempMap = new Map();
                tempMap.set(assetNo, pushData);
                dataCache.set(dataType, tempMap);
            }
        }
    };

    /**
     * 组装完整的大屏推送数据格式 JSON格式
     * @param param
     * @return {object} 返回组装好的完整数据
     */
    var buildReqData = function (param) {
        let reqData = {};
        reqData.type = 'invokeJs';
        reqData.js = 'receiver(' + JSON.stringify(param) + ')';
        return reqData;
    };

    /**
     * 根据数据类型和资产编号获取大屏服务的url
     * @param dataType
     * @param assetNo
     * @return {Array} 大屏服务列表 可能是多个
     */
    var getBigScreenUrl = async function (dataType, assetNo) {
        let urlList = [];
        try {
            // 调用db查询大屏服务信息
            let screenServices = [];
            switch (dataType) {
                case 'park':
                // 传类型"1"+parkId
                    let parkId = Number(assetNo);
                    screenServices = await linkAffairDao.getBigScreenServiceByAssetNo(parkId, '1');
                    break;
                case 'rfid':
                // 传类型"2"+资产编号(拆分)
                    let rfidCode = assetNo.split('-')[0];
                    screenServices = await linkAffairDao.getBigScreenServiceByAssetNo(rfidCode, '2');
                    break;
                case 'env':
                // 传类型"2"+资产编号
                    screenServices = await linkAffairDao.getBigScreenServiceByAssetNo(assetNo, '2');
                    break;
                default:
                    break;
            }

            if (screenServices && screenServices.length > 0) {
                for (let service of screenServices) {
                    let url = 'http://' + service.ip + ':' + service.port + '/command/' + service.macAddr;
                    urlList.push(url);
                }
            }
        } catch (exception) {
            logger.error('获取大屏url出现异常：', exception.message);
        }

        return urlList;
    };

    /**
     * 通过http post推送大屏数据
     * @param url 大屏服务url
     * @param pushData 大屏推送数据
     */
    var pushData2Service = function (url, pushData) {
        logger.info('大屏推送开始：地址[%s]，数据[%s].', url, JSON.stringify(pushData));
        let requestOptions = new httpClient.httpReqOptions();
        requestOptions.url = url;
        requestOptions.method = 'POST';
        requestOptions.headers = {};
        requestOptions.headers['Content-Type'] = 'application/json';
        requestOptions.data = pushData;
        let httpReq = new httpClient.httpClient();
        httpReq.sendRequest(requestOptions, function (error, response, body) {
            if (error) {
                logger.error('地址[%s]，大屏推送请求出错：[%s]', url, error.toString());
            } else {
                if (response.statusCode == 200) {
                    logger.info('地址[%s]，大屏推送成功，数据[%s].', url, requestOptions);
                } else {
                    logger.error('地址[%s]，大屏推送失败，http状态码[%s].', url, response.statusCode);
                }
            }
        });
    };
}

// 唯一实例
var pusher = new DataPusher();
module.exports = pusher;
