{
 "targets": [
  {
   "target_name": "aebellBroadcast",
   "sources": [
        "./addon/AebellBroadcast.cc", "./addon/AebellBroadcast.h", "./addon/AebellIpcastSdk.h",
        "./addon/Lock.h", "./addon/Lock.cc", "./addon/TaskQueue.h", "./addon/TaskQueue.cc",
        "./addon/CommonTypeDefine.h", "./addon/BroadcastTask.h", "./addon/BroadcastTask.cc", "./addon/UploadFileTask.h",
        "./addon/UploadFileTask.cc", "./addon/BaseThread.h", "./addon/BaseThread.cc", "./addon/AebellBusiThread.h",
        "./addon/AebellBusiThread.cc", "./addon/AebellUploadThread.h", "./addon/AebellUploadThread.cc"
   ],
   "libraries": ["../../../../dep/broadcast/AebellIpcastSdk.lib"]
  }
 ]
}
