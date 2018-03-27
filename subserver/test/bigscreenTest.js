/**
 * @file 大屏测试用例类
 * Created by yaoxinyu on 2018/3/19.
 */

var testBase = require('./testBase');
var mqMgr = require('../src/activeMQMgr');
mqMgr.initByLocalConfig();
var mqUtil = require('../src/common/util/activemqUtil');


function BigScreenTest() {
    /**
     * 运行大屏推送测试用例 通过发送MQ到mq.II，由事务联动模块处理，再转发到大屏推送模块
     * @param testCase 测试用例
     */
    this.runPushTestCase = function (testCase) {
        try {
            let optCmd = testCase.header.optCmd;
            if (optCmd == 'rfid_data_9003') {
                console.info('运行大屏推送-RFID测试用例...');
            } else if (optCmd == 'park_data_9011') {
                console.info('运行大屏推送-停车测试用例...');
            } else if (optCmd == 'senset_data_9001') {
                console.info('运行大屏推送-环境/气象测试用例...');
            } else if (optCmd == 'manhole_data_9017') {
                console.info('运行大屏推送-水位测试用例...');
            } else {
                console.warn('大屏推送测试用例不合法，optCmd=', optCmd);
                return;
            }

            // 发送消息到MQ对应topic，然后由分控协议网关处理
            let stringData = JSON.stringify(testCase);
            let reqData = new Buffer(stringData);
            mqUtil.sendMsg('/topic/mq.II', reqData);
        } catch (exception) {
            console.error('运行大屏推送测试用例出错：', exception.message);
        }
    };

    /**
     * 运行大屏推发布测试用例
     * @param testCase
     */
    this.runPublishTestCase = function (testCase) {
        try {
            let optCmd = testCase.header.optCmd;
            if (optCmd !== 'media_param_6100') {
                console.warn('大屏发布测试用例不合法，optCmd=', optCmd);
                return;
            }

            console.info('运行大屏发布测试用例...');
            testBase.sendBusiReq(testCase);
        } catch (exception) {
            console.error('运行大屏发布测试用例出错：', exception.message);
        }
    };

    /**
     * 运行大屏截图测试用例
     * @param testCase
     */
    this.runPrintScreenTestCase = function (testCase) {
        try {
            let optCmd = testCase.header.optCmd;
            if (optCmd !== 'media_param_6001') {
                console.warn('大屏截图测试用例不合法，optCmd=', optCmd);
                return;
            }

            console.info('运行大屏截图测试用例...');
            testBase.sendBusiReq(testCase);
        } catch (exception) {
            console.error('运行大屏截图测试用例出错：', exception.message);
        }
    };
}

var bigScreenTest = new BigScreenTest();
module.exports = bigScreenTest;