/**
 * @file 熙讯大屏请求类
 * Created by yaoxinyu on 2018/3/21.
 */

var httpClientUtil = require('../../../common/util/httpClientUtil');
var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function XixunCommon() {
    /**
     * 获取熙讯大屏url
     * @param assetNo 资产编号
     * @param optCmd
     */
    this.getBigScreenUrl = function (assetNo, optCmd) {
        // TODO 除了停车数据不一样其他查询一样？
        // 返回大屏服务url信息，可能是多个
        // let ip = "localhost";
        // let port = "8080";
        // let remark = await storageMgr.queryRemarkByAssetNo(devCode);
        // let result = await storageMgr.queryIpAndPortByAssetNo(devCode);
        // if (!result) {
        //     logger.error("资产编号为：" + devCode + "，未查询到ip和port");
        //     return;
        // }
        // ip = result.ip;
        // port = result.port;
        // url = ip + ":" + port + "/command/" + remark;
    };

    /**
     * 发送熙讯大屏http请求
     * @param url
     * @param data 请求数据 JSON格式
     * @param cb http响应回调
     */
    this.sendHttpRequest = function (url, data, cb) {
        let httpOptions = new httpClientUtil.httpReqOptions();
        httpOptions.url = url;
        httpOptions.method = 'POST';
        httpOptions.headers = {'Content-Type': 'application/json; charset=UTF-8'};
        httpOptions.data = data;

        let httpClient = new httpClientUtil.httpClient();
        logger.info('发送熙讯大屏http请求：', httpOptions);
        httpClient.sendRequest(httpOptions, (err, response, body) => {
            if (cb) {
                cb(err, response, body);
            }
        });
    };
}

var xxCommon = new XixunCommon();
module.exports = xxCommon;