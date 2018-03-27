/**
 * @file 缓存一些全局使用的数据
 * @author yaoxinyu
 * @date 2017/11/9
 */

var commonModule = require('../src/commonModuleExport');
const logServer = commonModule.logger.getLogger(0);
var fileUtil = require('../src/common/util/fileUtil');
var ymlParser = require('node-yaml');


function GlobalDataCache() {
    /**
     * 配置文件数据
     */
    var configJson = {};
    var isConfigInit = false;

    /**
     * 是否为地区主服务
     */
    var mainServerFlag = false;

    /**
     * map结构，namespace与schema的映射
     * @type {map}
     */
    var protoDataCache = {};

    /**
     * map结构，optCmd与schema的映射
     * @type {map}
     */
    var relaCache = {};

    /**
     * systemType,urlType与运行参数的映射
     * @type {map}
     */
    var runParam = {};

    /**
     * 地区编码和其直接上级区域编码的映射关系
     * @type {map}
     */
    var orgMapping = {};

    /**
     * 加入地区编码和其直接上级区域编码的映射关系
     * @param map
     */
    this.setOrgMapping = function (map) {
        orgMapping = map;
    };

    /**
     * 取得地区编码和其直接上级区域编码的映射关系
     * @param code
     */
    this.getOrgMapping = function (code) {
        return orgMapping[code];
    };

    /**
     * 加入系统类型，URL类型与运行参数的映射
     * @param map
     */
    this.setRunParam = function (map) {
        runParam = map
    };

    /**
     * 取得系统类型，URL类型与运行参数的映射
     * @param systemType 系统类型
     * @param urlType URL类型
     * @return {*}
     */
    this.getRunParam = function (systemType, urlType) {
        return runParam[systemType + urlType];
    };

    /**
     * 加入namespace与schema的映射
     * @param map
     */
    this.setProtoDataCache = function (map) {
        protoDataCache = map;
    };

    /**
     * 加入optCmd与schema的映射
     * @param map
     */
    this.setRelaCache = function (map) {
        relaCache = map;
    };

    /**
     * 取得namespace与schema的映射
     * @return {map}
     */
    this.getProtoDataCache = function () {
        return protoDataCache;
    };

    /**
     * 取得optCmd与schema的映射
     * @return {map}
     */
    this.getRelaCache = function () {
        return relaCache;
    };

    /**
     * 取得config.json数据
     */
    this.getConfigData = function () {
        return configJson;
    };

    /**
     * 设置地区主/子服务标记
     * @param {boolean} flag true:主服务 false:子服务
     */
    this.setMainSubFlag = function (flag) {
        mainServerFlag = flag;
    };

    /**
     * 是否为地区主服务
     * @return {boolean} true:主服务 false:子服务
     */
    this.isMainServer = function () {
        return mainServerFlag;
    };

    /**
     * 初始化读取配置并缓存
     */
    this.init = function () {
        if (isConfigInit) {
            return;
        }

        try {
            let configFilePath = fileUtil.path.join(fileUtil.getRootPath(), 'resource/config/config.yml');
            configJson = ymlParser.readSync(configFilePath, 'utf8');
            isConfigInit = true;
            logServer.info('读取config.yml配置文件数据完成.');
        }
        catch (exception) {
            logServer.error('解析配置文件config.yml数据异常: ' + exception.message);
            return;
        }
    };
}


// 单例
var globalData = new GlobalDataCache();
// 初始化就加载配置
globalData.init();
module.exports = globalData;