/**
 * @file sql_xml解析工具类
 * @author wangweizhen
 * @date 2017/10/18
 * modify by yaoxinyu on 2018/2/9
 */
/**
 * 解析xml中的sql.
 * xml:
 * <sqls>
 *    <sql id="query">
 *        SELECT * FROM  t
 *   </sql>
 *    <sql id="query2">
 *        SELECT * FROM  t
 *   </sql>
 * </sqls>
 *
 */

var fs = require('fs');
var parseString = require('xml2js').parseString; // 解析xml文件
var logger = require('./logger').getLogger();

function SqlXmlParser() {
    this.parse = function (file) {
        return new Promise((resolve, reject) => {
            parseFile(file, (data) => {
                resolve(data);
            });
        });
    };

    /**
     * 解析xml并返回数据库文件.
     * @param file xml文件
     * @return JSON，key->id,value->sql
     */
    var parseFile = function (file, callback) {
        try {
            let readableStream = fs.createReadStream(file);
            validator(readableStream, function (result) {
                parseXml(result, function (data) {
                    callback(data);
                });
            });
        } catch (exception) {
            logger.error('解析sql.xml异常：', exception.message);
        }
    };

    /**
     * 验证xml.
     * @param fileStream 文件流
     */
    var validator = function (fileStream, callback) {
        var data = '';
        fileStream.on('data', function (chunk) {
            data += chunk;
        });
        fileStream.on('end', function () {
            data = data.replace(/\r\n/g, '');
            parseString(data, function (err, result) {
                if (err) {
                    logger.error('解析SQLxml出错');
                    callback(err);
                }
                callback(result);
            });
        });
        fileStream.on('error', function (err) {
            logger.error(err.stack);
        });
    }

    /**
     * 解析xml.
     * @param fileStream 文件流
     * @return JSON
     */
    var parseXml = function (result, callback) {
        var data = {};
        var json_sql = result['sqls']['sql'];
        for (var i = 0, len = json_sql.length; i < len; i++) {
            data[json_sql[i].$.id] = json_sql[i]._;
        }
        callback(data);
    };
}

var sqlXmlParser = new SqlXmlParser();
module.exports = sqlXmlParser;
