/**
 * ActiveMQ通信管理模块，功能描述：
 * 1、管理ActiveMQ的连接；
 * 2、监听MQ的接收+MQ消息发送；
 * 3、根据不同的topic分发给不同的消费者；
 * 4、消息解析+业务分发到不同的业务处理类
 * @author yaoxinyu
 * @date 2017/11/30
 */

var commonModule = require('./commonModuleExport');
const logger = commonModule.logger.getLogger();
const constants = commonModule.constants;
const fileUtil = commonModule.fileUtil;
var protoClassify = require('./protoTypeClassify');
var httpReq = require('./httpRequests');
var mqUtil = require('./common/util/activemqUtil');
var globalData = require('./globalDataCache');
var avroUtil = require('./common/util/avroUtil');

function ActiveMQMgr() {
    var listenTopic = false;
    /**
     * ActiveMQ初始化工作，同步等待完成
     */
    this.init = async function () {
        // http请求run param数据，从中解析出ActiveMQ连接信息和topic
        // await httpReq.reqRunParam();
        let runParamData = globalData.getRunParam('001', '024');
        // let host;
        // let port;
        let loginName;
        let passwd;
        let retryCnt;
        let retryInterval;
        if (runParamData) {
            loginName = runParamData.userName;
            passwd = runParamData.userPwd;
            // let url = runParamData.url;
            // let pos = url.indexOf('//');
            // if (pos != -1) {
            //     url = url.substr(pos + 2);
            //     pos = url.indexOf(':');
            //     if (pos != -1) {
            //         host = url.substr(0, pos);
            //         port = url.substr(pos + 1);
            //     }
            // }
        }

        // 将MQ配置信息写到本地文件
        try {
            let mqConfig = {
                serverIP: 'mq.subctrl.smartcitybase.com',
                port: 61613,
                retries: -1,
                retryDelay: 60000,
                loginName: 'admin',
                password: 'admin'
            };
            if (loginName && passwd) {
                mqConfig.loginName = loginName;
                mqConfig.password = passwd;
            }
            if (retryCnt && retryInterval) {
                mqConfig.retries = retryCnt;
                mqConfig.retryDelay = retryInterval;
            }
            let configFilePath = fileUtil.path.join(fileUtil.getRootPath(), 'resource/config/mqConfig.json');
            fileUtil.writeFileSync(configFilePath, JSON.stringify(mqConfig, null, 2));

            // 判断是否为地区主服务，如果为主服务，连接MQ并设置监听
            if (globalData.isMainServer()) {
                logger.info('本服务为地区主服务，ActiveMQ初始化连接......');
                listenTopic = true;
                mqUtil.initByConfig();
                mqUtil.connect(onConnect);
            } else {
                logger.warn('本服务为地区子服务，不用监听MQ！');
            }

        } catch (exception) {
            logger.error('写mqConfig.json文件异常：', exception.message);
        }
    };

    /**
     * 读取配置文件完成ActiveMQ连接初始化
     */
    this.initByLocalConfig = function () {
        listenTopic = false;
        mqUtil.initByConfig();
        mqUtil.connect(onConnect);
    };

    /**
     * 连接回调函数
     */
    var onConnect = function (err, connect, reconnect, server) {
        if (err) {
            logger.error('MQ连接失败: ' + err.message);
            return;
        }
        mqUtil.setConnHandle(connect);
        connect.on('error', function (err) {
            if (err) {
                logger.error('MQ连接出现异常: ' + err.message);
                logger.debug('MQ发起重连......');
                reconnect();
            }
        });
        logger.info('ActiveMQ连接成功.');
        // 启动MQ监听
        if (listenTopic) {
            listen();
        }
    };

    /**
     * 建立监听，不同的topic交给对应的listener处理
     */
    var listen = function () {
        // 监听分控内部II类业务数据
        mqUtil.listen(constants.MQ_TOPIC.WS_DATA, onListenWebSocketData);
        // 监听集控到分控的业务MQ
        mqUtil.listen(constants.MQ_TOPIC.BUSINESS, onListenBusiData);
        // 监听集控到分控的告警MQ
        mqUtil.listen(constants.MQ_TOPIC.ALARM, onListenAlarmData);
        // 监听集控到分控的设备状态MQ
        mqUtil.listen(constants.MQ_TOPIC.DEV_STATUS, onListenDevStatusData);
        //监听分控内部事务联动数据
        mqUtil.listen(constants.MQ_TOPIC.LINK_AFFAIR, onListenLinkAffair);
    };

    /**
     * 监听"websocket.data"并分发处理
     */
    var onListenWebSocketData = function (err, message) {
        if (err) {
            logger.error('MQ监听异常[topic=%s]：%s！', constants.MQ_TOPIC.WS_DATA, err.message);
            return;
        }

        message.readString('binary', function (err, body) {
            if (err) {
                logger.error('MQ监听数据异常[topic=%s]: %s', constants.MQ_TOPIC.WS_DATA, err.message);
                return;
            }

            onDealMQData(constants.MQ_TOPIC.WS_DATA, body);
        });
    };

    /**
     * 监听"business.operation.data"并处理
     */
    var onListenBusiData = function (err, message) {
        logger.info('对监听到的II业务数据进行处理！');
        if (err) {
            logger.error('MQ监听异常[topic=%s]：%s！', constants.MQ_TOPIC.BUSINESS, err.message);
            return;
        }

        try {
            message.readString('binary', function (err, body) {
                if (err) {
                    logger.error('MQ监听数据异常[topic=%s]: %s！', constants.MQ_TOPIC.BUSINESS, err.message);
                    return;
                }

                onDealMQData(constants.MQ_TOPIC.BUSINESS, body);
            });
            message.on('end', function() {
                console.warn('接收MQ消息结束');
            });
        } catch (err) {
            logger.error('对监听到的II业务数据进行处理出现错误：', err.message);
        }
    };

    /**
     * 监听"alarm.data"并处理
     */
    var onListenAlarmData = function (err, message) {
        if (err) {
            logger.error('MQ监听异常[topic=%s]：%s！', constants.MQ_TOPIC.ALARM, err.message);
            return;
        }

        message.readString('binary', function (err, body) {
            if (err) {
                logger.error('MQ监听数据异常[topic=%s]: %s！', constants.MQ_TOPIC.ALARM, err.message);
                return;
            }

            onDealMQData(constants.MQ_TOPIC.ALARM, body);
        });
    };

    /**
     * 监听"devicestatus.data"并处理
     */
    var onListenDevStatusData = function (err, message) {
        if (err) {
            logger.error('MQ监听异常[topic=%s]：%s！', constants.MQ_TOPIC.DEV_STATUS, err.message);
            return;
        }

        message.readString('binary', function (err, body) {
            if (err) {
                logger.error('MQ监听数据异常[topic=%s]: %s！', constants.MQ_TOPIC.DEV_STATUS, err.message);
                return;
            }

            onDealMQData(constants.MQ_TOPIC.DEV_STATUS, body);
        });
    };

    /**
     * 监听"onListenLinkAffair"并处理
     */
    var onListenLinkAffair = function (err, message) {
        if (err) {
            logger.error('MQ监听异常[topic=%s]：%s！', constants.MQ_TOPIC.LINK_AFFAIR, err.message);
            return;
        }
        message.readString('binary', function (err, body) {
            if (err) {
                logger.error('MQ监听数据异常[topic=%s]: %s！', constants.MQ_TOPIC.LINK_AFFAIR, err.message);
                return;
            }

            onDealMQData(constants.MQ_TOPIC.LINK_AFFAIR, body);
        });
    };

    /**
     * 处理不同topic的MQ消息
     * @param topic
     * @param data buffer
     */
    var onDealMQData = function (topic, data) {
        let buffer = new Buffer(data, 'binary');
        let jsonData;
        try {
            switch (topic) {
                case constants.MQ_TOPIC.LINK_AFFAIR:
                // JSON格式
                    jsonData = JSON.parse(buffer.toString());
                    break;
                case constants.MQ_TOPIC.WS_DATA:
                // JSON格式
                    jsonData = JSON.parse(buffer.toString());
                    break;
                case constants.MQ_TOPIC.ALARM:
                // avro格式
                    jsonData = avroUtil.parseBufferToAvro('ad_data_9001', buffer);
                    break;
                case constants.MQ_TOPIC.DEV_STATUS:
                // avro格式
                    jsonData = avroUtil.parseBufferToAvro('ad_data_9500', buffer);
                    break;
                case constants.MQ_TOPIC.BUSINESS: {
                // avro格式 先解出II类协议头，从中取出optCmd再转avro
                    let schema = avroUtil.getSchemaByNamespace(constants.RETURN_DATA_HEADER_PROTOCOL);
                    if (schema) {
                        let partData = avroUtil.parseBufferToAvroNotCheck(buffer, schema);
                        logger.info('根据头协议解析出来的数据：', partData);
                        if (partData && partData.header) {
                            let optCmd = partData.header.optCmd;
                            jsonData = avroUtil.parseBufferToAvro(optCmd, buffer);
                            logger.info('解析出的完整avro数据：', jsonData);
                        }
                    }
                    break;
                }
                default:
                    logger.error('无法处理的MQ消息，topic=', topic);
                    break;
            }
        } catch (err) {
            logger.error('MQ消息解析出错[topic=%s]: %s！', topic, err.message);
            return;
        }

        logger.info('解析出的MQ消息[topic=%s]: %s', topic, JSON.stringify(jsonData));
        if (!jsonData) {
            return;
        }
        let optCmd;
        if (jsonData.header) {
            optCmd = jsonData.header.optCmd;
        }
        let protoHandle = getListenerHandle(topic, optCmd);
        if (protoHandle) {
            protoHandle.onMessage(jsonData);
        }
    };

    /**
     * 发送II类业务数据消息
     * @param data JSON格式
     */
    this.sendBusiDataForII = function (data) {
        if (!data || !data.header || !data.data) {
            logger.error('发送的II类业务数据格式错误！');
            return;
        }

        let optCmd = data.header.optCmd;
        let destination;
        switch (true) {
            case (protoClassify.isBroadProtoII(optCmd)):
            // 广播回复协议
                destination = constants.MQ_TOPIC.WS_DATA;
                break;
            case (protoClassify.isVideoProtoII(optCmd)):
            // 视频回复协议
                destination = constants.MQ_TOPIC.WS_DATA;
                break;
            case (protoClassify.isBigScreenProtoII(optCmd)):
            // 大屏回复协议
                destination = constants.MQ_TOPIC.WS_DATA;
                break;
            default:
                break;
        }

        if (destination) {
            let stringData = JSON.stringify(data);
            let businessData = new Buffer(stringData);
            mqUtil.sendMsg(destination, businessData);
        }
    };

    /**
     * 发送动作条件的成立的事务联动数据
     * @param data JSON格式
     */
    this.sendLinkAffair = function (data) {
        try {
            let stringData = JSON.stringify(data);
            let businessData = new Buffer(stringData);
            mqUtil.sendMsg(constants.MQ_TOPIC.LINK_AFFAIR, businessData);
        } catch (exception) {
            logger.error('发送事务联动数据到MQ异常：', exception.message);
        }
    };
}

