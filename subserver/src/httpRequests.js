/**
 * Created by wangweizhen on 2017/11/28.
 */

var request = require('request');
var commonModule = require('../src/commonModuleExport');
const logger = commonModule.logger.getLogger();
const constants = commonModule.constants;
var globalData = require('./globalDataCache');
const MAX_RETRY_CNT = 30;
var retryCount = 0;

/**
 * 请求协议数据，缓存到本地
 */
var requestProtocol = function () {
    return new Promise((resolve, reject) => {
        request.post({
            url: constants.POST_URL.PROTOCOL,
            form: {'orgCode': 86, 'identifyingCode': 0}
        },
        (err, httpResponse, body) => {
            let protoDataCache = {};
            let relaCache = {};
            if (err) {
                logger.error('请求协议数据失败: ' + err.message);
                if (++retryCount < MAX_RETRY_CNT) {
                    setTimeout(requestProtocol, 2000);
                }
                return;
            }
            try {
                let data = JSON.parse(body);
                if (data) {
                    let protocol = data.protocol;
                    for (let pro in protocol) {
                        protoDataCache[pro] = JSON.parse(protocol[pro]);
                    }
                    let rela = data.rela;
                    for (let r in rela) {
                        relaCache[r] = protoDataCache[rela[r]];
                    }
                    retryCount = 0;
                    globalData.setProtoDataCache(protoDataCache);
                    globalData.setRelaCache(relaCache);
                    logger.info('协议数据初始化成功！');
                    resolve(true);
                }
            } catch (err) {
                logger.error('协议数据解析错误: ' + err.message);
                resolve(null);
            }
        });
    });
};

/**
 * 请求运行参数数据，缓存到本地
 */
var requestRunParam = function () {
    return new Promise((resolve, reject) => {
        request.post({
            url: constants.POST_URL.RUN_PARAM,
            form: {'orgCode': 86, 'identifyingCode': 0}
        },
        (err, httpResponse, body) => {
            let runParam = {};
            if (err) {
                logger.error('请求运行参数失败: ' + err.message);
                if (++retryCount < MAX_RETRY_CNT) {
                    setTimeout(requestRunParam, 2000);
                }
                return;
            }
            try {
                let params = JSON.parse(body);
                if (params) {
                    for (let i = 0, len = params.length; i < len; i++) {
                        let param = params[i];
                        runParam[param.systemType + param.urlType] = param;
                    }
                    retryCount = 0;
                    globalData.setRunParam(runParam);
                    logger.info('运行参数初始化成功！');
                    resolve(true);
                }
            } catch (err) {
                logger.error('运行参数解析错误: ' + err.message);
                resolve(null);
            }
        });
    });
};

/**
 * 请求区域数据，缓存到本地
 */
var requestOrg = function () {
    return new Promise((resolve, reject) => {
        request.post({
            url: constants.POST_URL.ORG, form: {deploy: 0}
        },
        (err, httpResponse, body) => {
            let orgMapping = {};
            if (err) {
                logger.error('查询地区编码关系失败: ' + err.message);
                if (++retryCount < MAX_RETRY_CNT) {
                    setTimeout(requestOrg, 2000);
                }
                return;
            }
            try {
                orgMapping = JSON.parse(body);
                retryCount = 0;
                globalData.setOrgMapping(orgMapping);
                logger.info('地区编码关系初始化成功！');
                resolve(true);
            } catch (err) {
                logger.error('查询地区编码关系解析错误: ' + err.message);
                resolve(null);
            }
        })
    })
};

var reqProtocol = async function () {
    await requestProtocol();
};
var reqOrg = async function () {
    await requestOrg();
};
var reqRunParam = async function () {
    await requestRunParam();
};

module.exports = {
    reqProtocol: reqProtocol,
    reqOrg: reqOrg,
    reqRunParam: reqRunParam
};



