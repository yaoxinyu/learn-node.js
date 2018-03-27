/**
 * Created by wangweizhen on 2017/11/17.
 */

/**
 * 睡眠阻塞
 * @param time
 * @return {Promise}
 */
var sleep = function (time) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve(null);
        }, time);
    });
};
module.exports = sleep;