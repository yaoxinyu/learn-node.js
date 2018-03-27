/**
 * @file RFID数据解析模块
 * @author yaoxinyu
 * @date 2018/1/30
 */

var logger = require('../../common/util/logger').getLogger(0);

function RfidDataParser() {
    /**
     * 整合缓存中RFID数据
     */
    this.mergeCacheRfidData = function (cacheData, rfidData) {
        try {
            let dtTime = Number(rfidData.dtTime);
            let rfidCode = rfidData.rfidCode;
            let assetNo = rfidData.assetNo;
            //计算时间差 单位（分钟）
            let curTime = new Date().getTime();
            let interval = (curTime - dtTime) / 1000 / 60;
            if (interval > 60) {
                rfidData = null;
                return;
            }

            if (cacheData != null) {
                let dataArray = cacheData.data;
                // 逆序遍历，防止移除数组元素时导致遍历出错
                for (let i = dataArray.length - 1; i >= 0; i--) {
                    let tempRfidCode = dataArray[i].rfidCode;
                    if (tempRfidCode != rfidCode) {
                        continue;
                    }
                    if (interval > 60) {
                        dataArray.splice(i, 1);
                    } else {
                        dataArray[i].interval = interval;
                    }
                }
            } else {
                // 缓存中没有该assetNo的RFID数据
                rfidData = {};
                rfidData.assetNo = assetNo + '-' + rfidCode;
                rfidData.dataType = 'rfid';
                rfidData.data = [];
                let tempData = {};
                tempData.interval = interval;
                tempData.rfidCode = rfidCode;
                rfidData.data.push(tempData);
            }
        } catch (exception) {
            logger.error('大屏推送-整合RFID数据异常：', exception);
        }
    };
}


var parser = new RfidDataParser();
module.exports = parser;