/**
 * @file 根据optCmd对协议类型进行判断分类
 * @author yaoxinyu
 * @date 2017/12/14
 */


function ProtoTypeClassify() {
    const broadcastProtoI = [
        'broadcast_param_9003',
        'broadcast_param_9004',
        'broadcast_param_9005',
        'broadcast_param_9006',
        'broadcast_param_9007',
        'broadcast_param_9008',
        'broadcast_param_9009',
        'broadcast_param_9010'
    ];

    const broadcastProtoII = [
        'broadcast_data_9003',
        'broadcast_data_9004',
        'broadcast_data_9005',
        'broadcast_data_9006',
        'broadcast_data_9007'
    ];

    const videoProtoI = [
        'safe_param_6007',
        'safe_param_6008',
        'safe_param_6009',
        'safe_param_6010',
        'safe_param_6011',
        'safe_param_6012',
        'safe_param_6013',
        'safe_param_6014',
        'safe_param_6015',
        'safe_param_6016',
        'safe_param_6017',
        'safe_param_6018',
        'safe_param_6019',
        'safe_param_6020',
        'safe_param_6021'
    ];

    const videoProtoII = [
        'safe_data_9005',
        'safe_data_9006',
        'safe_data_9007',
        'safe_data_9008',
        'safe_data_9009',
        'safe_data_9010',
        'safe_data_9011',
        'safe_data_9012',
        'safe_data_9013',
        'safe_data_9014',
        'safe_data_9015',
        'safe_data_9016',
        'safe_data_9017',
        'safe_data_9018',
        'safe_data_9019',
        'safe_data_9021'
    ];

    const bigScreenProtoI = [
        'media_param_6001',
        'media_param_6100'
    ];

    const bigScreenProtoII = [
        'media_data_9001',
        'media_data_9100'
    ];

    /**
     * 根据optCmd判断是否为I类广播协议
     * @param optCmd
     * @return {boolean}
     */
    this.isBroadProtoI = function (optCmd) {
        if (broadcastProtoI.includes(optCmd)) {
            return true;
        }
        return false;
    };

    /**
     * 根据optCmd判断是否为II类广播协议
     * @param optCmd
     * @return {boolean}
     */
    this.isBroadProtoII = function (optCmd) {
        if (broadcastProtoII.includes(optCmd)) {
            return true;
        }
        return false;
    };

    /**
     * 根据optCmd判断是否为I类视频协议
     * @param optCmd
     * @return {boolean}
     */
    this.isVideoProtoI = function (optCmd) {
        if (videoProtoI.includes(optCmd)) {
            return true;
        }
        return false;
    };

    /**
     * 根据optCmd判断是否为II类视频协议
     * @param optCmd
     * @return {boolean}
     */
    this.isVideoProtoII = function (optCmd) {
        if (videoProtoII.includes(optCmd)) {
            return true;
        }
        return false;
    };

    /**
     * 根据optCmd判断是否为II类大屏协议
     * @param optCmd
     * @return {boolean}
     */
    this.isBigScreenProtoII = function (optCmd) {
        if (bigScreenProtoII.includes(optCmd)) {
            return true;
        }
        return false;
    };

    /**
     * 根据optCmd判断是否为I类大屏协议
     * @param optCmd
     * @return {boolean}
     */
    this.isBigScreenProtoI = function (optCmd) {
        if (bigScreenProtoI.includes(optCmd)) {
            return true;
        }
        return false;
    };
}


var protoClassify = new ProtoTypeClassify();
module.exports = protoClassify;