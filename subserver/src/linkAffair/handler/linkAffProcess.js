/**
 * @file 事务联动协议解析，动作处理，逻辑判断
 * @author wangWeiZHen
 * @date 2018/1/29
 */
var logger = require('../../common/util/logger').getLogger(0);
var linkAffairDao = require('../DB/linkAffairDao');
var DataTimeJSONPath = require('./DataTimeJSONPath');
var JSONPath = require('advanced-json-path');
var EventRecorder = require('./EventRecorder');
var constantMapping = require('../constantMapping');
var ExecuteActionHandler = require('../actionMgr/ExecuteActionHandler');

/**
 *
 * @param assetNo
 * @param eventCode
 * @param type
 * @constructor
 */
var LinkageMessageKey = function (assetNo, eventCode, type) {
    var key = {
        'assetNo': assetNo,
        'eventCode': eventCode,
        'type': type
    };
    this.getKey = function () {
        return key;
    };
    this.toString = function () {
        return '资产编号：' + key.assetNo +
            '事件编号' + key.eventCode +
            '类型' + key.type;
    };
};

/**
 * 事务联动协议解析
 * @constructor
 */
var ProtoAnalysis = function () {

    /**
     * 判断时间的有效性，保留有效时间的动作id
     * @param arrActionEventData 数组，value：动作事件的JSON数据
     * @param responseTime 数据的时间
     * @return {Promise.<*>} 数组，value: 时间有效的动作事件JSON数据
     */
    var validData = async function (arrActionEventData, responseTime) {
        let list = [];
        let day;
        let hour;
        let eventTime;
        try {
            eventTime = responseTime;
            let tempTime = new Date();
            tempTime.setTime(eventTime);
            day = tempTime.getDate();
            hour = tempTime.getHours();
            logger.info('事务联动-数据时间为[%s]日:[%s]点', day, hour);
        } catch (err) {
            logger.error('事务联动-日期转化出错，error:', err.message);
            return [];
        }
        //获取符合有效时间的联动数据
        for (let actionEvent of arrActionEventData) {
            let validFlag = false;
            logger.debug('事务联动-查询有效日期表,actionId: ', actionEvent.actionId);
            //根据动作ID查询有效日期表
            let arrActionTimeReal = await linkAffairDao.getActionTimeRealByActionId(actionEvent.actionId);
            logger.info('事务联动-查询有效日期信息: ', arrActionTimeReal);
            if (arrActionTimeReal) {
                for (let actionTimeReal of arrActionTimeReal) {
                    if (actionTimeReal.dtValidBegin <= eventTime && actionTimeReal.dtValidEnd >= eventTime) {
                        validFlag = true;
                        break;
                    }
                }
            } else {
                validFlag = true;
            }
            if (!validFlag) {
                continue;
            }
            logger.debug('事务联动-查询周期设置表,actionId: ', actionEvent.actionId);
            let arrActionCycleReal = await linkAffairDao.getActionCycleRealByActionId(actionEvent.actionId);
            logger.info('事务联动-查询周期设置表,arrActionCycleReal: ', arrActionCycleReal);
            if (arrActionCycleReal) {
                validFlag = false;
                let cycleDay = arrActionCycleReal[0].cycleDay;
                //先判断日
                if (cycleDay.length >= day && cycleDay.charAt(day - 1) == '1') {
                    //判断时间
                    let cycleHour = arrActionCycleReal[0].cycleHour;
                    if (cycleHour.length >= hour && cycleHour.charAt(hour - 1) == '1') {
                        validFlag = true;
                    }
                } else {
                    validFlag = true;
                }
            }
            if (validFlag) {
                list.push(actionEvent);
            }
        }
        return list;
    };

    /**
     * 动作判断以及时间有效性判断
     * @param msg 原始数据
     * @return {Promise.<*>}
     */
    this.actionJudgment = async function (msg) {
        try {
            let assetNo = msg.header.assetNo;
            let optCmd = msg.header.optCmd;
            let responseTime;
            logger.debug('事务联动-根据资产编号查询资产事务联动动作配置信息, assetNo: ', assetNo);
            let arrActionEventData = await linkAffairDao.getActionEventByAssetNo(assetNo);
            if (!arrActionEventData) {
                logger.info('事务联动-资产编号：' + assetNo + ',未配置联动事件！');
                return [];
            }
            logger.info('事务联动-资产编号：' + assetNo + ',已配置联动事件！');
            let jsonPath = DataTimeJSONPath.getJSONPathMap(optCmd);
            logger.debug('事务联动-根据optCmd[%s]获取联动事件的jsonPath表达式：[%s]', optCmd, jsonPath);
            responseTime = JSONPath(msg, jsonPath);//jsonPath通过表达式取出原始数据的时间
            logger.info('事务联动-原始数据的时间：', responseTime);
            if (!responseTime) {
                logger.info('事务联动-根据协议未取到数据对应的日期值，jsonPath：', jsonPath);
                return null;
            }
            logger.debug('事务联动-判断时间是否有效......');
            let list = await validData(arrActionEventData, responseTime);//判断时间是否有效，返回时间有效的事件数组
            return list;
        } catch (err) {
            logger.error('事务联动-协议解析错误：', err.message);
            return [];
        }
    }
};

