var cities = [
    { name: 'London', 'population': 8615246 },
    { name: 'Berlin', 'population': 3517424 },
    { name: 'Madrid', 'population': 3165235 },
    { name: 'Rome', 'population': 2870528 }
];

var testCase = {
    'store': {
        'book': [
            {
                'category': 'reference',
                'author': 'Nigel Rees',
                'title': 'Sayings of the Century',
                'price': 8.95
            }, {
                'category': 'fiction',
                'author': 'Evelyn Waugh',
                'title': 'Sword of Honour',
                'price': 12.99
            }, {
                'category': 'fiction',
                'author': 'Herman Melville',
                'title': 'Moby Dick',
                'isbn': '0-553-21311-3',
                'price': 8.99
            }, {
                'category': 'fiction',
                'author': 'J. R. R. Tolkien',
                'title': 'The Lord of the Rings',
                'isbn': '0-395-19395-8',
                'price': 22.99
            }
        ],
        'bicycle': {
            'color': 'red',
            'price': 19.95
        }
    }
};

var obj = {
    'name': {
        'height': 178,
        'age': 29
    },
    'sex': 'man'
};

// var jp = require('jsonpath');
// var names = jp.query(obj, '$[?($.sex == "man")]');
// var books = jp.query(testCase, '$..book[?(@.price==8.95)]');


// console.log(names);
// console.log(books);
// var res = eval("1-1");
// console.log(res);

// let a = {};
// if (JSON.stringify(a) !== "{}") {
//     console.log("not empty");
//     console.log(JSON.stringify(a));
// } else {
//     console.log("empty");
// }

let param1 = {
    dataType: 'rfid',
    num: -1
};
let param2 = {
    dataType: 'park',
    num: -1
};
let param3 = {
    dataType: 'env',
    num: -1
};

// let tempMap1 = {};
// tempMap1["key1"] = param1;
// tempMap1["key2"] = param1;
// tempMap1["key3"] = param1;
//
// let tempMap2 = {};
// tempMap2["key4"] = param1;
// tempMap2["key5"] = param1;
// tempMap2["key6"] = param1;
// let secondMap = {};
// secondMap["rfid"] = tempMap1;
// secondMap["park"] = tempMap2;
//
// for (let key1 in secondMap) {
//     console.log("当前外循环key值:", key1);
//     let obj = secondMap[key1];
//     for (let key2 in obj) {
//         if (key2 == "key1") {
//             delete obj[key2];
//         }
//         console.log("当前内循环key值=%s，value值=%s", key2, JSON.stringify(obj[key2]));
//     }
//
// }

var myMap = new Map();

// 我们给myMap设置值
myMap.set('keyString', '字符串\'');
myMap.set('keyObj', '对象');
myMap.set('keyFunc', '函数');

for (let id of myMap.keys()) {
    if (id == 'keyString') {
        myMap.delete(id);
    }
    console.log(id);
}

console.log(myMap);

console.log(Number(-1) + 1);

let tmpSet = new Set([1, 1, 3]);
console.log(tmpSet.size);

var a = [1, 2, 3];
var b = [...a];
console.log(b);

var crypto = require('crypto');
console.log(crypto.getHashes()); // 打印支持的hash算法
var md5Value = crypto.createHash('md5').update('12345').digest('hex');
console.log(md5Value);

async function f() {
    throw new Error('出错了');
}
f().then(
    v => console.log(v),
    err => console.log(err.message)
);

/**
 * 普通数组快速排序
 * @param arr Array 数字数组
 * @param dir asc升序、desc降序
 */
var sort = function (arr, dir) {
    dir = dir || 'asc';
    if (arr.length == 0) return [];

    var left = new Array();
    var right = new Array();
    var pivot = arr[0];

    if (dir === 'asc') {//升序
        for (var i = 1; i < arr.length; i++) {
            arr[i] < pivot ? left.push(arr[i]) : right.push(arr[i]);
        }
    } else {//降序
        for (var i = 1; i < arr.length; i++) {
            arr[i] > pivot ? left.push(arr[i]) : right.push(arr[i]);
        }
    }
    return sort(left, dir).concat(pivot, sort(right, dir));
};

var arr = [23, 12, 11, 43, 54, 43, 2, 12, 66];
console.log(arr);
console.log(arr.sort((x, y) => x > y));
console.log(sort(arr, 'desc'));

var exec = require('child_process').exec;
var server = null;


function startServer() {
    console.log('start server');
    server = exec('node E:\\智慧灯杆运维监控\\src\\trunk\\源码\\engima-sub-1.0\\bin\\main.js');
    console.log('node js pid is ' + server.pid);
    server.on('close', function (code, signal) {
        server = startServer();
    });
    server.on('error', function (code, signal) {
        server = startServer();
    });
    return server;
}

// startServer();

// var promise = new Promise(function (resolve, reject) {
//     // ... some code

//     if (/* 异步操作成功 */) {
//         resolve(value);
//     } else {
//         reject(error);
//     }
// });
// promise.then(
//     value => { }, // success
//     error => { }  // error
// ).catch(function (err) {
//     console.log(err);
// });


var fs = require('fs');

async function readFileSync() {
    return new Promise((resolve, reject) => {
        fs.readFile('./test/eventUtil.js', 'utf8', (err, data) => {
            if (err) {
                reject(err);
            } else {
                resolve(data);
            }
        });
    })
}

async function getFileData() {
    let fileData = await readFileSync();
    console.log(fileData);
}
// getFileData();
var us = require('underscore');
var ogj = us.map({ a: 1, b: 2, c: 3 }, (v, k) => k + '=' + v);
console.log(ogj);
var isEvery = us.every([1, 4, 7, -3, -9], x => x > 0);
var isSome = us.some([1, 4, 7, -3, -9], x => x > 0);
console.log('result1=' + isEvery + '，result2=' + isSome);