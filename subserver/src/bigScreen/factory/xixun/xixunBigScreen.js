/**
 * @file 熙讯大屏操作处理
 * Created by yaoxinyu on 2018/3/21.
 */

var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);
var xxRequest = require('./xixunCommon');
var xxScreenPrint = require('./xxBigScreenPrint');
var xxScreenPublish = require('./xxBigScreenPublish');

function XixunBigScreen() {
    /**
     * 处理大屏截图
     * @param req 请求消息 JSON格式
     */
    this.dealScreenPrint = function (req) {
        logger.info('处理熙讯大屏截图：', req);
        let header = req.header;
        let assetNos = header.assetNo;
        if (!assetNos) {
            logger.error('熙讯大屏截图任务资产编号为空！');
            return;
        }

        let requestTime = header.requestTime;
        let interval = Number(req.interval) * 1000; // 截图间隔
        let num = req.num; // 截图数量
        let arrAssetNos = assetNos.split('|');
        arrAssetNos.forEach(function (assetNo) {
            let screenPrint = new xxScreenPrint(assetNo, num, interval, requestTime);
            screenPrint.sendRequest();
        });
    };

    /**
     * 处理大屏发布
     * @param req 请求消息 JSON格式
     */
    this.dealScreenPublish = function (req) {
        logger.info('处理熙讯大屏发布：', req);
        let header = req.header;
        let assetNos = header.assetNo;
        if (!assetNos) {
            logger.error('熙讯大屏发布任务资产编号为空！');
            return;
        }

        let requestTime = header.requestTime;
        let reqUrl = req.url;
        let arrAssetNos = assetNos.split('|');
        arrAssetNos.forEach(function (assetNo) {
            let screenPublish = new xxScreenPublish(assetNo, reqUrl, requestTime);
            screenPublish.sendRequest();
        });
    };

    /**
     * 处理大屏推送
     * @param req 请求消息 JSON格式
     */
    this.dealScreenPush = function (req) {
        logger.info('处理熙讯大屏推送：', req);
        // TODO 获取大屏url
        let url = null;
        // TODO 构造请求option
        let data = null;
        // 发送请求
        xxRequest.sendHttpRequest(url, data, null);
    };
}

var xxBigScreen = new XixunBigScreen();
module.exports = xxBigScreen;

