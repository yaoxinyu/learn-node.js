/**
 *  定义视频平台映射到nodejs中的告警和状态
 * @author 潘翔
 * @date 2018/1/31
 */
const EventTable = {
    1: {//通用-设备下线
        0: {
            alarm: {
                alarmCode: '0002',
                alarmFlag: 100
            },
            status: {
                onlineType: '0',
                deviceType: '3'
            }
        }
    },
    2: {//通用-设备上线
        0: {
            alarm: {
                alarmCode: '0002',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    3: {//通用-设备故障
        0: {
            alarm: {
                alarmCode: '0081',
                alarmFlag: 100
            },
            status: {
                onlineType: '1',
                deviceType: '2'
            }
        }
    },
    10: {//移动侦测
        0: {
            alarm: {
                alarmCode: '0025',
                alarmFlag: 100
            },
            status: {
                onlineType: '1',
                deviceType: '3'
            }
        }
    },
    11: {//视频丢失
        0: {
            alarm: {
                alarmCode: '0023',
                alarmFlag: 100
            },
            status: {
                onlineType: '1',
                deviceType: '3'
            }
        }
    },
    12: {//视频遮挡
        0: {
            alarm: {
                alarmCode: '0024',
                alarmFlag: 100
            },
            status: {
                onlineType: '1',
                deviceType: '3'
            }
        }
    },
    16: {//音频报警
        0: {
            alarm: {
                alarmCode: '0049',
                alarmFlag: 100
            },
            status: {
                onlineType: '1',
                deviceType: '3'
            }
        }
    },
    17: {//音频异常
        0: {
            alarm: {
                alarmCode: '0049',
                alarmFlag: 100
            },
            status: {
                onlineType: '1',
                deviceType: '3'
            }
        }
    },
    50: {//智能-行为分析-普通事件
        1: {//人员聚集
            alarm: {
                alarmCode: '0036',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        },
        2: {//徘徊
            alarm: {
                alarmCode: '0033',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        },
        3: {//快速移动
            alarm: {
                alarmCode: '0035',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        },
        5: {//物品遗留
            alarm: {
                alaramCode: '0037',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        },
        6: {//物品拿取
            alarm: {
                alarmCode: '0038',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    51: {//智能-行为分析-报警事件
        1: {//防破坏报警
            alarm: {
                alarmCode: '0037',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    52: {//智能-区域-普通事件
        1: {//进入区域
            alarm: {
                alarmCode: '0029',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        },
        2: {//离开区域
            alarm: {
                alarmCode: '0030',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        },
        3: {//停车侦测
            alarm: {
                alarmCode: '0034',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    53: {//智能-区域-报警事件
        1: {//越界侦测
            alarm: {
                alarmCode: '0028',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        },
        2: {//区域入侵
            alarm: {
                alarmCode: '0031',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    56: {//智能-人脸识别-普通事件
        0: {
            alarm: {
                alarmCode: '0046',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    57: {//智能-人脸识别-报警事件
        1: {//人脸侦测报警
            alarm: {
                alarmCode: '0046',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    60: {//智能-车辆识别-普通事件
        0: {
            alarm: {
                alarmCode: '0041',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    61: {//智能-车辆识别-报警事件
        0: {
            alarm: {
                alarmCode: '0041',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    },
    71: {//智能-场景变化
        0: {
            alarm: {
                alarmCode: '0047',
                alarmFlag: 200
            },
            status: {
                onlineType: '1',
                deviceType: '1'
            }
        }
    }
}

module.exports = EventTable;