/**
 * avro工具类模块，功能描述：
 * 1、avro文件解析
 * 2. avro数据序列化;
 * 3. avro数据反序列化.
 * 注：初始化函数需要外部手动调用，两种方式：init和fastInit
 */

var avro = require('avsc');
const logger = require('./logger').getLogger(0);


function AvroUtil() {
    var protoDataCache = {};  // map结构，namespace与schema的映射
    var relaCache = {};       // map结构，optCmd与schema的映射
    var isInit = false;      // 初始化标记

    /**
     * @param schema
     * @return {*}
     */
    var getAvroType = function (schema) {
        let type = avro.Type.forSchema(schema);
        return type;
    };

    this.isInit = function () {
        return isInit;
    };

    // this.init = this.fastInit();

    /**
     * avro初始化，直接用数据数据化
     */
    this.fastInit = function (protoCache, rela) {
        if (isInit) {
            return;
        }
        protoDataCache = protoCache;  // map结构，namespace与schema的映射
        relaCache = rela;            // map结构，optCmd与schema的映射
        isInit = true;
    };

    /**
     * 获取缓存
     * @return {object}
     */
    this.getCache = function () {
        let cache = {};
        cache.protoDataCache = protoDataCache;
        cache.relaCache = relaCache;
        return cache;
    };

    /**
     * 根据namespace从缓存中获取schema.
     * @param namespace String
     * @return Schema
     */
    this.getSchemaByNamespace = function (namespace) {
        return protoDataCache[namespace];
    };

    /**
     * 根据optcmd从缓存取schema
     * @param optcmd
     * @return Schema
     */
    this.getSchemaByOptcmd = function (optcmd) {
        return relaCache[optcmd];
    };

    /**
     * 解析JSON数据.
     * @param data JSON数据
     * @return AVRO
     */
    this.parseJsonToAvro = function (data, schema) {
        try {
            let type = getAvroType(schema);
            let buf = type.toBuffer(data);
            let val = type.fromBuffer(buf);
            return val;
        }
        catch (err) {
            logger.error('JSON转AVRO错误: ' + err.message);
            return null;
        }
    };

    /**
     * 解析avro buffer.
     * @param optCmd
     * @param data buffer
     * @return AVRO
     */
    this.parseBufferToAvro = function (optCmd, data) {
        try {
            let schema = relaCache[optCmd];
            if (!schema) {
                logger.error('未找到对应的schema：', optCmd);
                return null;
            }
            let type = getAvroType(schema);
            let val = type.fromBuffer(data);
            return val;
        }
        catch (err) {
            logger.error('BUFFER转AVRO错误: ' + err.message);
            return null;
        }
    };

    /**
     * 解析avro buffer.不检查
     * @param data buffer
     * @return AVRO
     */
    this.parseBufferToAvroNotCheck = function (data, schema) {
        try {
            let type = getAvroType(schema);
            let val = type.fromBuffer(data, null, true);
            return val;
        }
        catch (err) {
            logger.error('BUFFER转AVRO错误(not check): ' + err.message);
            return null;
        }
    };

    /**
     * 根据schema组装avro
     * @param data JSON
     * @param schema
     * @return {*} AVRO字节流
     */
    this.constructAvroData = function (data, schema) {
        try {
            let type = getAvroType(schema);
            let buf = type.toBuffer(data);
            return buf;
        } catch (err) {
            logger.error('avro序列化错误: ' + err.message);
            return null;
        }
    };

    /**
     * 通过optCmd进行avro校验
     * @param data JSON数据
     * @param optCmd 操作命令
     * @return {AVRO} 校验过后的avro数据
     */
    this.getAvroDataByOptCmd = function (data, optCmd) {
        let schema = this.getSchemaByOptcmd(optCmd);
        if (!schema) {
            logger.error('未找到对应的schema，optCmd=', optCmd);
            return null;
        }
        let avroData = this.parseJsonToAvro(data, schema);
        return avroData;
    };
}

module.exports = new AvroUtil();