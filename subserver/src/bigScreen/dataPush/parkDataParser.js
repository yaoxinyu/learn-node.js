/**
 * @file 停车数据解析模块
 * @author yaoxinyu
 * @date 2018/1/30
 */

var logger = require('../../common/util/logger').getLogger(0);
var linkAffairDao = require('../../linkAffair/DB/linkAffairDao');

function ParkDataParser() {
    /**
     * 整合缓存中停车数据
     */
    this.mergeCacheParkData = function (cacheData, parkData) {
        // 重新计算空闲车位数
        try {
            let num = Number(parkData.num);
            if (cacheData) {
                num += Number(cacheData.num);
            }
            parkData.num = num;
        } catch (exception) {
            logger.error('大屏推送-计算空闲停车位异常：', exception);
        }
    };
}


var parser = new ParkDataParser();
module.exports = parser;
