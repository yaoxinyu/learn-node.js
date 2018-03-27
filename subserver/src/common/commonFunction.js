/**
 * @file 共通的JS函数
 * @author yaoxinyu
 * @date 2017/12/11
 */


/**
 * 深拷贝 object对象
 * @param obj
 * @return 拷贝后的object
 */
var cloneObj = function (obj) {
    var result;
    if (typeof obj == 'object') {
        if (obj === null) {
            result = null;
        } else {
            if (obj instanceof Array) {
                result = [];
                for (let i = 0, len = obj.length; i < len; i++) {
                    result.push(cloneObj(obj[i]));
                }
            } else {
                result = {};
                for (let j in obj) {
                    result[j] = cloneObj(obj[j]);
                }
            }
        }
    } else {
        result = obj;
    }
    return result;
};



module.exports = {
    clone: cloneObj
};