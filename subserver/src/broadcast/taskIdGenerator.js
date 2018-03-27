/**
 * 任务ID生成器
 * 功能描述：生成全局唯一的任务ID
 * @author yaoxinyu
 * @date 2017/11/2
 */

// 定义最大的任务ID号
const maxTaskId = 99999;
// 任务ID，全局变量
var taskId = 0;


/**
 * 任务ID生成器类
 * @constructor
 */
function TaskIdGenerator() {
    this.generateTaskId = function () {
        taskId++;
        if (taskId == maxTaskId) {
            // 超过后继续从1开始
            taskId = 1;
        }
        return taskId;
    }
}


// 全局单一实例
var generator = new TaskIdGenerator();
module.exports = generator;