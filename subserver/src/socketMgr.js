/**
 * socket通信管理模块，功能描述：
 * 1、管理socket连接；
 * 2、socket消息的收发；
 * @author yaoxinyu
 * @date 2017/11/30
 */

var commonModule = require('./commonModuleExport');
const logger = commonModule.logger.getLogger();
const constants = commonModule.constants;
var socketClient = require('./socketClient');
var avroUtil = require('./common/util/avroUtil');


function SocketMgr() {
    this.init = function () {
        // 建立socket连接
        socketClient.connect(constants.GW_SOCKET_SERVER.HOST, constants.GW_SOCKET_SERVER.PORT);
    };

    /**
     * 返回avro数据
     * @param msg JSON数据
     */
    var getAvroData = function (msg) {
        let avroData = null;
        if (msg && msg.header) {
            let optCmd = msg.header.optCmd;
            avroData = avroUtil.getAvroDataByOptCmd(msg, optCmd);
            if (!avroData) {
                logger.error('Avro序列化失败[optCmd=%s,data=%s]！', optCmd, JSON.stringify(msg));
            }
        }
        return avroData;
    };

    /**
     * socket发送数据
     * @param command 命令
     * @param avroData avro数据
     */
    var sendData = function (command, avroData) {
        try {
            // 组装成socket数据协议格式：命令（1字节）+类型（1字节）+数据来源（1字节）+数据长度（2字节）+数据（n字节）
            let avroBuffer = avroData.toBuffer();
            let base64Data = new Buffer(avroBuffer).toString('base64');  // base64编码
            let dataLength = base64Data.length;
            let headArray = [command, 1, 0];
            let msgHead = new Buffer(headArray);
            let msgLength = new Buffer(2);
            msgLength.writeInt16BE(dataLength, 0);
            let msgBody = new Buffer(base64Data);
            let bufList = [msgHead, msgLength, msgBody];
            let msg = Buffer.concat(bufList);
            // 发送数据
            socketClient.send(msg, msg.length);
        } catch (exception) {
            logger.error('socket发送数据异常：', exception.message);
        }
    };

    /**
     * 将II类协议数据发送到集控中心
     * @param data II类协议JSON数据
     */
    this.pushDataForII = function (data) {
        try {
            // 消息解析，得到JSON格式
            let msg = JSON.parse(JSON.stringify(data));
            let optCmd = msg.header.optCmd;
            let avroData = getAvroData(msg);
            let command = 0x0;
            // 拼接buffer
            switch (optCmd) {
                case 'ad_data_9500':
                // 设备状态协议
                    command = 0x08;
                    logger.info('socket发送II类设备状态数据：', avroData);
                    break;
                case 'ad_data_9001':
                // 告警协议
                    command = 0x07;
                    logger.info('socket发送II类告警数据：', avroData);
                    break;
                case 'broadcast_data_9003':
                case 'broadcast_data_9005':
                case 'broadcast_data_9006':
                // 广播状态协议
                    command = 0x06;
                    logger.info('socket发送II类广播业务数据：', avroData);
                    break;
                case 'safe_data_9005':
                case 'safe_data_9006':
                // 视频状态协议
                    command = 0x06;
                    logger.info('socket发送II类视频业务数据：', avroData);
                    break;
                case 'manhole_data_9001':
                // 井盖状态协议
                    command = 0x06;
                    logger.info('socket发送II类井盖数据：', avroData);
                    break;
                default:
                    logger.warn('socket发送数据，未找到对应的optCmd：', optCmd);
                    break;
            }
            // 发送数据
            if (avroData) {
                sendData(command, avroData);
            }
        } catch (exception) {
            logger.error('socket发送II类协议数据异常：' + exception.message);
            return;
        }
    };

    /**
     * 将I类协议数据发送到集控中心
     * @param data I类协议JSON数据
     */
    this.pushDataForI = function (data) {
        try {
            // 消息解析，得到JSON格式
            let msg = JSON.parse(JSON.stringify(data));
            let avroData = getAvroData(msg);
            let command = 0x05;
            // 发送数据
            logger.info('socket转发I类业务数据：', avroData);
            if (avroData) {
                sendData(command, avroData);
            }
        } catch (exception) {
            logger.error('处理socket转发的I类协议数据异常：' + exception.message);
            return;
        }
    };
}


var socketMgr = new SocketMgr();
module.exports = socketMgr;

