/**
 * Created by panxiang on 2018/2/2.
 */
/**
 * WordBigScreenAction 执行大屏动作
 * by 潘翔 on 2018/2/2
 */

function WordBigScreenAction() {
    /**
     * executeAction 执行大屏动作
     * @param
     *    content:告警的内容
     *    type:字段为type中的各个json对象值(比如:{"code":"1","param":""})
     *    actionModeParamModel:动作参数模型
     *    message:原始告警的信息
     * by 潘翔 on 2018/2/2
     */
    this.executeAction = function (content, type, actionModeParamModel, message) {
        //TODO 不需要返回 直接在大屏上播放
        console.log('文字提示:开始组装发送到大屏');
        let arrParams = type.param;
        console.log('文字提示:组装内容发送到大屏成功');
    }
}

var wordBigScreenAction = new WordBigScreenAction();
module.exports = wordBigScreenAction;