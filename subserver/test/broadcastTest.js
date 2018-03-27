/**
 * @file 广播测试用例类
 * Created by yaoxinyu on 2018/3/19.
 */

var testBase = require('./testBase');
var assert = require('assert');
var protolType = require('../src/protoTypeClassify');

function BroadcastTest() {
    /**
     * 运行测试用例
     * @param testCase 测试用例 JSON格式
     */
    this.runTestCase = function (testCase) {
        try {
            let optCmd = testCase.data.header.optCmd;
            let data = testCase.data;
            assert(protolType.isBroadProtoI(optCmd));
            switch (optCmd) {
            case 'broadcast_param_9003':
                // 广播
                switch (data.optType) {
                case '01':
                    // 开始广播
                    testStartBroadcast(testCase);
                    break;
                case '02':
                    // 停止广播
                    testStopBroadcast(testCase);
                    break;
                case '03':
                    // 查询文件列表
                    testQueryFile(testCase);
                    break;
                case '04':
                    // 调整音量
                    testAdjustVolume(testCase);
                    break;
                default:
                    console.error('错误的广播操作类型：', data.optType);
                    break;
                }
                break;
            case 'broadcast_param_9004':
                // 喊话
                if (data.optType == '01') {
                    // 开始喊话
                    testStartCall(testCase);
                } else if (data.optType == '02') {
                    // 停止喊话
                    testStopCall(testCase);
                } else {
                    console.error('错误的喊话操作类型：', data.optType);
                }
                break;
            case 'broadcast_param_9007':
                // 上传文件
                testUploadFile(testCase);
                break;
            case 'broadcast_param_9008':
                // 添加/修改方案
                if (data.optType == '01') {
                    // 添加方案
                    testAddPlan(testCase);
                } else if (data.optType == '02') {
                    // 修改方案
                    testModifyPlan(testCase);
                } else {
                    console.error('错误的方案操作类型：', data.optType);
                }
                break;
            case 'broadcast_param_9009':
                // 删除方案
                testDelPlan(testCase);
                break;
            case 'broadcast_param_9010':
                // 添加/删除会话设备
                if (data.optType == '01') {
                    // 添加会话设备
                    testAddSessionDev(testCase);
                } else if (data.optType == '02') {
                    // 删除会话设备
                    testDelSessionDev(testCase);
                } else {
                    console.error('错误的会话设备操作类型：', data.optType);
                }
                break;
            default:
                break;
            }
        } catch (exception) {
            console.error('运行广播测试用例出错：', exception.message);
        }
    };

    /**
     * 测试开始广播
     * @param testCase
     */
    var testStartBroadcast = function (testCase) {
        console.info('运行开始广播测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试停止广播
     * @param testCase
     */
    var testStopBroadcast = function (testCase) {
        console.info('运行停止广播测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试查询文件列表
     * @param testCase
     */
    var testQueryFile = function (testCase) {
        console.info('运行查询文件列表测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试调整音量
     * @param testCase
     */
    var testAdjustVolume = function (testCase) {
        console.info('运行调整音量测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试开始喊话
     * @param testCase
     */
    var testStartCall = function (testCase) {
        console.info('运行开始喊话测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试停止喊话
     * @param testCase
     */
    var testStopCall = function (testCase) {
        console.info('运行停止喊话测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试添加方案
     * @param testCase
     */
    var testAddPlan = function (testCase) {
        console.info('运行添加方案测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试修改方案
     * @param testCase
     */
    var testModifyPlan = function (testCase) {
        console.info('运行修改方案测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试删除方案
     * @param testCase
     */
    var testDelPlan = function (testCase) {
        console.info('运行删除方案测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试添加会话设备
     * @param testCase
     */
    var testAddSessionDev = function (testCase) {
        console.info('运行添加会话设备测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试删除会话设备
     * @param testCase
     */
    var testDelSessionDev = function (testCase) {
        console.info('运行删除会话设备测试用例...');
        testBase.sendBusiReq(testCase);
    };

    /**
     * 测试上传音乐文件
     * @param testCase
     */
    var testUploadFile = function (testCase) {
        console.info('运行上传音乐文件测试用例...');
        testBase.sendBusiReq(testCase);
    };
}

var broadcastTest = new BroadcastTest();
module.exports = broadcastTest;