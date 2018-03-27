/**
 * @file 文件工具类
 * @author yaoxinyu
 * @date 2017/9/18
 */

// 引入file system
var fs = require('fs');
var path = require('path');
// 引入常量定义模块
var constants = require('../constant');
// 引入错误定义模块
var errorDefine = require('../errorDefine');

function FileUtil() {
    this.path = path;
    /**
     * 获取项目根目录
     * @return {string}
     */
    this.getRootPath = function () {
        let projectName = constants.PROJECT_NAME;
        let index = __dirname.lastIndexOf(projectName);
        if (index == -1) {
            return __dirname;
        }
        else {
            return __dirname.substring(0, index + projectName.length + 1);
        }
    };

    /**
     * 创建新的文件目录 （同步方式）
     * @param filePath 文件目录路径
     */
    this.createDir = function (filePath) {
        if (!fs.existsSync(filePath)) {
            fs.mkdirSync(filePath);
        }
    };

    /**
     * 读取文件内容（同步方式）
     * @param {String} filePath 文件路径
     */
    this.readFileBySync = function (filePath, encoding) {
        let content = null;
        let encode = encoding ? encoding : constants.CHARSET.UTF8; // 默认使用UTF-8
        if (fs.existsSync(filePath)) {
            content = fs.readFileSync(filePath, encode);
        }
        return content;
    };

    /**
     * 读取文件内容（异步方式）
     * @param {String} filePath 文件路径
     * @param {function} callBackFunc 异步读取回调函数
     */
    this.readFileByASync = function (filePath, callBackFunc) {
        if (fs.existsSync(filePath)) {
            fs.readFile(filePath, constants.CHARSET.UTF8, callBackFunc);
        }
        else {
            callBackFunc(errorDefine.FILE_NOT_EXIST);
        }
    };

    /**
     * 判断指定路径文件是否存在
     * @param {String} filePath 文件路径
     * @return {boolean} 存在返回true，不存在返回false
     */
    this.fileExist = function (filePath) {
        return fs.existsSync(filePath);
    };

    /**
     * 同步读取文件内容
     * @param relativePath 文件相对路径
     * @returns {JSON} JSON格式的文件内容
     */
    this.loadFileBySync = function (relativePath) {
        try {
            let jsonData = {};
            let filePath = path.join(this.getRootPath(), relativePath);
            let buffer = this.readFileBySync(filePath);
            if (buffer) {
                jsonData = JSON.parse(buffer);
            }
            return jsonData;
        } catch (exception) {
            console.error('读取文件[%s]异常[%s]!', relativePath, exception.message);
            return null;
        }
    };

    /**
     * 异步读取文件内容
     * @param relativePath 文件相对路径
     * @param callback 异步回调函数
     */
    this.loadFileByASync = function (relativePath, callback) {
        let filePath = path.join(this.getRootPath(), relativePath);
        this.readFileByASync(filePath, function (err, data) {
            callback(err, data);
        });
    };

    /**
     * 同步获取文件信息
     * @param filePath
     * @return
     */
    this.statSync = function (filePath) {
        if (fs.existsSync(filePath)) {
            let info = fs.statSync(filePath);
            return info;
        }
        return null;
    };

    /**
     * 同步写入数据
     * @param filePath 文件写入的绝对路径
     * @param data 数据
     * @param encoding 编码
     * @return {boolean} 返回操作结果
     */
    this.writeFileSync = function (filePath, data, encoding) {
        try {
            fs.writeFileSync(filePath, data, encoding);
            return true;
        } catch (exception) {
            console.error('写文件[%s]异常[%s]!', filePath, exception.message);
            return false;
        }
    };

    /**
     * 清空文件夹
     * @param folderPath
     */
    this.emptyFolder = function (folderPath) {
        if (this.fileExist(folderPath)) {
            var dirList = fs.readdirSync(folderPath);
            dirList.forEach(function (fileName) {
                fs.unlinkSync(folderPath + '\\' + fileName);
            });
        }
    };

    /**
     * 删除文件夹中修改时间超时的文件夹
     * @param folderPath
     * @param time 时间段
     */
    this.deleteFile = function (folderPath, time) {
        let times = 172800000;//毫秒，两天
        if(time){
            times = time;
        }
        if (this.fileExist(folderPath)) {
            var dirList = fs.readdirSync(folderPath);
            let that = this;
            dirList.forEach(function (fileName) {
                let filePath = folderPath + '\\' + fileName;
                let info = fs.statSync(filePath);
                if(info){
                    if(new Date().getTime() - new Date(info.ctime).getTime() > times){
                        that.deleteDir(filePath);
                    }
                }
            });
        }
    };

    /**
     * 创建深层文件夹
     * @param dirPath 文件夹路径
     * @param dirName 文件夹名（不传,递归调用时用到的）
     */
    this.mkDir = function (dirPath,dirName){
        //判断是否是第一次调用
        if(typeof dirName === 'undefined'){
            if(fs.existsSync(dirPath)){
                return;
            }else{
                this.mkDir(dirPath,path.dirname(dirPath));
            }
        }else{
            //判断第二个参数是否正常，避免调用时传入错误参数
            if(dirName !== path.dirname(dirPath)){
                this.mkDir(dirPath);
                return;
            }
            if(fs.existsSync(dirName)){
                fs.mkdirSync(dirPath)
            }else{
                this.mkDir(dirName,path.dirname(dirName));
                fs.mkdirSync(dirPath);
            }
        }
    }

    /**
     * 删除文件夹及文件夹下面的子文件夹和文件
     * @param path 文件夹
     */
    this.deleteDir = function(path) {
        var files = [];
        if( fs.existsSync(path) ) {
            files = fs.readdirSync(path);
            let that = this;
            files.forEach(function(file,index){
                var curPath = path + '/' + file;
                if(fs.statSync(curPath).isDirectory()) { // recurse
                    that.deleteDir(curPath);
                } else { // delete file
                    fs.unlinkSync(curPath);
                }
            });
            fs.rmdirSync(path);
        }
    };
}

module.exports = new FileUtil();