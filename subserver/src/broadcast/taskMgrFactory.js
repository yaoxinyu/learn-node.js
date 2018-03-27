/**
 * 任务管理器生产类模块
 * 功能描述：根据不同厂家类型导出对应的任务管理器对象
 * @author yaoxinyu
 * @date 2017/10/31
 */

var commonModule = require('../commonModuleExport');
// 常量模块
const constants = commonModule.constants;

/**
 * 对外导出一个接口，获取任务管理类对象
 */
function TaskMgrFactory() {
    // 任务管理器map，每个厂商对应一个任务管理器实例
    var managerMap = new Map();

    /**
     * 初始化生成各个厂商的任务管理器
     */
    this.init = function () {
        // 目前只有美电贝尔
        let taskMgr = require('./aebell/aebellTaskMgr');
        managerMap.set(constants.BROADCAST_FACTORY.AEBELL, taskMgr);
    };

    /**
     * 获取对应设备厂商的任务管理器对象
     * @param facType 设备厂商类型
     * @return 任务管理器对象
     */
    this.getManager = function (facType) {
        if (managerMap.has(facType)) {
            // 已存在，从map中直接返回
            return managerMap.get(facType);
        } else {
            let taskMgr = null;
            // 创建对象并加入到map中
            switch (facType) {
                case constants.BROADCAST_FACTORY.AEBELL:
                    taskMgr = require('./aebell/aebellTaskMgr');
                    break;
                case constants.BROADCAST_FACTORY.PASTAR:
                // TODO 暂时没有
                    break;
                default:
                // DO nothing
                    break;
            }

            if (taskMgr) {
                managerMap.set(facType, taskMgr);
            }
            return taskMgr;
        }
    };
}


// 实例
var instance = new TaskMgrFactory();
module.exports = instance;
