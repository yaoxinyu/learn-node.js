/**
 * @file 测试用例：包括广播、视频、大屏、事务联动
 * Created by yaoxinyu on 2018/3/19.
 */
var fileUtil = require('../src/common/util/fileUtil');
let filePath = 'G:/node/2002年的第一场雪 - 刀郎.mp3';//上传文件的本地路径
let fileData = fileUtil.readFileBySync(filePath, 'binary');
let stat = fileUtil.statSync(filePath);//获取文件信息
let fileSize = 0;//文件大小
let fileName = '';//文件名
if (fileData) {
    fileName = filePath.match(/[^/]*$/);//通过文件路径，用正则去匹配得到文件名
}
if (stat) {
    fileSize = stat.size;//获取文件大小
}
//连接
const connect = {
    connection: {
        clientId: '111111',
        data: {
            header: {
                optCmd: 'session_param_6001'
            }
        }
    }
};

// 广播测试用例
const BroadcastTestCase = {
    //广播参数测试数据模板
    broadcast: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000165',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9003',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            //"type": "string", "doc":"01：播放，02：停止，03：文件列表，04：音量控制，05、状态", "dataKey": "optType"
            optType: '01',
            fileId: [1],//"type": "int", "doc":"播放时必须设置的值，播放文件ID", "dataKey": "fileId"
            volume: 12,//"type": "int", "doc":"设备音量(派思达音量范围：1-15)", "dataKey": "volume"
        }
    },
    //播放
    play: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',
                optCmd: 'broadcast_param_9003',
                requestTime: 1509702156822,
                equipType: null,
                dataSource: '1'
            },
            optType: '01',
            fileId: [13, 14],
            volume: 12,
        }
    },
    //停止
    stop: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',
                optCmd: 'broadcast_param_9003',
                requestTime: 1509702156825,
                equipType: null,
                dataSource: '1'
            },
            optType: '02',
            fileId: [13, 14],
            volume: 12,
        }
    },
    //文件列表
    fileList: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '0503000000001|05030000000002|05030000000003',
                optCmd: 'broadcast_param_9003',
                requestTime: 1509702156822,
                equipType: null,
                dataSource: '1'
            },
            optType: '03',
            fileId: [1],
            volume: 12
        }
    },
    //音量控制
    volumeControl: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',
                optCmd: 'broadcast_param_9003',
                requestTime: 1509702156822,
                equipType: null,
                dataSource: '1'
            },
            optType: '04',
            fileId: [13],
            volume: 10,
        }
    },
    //喊话参数测试数据模板
    shout: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9004',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            optType: '01',//"type": "string", "doc":"01：喊话，02：终止喊话", "dataKey": "optType"
            dstAssetNo: '05030000000165',//"type": "string", "doc":"接收端资产编号，多个用|分隔", "dataKey": "dstAssetNo"
            volume: 12,//"type": "int", "doc":"设备音量(派思达音量范围：1-15)", "dataKey": "volume"
        }
    },
    //喊话
    shoutStart: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000002',
                optCmd: 'broadcast_param_9004',
                requestTime: 1509702156822,
                equipType: null,
                dataSource: '0'
            },
            optType: '01',
            dstAssetNo: '05030000000031',
            volume: 12,
        }
    },
    //终止喊话
    shoutEnd: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000002',
                optCmd: 'broadcast_param_9004',
                requestTime: 1509702156822,
                equipType: null,
                dataSource: '0'
            },
            optType: '02',
            dstAssetNo: '05030000000031',
            volume: 12,
        }
    },
    //增加设备参数测试数据
    addDevice: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000031',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9005',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            deviceType: 2 //"type": "int, "doc":"设备类型编号（必填）", "dataKey": "deviceType"
        }
    },
    //删除设备参数测试数据
    deleteDevice: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000031',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9006',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
        }
    },
    //上传文件参数测试数据
    uploadFile: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000165',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9007',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            data: {
                fileName: fileName,//"type": "string", "doc":"文件名（必填，带后缀名）", "dataKey": "fileName"
                fileType: 0,//"type": "int", "doc":"文件类型（必填）", "dataKey": "fileType"
                fileSize: fileSize,//"type": "long", "doc":"文件大小（选填，单位字节）", "dataKey": "fileSize"
                fileData: fileData//"type": "string", "doc":"文件数据（必填）", "dataKey": "fileData"
            }
        }
    },
    //广播添加/修改定时任务方案测试数据
    addTiming: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9008',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            optType: '01',//"type": "string", "doc":"01：添加方案，02：修改方案"
            planName: '方案一',//"type": "string", "doc":"方案名称"
            taskName: '定时广播',//"type": "string", "doc":"任务名称"
            planBeginTime: '2017-11-29',//"type": "string", "doc":"方案开始日期 字符串格式（2017-11-28）
            planEndTime: '2018-11-19',//"type": "string", "doc":"方案结束日期 字符串格式（2017-11-28）
            taskBeginTime: '09:30:00',//"type": "string", "doc":"任务执行开始时间 字符串格式（16:35:00）
            taskEndTime: '18:15:00',//"type": "string", "doc":"任务执行结束时间 字符串格式（16:35:00）
            cycleMode: 2,//"type": "int", "doc":"循环模式 1每天 2每周 3每月
            taskRunDate: '1,2,3,4,5,6',// "type": "string", "doc":"字符串格式（每周为0-6，每月为1-31，多天逗号分隔）"
            fileList: [1, 2],//"type": {"type": "array", "items": "int"}, "doc":"文件ID列表
            deviceList: ['172.17.2.6'],//"type": {"type": "array", "items": "string"}, "doc":"设备IP列表
            playMode: 2,//"type": "int", "doc":"播放模式 0单曲、1单曲循环、2顺序、3循环、4随机"
            playTimes: 0,//"type": "int", "doc":"播放次数 0表示连续"
            volume: 15,//"type": "int", "doc":"任务音量0-100"
        }
    },
    //广播修改定时任务方案
    modifyTiming: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',
                optCmd: 'broadcast_param_9008',
                requestTime: 1509702156822,
                equipType: null,
                dataSource: '0'
            },
            optType: '02',
            planName: '方案一',
            taskName: '定时广播',
            planBeginTime: '2017-11-30',
            planEndTime: '2018-11-19',
            taskBeginTime: '15:30:00',
            taskEndTime: '18:15:00',
            cycleMode: 2,
            taskRunDate: '0,1,2,3,4,5,6',
            fileList: [1, 2],
            deviceList: ['172.17.2.6', '172.17.2.9'],
            playMode: 3,
            playTimes: 0,
            volume: 25,
        }
    },
    //广播删除方案测试数据
    removeSchema: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9009',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            planName: '方案一'//"type": "string", "doc":"方案名称"
        }
    },
    //广播添加会话中设备测试数据
    addAsset: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9009',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            optType: '01',//"type": "string", "doc":"01：添加会话设备，02：删除会话设备"
            assetNo: '05030000000002'//"type": "string", "doc":"会话中的一个设备资产编号"
        }
    },
    //广播删除会话中设备测试数据
    deleteAsset: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000001',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'broadcast_param_9009',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            optType: '02',//"type": "string", "doc":"01：添加会话设备，02：删除会话设备"
            assetNo: '05030000000002'//"type": "string", "doc":"会话中的一个设备资产编号"
        }
    },
};

