/**
 * Created by panxiang on 2018/1/11.
 */
var mqUtil = require('../activeMQMgr');
var commonModule = require('../commonModuleExport');
// 日志模块
const logger = commonModule.logger.getLogger(0);

function WebBusiHttpHandlers() {

    let arrJsonResult = [];
    let m_resCount = 0;
    let m_reqCount = 0;

    /**
     * setReqCount:设置请求的Http的数量
     * @param
     *      reqCount:请求的http数量
     * by 潘翔 on 2018/1/18
     */
    this.setReqCount = function(reqCount) {
        m_reqCount = reqCount;
    }

    /**
     * addResult:添加从视频平台返回结果后处理的结果（此结果为json格式）
     * @param
     *      resultJosn:转换后的结果
     * by 潘翔 on 2018/1/16
     */
    this.addResult = function(resultJson) {
        arrJsonResult.push(resultJson);
        m_resCount++;
        if(m_resCount == m_reqCount) {
            logger.info('发送请求的数量和收到回复的数量相等，开始组装数据发送给MQ');
            let mqJson = {};//发送给mq的json对象,多个回复的时候，以哪个时间为主
            mqJson.header = {};
            let arrAsset = [];
            let arrData = [];
            for(let i = 0; i < arrJsonResult.length; i++) {
                if(i == 0) {
                    mqJson.header.equipType = arrJsonResult[i].header.equipType;
                    mqJson.header.optCmd = arrJsonResult[i].header.optCmd;
                    mqJson.header.requestTime = arrJsonResult[i].header.requestTime;
                    mqJson.header.dataSource = arrJsonResult[i].header.dataSource;
                    mqJson.header.code = arrJsonResult[i].header.code;
                    mqJson.header.msg = arrJsonResult[i].header.msg;
                }
                arrAsset.push(arrJsonResult[i].header.assetNo);
                arrData.push(arrJsonResult[i].data);
            }
            mqJson.header.assetNo = arrAsset.join('|');
            mqJson.header.responseTime = new Date().getTime();
            mqJson.data = arrData;

            logger.info('视频业务发送给MQ的信息是[%s]', JSON.stringify(mqJson));
            mqUtil.sendBusiDataForII(mqJson);
        }
    }
}

module.exports = WebBusiHttpHandlers;

