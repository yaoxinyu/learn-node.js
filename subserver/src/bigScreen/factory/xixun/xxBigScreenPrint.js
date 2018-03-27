/**
 * @file 熙讯大屏截图类
 * Created by yaoxinyu on 2018/3/22.
 */

var bigScreenCommon = require('../../bigScreenCommon');
var xxCommon = require('./xixunCommon');

/**
 * 带参数构造
 * @param assetNo 资产编号
 * @param picNum 截图数量
 * @param interval 截图间隔 整型
 * @param requestTime 请求时间
 * @constructor
 */
function XXBigScreenPrint(assetNo, picNum, interval, requestTime) {
    this.assetNo = assetNo;
    this.picNum = picNum;
    this.interval = interval ? (interval < 3000 ? 3000 : interval) : 3000; // TODO
    this.requestTime = requestTime ? requestTime : new Date().getTime();

    /**
     * 发送大屏截图请求
     * @return {Promise.<void>}
     */
    this.sendRequest = async function () {
        let reqInfo = getReqInfo();
        let bigScreenUrl = await xxCommon.getBigScreenUrl(assetNo); // TODO 大屏url
        for (let i = 0; i < this.picNum; i++) {
            xxCommon.sendHttpRequest(bigScreenUrl, reqInfo, onScreenPrintResponse);
            // sleep
        }
    };

    /**
     * 获取大屏截图请求
     * @return {{type: string, fn: string, arg1: number, arg2: number}}
     */
    var getReqInfo = function () {
        let reqInfo = {
            'type': 'callCardService',
            'fn': 'screenshot',
            'arg1': 100, //quality
            'arg2': 100 //scale
        };
        return reqInfo;
    };

    /**
     * 处理大屏截图http响应
     * @param err
     * @param response
     * @param body
     */
    var onScreenPrintResponse = function (err, response, body) {
        // if (err) {
        //     logger.error("资产编号为：" + devCode + ",第" + (i + 1) + "张截图错误" + err.message.toString());
        //     resData = getResData(devCode, requestTime, 100, err.message, imgUrl);
        // } else {
        //     try {
        //         let img;
        //         if (body) {
        //             img = JSON.parse(body).result;//解析请求来的base64格式的截图
        //         } else {
        //             return;
        //         }
        //         imgUrl = savePicture(devCode, i + 1, img);
        //         resData = getResData(devCode, requestTime, 200, "OK", imgUrl);
        //     } catch (err) {
        //         resData = getResData(devCode, requestTime, 100, err.message, imgUrl);
        //     }
        // }
        // 发送回复
        // bigScreenCommon.sendScreenPrintRes();
    };

    /**
     * 保存截图到本地
     * @param assetNo
     * @param i
     * @param imgData
     */
    var savePicture = function (assetNo, i, imgData) {
        // let imaDirPath = fileUtil.getRootPath();
        // let year = new Date().getYear()+1900;
        // let month = new Date().getMonth()+1;
        // let day = new Date().getDate();
        // fileUtil.mkDir(imaDirPath);
        // let name =commonModule.constants.PICTURE_PATH + year + "/" + month + "/" + day + "/" + assetNo + "/" + new Date().getTime() + assetNo + i + ".png";
        // var base64Data = imgData.replace(/^data:image\/\w+;base64,/, "");
        // var dataBuffer = new Buffer(base64Data, 'base64');
        // try {
        //     fs.writeFileSync(imaDirPath + name, dataBuffer);
        // } catch (error) {
        //     // 文件夹不存在，或者权限错误
        //     logger.error("截图保存出错", error.message);
        //     return null;
        // }
        // logger.info("截图保存成功！");
        // return name;
    };
}

module.exports = XXBigScreenPrint;