/**
 * 条件表达式判断
 * @constructor
 */
var ConditionExpression = function () {

    /**
     * 次数、人数.
     * @param condition 条件
     * @param key
     * @param unitTime 单位时间，单位是分钟
     * @return {*}
     */
    var doCount = function (condition, key, unitTime) {
        //运算单位类型
        if (condition.valType == '2') {
            let eventTimeList = EventRecorder.getRecord(key);
            let eventTimeLast = eventTimeList.pop();
            eventTimeList.push(eventTimeLast);
            let integer = 0;
            let subList = [];
            if (eventTimeList) {
                let unitTimeLong = unitTime * 60 * 1000;
                let min = eventTimeLast - unitTimeLong;
                let max = eventTimeLast;
                for (let temp of eventTimeList) {
                    if (temp >= min && temp <= max) {
                        integer++;
                    } else {
                        subList.push(temp);
                    }
                }
                //规定时间内发生的次数
                let times = integer;
                //删除已经过时的时间缓存
                EventRecorder.removeEventTimeList(key, subList);
                //运算关系
                let operation = constantMapping.RELATIONTYPE[condition.operation];
                if (!operation) {
                    logger.info('事务联动-发现配置错误，未找到关系符映射');
                    return false;
                }
                let expression = times + ' ' + operation + ' ' + condition.value[0];
                return eval(expression);
            }
        }
    };

    /**
     * 持续时长
     * @param condition 条件数据
     * @return {boolean}
     */
    var doTime = function (condition) {
        logger.info('联动条件-持续时长，暂未实现.');
        return false;
    };

    /**
     * 数据异常.
     * @param condition
     * @return {boolean}
     */
    var doData = function (condition) {
        logger.info('联动条件-数据，暂未实现');
        return false;
    };

    /**
     * 条件表达式判断
     * @param condition 条件数据
     * @param value JSON数据通过jsonPath取到的值
     * @return {*}
     */
    var doCheckCode = function (condition, value) {
        if (!value) {
            return false;
        }
        let operation = constantMapping.RELATIONTYPE[condition.operation];
        if (!operation) {
            logger.info('事务联动-没有找到相应的关系符：', condition.operation);
            return false;
        }
        let valType = condition.valType;
        let valueArray = condition.value;
        let checkValue = valueArray[0];
        logger.info('事务联动-valType: ', valType);
        logger.info('事务联动-valueArray:[%s], operation:[%s],checkValue:[%s]', valueArray, operation, checkValue);
        let expression = false;
        switch (valType) {
        //文本
            case '1':
                expression = '\'' + value + '\' ' + operation + '\'' + checkValue + '\' ';
                break;
            //数字
            case '2':
                expression = value + operation + checkValue;
                break;
            //布尔
            case '3':
                checkValue = checkValue ? true : false;
                value = value ? true : false;
                expression = value + operation + checkValue;
                break;
            //日期
            case '4':
                checkValue = new Date(checkValue).getTime();
                if (!value) {
                    value = new Date().getTime();
                }
                expression = value + operation + checkValue;
                break;
            //集合
            case '5':
                expression = value + operation + checkValue;
                break;
            default:
                logger.info('事务联动-未找到此类型条件的处理，valType:', valType);
                break;
        }
        logger.info('expression=', expression);
        return eval(expression);
    };

    /**
     *事务联动触发条件判断
     * @param condition 触发条件
     * @param isAnd
     * @param key
     * @param msg 原始II协议数据
     * @return {boolean}
     */
    var defaultVarCheck = async function (condition, isAnd, key, msg) {
        let assetNo = key.assetNo;
        let deviceType = assetNo.substring(0, 4);
        let eventCode = key.eventCode;
        if (!eventCode) {
            return false;
        }
        let eventCodes = eventCode.split(',');
        let varName = condition.var.replace(/(^\s*)|(\s*$)/g, '');
        let arrActionEventVar = null;
        for (let code of eventCodes) {
            logger.debug('事务联动-根据设备类型:[%s],事件编码[%s], varName = [%s]查询表达式', deviceType, code, varName);
            arrActionEventVar = await linkAffairDao.getExpressionInfo(deviceType, code, varName);
            logger.info('事务联动-查询的jsonPath表达式：', arrActionEventVar);
            if (arrActionEventVar) {
                break;
            }
        }
        if (!arrActionEventVar) {
            logger.info('事务联动-资产编号：{%s}，变量名称：{%s}，未查询到条件表达式！', assetNo, varName);
            return false;
        }
        let expression = arrActionEventVar[0].varCode;
        logger.debug('事务联动-资产编号：{%s}，变量名称：{%s}，计算表达式：{%s}', assetNo, varName, expression);
        let value = null;
        try {
            let ex = expression.replace(/\\\*/g, '#');//对特殊的乘号*进行替换处理
            let arrExp = ex.split(/[\+\-#/]/);//匹配表达式，分割成数组
            let allArrOpe = ex.split(/[^\+\-#/]/).join('').replace(/#/g, '*').split('');//匹配运算符，转成数组
            let result = [];//存放JSONPath表达式取值结果
            for (let exp of arrExp) {
                value = JSONPath(msg, exp);
                result.push(value);
            }
            arrExp = result;
            let str = '';
            if (arrExp.length == allArrOpe.length + 1) {
                allArrOpe.push('');
                for (let i = 0; i < arrExp.length; i++) {
                    if (typeof arrExp[i] == 'object') {
                        arrExp[i] = true;
                    }
                    str = str + arrExp[i] + allArrOpe[i];
                }
            }
            value = eval(str);
        } catch (err) {
            logger.error('事务联动-JSONPATH取值失败：', err.message);
            return false;
        }
        logger.info('事务联动-jsonPath取值，value: ', value);
        let data = value;
        //判断是否为数组
        if (Object.prototype.toString.call(value) == '[object Array]') {
            data = value[0];
        }
        logger.info('事务联动-进行eval表达式判断,condition:[%s],data:[%s]', JSON.stringify(condition), data);
        let isFindCondition = doCheckCode(condition, data);
        logger.info('事务联动-eval表达式判断结果，isFindCondition：', isFindCondition);
        if (isFindCondition) {
            logger.info('事务联动-资产编号：{%s}，变量名称：{%s}', assetNo, varName);
            return true;
        } else {
            logger.info('事务联动-资产编号：{%s}，变量名称：{%s}', assetNo, varName);
            return false;
        }
        return false;
    };

    /**
     * 动作条件检查
     * @param andConditions 动作条件
     * @param unitTime 单位时间，单位是分钟
     * @param isAnd 表达式关系
     * @param key
     * @param data 原始数据
     * @return {*}
     */
    var checkConditions = async function (andConditions, unitTime, isAnd, key, data) {
        if (unitTime <= 0) {
            logger.info('事务联动-单位时间 [%s] 配置错误', unitTime);
            return null;
        }
        if (!andConditions) {
            logger.info('事务联动-动作条件内容为空');
            return null;
        }
        let result = false;
        if (isAnd) {
            result = true;
        }
        for (let object of andConditions) {
            logger.info('事务联动-单个表达式信息：', object);
            let condition = object;
            let varchar = null;
            let isFindCondition = false;
            try {
                if (typeof object == 'string') {
                    condition = JSON.parse(object);
                }
                varchar = condition.var.toUpperCase();
                logger.info('事务联动-varchar:', varchar);
                isFindCondition = false;
                switch (varchar) {
                    case 'COUNT':
                        isFindCondition = doCount(condition, key, unitTime);
                        break;
                    case 'TIME':
                        isFindCondition = doTime(condition);
                        break;
                    case 'DATA':
                        isFindCondition = doData(condition);
                        break;
                    case 'alarmCode':
                        isFindCondition = doCheckCode(condition, key);
                        break;
                    default:
                        isFindCondition = await defaultVarCheck(condition, isAnd, key, data);
                        break;
                }
            } catch (err) {
                logger.error('事务联动-表达式解析出错');
                isFindCondition = false;
            }
            logger.info('事务联动-当前表达式结果，isFindCondition:', isFindCondition);
            if (isAnd) {
                result = eval(result && isFindCondition);
            } else {
                result = eval(result || isFindCondition);
            }
            logger.info('事务联动-当前判断结果，result:', result);
        }
        logger.info('事务联动-最终判断结果，result:', result);
        return result;
    };

    /**
     * 动作条件检查
     * @param actionId 动作ID
     * @param key 封装资产编号：assetNo， 事件编码：eventCode,类型：type等信息
     * @param msg 事务联动JSON数据
     * @return {Promise.<null>}
     */
    var conditionResolve = async function (actionId, key, msg) {
        //根据动作ID查询动作条件
        logger.debug('事务联动-根据动作ID查询动作条件, actionId', actionId);
        let conditions = await linkAffairDao.getActionConditionsByActionId(actionId);
        logger.info('事务联动-查询的动作条件：', conditions);
        let conditionOk = false;//判断是否满足条件
        if (!conditions) {
            return null;
        }
        try {
            let data = msg.data;
            for (let cond of conditions) {
                logger.info('事务联动-每个动作条件：', cond);
                let condition = cond.condition;
                logger.info('事务联动-每个动作条件表达式参数：', condition);
                let conditionObject = eval('(' + condition + ')');
                logger.debug('事务联动-动作条件检查, conditionObject: ', conditionObject);
                let andConditions = conditionObject['AND'];
                if (andConditions) {
                    //动作条件检查
                    logger.debug('事务联动-AND关系检查');
                    conditionOk = await checkConditions(andConditions, cond.unitTime, true, key, data);
                } else {
                    andConditions = conditionObject['OR'];
                    //动作条件检查
                    logger.debug('事务联动-OR关系检查');
                    conditionOk = await checkConditions(andConditions, cond.unitTime, false, key, data);
                }
                logger.info('事务联动-动作条件是否满足：', conditionOk);
                if (!conditionOk) {
                    break;
                }
            }
        } catch (err) {
            logger.log('事务联动-处理条件时错误, error: ', err.message);
        }
        return conditionOk ? conditions : null;
    };

    /**
     * 解析动作条件
     * @param msg 事务联动JSON数据
     * @param type 类型 "1":业务数据，"2":告警数据，"3":设备状态数据
     */
    this.analysisAndAction = async function (msg, type) {
        let actionId = null;
        let assetNo = null;
        let key = null;
        let conditions = null;
        let eventCode = null;
        try {
            actionId = msg.actionId;
            assetNo = msg.data.header.assetNo;
            eventCode = msg.eventCode;
            key = new LinkageMessageKey(assetNo, eventCode, type).getKey();
            logger.debug('事务联动-缓存时间，key: [%s], time: [%s]', JSON.stringify(key), msg.eventTime);
            EventRecorder.setRecord(key, msg.eventTime);
            //动作条件检查
            logger.debug('事务联动-动作条件检查, actionId: ', actionId);
            conditions = await conditionResolve(actionId, key, msg);
            logger.info('事务联动-动作条件检查结果：', conditions);
            if (conditions) {
                ExecuteActionHandler.handleMessage(msg);

            } else {
                logger.info('事务联动-解析后不满足联动条件！数据：', JSON.stringify(key));
            }
        } catch (err) {
            logger.error('事务联动-条件解析出错，error：', err.message);
        }
    }
};

module.exports = {
    ProtoAnalysis: new ProtoAnalysis(),
    ConditionExpression: new ConditionExpression()
};

