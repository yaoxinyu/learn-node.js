/**
 * @file 定时任务管理类
 * Created by wangweizhen on 2017/11/24.
 * modify by yaoxinyu 2018/2/9
 */

var schedule = require('node-schedule');

class ScheduleJobMgr {
    constructor() {
        // 管理job的话，可以使用命名job，用name做key job对象做value
        // this.jobMap = new Map();
    }

    /**
     * 创建一个定时任务
     * @param rule 定时规则 1、确定的时间可以传Date()；2、其他参考schedule.RecurrenceRule()
     * @return {Object} job对象
     */
    newJob(rule, callback) {
        if (rule) {
            return schedule.scheduleJob(rule, callback);
        }
        return null;
    }

    /**
     * 设置定时任务按照新规则执行
     * @param job
     * @param rule
     * @return {Object} job对象
     */
    reScheduleJob(job, rule) {
        if (job && rule) {
            return schedule.rescheduleJob(job, rule);
        }
        return null;
    }

    /**
     * 取消定时任务
     * @param job
     */
    cancelJob(job) {
        if (job) {
            schedule.cancelJob(job);
        }
    }
}


// 导出
var jobManager = new ScheduleJobMgr();

module.exports = {
    jobRule: schedule.RecurrenceRule, // 外部需要new
    jobMgr: jobManager
};
