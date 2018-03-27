/**
 * Created by wangweizhen on 2017/10/12.
 */
'use strict';

var commonModule = require('../commonModuleExport');
var logger = commonModule.logger.getLogger(0);
var assetOperation = require('./assetOperation');
var storageMgr = require('../../src/storageMgr');
var serverMgr = require('../serverMgr');
// 常量模块
const constants = commonModule.constants;
var cameraManageReq = require('../../src/gcsoftVideo/cameraManageReq');

function AssetServer() {
    /**
     * 初始化
     */
    this.init = function () {
        // TODO
    };

    /**
     * http推送的资产同步数据业务处理
     * @param data
     * @param res
     */
    this.assetSync = async function (data, res) {
        logger.info('收到资产同步请求数据：', data);
        let request = JSON.parse(data);
        let optCmd = request.optCmd;//数据同步的操作类型
        logger.debug('资产同步请求的optCmd: ', optCmd);
        var requestTime = request.requestTime;//发送请求的时间
        //响应客户端内容基本格式
        let response = {
            'requestTime': requestTime,
            'responseTime': null,
            'data': []
        };
        //响应客户端内容的变量
        let respData = {};
        switch (optCmd) {
            case 'asset_param_6001':
                respData = await assetSyncOpt(request, assetOperation.assetAdd);//资产同步，新增资产
                break;
            case 'asset_param_6002':
                respData = await assetSyncOpt(request, assetOperation.assetUpdate);//资产同步，更新资产
                break;
            case 'asset_param_6003':
                respData = await assetSyncOpt(request, assetOperation.assetDelete);//资产同步，删除资产
                break;
            case 'asset_param_6019':
                respData = broadcastSyncAdd(request);//广播同步，添加广播设备
                break;
            case 'asset_param_6020':
                respData = broadcastSyncModify(request);//广播同步，更新广播设备
                break;
            case 'asset_param_6021':
                respData = broadcastSyncDelete(request);//广播同步，删除广播设备
                break;
            case 'asset_param_6022':
                respData = await safeSync(request, safeSyncAdd);//视频同步，添加视频设备
                break;
            case 'asset_param_6023':
                respData = await safeSync(request, safeSyncModify);//视频同步，更新视频设备
                break;
            case 'asset_param_6024':
                respData = await safeSync(request, safeSyncDelete);//视频同步，删除视频设备
                break;
            default:
                logger.error('http同步请求命令未识别，optCmd=', optCmd);
                response.responseTime = new Date().getTime();
                let temData = {};
                temData.code = 100;
                temData.msg = '未识别的操作';
                response.data.push(temData);
                respData = response;
                break;
        }
        logger.info('http资产同步，http响应数据：', JSON.stringify(respData));
        res.writeHead(200, {'Content-Type': 'application/json'});
        res.write(JSON.stringify(respData));
        res.end();
    };

    /**
     * 资产同步，新增，修改，删除
     * @param request 请求的数据内容
     * @return 响应的数据
     */
    var assetSyncOpt = async function (request, func) {
        logger.debug('处理资产同步请求：', JSON.stringify(request));
        //资产同步响应客户端内容的格式
        let response = {
            'requestTime': request.requestTime,
            'responseTime': null,
            'data': []
        };
        for (let i = 0; i < request.data.length; i++) {
            let data = {
                'assetNo': null,
                'code': 100,
                'msg': null
            };
            let requestData;
            let resData;
            let results;
            try {
                //requestData，经过base64解密
                requestData = new Buffer(request.data[i], 'base64').toString('utf-8');
                requestData = JSON.parse(requestData);
                results = await func(requestData);
                resData = assetResponse(results, data);
                if (requestData['r_device_asset']) {
                    resData.assetNo = requestData['r_device_asset']['device_code'];
                } else if (requestData['r_park_place']) {
                    resData.assetNo = requestData['r_park_place']['place_id'];
                } else if (requestData['r_road']) {
                    resData.assetNo = requestData['r_road']['road_id'];
                } else if (requestData['r_unit']) {
                    resData.assetNo = requestData['r_unit']['unit_id'];
                } else if (requestData['r_car_charger_station']) {
                    resData.assetNo = requestData['r_car_charger_station']['station_id'];
                } else if (requestData['r_car_fee_standard_det']) {
                    resData.assetNo = requestData['r_car_fee_standard_det']['standard_id'];
                } else {
                    resData.assetNo = null;
                }
            } catch (err) {
                resData = data;
                resData.msg = err.message;
            }
            response.data.push(resData);
        }
        response.responseTime = new Date().getTime();
        return response;
    };

    /**
     * 资产同步响应数据封装
     * @param results
     * @return {*}
     */
    var assetResponse = function (results, data) {
        try {
            data.code = results.err ? 100 : 200;
            data.msg = results.err ? results.err : 'OK';
        } catch (err) {
            data.code = 100;
            data.msg = err.message;
        }
        return data;
    };

    /**
     * 添加广播设备
     * @param request
     */
    var broadcastSyncAdd = function (request) {
        logger.debug('处理广播资产同步-添加设备请求：', JSON.stringify(request));
        //响应客户端的内容
        let response = {
            'requestTime': request.requestTime,
            'responseTime': null,
            'data': []
        };
        //添加广播设备I类协议
        let addData = {
            header: {
                assetNo: '',//资产编号，多个资产编号用|分割
                optCmd: 'broadcast_param_9005',
                requestTime: request.requestTime,
                equipType: null,
                dataSource: '0'
            },
            optType: '01',//01：增加设备，02：修改设备
            data: []
        };
        let arrAssetNo = [];
        for (let i = 0; i < request.data.length; i++) {
            let requestData;
            let data = {
                'assetNo': null,
                'code': 200,
                'msg': 'ok'
            };
            try {
                //requestData，经过base64解密
                requestData = new Buffer(request.data[i], 'base64').toString('utf-8');
                requestData = JSON.parse(requestData);
                let temData = {};
                temData.devCode = requestData.devCode;//资产编号
                temData.devName = requestData.devName;//资产名称
                temData.devType = requestData.devType;//设备类型，1：音频，2：对讲呼叫设备，3：求助器
                temData.devIP = requestData.devIP;//设备IP
                temData.devId = null;//设备ID，新增设备操作，此字段为空
                addData.data.push(temData);
                //拼接头部资产编号
                arrAssetNo.push(requestData.devCode);
                data.assetNo = requestData.devCode;
            } catch (err) {
                data.msg = err.message;
                data.code = 100;
            }
            response.data.push(data);
        }
        addData.header.assetNo = arrAssetNo.join('|');
        logger.info('http广播同步，添加广播，I类广播添加协议数据：', JSON.stringify(addData));
        //调用添加广播设备的接口
        sendBroadcastTask(addData);

        response.responseTime = new Date().getTime();
        return response;
    };

    /**
     * 更新广播设备
     * @param request
     */
    var broadcastSyncModify = function (request) {
        logger.debug('处理广播资产同步-修改设备请求：', JSON.stringify(request));
        //响应客户端的内容
        let response = {
            'requestTime': request.requestTime,
            'responseTime': null,
            'data': []
        };
        //广播新增/修改II类协议
        let modifyData = {
            header: {
                assetNo: '',//资产编号，多个资产编号用|分割
                optCmd: 'broadcast_param_9005',
                requestTime: request.requestTime,
                equipType: null,
                dataSource: '0'
            },
            optType: '02',//01：增加设备，02：修改设备
            data: []
        };
        let arrAssetNo = [];
        for (let i = 0; i < request.data.length; i++) {
            let requestData;
            let data = {
                'assetNo': null,
                'code': 200,
                'msg': 'ok'
            };
            try {
                //requestData，经过base64解密
                requestData = new Buffer(request.data[i], 'base64').toString('utf-8');
                requestData = JSON.parse(requestData);
                let tmpData = {};
                tmpData.devCode = requestData.devCode;//资产编号
                tmpData.devName = requestData.devName;//资产名称
                tmpData.devType = requestData.devType;//设备类型，1：音频，2：对讲呼叫设备，3：求助器
                tmpData.devIP = requestData.devIP;//设备IP
                tmpData.devId = requestData.devId;//设备ID，更新设备根据此字段进行操作
                modifyData.data.push(tmpData);
                arrAssetNo.push(requestData.devCode);
                data.assetNo = requestData.devCode;
            } catch (err) {
                data.msg = err.message;
                data.code = 100;
            }
            response.data.push(data);
        }
        modifyData.header.assetNo = arrAssetNo.join('|');
        logger.info('http广播同步，广播设备更新，I类广播更新协议数据：', JSON.stringify(modifyData));
        //调用修改广播设备的接口
        sendBroadcastTask(modifyData);

        response.responseTime = new Date().getTime();
        return response;
    };

    /**
     * 删除广播设备
     * @param request
     */
    var broadcastSyncDelete = function (request) {
        logger.debug('处理广播资产同步-删除设备请求：', JSON.stringify(request));
        //响应客户端的内容
        let response = {
            'requestTime': request.requestTime,
            'responseTime': null,
            'data': []
        };
        //删除广播设备的I类协议
        let deleteData = {
            header: {
                assetNo: '',//资产编号，多个资产编号用|分割
                optCmd: 'broadcast_param_9006',
                requestTime: request.requestTime,
                equipType: null,
                dataSource: '0'
            },
            devId: ''////设备ID，多个设备ID用|分割
        };
        let arrAssetNo = [];
        let arrDevId = [];
        for (let i = 0; i < request.data.length; i++) {
            let requestData;
            let data = {
                'assetNo': null,
                'code': 200,
                'msg': 'ok'
            };
            try {
                //requestData，经过base64解密
                requestData = new Buffer(request.data[i], 'base64').toString('utf-8');
                requestData = JSON.parse(requestData);
                arrAssetNo.push(requestData.assetNo);
                arrDevId.push(requestData.devId);
                data.assetNo = requestData.assetNo;
            } catch (err) {
                data.msg = err.message;
                data.code = 100;
            }
            response.data.push(data);
        }
        deleteData.header.assetNo = arrAssetNo.join('|');
        deleteData.devId = arrDevId.join('|');
        logger.info('http广播同步，删除广播设备，I类删除广播协议数据：', JSON.stringify(deleteData));
        //调用删除广播设备的接口
        sendBroadcastTask(deleteData);

        response.responseTime = new Date().getTime();
        return response;
    };

    /**
     * 发送广播请求任务
     * @param reqData JSON格式
     */
    var sendBroadcastTask = function (reqData) {
        let broadcastTask = {};
        broadcastTask.name = constants.PROCESS_MESSAGE_DEFINE.BROADCAST_MSG.TASK_REQ;
        broadcastTask.data = reqData;
        serverMgr.sendMsg(constants.SERVER_TYPE.BROADCAST, JSON.stringify(broadcastTask));
    };

    /**
     * 视频设备同步
     * @param request
     * @return {Promise.<{requestTime, responseTime: null, optCmd, data: Array}>}
     */
    var safeSync = async function (request, func) {
        logger.debug('处理视频资产同步......');
        //响应客户端的内容
        let response = {
            'requestTime': request.requestTime,
            'responseTime': null,
            'optCmd': request.optCmd,
            'data': []
        };
        let data = [];
        let tempAssetNo = [];
        for (let i = 0; i < request.data.length; i++) {
            let requestData;
            try {
                requestData = new Buffer(request.data[i], 'base64').toString('utf-8');
                requestData = JSON.parse(requestData);
                tempAssetNo.push(requestData.assetNo);
                delete requestData.assetNo;
                data.push(requestData);
            } catch (err) {
                logger.error('视频同步，数据解析错误：', err.message);
            }
        }
        let results = await func(data);
        for (let i = 0; i < results.length; i++) {
            results[i].assetNo = tempAssetNo[i];
        }
        response.responseTime = new Date().getTime();
        response.data = results;
        return response;
    };

    /**
     * 添加视频设备
     * @param request
     * @return {Promise}
     */
    var safeSyncAdd = function (data) {
        logger.debug('处理视频资产同步-添加视频设备：', data);
        let msg = data;
        return new Promise((resolve, reject) => {
            cameraManageReq.addCamera(msg, (response) => {
                resolve(response);
            });
        });
    };

    /**
     * 更新视频设备
     * @param request
     * @return {Promise}
     */
    var safeSyncModify = function (data) {
        logger.debug('处理视频资产同步-更新视频设备：', data);
        let msg = data;
        return new Promise((resolve, reject) => {
            cameraManageReq.modifyCamera(msg, (response) => {
                resolve(response);
            });
        });
    };

    /**
     * 删除视频设备
     * @param request
     * @return {Promise}
     */
    var safeSyncDelete = function (data) {
        logger.debug('处理视频资产同步-删除视频设备：', data);
        let msg = data;
        return new Promise((resolve, reject) => {
            cameraManageReq.deleteCamera(msg, (response) => {
                resolve(response);
            });
        });
    };
}

var assetServer = new AssetServer();
assetServer.init();

/**
 * 接收主进程的消息
 * @param name 消息的名称
 * @param msg 消息内容：JSON string
 */
process.on('message', function (msg) {
    try {
        //msg = JSON.parse(msg);

    }
    catch (exception) {
        logger.error('解析主进程发来的消息异常:' + exception.message);
    }
});

module.exports = assetServer;




