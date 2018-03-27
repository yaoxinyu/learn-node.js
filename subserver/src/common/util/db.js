/**
 * @file sql工具类
 * @author wangweizhen
 * @date 2017/10/20
 */
var commonModele = require('../../commonModuleExport');
var globalData = require('../../globalDataCache');
var mysql = require('mysql2');
var async = require('async');
var SqlUtils = require('./sql');
var logger = commonModele.logger.getLogger(2);
var errorDefine = commonModele.errDef;
/**
 *数据库操作，数据库连接、查询、插入、修改、删除等.
 *
 */

function DBService() {
    // this.initPool();
    this.dbClient;
}


DBService.prototype = {
    /**
     * 初始化数据库连接池.
     * 数据库配置项从db-config.json中获取
     */
    initPool: function () {
        logger.debug('初始化数据库连接池......');
        let config = globalData.getConfigData();
        this.pool = mysql.createPool(
            config.dbConfig
            // {
            //     "host": "172.17.2.88",
            //     "user": "root",
            //     "password": "gcsoft123",
            //     "database": "cishi",
            //     "port": 9003,
            //     "Promise": "bluebird",
            //     "wait_timeout": 10
            // }
        );
        logger.info('数据库连接池初始化完毕');
    },

    /**
     * 获取数据库连接.
     */
    getConnection: function () {
        logger.debug('获取数据库连接......');
        return new Promise((resolve, reject) => {
            this.pool.getConnection((err, connection) => {
                if (err) {
                    logger.error(errorDefine.DB.CONNECTION_FAIL + err.message);
                    reject(err);
                } else {
                    logger.info('数据库连接成功');
                    resolve(connection);
                }
            });
        });
    },

    /**
     * 查询数据，返回单条数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 返回JSON
     */
    query: async function (sqlId, params) {
        logger.debug('查询单条数据......');
        try {
            var connection = await this.getConnection();
        } catch (err) {
            connection = null;
        }
        if (connection) {
            try {
                return new Promise((resolve, reject) => {
                    logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
                    connection.query(SqlUtils.getSql(sqlId), params, (err, rows, filed) => {
                        if (err) {
                            logger.error(errorDefine.DB.QUERY_ERROR + err.message);
                            resolve(-1);
                        } else {
                            logger.info('查询结果:' + JSON.stringify(rows));
                            if (rows.length) {
                                resolve(rows[0]);
                            } else {
                                resolve(null);
                            }
                        }
                    });
                });
            } catch (err) {
                logger.error(errorDefine.DB.QUERY_EXCEPTION + err.message);
                return -1;
            } finally {
                logger.info('释放连接');
                connection.release();
            }
        } else {
            logger.error('连接断开');
            return null;
        }
    },

    /**
     * 查询数据，返回多条数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 返回JSON
     */
    queryList: async function (sqlId, params) {
        try {
            var connection = await this.getConnection();
        } catch (err) {
            connection = null;
        }
        if (connection) {
            try {
                return new Promise((resolve, reject) => {
                    logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
                    connection.query(SqlUtils.getSql(sqlId), params, (err, rows, filed) => {
                        if (err) {
                            logger.error(errorDefine.DB.QUERY_ERROR + err.message);
                            resolve(-1);
                        } else {
                            logger.info('查询结果: ' + JSON.stringify(rows));
                            if (rows) {
                                resolve(rows);
                            } else {
                                resolve([]);
                            }
                        }
                    });
                });
            } catch (err) {
                logger.error(errorDefine.DB.QUERY_EXCEPTION + err.message);
                return -1;
            } finally {
                logger.info('释放连接');
                connection.release();
            }
        } else {
            logger.error('连接断开');
            return -1;
        }
    },

    /**
     * 插入数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 影响的行数
     */
    insert: async function (sqlId, params) {
        try {
            var connection = await this.getConnection();
        } catch (err) {
            connection = null;
        }
        if (connection) {
            try {
                return new Promise((resolve, reject) => {
                    logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
                    connection.execute(SqlUtils.getSql(sqlId), params, (err, result) => {
                        if (err) {
                            logger.error(errorDefine.DB.INSERTION_ERROR + err.message);
                            resolve(-1);
                        } else {
                            logger.info('插入数据，影响结果: ' + result['affectedRows']);
                            resolve(result);
                        }
                    });
                });
            } catch (err) {
                logger.error(errorDefine.DB.INSERTION_EXCEPTION + err.message);
                return -1;
            } finally {
                logger.info('释放连接');
                connection.release();
            }
        } else {
            logger.error('连接中断');
        }
    },

    /**
     * 修改数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 影响的行数
     */
    update: async function (sqlId, params) {
        try {
            var connection = await this.getConnection();
        } catch (err) {
            connection = null;
        }
        if (connection) {
            try {
                return new Promise((resolve, reject) => {
                    logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
                    connection.execute(SqlUtils.getSql(sqlId), params, (err, result) => {
                        if (err) {
                            logger.error(errorDefine.DB.UPDETE_ERROR + err.message);
                            resolve(-1);
                        } else {
                            logger.info('修改数据，影响结果: ' + result['affectedRows']);
                            resolve(result);
                        }
                    });
                });
            } catch (err) {
                logger.error(errorDefine.DB.UPDATE_ANOMALY + err.message);
                return -1;
            } finally {
                logger.info('释放连接');
                connection.release();
            }
        } else {
            logger.error('连接中断');
        }
    },

    /**
     * 删除数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 影响的行数
     */
    delete: async function (sqlId, params) {
        try {
            var connection = await this.getConnection();
        } catch (err) {
            connection = null;
        }
        if (connection) {
            try {
                return new Promise((resolve, reject) => {
                    logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
                    connection.execute(SqlUtils.getSql(sqlId), params, (err, result) => {
                        if (err) {
                            logger.error(errorDefine.DB.DELETE_ERROR + err.message);
                            resolve(-1);
                        } else {
                            logger.info('删除数据，影响结果: ' + result['affectedRows']);
                            resolve(result);
                        }
                    });
                });
            } catch (err) {
                logger.error(errorDefine.DB.DELETE_EXCEPTION + err.message);
                return -1;
            } finally {
                logger.info('释放连接');
                connection.release();
            }
        } else {
            logger.error('连接中断');
        }
    },


    /**
     * 批量插入数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 影响的行数，数组
     */
    batchInsert: async function (sqlId, params) {
        logger.debug('执行批量插入数据操作......');
        let sql1 = SqlUtils.getSql(sqlId);
        logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
        let sqlparamsEntities = this.paramsMask(sql1, params);
        return await this.batch(sqlparamsEntities);
    },

    /**
     * 批量修改数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 影响的行数，数组
     */
    batchUpdate: async function (sqlId, params) {
        logger.debug('执行批量修改数据操作......');
        let sql1 = SqlUtils.getSql(sqlId);
        logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
        let sqlparamsEntities = this.paramsMask(sql1, params);
        return await this.batch(sqlparamsEntities);
    },

    /**
     * 批量删除数据.
     * @param sqlId sql的id
     * @param params sql 参数
     * @return 影响的行数，数组
     */
    batchDelete: async function (sqlId, params) {
        logger.debug('执行批量删除数据操作......');
        let sql1 = SqlUtils.getSql(sqlId);
        logger.debug('sql: ' + SqlUtils.getSql(sqlId) + ', params: ' + params);
        let sqlparamsEntities = this.paramsMask(sql1, params);
        return await this.batch(sqlparamsEntities);
    },

    /**
     * 执行sql.
     * @param fun 回调函数
     * @param fun.connection 数据库连接
     */
    execute: async function (fun) {
        try {
            var connection = await this.getConnection();
        } catch (err) {
            connection = null;
        }
        fun(connection);
        logger.info('释放连接');
        connection.release();
    },

    /**
     * 关闭数据库连接.
     * @param conn 数据库连接
     */
    /**
     closeConn: function (conn) {
        conn.end(function(err){
            logger.log(err);
        });
    },

     /**
     * 关闭数据库连接池.
     *
     */
    closePool: function () {
        this.pool.end(function (err) {
            logger.error(err);
        });
        logger.info('数据库连接池关闭');
    },

    /**
     *
     * @param sqlparamsEntities JSON封装的sql和参数的数组
     * @param callback
     * @returns {Promise.<void>}
     */
    execTrans: async function (sqlparamsEntities, callback) {
        try {
            var connection = await this.getConnection();
        } catch (err) {
            connection = null;
        }
        if (connection) {
            connection.beginTransaction(function (err) {
                if (err) {
                    return callback(err, null);
                }
                logger.debug('开始执行transaction，共执行' + sqlparamsEntities.length + '条数据');
                var funcAry = [];
                sqlparamsEntities.forEach(function (sql_param) {
                    var temp = function (cb) {
                        var sql = sql_param.sql;
                        var param = sql_param.params;
                        logger.debug('sql: ' + sql + ',param: ' + param);
                        connection.execute(sql, param, function (tErr, rows, fields) {
                            if (tErr) {
                                connection.rollback(function () {
                                    logger.error('事务失败，' + sql_param + '，ERROR：' + tErr);
                                    // throw tErr;
                                    return cb(tErr, null);
                                });
                            } else {
                                return cb(null, rows['affectedRows']);
                            }
                        })
                    };
                    funcAry.push(temp);
                });

                async.series(funcAry, function (err, result) {
                    if (err) {
                        connection.rollback(function () {
                            logger.error('transaction error: ' + err);
                            logger.info('释放连接');
                            connection.release();
                            return callback(err, null);
                        });
                    } else {
                        connection.commit(function (err, info) {
                            logger.error('transaction info: ' + JSON.stringify(info));
                            if (err) {
                                logger.error('执行事务失败，' + err.message);
                                connection.rollback(function (err) {
                                    logger.error('transaction error: ' + err);
                                    logger.info('释放连接');
                                    connection.release();
                                    return callback(err, null);
                                });
                            } else {
                                logger.info('释放连接');
                                connection.release();
                                return callback(null, result);
                            }
                        })
                    }
                })
            });
        } else {
            logger.error('连接中断');
        }
    },

    /**
     *
     * @param sql1 sql语句
     * @param sqlParamsEntity sql语句的参数
     * @returns {Array}
     */
    paramsMask: function (sql1, sqlParamsEntity) {
        let sqlparamsEntities = [];

        function _getNewSqlParamEntity(sql1, params) {
            return {
                sql: sql1,
                params: params
            }
        }

        for (var i = 0, len = sqlParamsEntity.length; i < len; i++) {
            sqlparamsEntities.push(_getNewSqlParamEntity(sql1, sqlParamsEntity[i]));
        }
        return sqlparamsEntities;
    },

    /**
     *
     * @param sqlparamsEntities JSON封装的sql和参数的数组
     * @returns {Promise}Promise包装的事务执行结果
     */
    batch: function (sqlparamsEntities) {
        let re = {err: null, result: null};
        return new Promise((resolve, reject) => {
            this.execTrans(sqlparamsEntities, (err, result) => {
                if (err) {
                    re.err = err.message;
                } else {
                    logger.info('数据库事务执行，影响结果: ' + result);
                    re.result = result;
                }
                resolve(re)
            })
        });
    },

    /**
     * 开启数据库事务
     * @return {Promise.<void>}
     */
    beginTransaction: async function () {
        logger.debug('开启事务......');
        try {
            let connection = await this.getConnection();//从数据库连接池获取连接
            this.dbClient = new Transaction(connection);//数据库事务对象
            await this.dbClient.startTransConnect();//开启事务
        } catch (err) {
            throw err;
        }
    },

    /**
     * 开启事务后，sql插入语句
     * @param sql
     * @param param
     */
    insertBatch: function (sql, param) {
        this.dbClient.query(sql, param);
    },

    /**
     * 开启事务后，sql更新语句
     * @param sql
     * @param param
     */
    updateBatch: function (sql, param) {
        this.dbClient.query(sql, param);
    },

    /**
     * 开启事务后，sql删除语句
     * @param sql
     * @param param
     */
    deleteBatch: function (sql, param) {
        this.dbClient.query(sql, param);
    },

    /**
     * 开启事务后，sql查询语句
     * @param sql
     * @param param
     */
    queryBatch: function (sql, param) {
        this.dbClient.query(sql, param);
    },

    /**
     * 事务commit
     * @return {Promise}
     */
    transCommit: function () {
        return new Promise((resolve, reject) => {
            this.dbClient.commit((err, result) => {
                if (err) {
                    logger.error('事务执行错误：', err.message);
                    resolve({err: err.message, result: null});
                } else {
                    logger.info('事务处理执行成功');
                    resolve({err: null, result: result});
                }
            });
        });
    }
};

