/**
 * @file 一些共通的常量定义
 * @author yaoxinyu
 * @date 2017/9/18
 */

const constants = {
    /**
     * 项目名称
     */
    PROJECT_NAME: 'engima-sub-1.0',

    /**
     * 存放截图的静态路径
     */
    PICTURE_PATH: 'picture/',
    /**
     * 字符编码
     */
    CHARSET: {
        GBK: 'gbk',
        GB2312: 'gb2312',
        UTF8: 'utf8'
    },
    /**
     * HTTP服务相关配置
     */
    HTTP_SERVER: {
        PORT: 9010,           // 监听端口
        TIMEOUT: 120000,      // 超时时间（ms）
        VERSION: 'HTTP/1.1',
        CONTENT_TYPE: '',
        /**
         * http 请求方法
         */
        METHOD: {
            GET: 'get',
            POST: 'post'
        },
        /**
         * 响应状态码
         */
        STATUS_CODE: {
            OK: 200,   // 成功
            FAIL: 100  // 失败
        },
    },
    /**
     * WebSocket服务相关配置
     */
    WS_SERVER: {
        PORT: 9009,     // 监听端口
        /**
         * 响应状态码
         */
        STATUS_CODE: {
            OK: 200,   // 成功
            FAIL: 100  // 失败
        },
    },

    /**
     * MQ topic
     */
    MQ_TOPIC: {
        WS_DATA: '/topic/websocket.data',           // WebSocket MQ topic
        BUSINESS: '/topic/mq.II',                   // 集控到分控业务数据topic
        ALARM: '/topic/mq.alarm',                   // 集控到分控告警数据topic
        DEV_STATUS: '/topic/mq.deviceStatus',       // 集控到分控设备状态数据topic
        LINK_AFFAIR: '/topic/mq.linkageAffair'      // 事务联动topic
    },


    /**
     * socket 客户端配置
     */
    GW_SOCKET_SERVER: {
        PORT: 9010,
        HOST: 'gw.cetctrl.smartcitybase.com'  // 这里配置域名连不上？
    },

    BROADCAST_FACTORY: {
        HIKVISION: '001', //海康威视
        UOB: '002', //大华
        IVISIONS: '003', //宇视
        SONY: '004', //索尼
        HONEYWELL: '005', //霍尼韦尔
        BOSCH: '006', //博世
        SAMSUNG: '007', //三星
        AXIS: '008', //安讯士
        INFINOVA: '009', //英飞拓
        TIANDY: '010', //天地伟业
        KEDACOM: '011', //科达
        SANTACHI: '012', //金三立
        YAAN: '013', //天津亚安
        AEBELL: '014', //美电贝尔
        PASTAR: '015'  // 派思达
    },
    BROADCAST_REQ_PARAM: {
        START: '01',
        STOP: '02',
        QUERY_FILE: '03',
        ADJUST_VOLUME: '04',
        DEVICE_STATUS: '05'
    },
    CALL_REQ_PARAM: {
        START: '01',
        STOP: '02'
    },
    DEV_REQ_PARAM: {
        ADD: '01',
        UPDATE: '02'
    },
    BROADCAST_RES_PARAM: {
        START_BROADCAST: '01',
        STOP_BROADCAST: '02',
        QUERY_FILE: '03',
        ADJUST_VOLUME: '04',
        DEVICE_STATUS: '05',
        START_CALL: '06',
        STOP_CALL: '07',
        ADD_DEVICE: '08',
        DEL_DEVICE: '09',
        UPLOAD_FILE: '10'
    },
    PLAN_REQ_PARAM: {
        ADD: '01',
        UPDATE: '02'
    },
    SESSION_DEV_REQ_PARAM: {
        ADD: '01',
        DELETE: '02'
    },
    /**
     * 返回数据的协议必须引用的标准头协议
     */
    RETURN_DATA_HEADER_PROTOCOL: 'com.smartcity.avro.base.ProtocolForII',

    //post请求地址
    POST_URL: {
        //获得协议内容的地址
        PROTOCOL: 'http://gw.cetctrl.smartcitybase.com:9002/smartcity/hi/protocolData',

        //获得运行参数的地址
        RUN_PARAM: 'http://gw.cetctrl.smartcitybase.com:9002/smartcity/hi/systemVisitParam',

        //获得地区编码和其直接上级区域编码的映射关系的地址
        ORG: 'http://gw.cetctrl.smartcitybase.com:9002/smartcity/hi/orgMap',
    },
    /**
     * 进程间通信消息名称定义
     */
    PROCESS_MESSAGE_DEFINE: {
        AVRO_CACHE: 'avroCache',
        /**
         * 广播服务
         */
        BROADCAST_MSG: {
            TASK_REQ: 'broadcastTaskReq',
            TASK_RES: 'broadcastTaskRes'
        },
        /**
         * 视频服务
         */
        VIDEO_MSG: {
            TASK_REQ: 'videoTaskReq',
            TASK_RES: 'videoTaskRes'
        },
        /**
         * 大屏服务
         */
        BIG_SCREEN_MSG: {
            TASK_REQ: 'bigScreenTaskReq',
            TASK_RES: 'bigScreenTaskRes'
        },
    },
    /**
     * 子服务类型定义
     */
    SERVER_TYPE: {
        BROADCAST: 1,
        ASSETSYNC: 2,
        VIDEO: 3,
        BIG_SCREEN: 4,
        LINK_AFFAIR: 5
    }
};


module.exports = constants;
