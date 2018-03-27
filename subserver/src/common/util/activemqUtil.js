/**
 * @file ActiveMQ工具类模块
 * @author yaoxinyu
 * @date 2017/9/18
 */

// stomp协议模块
var stompit = require('stompit');
// 文件工具类模块
var fileUtil = require('./fileUtil');
var logger = require('./logger').getLogger(0);

const MIN_SEND_ONCE = 10;        // 每次最少发送消息数目
// const MAX_SEND_ONCE = 50;        // 每次最多发送消息数目
const MAX_SEND_INTERVAL = 3000;  // 最大延迟发送间隔

/**
 * ActiveMQ连接信息
 */
function MQConnInfo() {
    this.serverIP = '';     // ActiveMQ服务IP
    this.port = 0;          // ActiveMQ连接端口
    this.loginName = '';    // 登录用户名
    this.password = '';     // 登录密码
    this.retries = 0;       // 连接重试次数
    this.retryDelay = 0;    // 连接重试间隔，单位ms

    /**
     * 赋值函数
     * @param {Object} connectInfo
     */
    this.copyValue = function (connectInfo) {
        this.serverIP = connectInfo.serverIP;
        this.port = connectInfo.port;
        this.loginName = connectInfo.loginName;
        this.password = connectInfo.password;
        this.retries = connectInfo.retries;
        this.retryDelay = connectInfo.retryDelay;
    }
}

function MQUtil() {
    // mq配置信息
    this.connInfo = new MQConnInfo();

    // 连接句柄
    var client;

    // 是否已初始化配置
    var isInit = false;

    // 消息队列，缓存MQ发送的消息
    var msgQueue = [];
    // 上一次发送消息的时间
    var lastSendTick = 0;

    /**
     * 处理MQ发送消息队列，控制发送的频率和一次发送的消息个数
     */
    var processSendQueue = function () {
        let curTime = new Date().getTime();
        if (lastSendTick == 0 || curTime - lastSendTick > MAX_SEND_INTERVAL) {
            msgQueue.forEach(function (item) {
                if (item) {
                    let frame = client.send(item.header);
                    frame.write(new Buffer(item.data));
                    frame.end();
                }
            });
            msgQueue.splice(0, msgQueue.length);
            lastSendTick = new Date().getTime();
        }
    };

    /**
     * 通过读取本地配置文件初始化连接信息
     */
    this.initByConfig = function () {
        if (isInit) {
            return;
        }
        logger.debug('读取本地配置，初始化ActiveMQ连接信息......');
        // 读取mq配置文件信息
        let mqConfigPath = fileUtil.path.join(fileUtil.getRootPath(), 'resource/config/mqConfig.json');
        let buffer = fileUtil.readFileBySync(mqConfigPath, null);
        try {
            let jsonData = JSON.parse(buffer);
            this.connInfo.copyValue(jsonData);
        }
        catch (exception) {
            logger.error('本地ActiveMQ连接信息初始化异常: ' + exception.message);
        }
        isInit = true;
        logger.info('本地ActiveMQ连接信息初始化完成');
    };

    /**
     * 手动初始化连接信息
     * @param {Object} connectInfo 对象成员与mqConnInfo中成员一致
     */
    this.initByManual = function (connectInfo) {
        if (isInit) {
            return;
        }
        logger.debug('手动初始化连接信息......');
        this.connInfo.copyValue(connectInfo);
        isInit = true;
        logger.info('手动初始化连接信息完成');
    };

    /**
     * 建立连接
     * @param connectCallback 连接回调函数
     */
    this.connect = function (connectCallback) {
        logger.debug('建立MQ连接......');
        if (isInit) {
            let connectOptions = {
                'host': this.connInfo.serverIP,
                'port': this.connInfo.port,
                'connectHeaders': {
                    'host': this.connInfo.serverIP,
                    'login': this.connInfo.loginName,
                    'passcode': this.connInfo.password
                    // 'heart-beat': '5000,5000'  // 发送/接收的超时时间
                }
            };
            var reconnectOptions = {
                'maxReconnects': this.connInfo.retries,         // MQ重连次数
                'maxReconnectDelay': this.connInfo.retryDelay   // MQ每次重连的最大间隔（ms）
            };
            var servers = [connectOptions];
            let manager = new stompit.ConnectFailover(servers, reconnectOptions);
            manager.connect(connectCallback);
            // 启动定时处理MQ发送队列
            setInterval(processSendQueue, 1000);
        }
    };

    /**
     * 设置连接对象
     * @param connect 连接成功后返回的连接对象
     */
    this.setConnHandle = function (connect) {
        client = connect;
    };

    /**
     * 断开连接
     * @param disconnectCallBack 断开连接回调函数，默认不传
     */
    this.disConnect = function (disconnectCallBack = null) {
        if (client) {
            client.disconnect(disconnectCallBack);
        }
    };

    /**
     * 建立消费者监听
     * @param destination 监听对象
     * @param onMessage 消息回调函数
     */
    this.listen = function (destination, onMessage) {
        if (client) {
            var subscribeHeaders = {
                'destination': destination,
                // 'ack': 'client-individual'
                'ack': 'auto'
            };
            client.subscribe(subscribeHeaders, onMessage);
            logger.info('开启MQ监听[destination:%s]......', destination);
        } else {
            logger.error('监听[destination:%s]失败！', destination);
        }
    };

    /**
     * 生产者发送消息
     * @param destination 目的topic/queue
     * @param buffer 消息buffer
     */
    this.sendMsg = function (destination, buffer) {
        logger.debug('准备发送MQ消息[destination=%s]......', destination);
        if (client) {
            logger.info('MQ发送：destination[%s], message[%s].', destination, buffer);
            let sendHeaders = {
                'destination': destination,
                'content-type': 'application/octet-stream',  // 二进制数据
                'content-length': buffer.length,
            };
            // 先加入发送队列缓存
            let msg = {};
            msg.header = sendHeaders;
            msg.data = buffer;
            msgQueue.push(msg);
            // 判断队列消息数目
            let totalQueueLen = msgQueue.length;
            if (totalQueueLen == MIN_SEND_ONCE) {
                msgQueue.forEach(function (item) {
                    if (item) {
                        let frame = client.send(item.header);
                        frame.write(new Buffer(item.data));
                        frame.end();
                    }
                });
                msgQueue.splice(0, MIN_SEND_ONCE);
                lastSendTick = new Date().getTime();
            }
        }
    };
}

var mqUtil = new MQUtil();
// mqUtil.initByConfig();

module.exports = mqUtil;