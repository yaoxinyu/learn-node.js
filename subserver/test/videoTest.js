/**
 * @file 视频测试用例类
 * Created by yaoxinyu on 2018/3/19.
 */

var testBase = require('./testBase');
var assert = require('assert');
var protolType = require('../src/protoTypeClassify');

function VideoTest() {
    /**
     * 运行测试用例
     * @param testCase 测试用例 JSON格式
     */
    this.runTestCase = function (testCase) {
        try {
            let optCmd = testCase.data.header.optCmd;
            assert(protolType.isVideoProtoI(optCmd));
            switch (optCmd) {
            case 'safe_param_6010': //云台控制开始
                console.info('运行云台控制开始测试用例...');
                break;
            case 'safe_param_6011': //云台控制结束
                console.info('运行云台控制结束测试用例...');
                break;
            case 'safe_param_6021': //设置预置点
                console.info('运行设置预置点测试用例...');
                break;
            case 'safe_param_6020': //云台PTZ控制
                console.info('运行云台PTZ控制测试用例...');
                break;
            case 'safe_param_6012': //视频播放
                console.info('运行视频播放测试用例...');
                break;
            case 'safe_param_6013': //录像列表查询
                console.info('运行录像列表查询测试用例...');
                break;
            case 'safe_param_6014': //截图列表查询
                console.info('运行截图列表查询测试用例...');
                break;
            case 'safe_param_6015': //触发录像(自动停止)
                console.info('运行触发录像（自动停止）测试用例...');
                break;
            case 'safe_param_6016': //触发录像(手动开始)
                console.info('运行触发录像（手动开始）测试用例...');
                break;
            case 'safe_param_6017': //触发录像(手动结束)
                console.info('运行触发录像（手动结束）测试用例...');
                break;
            case 'safe_param_6018': //触发截图
                console.info('运行触发截图测试用例...');
                break;
            case 'safe_param_6019': //录像设置
                console.info('运行录像设置测试用例...');
                break;
            default:
                break;
            }
            testBase.sendBusiReq(testCase);
        } catch (exception) {
            console.error('运行视频测试用例出错：', exception.message);
        }
    };

}

var videoTest = new VideoTest();
module.exports = videoTest;