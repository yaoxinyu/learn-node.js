/**
 * @file Describe the file
 * Created by yaoxinyu on 2018/3/19.
 */

var sleep = require('../src/common/util/sleep');
var testCase = require('./subGWTestCase');   // 测试用例
var testBase = require('./testBase');
var testAssetSync = require('./assetSyncTest');     // 资产同步测试
var testBroadcast = require('./broadcastTest');     // 广播测试
var testVideo = require('./videoTest');             // 视频测试
var testBigScreen = require('./bigscreenTest');     // 大屏测试
var testLinkAffair = require('./linkAffairTest');   // 事务联动测试

// 运行测试
var runTest = async function () {
    await sleep(1000);
    testBase.runConnectCase();   // 建立WebSocket session连接

    await sleep(1000);
    testBroadcast.runTestCase(testCase.BroadcastTestCase.fileList);
    testBigScreen.runPushTestCase(testCase.BigScreenTestCase.park);
};
runTest();