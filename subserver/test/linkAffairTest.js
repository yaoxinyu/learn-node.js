/**
 * @file 事务联动测试用例类
 * Created by yaoxinyu on 2018/3/19.
 */

var testBase = require('./testBase');
var mqMgr = require('../src/activeMQMgr');
mqMgr.initByLocalConfig();
var mqUtil = require('../src/common/util/activemqUtil');

function LinkAffairTest() {
    /**
     * 运行测试用例
     * @param testCase 测试用例 动作配置需要事先配好，将文字、广播、视频、大屏动作都加上
     */
    this.runTestCase = function (testCase) {
        try {
            // 发送消息到MQ对应topic，然后由分控协议网关处理
            let stringData = JSON.stringify(testCase);
            let reqData = new Buffer(stringData);
            mqUtil.sendMsg('/topic/mq.II', reqData);
        } catch (exception) {
            console.error('运行事务联动测试用例出错：', exception.message);
        }
    };
}

var linkAffairTest = new LinkAffairTest();
module.exports = linkAffairTest;