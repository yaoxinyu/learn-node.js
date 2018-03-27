/**
 * @file 大屏操作类
 * Created by yaoxinyu on 2018/3/21.
 */

// 日志模块
var logger = require('../commonModuleExport').logger.getLogger();

function BigScreenOperation() {
    /**
     * 处理大屏请求操作
     * @param req 请求消息 JSON格式
     */
    this.dealOperation = function (req) {
        try {
            // TODO 解析出大屏厂家类型
            let facType = null;
            let operator = getOperator(facType);
            // 交给对应operator处理 统一处理接口
            if (operator) {
                let opCmd = req.header.optCmd;
                switch (opCmd) {
                    case 'media_param_6001':
                        operator.dealScreenPrint(req);
                        break;
                    case 'media_param_6100':
                        operator.dealScreenPublish(req);
                        break;
                    default :
                        logger.warn('大屏任务，无法处理的optCmd：', opCmd);
                        break;
                }
            }
        } catch (exception) {
            logger.error('处理大屏请求异常：', exception.message);
        }
    };

    /**
     * 根据大屏厂家类型获取对应的处理对象
     * @param facType
     */
    var getOperator = function (facType) {
        let operator = null;
        switch (facType) {
        // 熙讯大屏
        // operator = require('./factory/xixun/xixunBigScreen');
        // 其他 TODO
            default:
                logger.error('无法处理的大屏厂商：', facType);
                break;
        }

        return operator;
    };
}

var bsOperation = new BigScreenOperation();
module.exports = bsOperation;
