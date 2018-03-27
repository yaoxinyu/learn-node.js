/**
 * 从sql-xml文件中读取sql语句
 * modify by yaoxinyu on 2018/2/9
 */
'use strict';

const sqlXmlParser = require('./xml');
const fileUtil = require('./fileUtil');

function SqlUtil() {
    // sql缓存
    var sqlCache = {};

    /**
     * 从sql.xml文件中读取sql语句并缓存数据——外部初始化时手动调用
     */
    this.loadSqlFile = async function () {
        // sql.xml配置文件路径
        let filePath = fileUtil.path.join(fileUtil.getRootPath(), 'resource/config/sql.xml');
        let data = await sqlXmlParser.parse(filePath);
        if (JSON.stringify(sqlCache) == '') {
            var str = (JSON.stringify(sqlCache) + JSON.stringify(data)).replace(/}{/, ',');
            sqlCache = eval('(' + str + ')');
        } else {
            sqlCache = data;
        }
    };

    /**
     * 根据sqlId查询sql语句.
     * @param sqlId sqlId
     */
    this.getSql = function (sqlId) {
        return sqlCache[sqlId];
    };
}


var sqlUtil = new SqlUtil();
module.exports = sqlUtil;