/**
 * 数据库事务操作类
 * @param connection 数据库连接
 * @constructor
 */
function Transaction(connection) {
    // 数据库连接
    this.connection = connection;
    this.excuteQueue = [];

    this.startTransConnect = async function () {
        return new Promise((resolve, reject) => {
            connection.beginTransaction((err) => {
                if (err) {
                    logger.error('事务开启失败: ', err.message);
                    reject(err);
                    resolve(false);
                } else {
                    logger.info('开始数据库事务......');
                    resolve(true);
                }
            });
        });
    };

    /**
     * 查询
     */
    this.query = function (sql, param) {
        // 加入队列
        logger.info('事务处理的语句，sql:' + sql + ',param:' + param);
        let temp = function (cb) {
            connection.query(sql, param, function (err, rows) {
                if (err) {
                    connection.rollback(function () {
                        logger.error('事务sql语句执行失败，ERROR：' + err.message);
                        return cb(err, null);
                    });
                } else {
                    return cb(null, rows['affectedRows']);
                }
            })
        };
        this.excuteQueue.push(temp);
    };

    /**
     * 事务提交
     */
    this.commit = function (callback) {
        async.series(this.excuteQueue, function (err, result) {
            if (err) {
                connection.rollback(function () {
                    logger.error('SQL语句同步执行错误，error: ' + err);
                    logger.info('释放数据库事务连接');
                    connection.release();
                    return callback(err, null);
                });
            } else {
                connection.commit(function (err, info) {
                    if (err) {
                        logger.error('执行事务失败，' + err.message);
                        connection.rollback(function (err) {
                            logger.error('transaction error: ' + err);
                            logger.info('释放数据库事务连接');
                            connection.release();
                            return callback(err, null);
                        });
                    } else {
                        logger.error('事务提交成功：' + JSON.stringify(info));
                        logger.info('释放数据库事务连接');
                        connection.release();
                        return callback(null, result);
                    }
                })
            }
        })
    };
}


module.exports = new DBService();
  