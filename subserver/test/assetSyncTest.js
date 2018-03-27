/**
 * @file 资产同步测试用例类
 * Created by yaoxinyu on 2018/3/19.
 */

var testBase = require('./testBase');

function AssetSyncTest() {
    this.runTestCase = function (testCase) {
        try {
            let optCmd = testCase.optCmd;
            switch (optCmd) {
            case 'asset_param_6001':
                console.info('运行资产同步-同步分控-添加资产测试用例...');
                testSyncSubctrl(testCase);
                break;
            case 'asset_param_6002':
                console.info('运行资产同步-同步分控-更新资产测试用例...');
                testSyncSubctrl(testCase);
                break;
            case 'asset_param_6003':
                console.info('运行资产同步-同步分控-删除资产测试用例...');
                testSyncSubctrl(testCase);
                break;
            case 'asset_param_6019':
                console.info('运行资产同步-同步广播-添加设备测试用例...');
                testSyncBroadcast(testCase);
                break;
            case 'asset_param_6020':
                console.info('运行资产同步-同步广播-更新设备测试用例...');
                testSyncBroadcast(testCase);
                break;
            case 'asset_param_6021':
                console.info('运行资产同步-同步广播-删除设备测试用例...');
                testSyncBroadcast(testCase);
                break;
            case 'asset_param_6022':
                console.info('运行资产同步-同步视频-添加设备测试用例...');
                testSyncVideo(testCase);
                break;
            case 'asset_param_6023':
                console.info('运行资产同步-同步视频-更新设备测试用例...');
                testSyncVideo(testCase);
                break;
            case 'asset_param_6024':
                console.info('运行资产同步-同步视频-删除设备测试用例...');
                testSyncVideo(testCase);
                break;
            default:
                console.warn('http资产同步请求测试用例不合法，optCmd=', optCmd);
                break;
            }
        } catch (exception) {
            console.error('运行资产同步测试用例错误：', exception.message);
        }
    };

    /**
     * 测试同步分控
     * @param testCase
     */
    var testSyncSubctrl = function (req) {
        testBase.sendAssetSyncRequest(req);
    };

    /**
     * 测试同步广播设备
     * @param testCase
     */
    var testSyncBroadcast = function (req) {
        testBase.sendAssetSyncRequest(req);
    };

    /**
     * 测试同步视频设备
     * @param testCase
     */
    var testSyncVideo = function (req) {
        testBase.sendAssetSyncRequest(req);
    };
}

var assetSyncTest = new AssetSyncTest();
module.exports = assetSyncTest;