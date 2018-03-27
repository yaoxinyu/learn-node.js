/**
 * @file 熙讯大屏发布类
 * Created by yaoxinyu on 2018/3/22.
 */

var bigScreenCommon = require('../../bigScreenCommon');
var xxCommon = require('./xixunCommon');

/**
 * 带参数构造
 * @param assetNo
 * @param reqUrl
 * @param requestTime
 * @constructor
 */
function XXBigScreenPublish(assetNo, reqUrl, requestTime) {
    this.assetNo = assetNo;
    this.reqUrl = reqUrl;
    this.requestTime = requestTime ? requestTime : new Date().getTime();

    this.sendRequest = async function () {
        let reqInfo = getReqInfo();
        let bigScreenUrl = await xxCommon.getBigScreenUrl(assetNo); // TODO 大屏url
        xxCommon.sendHttpRequest(bigScreenUrl, reqInfo, onScreenPublishResponse);
    };

    var getReqInfo = function () {
        let url = this.reqUrl + (this.reqUrl.indexOf('?') > 0 ? '&' : '?') + 'assetNo=' + this.assetNo;
        let reqInfo = {
            'type': 'callXwalkFn',
            'fn': 'loadUrl',
            'arg': {
                'url': url,
                'backupUrl': '', //备用地址(可省略不填),没网时自动加载此地址,
                'persistent': true, //持久化，重启会自动加载url
                'extra': {} //额外数据(可省略), 它的值可以为任意类型，,在网页里使用window.$extra获取
            }
        };
        return reqInfo;
    };

    /**
     * 处理大屏截图http响应
     * @param err
     * @param response
     * @param body
     */
    var onScreenPublishResponse = function (err, response, body) {
        // if (err) {
        //     logger.error("大屏服务加载网页失败：", err.message);
        //     resData = getResData(devCode, requestTime, 100, err.message);
        //     activeMQMgr.sendBusiDataForII(resData);
        // } else {
        //     logger.error("大屏服务加载网页成功：", body);
        //     resData = getResData(devCode, requestTime, 100, "OK");
        //     activeMQMgr.sendBusiDataForII(resData);
        // }
        // 发送回复
        // bigScreenCommon.sendScreenPublishRes();
    };
}

module.exports = XXBigScreenPublish;