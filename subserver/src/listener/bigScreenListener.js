/**
 * Created by wangweizhen on 2018/1/17.
 */
var webSocketMgr = require('../wsClientMgr');

function BigScreenListener() {
    /**
     * 大屏截图II类协议数据
     * @param header
     * @param data
     * @return {{header: *, imgData: *}}
     */
    var getShotDataII = function (header, data) {
        let resData = {
            'header': header,
            'imgData': data.imgData
        };
        return resData;
    };
    /**
     * 大屏发布II类协议数据
     * @param header
     * @param data
     * @return {{header: *, code: number, msg: number}}
     */
    var getReleaseDataII = function (header, data) {
        let resData = {
            'header': header,
            'code': data.code,
            'msg': data.code
        };
        return resData;
    };
    this.onMessage = function(msg) {
        let header = msg.header;
        let optCmd = header.optCmd;
        let data = msg.data;
        let resData;
        switch (optCmd){
            case 'media_data_9001':
                resData = getShotDataII(header, data);
                webSocketMgr.sendBusiDataForII(resData);
                break;
            case 'media_data_9100':
                resData = getReleaseDataII(header, data);
                webSocketMgr.sendBusiDataForII(resData);
                break;
            default:
                break;
        }
    };

}

module.exports = new BigScreenListener();