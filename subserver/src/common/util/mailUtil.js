/**
 * Created by yaoxinyu on 2018/1/28
 * @file node中发送邮件工具类
 * @desc 使用nodemailer模块
 */

'use strict';

var mailer = require('nodemailer');
var linkAffairDB = require('../../linkAffair/DB/linkAffairDao');
const logger = require('./logger').getLogger(0);
const SEND_MAIL_INTERVAL = 5000;  // 邮件发送间隔


function MailUtil() {
    var transporter;
    var mailQueue = [];  // 待发送邮件队列
    var isInit = false;
    // 邮件服务器配置信息
    var transportConfig = {};
    // 发件人邮件地址
    var fromEmailAddress = null;

    /**
     * 模块初始化
     */
    this.init = async function () {
        if (isInit) {
            return true;
        }

        let bInitOK;
        do {
            // 从数据库读取邮件服务器配置信息
            // SELECT a.contents AS "serverConfig" FROM ipole.d_server_config a WHERE a.sc_type = 1 LIMIT 1
            let emailConfig = await linkAffairDB.getEmailConfig();
            if(!emailConfig || emailConfig.length == 0) {
                logger.error('数据库未查到邮件配置信息内容!');
                break;
            }
            let emailConfigJson = null;
            try {
                emailConfigJson = JSON.parse(emailConfig[0].serverConfig);
            } catch (exception) {
                logger.error('解析邮件配置信息异常：', exception.message);
            }
            if(!emailConfigJson) {
                logger.error('邮件配置JSON格式错误!');
                break;
            }
            let serverHost = emailConfigJson['SMTP_HOST'];
            if(serverHost == '') {
                logger.error('邮件服务器ip为空!');
                break;
            }
            let serverPort = emailConfigJson['SMTP_PORT'];
            if(serverPort == '') {
                logger.error('邮件服务器端口为空!');
                break;
            }
            let authUser = emailConfigJson['AUTH_USER'];
            if(authUser == '') {
                logger.error('发件人为空!');
                break;
            }
            let authPasswd = emailConfigJson['AUTH_PWD'];
            if(authPasswd == '') {
                logger.error('邮箱登录密码为空!');
                break;
            }
            let fromAddr = emailConfigJson['FROM_ADDR'];
            if(fromAddr == '') {
                logger.error('发件人Email为空!');
                break;
            }

            // 没有错误
            fromEmailAddress = fromAddr;
            transportConfig.host = serverHost;              // 主机
            transportConfig.secureConnection = true;        // 使用SSL标记
            transportConfig.port = Number(serverPort);      // SMTP 端口
            transportConfig.auth = {};
            transportConfig.auth.user = authUser;           //邮箱登录账号
            transportConfig.auth.pass = authPasswd;         //邮箱登录密码，使用QQ邮箱时必须使用QQ邮箱里的授权码
            bInitOK = true;
        } while (false);

        if (bInitOK) {
            transporter = mailer.createTransport(transportConfig);
            // 启动定时任务，驱动发送邮件
            setInterval(scheduleSendMail, SEND_MAIL_INTERVAL);
            isInit = true;
        } else {
            logger.error('邮件发送配置初始化失败!');
        }

        return isInit;
    };

    /**
     * 发送邮件接口
     * @param mailOptions 邮件发送信息
     */
    this.sendEmail = function (mailOptions) {
        let sendOptions = {
            from: fromEmailAddress,         // 必填 发送者
            to: mailOptions.to,             // 必填 接受者,可以同时发送多个,以逗号隔开
            subject: mailOptions.subject,   // 必填 标题
            text: mailOptions.text,         // 文本
        };
        if (mailOptions.html) {
            // 邮件内容
            sendOptions.html = mailOptions.html;
        }
        if (mailOptions.attachments) {
            // 附件
            sendOptions.attachments = mailOptions.attachments;
        }

        // 这里不立即发送，加入队列，由定时任务驱动
        logger.info('将待发送邮件[%s]加入队列', JSON.stringify(sendOptions));
        mailQueue.unshift(sendOptions);
    };

    /**
     * 定时任务
     */
    var scheduleSendMail = function () {
        if (mailQueue.length == 0) {
            return;
        }

        // 从队列取出一个待发送邮件
        let sendOptions = mailQueue.pop();
        if (transporter) {
            transporter.sendMail(sendOptions, function (err, info) {
                if (err) {
                    logger.error('邮件发送出错：', err);
                    return;
                }

                logger.info('邮件[%s]发送成功', JSON.stringify(sendOptions));
            });
        }
    };
}


var mailUtil = new MailUtil();
//mailUtil.init();


module.exports = mailUtil;

