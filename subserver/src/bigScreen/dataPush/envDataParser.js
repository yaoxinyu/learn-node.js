/**
 * @file 环境/气象数据解析模块
 * @author yaoxinyu
 * @date 2018/1/30
 */

var logger = require('../../common/util/logger').getLogger(0);

function EnvDataParser() {
    /**
     * 根据code和value为推送数据添加参数
     * @param code
     * @param value
     * @param pushData 待推送大屏的环境/气象数据
     */
    this.addParam = function (code, value, pushData) {
        switch (code) {
            case '101':
            //101空气温度
                pushData['temperature'] = value;
                break;
            case '102':
            //102相对湿度
                pushData['humidity'] = value;
                break;
            case '103':
            //103瞬时风速
                pushData['windSpeed'] = value;
                break;
            case '104':
            //104瞬时风向
                pushData['windDirection'] = value;
                break;
            case '105':
            //105分钟雨量
                pushData['rainfall'] = value;
                break;
            case '106':
            //106光照度值
                pushData['illumination'] = value;
                break;
            case '107':
            //107气压压强
                pushData['pressure'] = value;
                break;
            case '108':
            //108系统电压
                pushData['voltage'] = value;
                break;
            case '503':
            //503一氧化氮
                pushData['no'] = value;
                break;
            case '504':
            //504二氧化氮
                pushData['no2'] = value;
                break;
            case '505':
            //505一氧化碳
                pushData['co'] = value;
                break;
            case '506':
            //506二氧化碳
                pushData['co2'] = value;
                break;
            case '507':
            //507臭氧
                pushData['o3'] = value;
                break;
            case '508':
            //508二氧化硫
                pushData['so2'] = value;
                break;
            case '509':
            //509PM1.0
                pushData['pm1.0'] = value;
                break;
            case '510':
            //510PM2.5
                pushData['pm2.5'] = value;
                break;
            case '511':
            //511PM10
                pushData['pm10'] = value;
                break;
            case '512':
            //512总挥发性有机化合物
                pushData['tvoc'] = value;
                break;
            case '513':
            //513硫化氢
                pushData['h2s'] = value;
                break;
            default:
                break;
        }
    };
}


var parser = new EnvDataParser();
module.exports = parser;