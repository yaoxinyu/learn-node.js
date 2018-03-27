/**
 * http client工具类模块，功能描述：
 * 在request模块基础上封装http请求的接口，方便外部调用；
 * @author yaoxinyu
 * @date 2017/12/22
 */

// 使用node request模块
var request = require('request');
var queryString = require('querystring');
var commonModule = require('../../commonModuleExport');
const loggerReq = commonModule.logger.getLogger(1);

/**
 * http client
 * @constructor
 */
function HttpClient() {
    // http请求的参数，结构为HttpRequestOptions
    var requestOptions = {};

    /**
     * 发送http请求
     * @param onHttpResponse 外部提供回调函数 onHttpResponse(error, response, body)
     * error：错误信息；response：http response对象；body：返回的body数据
     */
    this.sendRequest = function (httpOptions, onHttpResponse) {
        requestOptions = httpOptions;
        if (httpOptions.method) {
            // 统一转换成大写
            requestOptions.method = httpOptions.method.toUpperCase();
        }
        // 构造http请求参数
        let req = buildRequestParam();
        loggerReq.info('发送http请求数据：',JSON.stringify(req));
        // 不同的请求，调用不同的接口
        switch (requestOptions.method) {
            case 'GET':
                httpGet(req, onHttpResponse);
                break;
            case 'POST':
                httpPost(req, onHttpResponse);
                break;
            case 'PUT':
                httpPut(req, onHttpResponse);
                break;
            case 'DELETE':
                httpDelete(req, onHttpResponse);
                break;
            default:
                break;
        }
    };

    /**
     * 发送get请求
     * @param req http请求体
     * @param onResponse http响应回调函数
     */
    var httpGet = function (req, onResponse) {
        request.get(req, function (error, response, body) {
            onResponse(error, response, body);
        });
    };

    /**
     * 发送post请求 需要根据Content-Type值决定post方式：
     * 1、'application/x-www-form-urlencoded'：普通http请求方式，参数是普通的url参数拼接；
     * 2、'application/json'：JSON请求方式，参数是json格式
     * 3、'multipart/form-data'：文件上传
     * @param req http请求体
     * @param onResponse http响应回调函数
     */
    var httpPost = function (req, onResponse) {
        request.post(req, function (error, response, body) {
            onResponse(error, response, body);
        });
    };

    /**
     * 发送delete请求
     * @param req http请求体
     * @param onResponse http响应回调函数
     */
    var httpDelete = function (req, onResponse) {
        request.delete(req, function (error, response, body) {
            onResponse(error, response, body);
        });
    };

    /**
     * 发送put请求
     * @param req http请求体
     * @param onResponse http响应回调函数
     */
    var httpPut = function (req, onResponse) {
        request.put(req, function (error, response, body) {
            onResponse(error, response, body);
        });
    };

    /**
     * 根据requestOptions构造request请求的param
     * @return {object} request请求的param
     */
    var buildRequestParam = function () {
        let req = {};
        let requestUrl = requestOptions.url;
        let contentType = null;  // post put delete默认值为application/x-www-form-urlencoded
        if (requestOptions.headers) {
            contentType = requestOptions.headers['Content-Type'];
        }
        contentType = contentType ? contentType : 'application/x-www-form-urlencoded';

        // 不同的请求，param不同
        switch (requestOptions.method) {
            case 'GET':
            // 构造get请求的完整url，包括参数
                if (requestOptions.data) {
                    requestUrl += '?' + queryString.stringify(requestOptions.data);
                }

                req = {
                    url: requestUrl,
                    headers: requestOptions.headers
                };
                break;
            case 'POST':
            case 'PUT':
            case 'DELETE':
                if (contentType.includes('application/x-www-form-urlencoded')) {
                // 普通http post方式，参数是普通的url参数拼接
                    if (requestOptions.data) {
                        requestUrl += '?' + queryString.stringify(requestOptions.data);
                    }

                    req = {
                        url: requestUrl,
                        headers: requestOptions.headers
                    };
                } else if (contentType.includes('application/json')) {
                    req = {
                        url: requestUrl,
                        headers: requestOptions.headers,
                        json: true,
                        body: requestOptions.data
                    };
                } else if (contentType.includes('multipart/form-data')) {
                    req = {
                        url: requestUrl,
                        headers: requestOptions.headers,
                        formData: requestOptions.data
                    };
                } else {
                // do nothing
                }
                break;
            default:
                break;
        }

        return req;
    };
}

/**
 * http请求参数
 * @constructor
 */
function HttpRequestOptions() {
    this.url = '';                  // http请求的url
    this.method = 'GET';            // http请求方法
    this.headers = null;            // http请求头部
    this.data = null;               // http请求体
}


module.exports = {
    httpClient: HttpClient,
    httpReqOptions: HttpRequestOptions
};