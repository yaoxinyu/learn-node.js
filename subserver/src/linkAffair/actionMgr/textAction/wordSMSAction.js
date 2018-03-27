/**
 * Created by panxiang on 2018/2/2.
 */
/**
 * 执行短信的动作
 * by 潘翔 on 2018/2/2
 */

function WordSMSAction() {
    /**
     * executeAction : 执行短息发送动作
     * @param
     *    content:告警的内容,string类型
     *    type:字段为type中的各个json对象值(比如:{"code":"1","param":""})对象类型
     *    actionModeParamModel:动作参数模型,对象类型
     *    message:原始告警的信息,对象类型
     * by 潘翔 2018/2/2
     */
    this.executeAction = function (content, type, actionModeParamModel, message) {
        //TODO 仅仅就是发短信,不需要返回信息

    }
}

var wordSMSAction = new WordSMSAction();
module.exports = wordSMSAction;