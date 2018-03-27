var express = require('express');
var router = express.Router();
var asset = require('../src/assetSync/asset-sync');
var cameraStatus = require('../src/gcsoftVideo/routeCameraStatus');
var cameraEvent = require('../src/gcsoftVideo/routeCameraEvent');

/* GET home page. */
router.get('/', function (req, res, next) {
    res.render('index', {title: 'Express'});
});

/**
 * 资产同步 POST请求
 */
router.post('/asset', function (req, res, next) {
    var reqData = req.body;
    asset.assetSync(JSON.stringify(reqData), res);
});

/**
 * 视频平台状态推送 POST请求
 */
router.post('/engima-sub/camera/push/status', function (req, res, next) {
    var reqData = req.body;
    cameraStatus.businessProcess(JSON.stringify(reqData), res);
});

/**
 * 视频平台事件推送 POST请求
 */
router.post('/engima-sub/camera/push/event', function (req, res, next) {
    var reqData = req.body;
    cameraEvent.businessProcess(JSON.stringify(reqData), res);
});

module.exports = router;
