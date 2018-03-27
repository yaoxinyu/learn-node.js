/**
 * @file 大屏共通类
 * Created by yaoxinyu on 2018/3/22.
 */

var activeMQMgr = require('../activeMQMgr');

function BigScreenCommon() {

}

BigScreenCommon.prototype = {
    /**
     * 发送大屏截图回复
     * @param assetNo
     * @param requestTime
     * @param errCode
     * @param errMsg
     * @param imgData 截图数据
     */
    sendScreenPrintRes: function (assetNo, requestTime, errCode, errMsg, imgData) {
        let resData = {
            'header': {
                'assetNo': assetNo,
                'equipType': null,
                'optCmd': 'media_data_9001',
                'requestTime': requestTime,
                'responseTime': new Date().getTime(),
                'dataSource': 0,
                'code': errCode,
                'msg': errMsg
            },
            'data': {
                'imgData': imgData
            }
        };

        // 发送到MQ
        activeMQMgr.sendBusiDataForII(resData);
    },

    /**
     * 发送大屏发布回复
     * @param assetNo
     * @param requestTime
     * @param errCode
     * @param errMsg
     */
    sendScreenPublishRes: function (assetNo, requestTime, errCode, errMsg) {
        let resData = {
            'header': {
                'assetNo': assetNo,
                'equipType': null,
                'optCmd': 'media_data_9100',
                'requestTime': requestTime,
                'responseTime': new Date().getTime(),
                'dataSource': 0,
                'code': errCode,
                'msg': errCode
            },
            'data': {
                'msg': errMsg,
                'code': errCode
            }
        };

        // 发送到MQ
        activeMQMgr.sendBusiDataForII(resData);
    }
};

module.exports = new BigScreenCommon();