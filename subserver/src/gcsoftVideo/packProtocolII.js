/**
 * 用于封装视频II协议模块
 * @author 潘翔
 * @date 2017/12/01
 */

function PackVideoProtocolII() {
    /**
     *@brief   打包II协议的头部,将第二个参数中的头信息打包到第一个参数中的头部中
     *@param   资产编号
     *@param   数据操作码
     *@param   实际的头部信息，将此参数打包到第一个参数中头部中
     */
    this.packHeader = function (data, assetNo, optCmd) {
        data.header = {};
        data.header.assetNo = assetNo;
        data.header.equipType = '0';
        data.header.optCmd = optCmd;
        data.header.requestTime = 0;
        data.header.responseTime = new Date().getTime();
        data.header.dataSource = '0';
        data.header.code = 200;
        data.header.msg = null;
    };

    /**
     *@brief   打包发送给主控摄像机状态的II协议
     *         根据头中optCmd来判断是什么类型的状态，根据不同的optCmd做出不同的处理
     *@param   待打包的发送给主控状态II协议
     *@param   json数据，源数据，将此源数据打包给第一个参数
     *@return  返回打包后的数据
     */
    this.packMainControlCameraStatus = function (data, sourceData) {
        var online = sourceData.online;
        var runStatus = sourceData.runStatus;
        data.deviceTypeTime = new Date().getTime();
        if (online == 0) {
            data.deviceType = '1';
            data.onlineType = '1';
        }
        else {
            data.deviceType = '2';
            data.onlineType = '0';
        }
    };

    /**
     *@brief   打包发送给主控摄像机告警的II协议
     *         根据头中optCmd来判断是什么类型的状态，根据不同的optCmd做出不同的处理
     *@param   待打包的发送给主控告警II协议
     *@param   json数据，源数据，将此源数据打包给第一个参数
     *@return  返回打包后的数据
     *by 潘翔 on 2017/12/15
     */
    this.packMainControlCameraAlarm = function (data, sourceData) {
        var online = sourceData.online;
        var runStatus = sourceData.status;
        var recordStatus = sourceData.recordStatus;
        // console.log("online:runStatus+recordStatus" + "---" + online + ":" + runStatus + ":" + recordStatus + "----");
        data.alarmTime = new Date().getTime();
        data.data = [];
        if (online == 0) {
            var arrAlarm = [];
            if (recordStatus == 0) {
                arrAlarm[0] = {'alarmCode': '0002', 'alarmFlag': 200};
                arrAlarm[1] = {'alarmCode': '0075', 'alarmFlag': 200};
                data.data = arrAlarm;
            } else {
                arrAlarm[0] = {'alarmCode': '0002', 'alarmFlag': 200};
                arrAlarm[1] = {'alarmCode': '0075', 'alarmFlag': 100};
                data.data = arrAlarm;
            }
        }
        else {
            if (recordStatus == 1) {
                var arrAlarm = [];
                arrAlarm[0] = {'alarmCode': '0002', 'alarmFlag': 100};
                arrAlarm[1] = {'alarmCode': '0075', 'alarmFlag': 100};
                data.data = arrAlarm;
            } else {
                var arrAlarm = [];
                arrAlarm[0] = {'alarmCode': '0002', 'alarmFlag': 100};
                arrAlarm[1] = {'alarmCode': '0075', 'alarmFlag': 100};
                data.data = arrAlarm;
            }
        }
    };

    /**
     *@brief   打包发送给WEB端为状态II协议
     *         根据包头中的optCmd来区分是广播转态还是摄像机状态
     *@param   待打包的数据
     *@param   原始数据,将此数据放入第一个参数中
     *@return  返回打包后的数据
     * by 潘翔 on 2017/12/15
     */
    this.packWebStatus = function (data, sourceData) {
        var optCmd = data.header.optCmd;
        switch (optCmd) {
            case 'safe_data_9005':
                packWebCameraStatus(data, sourceData);
                break;
        }
    };


    var packWebCameraStatus = function (data, sourceData) {
        //console.log("业务数据是:::" + JSON.stringify(sourceData));
        data.online = sourceData.online;
        data.disableDevCount = sourceData.disableDevCount;
        data.recordStatus = '' + sourceData.recordStatus;
        data.runTime = sourceData.sinceStartup;
        data.runStatus = '' + sourceData.status;
    };

    /**
     * packReturWebPlayVideoWebSocket:打包返回Web的播放视频的Websocket
     * @param
     *      destData:待打包的数据
     *      sourceData:原始数据（此数据是内部协议制定的data字段，为json对象,实际上是视频服务返回的body部分）
     *      code:错误码(此错误码来自视频服务的错误码)
     *  by 潘翔 on 2017/12/25
     */
    this.packReturWebPlayVideoWebSocket = function (destData, sourceData, code, msg) {
        destData.data = [];
        var temp = {};
        temp.code = code;
        temp.msg = msg;
        if (code == 200) {
            temp.webSocketUrl = sourceData.webSocketUrl;
            temp.rtspUrl = sourceData.rtspUrl;
            temp.rtspPort = sourceData.rtspPort;
        }
        destData.data.push(temp);
    };

    /**
     * packReturnWebQueryVideoList:打包返回Web的查询录像列表的数据
     * @param
     *    destData: 待打包的数据
     *    sourceData:原始的数据(实际上是视频服务返回的body部分)
     *  by 潘翔 on 2017/12/15
     */
    this.packReturnWebQueryVideoList = function (destData, sourceData) {
        destData.fileList = [];
        if(sourceData && sourceData.length > 0) {
            for(let i = 0; i < sourceData.length; i++) {
                let temp = {};
                temp.beginTime = sourceData[i].beginTime;
                temp.endTime = sourceData[i].endTime;
                temp.fileName = sourceData[i].fileName;
                temp.fileSize = sourceData[i].fileSize;
                temp.fileLength = sourceData[i].fileLength;
                temp.mediaFormat = sourceData[i].mediaFormat;
                temp.videoPath = sourceData[i].videoPath;
                destData.fileList.push(temp);
            }
        }
    };

    /**
     * packWebExecRecordAndVideoConfig:打包返回触录像和录像配置II级数据
     * @param
     *      destData:待打包的数据
     *      msg:源数据
     * by 潘翔 on 2017/12/15
     */
    this.packWebExecRecordAndVideoConfig = function (destData, msg) {
        destData.data = [];
        for(let i = 0; i < msg.length; i++) {
            destData.data.push(msg[i]);
        }
    };

    /**
     * packWebPreset:打包返回预置位II级数据
     * @param
     *      destData:待打包的数据
     *      msg:源数据
     */
    this.packWebPreset = function(destData, msg) {
        destData.code = msg.code;
        destData.msg = msg.msg;
    };

    /**
     * packReturnVideoConfig:打包返回的录像配置II级数据
     * @param
     *      destData:待打包的数据
     *      code:错误码
     *      msg:返回的信息
     * by 潘翔 on 2017/12/15
     */
    this.packReturnVideoConfig = function(destData, code, msg) {
        destData.data = [];
        var temp = {};
        temp.code = code;
        temp.msg = msg;
        destData.data.push(temp);
    };
}

var packVideoProtocolII = new PackVideoProtocolII();
module.exports = packVideoProtocolII;