/**
 * 根据不同的topic返回对应的listener handle
 * @param topic
 * @param optCmd
 */
function getListenerHandle(topic, optCmd) {
    let handle = null;
    switch (topic) {
        case constants.MQ_TOPIC.WS_DATA:
            if (protoClassify.isBroadProtoII(optCmd)) {
            // 处理广播协议回复数据
                handle = require('./listener/broadcastListener');
            } else if (protoClassify.isVideoProtoII(optCmd)) {
            // 处理视频协议回复数据
                handle = require('./listener/videoListener');
            } else if (protoClassify.isBigScreenProtoII(optCmd)) {
            // 处理大屏协议回复数据
                handle = require('./listener/bigScreenListener');
            } else {
                logger.error('topic=websocket.data，不支持的MQ消息处理: optCmd=' + optCmd);
            }
            break;
        case constants.MQ_TOPIC.ALARM:
        // II类告警协议回复数据
            handle = require('./listener/alarmTopicListener');
            break;
        case constants.MQ_TOPIC.DEV_STATUS:
        // II类设备状态回复数据
            handle = require('./listener/statusTopicListener');
            break;
        case constants.MQ_TOPIC.BUSINESS:
        // II类业务回复数据
            handle = require('./listener/businessTopicListener');
            break;
        case constants.MQ_TOPIC.LINK_AFFAIR:
        // 事务联动
            handle = require('./listener/linkAffairTopicListener');
            break;
        // 其他业务 TODO
        default:
            logger.error('不支持该MQ消息的处理: optCmd=' + optCmd);
            break;
    }

    return handle;
}


var mqMgr = new ActiveMQMgr();
module.exports = mqMgr;
