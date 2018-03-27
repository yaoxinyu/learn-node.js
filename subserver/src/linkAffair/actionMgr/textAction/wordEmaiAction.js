/**
 * 执行发送邮件的动作
 * by 潘翔 on 2018/2/2
 */

var mailUtil = require('../../../common/util/mailUtil');
var linkAffairDB = require('../../DB/linkAffairDao');
var commonModule = require('../../../commonModuleExport');
const logger = commonModule.logger.getLogger(0);

function WordEmailAction() {
    /**
     * 执行发送邮件的动作
     * @param content 邮件内容
     * @param ccIDs 邮件收件人ID列表 Array
     * @return {Promise.<void>}
     */
    this.executeAction = async function (content, ccIDs) {
        if (!ccIDs || ccIDs.length == 0) {
            logger.error('邮件动作收件人为空！');
            return;
        }

        for (let ccID of ccIDs) {
            let concatNumberModel = await linkAffairDB.getConcatNumberById(ccID);
            logger.info('查询到邮件动作收件人信息：', concatNumberModel);
            if (concatNumberModel && concatNumberModel[0].emailAddress !== '') {
                let mailOptions = {};
                mailOptions.to = concatNumberModel[0].emailAddress;
                mailOptions.subject = content;//主题 content
                mailOptions.text = content;
                mailOptions.html = content;
                mailUtil.sendEmail(mailOptions);
            }
        }
    }
}

var wordEmailAction = new WordEmailAction();

module.exports = wordEmailAction;