// 视频测试用例
const VideoTestCase = {
    //国创视频服务-云台控制开始
    cloudTerraceStart: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000070',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6010',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            command: '120',//"type": "string", "doc":"转动的命令（开始云台控制时传）"
            speed: 4,//"speed", "type": "int", "doc":"速度参数 (1-9)  若不设置速度，参数设为0"
            orientation: 0,//操作方向  0:设置；1:获取命令对应属性值；2:不做操作
            params: [1, 1200, 1570, 2200]
        }
    },

    //国创视频服务-云台控制结束
    cloudTerraceEnd: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000071',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6011',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            command: '120',//"type": "string", "doc":"转动的命令（开始云台控制时传）"
            speed: 4,//"speed", "type": "int", "doc":"速度参数 (1-9)  若不设置速度，参数设为0"
            orientation: 0,//操作方向  0:设置；1:获取命令对应属性值；2:不做操作
            /**
             * 当commond=120时启作用，传4个值，
             第一个：0 无效，1 设置PTZ，2 设置P，3 设置T，4 设置Z，5 设置PT
             第二个：P参数，单位为0.1度 如1750表示175度
             第三个：T参数，单位为0.1度 如1750表示175度
             第四个：Z参数，单位为0.1度 如1750表示175度
             */
            params: [1, 1200, 1570, 2200]
        }
    },

    //国创视频服务-视频播放（获取websocket接口）
    videoPlay: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000073',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6012',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            type: '1'//"type": "string", "doc":"主辅码流 （1代表辅码流，不填代表主码流）"
        }
    },

    //国创视频服务-录像列表查询
    videoListQuery: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000074',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6013',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            beginTime: 1513670780,//"type": "long", "doc":"开始时间，unix时间戳，单位秒"
            endTime: 1513670827// "type": "long", "doc":"结束时间，unix时间戳，单位秒"
        }
    },

    //国创视频服务-截图列表查询
    screenshotListQuery: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000060',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6014',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            beginTime: 1513670780,//"type": "long", "doc":"开始时间，unix时间戳，单位秒"
            endTime: 1513670827// "type": "long", "doc":"结束时间，unix时间戳，单位秒"
        }
    },

    //国创视频服务-触发录像（自动停止）
    videoAutoStop: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000061',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6015',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            //"type": {"type": ["array", "null"], "items": {"type": "map", "value": "int"}}, "doc":"录像数据"
            data: [
                {
                    duration: 10,//type: int,录像持续时间，单位秒
                    streamType: 0,//type: int,码流类型，0-主码流，1-辅码流，>1-其他码流
                    preRecordTime: 3//type: int,预录时长(1:0; 2:5s; 3:10s; 4:20s; 5:30s)
                },
                {
                    duration: 20,//type: int,录像持续时间，单位秒
                    streamType: 1,//type: int,码流类型，0-主码流，1-辅码流，>1-其他码流
                    preRecordTime: 5//type: int,预录时长(1:0; 2:5s; 3:10s; 4:20s; 5:30s)
                }
            ]
        }
    },

    //国创视频服务-触发录像（手动开始）
    videoManualOn: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000062',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6016',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            //"type": {"type": ["array", "null"], "items": {"type": "map", "value": "int"}}, "doc":"录像数据"
            data: [
                {
                    streamType: 0,//type: int,码流类型，0-主码流，1-辅码流，>1-其他码流
                    preRecordTime: 2//type: int,预录时长(1:0; 2:5s; 3:10s; 4:20s; 5:30s)
                },
                {
                    streamType: 0,//type: int,码流类型，0-主码流，1-辅码流，>1-其他码流
                    preRecordTime: 4//type: int,预录时长(1:0; 2:5s; 3:10s; 4:20s; 5:30s)
                }
            ]
        }
    },

    //国创视频服务-触发录像（手动结束）
    videoManualEnd: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000063',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6017',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            }
        }
    },

    //国创视频服务-触发截图
    triggerCutOff: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000064',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6018',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            //"type": {"type": ["array", "null"], "items": {"type": "map", "value": "int"}}, "doc":"录像数据"
            data: [
                {
                    interval: 100,//type: int, 截图间隔(单位毫秒，一般不少于40)
                    maxSnapNum: 6,//type: int, 截图最大数量
                    startOffset: 1//type: long, 截图开始偏移（相对于录像），单位s
                },
                {
                    interval: 300,//type: int, 截图间隔(单位毫秒，一般不少于40)
                    maxSnapNum: 10,//type: int, 截图最大数量
                    startOffset: 2//type: long, 截图开始偏移（相对于录像），单位s
                }
            ]
        }
    },

    //国创视频服务-录像设置
    recordingSettings: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05040000000065',//"type": "string","doc":"资产编号", "dataKey": "assetNo"
                optCmd: 'safe_param_6019',//
                requestTime: 1509702156822,//"type": "long","doc":"操作时间", "dataKey": "requestTime"
                equipType: null,//"type": ["string", "null"],"doc":"设备类型", "dataKey": "equipType"
                //"type": ["string", "null"],"doc":"数据来源，默认为集控，
                // 0：分控系统 1：运维系统 2：APP，3：定时任务,4:资产管理系统", "dataKey": "dataSource"
                dataSource: '0'
            },
            //"type": {"type": "array", "items": "string"}, "doc":"录像设置信息"
            data: [
                JSON.stringify({
                    'devId': '',//设备ID（业务系统不需要传，由协议网关从数据库查询）
                    'audioRec': 1,//记录音频标记（1：记录，0：不记录）
                    'recordTime': 3,//录像时长(1:5s; 2:10s; 3:20s; 4:30s; 5:1min; 6:10min; 7:30min)
                    'preRecordTime': 3,//预录时长(1:0; 2:5s; 3:10s; 4:20s; 5:30s)
                    'holdTime': 3,//保存时长(天)
                    'streamType': 0,//码流类型，0-主码流，1-辅码流，>1-其他码流
                    'disable': 1,//启用标记(高级参数启用标记)（1：启用，0：不启用）
                    'dataList': JSON.stringify([
                        {
                            'weekNum': 1,//1---7（周一至周日）
                            'cause': 1,//录像诱因(1:定时，2:异常，3:移动，4:移动或异常，5:移动和异常)
                            'startTime': '12:30',//开始时间（00:00-23:59）
                            'endTime': '18:00'//结束时间（00:00-23:59）
                        },
                        {
                            'weekNum': 2,//1---7（周一至周日）
                            'cause': 1,//录像诱因(1:定时，2:异常，3:移动，4:移动或异常，5:移动和异常)
                            'startTime': '12:30',//开始时间（00:00-23:59）
                            'endTime': '18:00'//结束时间（00:00-23:59）
                        },
                        {
                            'weekNum': 3,//1---7（周一至周日）
                            'cause': 1,//录像诱因(1:定时，2:异常，3:移动，4:移动或异常，5:移动和异常)
                            'startTime': '12:30',//开始时间（00:00-23:59）
                            'endTime': '18:00'//结束时间（00:00-23:59）
                        },
                        {
                            'weekNum': 4,//1---7（周一至周日）
                            'cause': 1,//录像诱因(1:定时，2:异常，3:移动，4:移动或异常，5:移动和异常)
                            'startTime': '12:30',//开始时间（00:00-23:59）
                            'endTime': '18:00'//结束时间（00:00-23:59）
                        },
                        {
                            'weekNum': 5,//1---7（周一至周日）
                            'cause': 1,//录像诱因(1:定时，2:异常，3:移动，4:移动或异常，5:移动和异常)
                            'startTime': '12:30',//开始时间（00:00-23:59）
                            'endTime': '18:00'//结束时间（00:00-23:59）
                        }
                    ])
                }),
                JSON.stringify({
                    'devId': '',//设备ID（业务系统不需要传，由协议网关从数据库查询）
                    'audioRec': 1,//记录音频标记（1：记录，0：不记录）
                    'recordTime': 3,//录像时长(1:5s; 2:10s; 3:20s; 4:30s; 5:1min; 6:10min; 7:30min)
                    'preRecordTime': 3,//预录时长(1:0; 2:5s; 3:10s; 4:20s; 5:30s)
                    'holdTime': 3,//保存时长(天)
                    'streamType': 0,//码流类型，0-主码流，1-辅码流，>1-其他码流
                    'disable': 1,//启用标记(高级参数启用标记)（1：启用，0：不启用）
                    'dataList': JSON.stringify([
                        {
                            'weekNum': 6,//1---7（周一至周日）
                            'cause': 1,//录像诱因(1:定时，2:异常，3:移动，4:移动或异常，5:移动和异常)
                            'startTime': '12:30',//开始时间（00:00-23:59）
                            'endTime': '18:00'//结束时间（00:00-23:59）
                        },
                        {
                            'weekNum': 7,//1---7（周一至周日）
                            'cause': 1,//录像诱因(1:定时，2:异常，3:移动，4:移动或异常，5:移动和异常)
                            'startTime': '12:30',//开始时间（00:00-23:59）
                            'endTime': '18:00'//结束时间（00:00-23:59）
                        }
                    ])
                }),
            ]
        }
    },
};

