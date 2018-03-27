/**
 * @file 解析数据模块
 * @author wangWeiZHen
 * @date 2018/1/31
 */
var logger = require('../../common/util/logger').getLogger(0);
var linkAffProcess = require('./linkAffProcess');
var pusher = require('../../bigScreen/dataPush/dataPusher');
var activeMQMgr = require('../../activeMQMgr');
var DataOperation = function () {
    /**
     *封装发送MQ的JSON数据，
     * @param actionId 动作ID
     * @param eventCode 事件编码
     * @param responseTime
     * @param record
     * @return {{}}
     */
    var packJsonData = function (assetNo, actionId, eventCode, responseTime, record) {
        let data = {};
        data.assetNo = assetNo;
        data.actionId = actionId;
        data.eventCode = eventCode;
        data.eventTime = responseTime;
        data.data = record;
        return data;
    };
    /**
     * 对设备状态，告警，业务II类数据进行解析，并判断时间的有效性
     * @param record 事务联动原始数据
     * @return {Promise.<null>}
     */
    this.actionJudgment = async function (record) {
        logger.info('事务联动-开始根据协议解析联动条件, 原始数据：', record);
        let header = null;
        let optCmd = null;
        let assetNo = null;
        try {
            header = record.header;
            assetNo = header.assetNo;
            if (!assetNo) {
                logger.info('事务联动-解析协议数据后，资产编号为空！');
                return;
            }
            optCmd = header.optCmd;
            logger.info('事务联动-判断动作的存在以及时间是否有效');
            let list = await linkAffProcess.ProtoAnalysis.actionJudgment(record);
            logger.info('事务联动-满足日期有效的的动作ID列表：', list);
            let deviceTypeSet = new Set();
            for (let action of list) {
                try {
                    //获取推送到大屏单独处理的推送者
                    if (optCmd == 'rfid_data_9003' || optCmd == 'park_data_9011' ||
                        optCmd == 'senset_data_9001' || optCmd == 'manhole_data_9017') {
                        let deviceType = action.deviceType;
                        if (!deviceTypeSet.has(deviceType)) {
                            logger.debug('事务联动-需要推送到大屏的数据: ', record);
                            pusher.pushScreenData(record);
                            deviceTypeSet.add(deviceType);
                        }
                    }
                    let jsonData = packJsonData(assetNo, action.actionId, action.eventCode, new Date().getTime(), record);
                    //把动作ID存在以及时间有效的数据打包发送到事务联动MQ
                    logger.debug('事务联动-把动作ID及时间有效的数据打包发送到事务联动MQ，JSONData：', jsonData);
                    activeMQMgr.sendLinkAffair(jsonData);
                } catch (err) {
                    logger.error('事务联动-发送出现错误，error：', err.message);
                }
            }
        } catch (err) {
            logger.error('事务联动-解析协议数据错误，error:', err.message);
        }
    };
};
module.exports = new DataOperation();
