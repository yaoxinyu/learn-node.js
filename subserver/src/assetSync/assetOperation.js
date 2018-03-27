/**
 * @file 资产同步的具体业务操作：新增、更新、删除
 * @author wangweizhen
 * @date 2017/10/24
 */
var commonModule = require('../commonModuleExport');
var url = require('url');
var db = require('../common/util/db');
var sql = require('../common/util/sql');
var async = require('async');
var sd = require('silly-datetime');
var logger = commonModule.logger.getLogger(0);

function AssetOperation() {
    /**
     * 资产添加
     * @param requestData 接收的请求数据
     * @return  成功:数组影响行数，失败:-1
     */
    this.assetAdd = async function (requestData) {
        logger.debug('http资产同步，资产添加......');
        let sqlParamsEntities = getSqlArray(requestData); //存放数据解析出来的SQL语句
        logger.info('http资产同步，资产添加，需要事务处理的SQL: ', sqlParamsEntities);
        await db.beginTransaction();//调用数据库事务处理，返回数据库执行结果
        for (let i = 0; i < sqlParamsEntities.length; i++) {
            let sql = sqlParamsEntities[i].sql;
            let param = sqlParamsEntities[i].params;
            db.insertBatch(sql, param);
        }
        let results = await db.transCommit();
        if (results.result) {
            logger.info('事务执行成功, 结果：', results);
        } else {
            logger.error('事务执行失败');
        }
        return results;
    };

    /**
     * 资产更新
     * @param requestData 接收的请求数据
     * @return  成功:数组影响行数，失败:-1
     */
    this.assetUpdate = async function (requestData) {
        logger.debug('http资产同步，资产更新......');
        let sqlParamsEntities = getSqlArray(requestData); //存放数据解析出来的SQL语句
        logger.info('http资产同步，资产更新，需要事务处理的SQL: ', sqlParamsEntities);
        await db.beginTransaction();//调用数据库事务处理，返回数据库执行结果
        for (let i = 0; i < sqlParamsEntities.length; i++) {
            let sql = sqlParamsEntities[i].sql;
            let param = sqlParamsEntities[i].params;
            db.updateBatch(sql, param);
        }
        let results = await db.transCommit();
        if (results.result) {
            logger.info('事务执行成功, 结果：', results);
        } else {
            logger.error('事务执行失败');
        }
        return results;
    };

    /**
     * 资产删除
     * @param requestData 接收的请求数据
     * @return  成功:数组影响行数，失败:-1
     */
    this.assetDelete = async function (requestData) {
        logger.debug('http资产同步，资产删除......');
        let sqlParamsEntities = getSqlArray(requestData); //存放数据解析出来的SQL语句
        logger.info('http资产同步，资产删除，需要事务处理的SQL: ', sqlParamsEntities);
        await db.beginTransaction();//调用数据库事务处理，返回数据库执行结果
        for (let i = 0; i < sqlParamsEntities.length; i++) {
            let sql = sqlParamsEntities[i].sql;
            let param = sqlParamsEntities[i].params;
            db.deleteBatch(sql, param);
        }
        let results = await db.transCommit();
        if (results.result) {
            logger.info('事务执行成功,执行结果：', results);
        } else {
            logger.error('事务执行失败');
        }
        return results;
    };

    /**
     * 获取资产同步请求数据解析出来的SQL语句
     * @param requestData 资产同步请求数据
     */
    var getSqlArray = function (requestData) {
        let sqlArray = [];
        // 遍历数据，得到表名
        for (let tableName in requestData) {
            if (tableName == 'r_device_relation') {
                // 此表数据特殊，表名key对应的value为多条数据
                let sqls = getOperateSql(null, tableName, requestData[tableName]);
                for (let sql of sqls) {
                    sqlArray.push(sql);
                }
            } else {
                let sql = getOperateSql('2', tableName, requestData[tableName]);
                sqlArray.push(sql);
            }
        }
        return sqlArray;
    };

    /**
     *
     * @param operType 0 add 1 update 2 delete
     * @param tableName 表名
     * @param data 操作数据
     */
    var getOperateSql = function (operType, tableName, tableDatas) {
        let fieldName = [];//存放表的字段
        let fieldData = [];//存放表对应字段数据
        let placeholder = [];//存放占位符？
        let str = '';
        let j = 0;
        if (tableName == 'r_device_relation' && operType == null) {//此表传来的表数据为多条，需要进一步解析
            let sqls = [];//存放此表所有数据生成的sql
            let del = tableDatas['delete'];//去除delete对应的数据
            if (del) {
                for (let i = 0, len = del.length; i < len; i++) {//分别对单条数据进行处理
                    //调用自身函数，此时数据为单条，为防止再次进入此if，故把operType置为null
                    let sql = getOperateSql('2', tableName, del[i]);
                    sqls.push(sql);
                }
            }
            let add = tableDatas['add'];
            if (add) {
                for (let i = 0, len = add.length; i < len; i++) {
                    //调用自身函数，此时数据为单条，为防止再次进入此if，故把operType置为null
                    let sql = getOperateSql('1', tableName, add[i]);
                    sqls.push(sql);
                }
            }
            return sqls;//返回sql的集合
        }
        for (let tableData in tableDatas) {
            placeholder[j] = '?';
            fieldName[j] = tableData;
            fieldData[j] = tableDatas[tableData];
            str += tableData + '=' + placeholder[j] + ' and ';
            j++;
        }
        str = str.substring(0, str.length - 4);
        if (operType == '2') {
            //删除语句
            let sql = 'delete from ' + tableName + ' where ' + str;
            return {sql: sql, params: fieldData};
        } else {
            //手动为r_device_relation加入俩个字段数据
            if (tableName == 'r_device_relation') {
                fieldName[j] = 'dt_create';
                fieldData[j] = sd.format(new Date(), 'YYYY-MM-DD HH:mm:ss');
                placeholder[j] = '?';
                fieldName[j + 1] = 'user_create';
                fieldData[j + 1] = 'collecter';
                placeholder[j + 1] = '?';
            }
            //更新查询语句
            let sql = 'REPLACE INTO ' + tableName + '(' + fieldName + ')' + 'values(' + placeholder + ')';
            return {sql: sql, params: fieldData};
        }
    };
}


module.exports = new AssetOperation();