// 大屏测试用例
const BigScreenTestCase = {
    //大屏截圖
    bigScreenShot: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '05030000000002|05030000000003',
                optCmd: 'media_param_6001',
                requestTime: 1509702156825,
                equipType: null,
                dataSource: '1'
            },
            interval: 5,//每张截图时间间隔
            num: 10//截图数量
        }
    },
    //大屏发布
    bigScreenPush: {
        clientId: '111111',
        sessionId: '1',
        data: {
            header: {
                assetNo: '07020000000004',
                optCmd: 'media_param_6100',
                requestTime: 1509702156825,
                equipType: null,
                dataSource: '1'
            },
            url: 'http://localhost:8021/ipole-web//html/bigscreen/screencontent/975615499666718720.html',//发布地址，http开头的
        }
    },
    /**
     *  下面为事务联动大屏推送测试数据，使用测试数据测试前，需要为资产配置推送大屏的联动动作。
     配置过程：登录智慧灯杆运营支撑平台，选择新分控或者分控，点击系统管理，选择事务联动动作配
     置，在查询里面里面选择需要测试的资产，点击动作配置，为资产添加触发条件，然后再勾选左侧大
     屏启用，为了测试效果，其他的可以不勾选启用，大屏推送选择文字提示就可以了。
     */
    //大屏推送停车
    park: {
        'header': {
            'assetNo': '09020000000176',
            'equipType': '',
            'optCmd': 'park_data_9011',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'status': '200',
        'statusType': '002',
        'time_status': 1513763583639
    },
    //水位监控数据
    waterLevel: {
        'header': {
            'assetNo': '09070000000141',
            'equipType': '',
            'optCmd': 'manhole_data_9017',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'wellHeight': 5,
        'waterLevel': 7,
        'dataTime': 1513763583639
    },
    //基站上报井盖标签数据
    manhole: {
        'header': {
            'assetNo': '09010000000170',
            'equipType': '',
            'optCmd': 'manhole_data_9001',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'data': [{
            'code': '500',
            'value': '200'
        }, {
            'code': '503',
            'value': 60
        }],
        'dataTime': 1513763583639
    },
    //环境
    senset: {
        'header': {
            'assetNo': '09010000000170',
            'equipType': '',
            'optCmd': 'senset_data_9001',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'data': [{
            'code': '500',
            'value': '200'
        }, {
            'code': '503',
            'value': 60
        }],
        'dataTime': 1513763583639
    },
    //读取标签指令（设备主动上传模式）-协议是30
    rfid: {
        'header': {
            'assetNo': '09010000000170',
            'equipType': '',
            'optCmd': 'rfid_data_9003',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'data': [{
            'code': '500',
            'value': '200'
        }, {
            'code': '503',
            'value': 60
        }],
        'dataTime': 1513763583639
    }
};

// 事务联动测试用例
/**
 * 事务联动测试说明：测试事务联动前，动作及条件需要配置，登录智慧灯杆运营平台，选择集
 * 控，点击基础数据事务联动事件管理，通过左侧的部件分类树，选择需要测试的资产类型，鼠标右
 * 击添加事件，然后为事件添加表达式。之后切换到分控，点击系统管理，选择事务联动动作配置，
 * 在查询里面里面选择需要测试的资产，点击动作配置，在条件配置里面选择刚刚添加的事件表达式，
 * 在弹框下面，也可添加事件周期和时间有效期等条件，最后是勾选需要触发的动作，选择相应的动作
 * 启用后保存。
 */
const LinkAffairTestCase = {
    //停车
    park: {
        'header': {
            'assetNo': '09020000000176',
            'equipType': '',
            'optCmd': 'park_data_9011',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'status': '200',
        'statusType': '002',
        'time_status': 1513763583639
    },
    //水位监控数据
    waterLevel: {
        'header': {
            'assetNo': '09070000000141',
            'equipType': '',
            'optCmd': 'manhole_data_9017',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'wellHeight': 5,
        'waterLevel': 7,
        'dataTime': 1513763583639
    },
    //基站上报井盖标签数据
    manhole: {
        'header': {
            'assetNo': '09010000000170',
            'equipType': '',
            'optCmd': 'manhole_data_9001',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'data': [{
            'code': '500',
            'value': '200'
        }, {
            'code': '503',
            'value': 60
        }],
        'dataTime': 1513763583639
    },
    //环境
    senset: {
        'header': {
            'assetNo': '09010000000170',
            'equipType': '',
            'optCmd': 'senset_data_9001',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'data': [{
            'code': '500',
            'value': '200'
        }, {
            'code': '503',
            'value': 60
        }],
        'dataTime': 1513763583639
    },
    //读取标签指令（设备主动上传模式）-协议是30
    rfid: {
        'header': {
            'assetNo': '09010000000170',
            'equipType': '',
            'optCmd': 'rfid_data_9003',
            'requestTime': 1513763583639,
            'responseTime': 1513763583639,
            'dataSource': '0',
            'code': 200,
            'msg': '数据取得成功。'
        },
        'data': [{
            'code': '500',
            'value': '200'
        }, {
            'code': '503',
            'value': 60
        }],
        'dataTime': 1513763583639
    }
};

//资产同步
/**
 * 资产同步通过http发送请求数据，每个数据为JSON类型，数据里面的data
 * 为数组，数组的每个元素是JSON数据通过base64转化的字符串
 */
const AssetSyncTestCase = {
    //资产同步，视频设备添加
    safeSyncAdd: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_6022',
        data: [
            new Buffer(JSON.stringify({
                'assetNo': '05040000000062',
                'sid': '',
                'deviceName': '摄像机1',
                'loginIp': '192.168.50.55',
                'loginPort': '8080',
                'loginName': 'admin',
                'loginPass': 'overseas',
                'vendorId': '',
                'connProto': '',
                'urlConn': ''
            })).toString('base64')
        ]
    },
    //资产同步，视频设备修改
    safeSyncModify: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_6023',
        data: [
            new Buffer(JSON.stringify({
                'assetNo': '05040000000062',
                'sid': '',
                'deviceName': '监控1',
                'loginIp': '172.17.2.33',
                'loginPort': '9003',
                'loginName': 'collector',
                'loginPass': 'eBT123',
                'vendorId': '',
                'connProto': '',
                'urlConn': ''
            })).toString('base64')
        ]
    },
    //资产同步，视频设备删除
    safeSyncDelete: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_6024',
        data: [
            new Buffer(JSON.stringify({
                'assetNo': '05040000000062',
                'sid': ''
            })).toString('base64')
        ]
    },
    //资产同步，资产添加
    assetSyncAdd: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_9001',
        data: [
            new Buffer(JSON.stringify({
                'r_device_asset': {
                    'remark': '',
                    'road_id': 6,
                    'mac_addr': '5876',
                    'org_code': '340104',
                    'device_id': 119,
                    'dt_delete': null,
                    'gis_pos_x': null,
                    'gis_pos_y': null,
                    'model_code': 'dl8923',
                    'run_status': '2',
                    'date_modify': '2017-12-16 14:15:10',
                    'device_code': '00000000000119',
                    'device_name': '大屏资产',
                    'flag_delete': 0,
                    'user_delete': null,
                    'device_state': '01',
                    'factory_code': '009',
                    'date_original': '2017-12-16 14:15:10',
                    'serial_number': 3000000022,
                    'supplier_code': '03',
                    'date_ex_factory': '2017-12-16 14:15:10',
                    'first_type_code': '07',
                    'network_unit_id': null,
                    'second_type_code': '02',
                    'competent_unit_id': 3,
                    'data_sources_code': null,
                    'ownership_unit_id': null,
                    'maintenance_unit_id': null,
                    'classification_standard_code': null
                },
                'd_device_status': {
                    'device_id': 119,
                    'st_online': '1',
                    'st_running': '1',
                    'dt_last_connect': null,
                    'dt_online_changed': '2017-12-07 09:52:59',
                    'dt_running_changed': '2017-12-07 09:52:59'
                },
                'r_device_relation': {
                    'add': [
                        {
                            'child_device_id': 1,
                            'parent_device_id': 119
                        },
                        {
                            'child_device_id': 2,
                            'parent_device_id': 120
                        }
                    ],
                    'delete': [
                        {
                            'child_device_id': 1,
                            'parent_device_id': 2
                        },
                        {
                            'child_device_id': 3,
                            'parent_device_id': 4
                        }
                    ]
                },
                'r_bigscreen_extend': {
                    'ip': '9.8.7.6',
                    'port': 9987,
                    'width': 256,
                    'height': 128,
                    'bigscreen_id': 119
                }
            })).toString('base64')
        ]
    },
    //资产同步，资产修改
    assetSyncModify: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_9002',
        data: [
            new Buffer(JSON.stringify({
                'r_device_asset': {
                    'remark': '',
                    'road_id': 6,
                    'mac_addr': '5876',
                    'org_code': '340104',
                    'device_id': 119,
                    'dt_delete': null,
                    'gis_pos_x': null,
                    'gis_pos_y': null,
                    'model_code': 'dl8923',
                    'run_status': '2',
                    'date_modify': '2017-12-16 14:15:10',
                    'device_code': '00000000000119',
                    'device_name': '广播',
                    'flag_delete': 0,
                    'user_delete': null,
                    'device_state': '01',
                    'factory_code': '009',
                    'date_original': '2017-12-16 14:15:10',
                    'serial_number': 3000000022,
                    'supplier_code': '03',
                    'date_ex_factory': '2017-12-16 14:15:10',
                    'first_type_code': '07',
                    'network_unit_id': null,
                    'second_type_code': '02',
                    'competent_unit_id': 3,
                    'data_sources_code': null,
                    'ownership_unit_id': null,
                    'maintenance_unit_id': null,
                    'classification_standard_code': null
                },
                'd_device_status': {
                    'device_id': 119,
                    'st_online': '1',
                    'st_running': '2',
                    'dt_last_connect': null,
                    'dt_online_changed': '2017-12-07 09:52:59',
                    'dt_running_changed': '2017-12-07 09:52:59'
                },
                'r_device_relation': {
                    'add': [
                        {
                            'child_device_id': 5,
                            'parent_device_id': 123
                        },
                        {
                            'child_device_id': 6,
                            'parent_device_id': 124
                        }
                    ],
                    'delete': [
                        {
                            'child_device_id': 1,
                            'parent_device_id': 119
                        },
                        {
                            'child_device_id': 2,
                            'parent_device_id': 120
                        }
                    ]
                },
                'r_bigscreen_extend': {
                    'ip': '192.178.50.11',
                    'port': 9001,
                    'width': 256,
                    'height': 128,
                    'bigscreen_id': 119
                }
            })).toString('base64')
        ]
    },
    //资产同步，资产删除
    assetSyncDelete: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_9003',
        data: [
            new Buffer(JSON.stringify({
                'r_device_asset': {
                    'device_code': '00000000000119',
                    'first_type_code': '07',
                    'second_type_code': '02',
                },
                'd_device_status': {
                    'device_id': 119,
                },
                'r_device_relation': {
                    'add': [
                        {
                            'child_device_id': 119,
                            'parent_device_id': 119
                        },
                        {
                            'child_device_id': 120,
                            'parent_device_id': 2
                        }
                    ],
                    'delete': [
                        {
                            'child_device_id': 120,
                            'parent_device_id': 2
                        },
                        {
                            'child_device_id': 3,
                            'parent_device_id': 4
                        }
                    ]
                },
                'r_bigscreen_extend': {
                    'bigscreen_id': 119
                }
            })).toString('base64')
        ]
    },
    //资产同步，广播设备添加
    broadcastAdd: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_6019',
        data: [
            new Buffer(JSON.stringify({
                'devCode': '05030000000001',
                'devName': '呼叫站1',
                'devType': 1,
                'devIP': '192.168.60.1'
            })).toString('base64')
        ]
    },
    //资产同步，广播设备修改
    broadcastMdf: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_6020',
        data: [
            new Buffer(JSON.stringify({
                'devCode': '05030000000001',
                'devName': '广播1',
                'devType': 1,
                'devIP': '192.168.70.1',
                'devId': 'e02facbf-940e-4353-ac11-6f0adade4041'
            })).toString('base64')
        ]
    },
    //资产同步，广播设备删除
    broadcastDel: {
        requestTime: 1509702156822,
        optCmd: 'asset_param_6021',
        data: [
            new Buffer(JSON.stringify({
                'assetNo': '05030000000001',
                'devId': 'c1b74cb6-e623-4bee-9485-ac1084633aab'
            })).toString('base64')
        ]
    }

};

module.exports = {
    BroadcastTestCase: BroadcastTestCase,
    VideoTestCase: VideoTestCase,
    BigScreenTestCase: BigScreenTestCase,
    LinkAffairTestCase: LinkAffairTestCase,
    AssetSyncTestCase: AssetSyncTestCase
};