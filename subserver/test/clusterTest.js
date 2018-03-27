/**
 * @file Describe the file
 * @author yaoxinyu
 * @date 2018/3/12
 */

var cluster = require('cluster');
var http = require('http');
var numCPUs = require('os').cpus().length;

if (cluster.isMaster) {
    console.log('master start...');

    // Fork workers.
    for (var i = 0; i < numCPUs; i++) {
        cluster.fork();
    }

    cluster.on('listening', function (worker, address) {
        console.log('listening: worker ' + worker.process.pid + ', Address: ' + address.address + ':' + address.port);
    });

    cluster.on('exit', function (worker, code, signal) {
        console.log('worker ' + worker.process.pid + ' died');
    });
} else if (cluster.isWorker) {
    console.log('[worker] ' + 'start worker ...' + cluster.worker.process.pid);
    cluster.worker.on('message', msg => console.log('worker pid=' + worker.process.pid + '收到消息：' + msg));

    http.createServer(function (req, res) {
        res.writeHead(200);
        res.end('worker' + cluster.worker.id + ',PID:' + process.pid);
    }).listen(9000);
}