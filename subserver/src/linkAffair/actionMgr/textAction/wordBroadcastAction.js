/**
 * Created by panxiang on 2018/2/2.
 */
/**
 * 执行广播的文本动作
 * by 潘翔 on 2018/2/2
 */

function WordBroadcastAction() {
    /**
     * executeAction 执行广播动作
     * @param
     *    content:告警的内容
     *    type:字段为type中的各个json对象值(比如:{"code":"1","param":""})
     *    actionModeParamModel:动作参数模型
     *    message:原始告警的信息
     * by 潘翔 on 2018/2/2
     */
    this.executeAction = function (content, type, actionModeParamModel, message) {
        //TODO 有待实现
    }
}

var wordBroadcastAction = new WordBroadcastAction();
module.exports = wordBroadcastAction;