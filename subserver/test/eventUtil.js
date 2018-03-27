/**
 * @file 自定义事件管理模块：管理事件监听和注册事件处理函数
 * @author yaoxinyu
 * @date 2017/12/27
 */

// EventEmitter常用的API：
// EventEmitter.on(event,listener)、emitter.addListener(event,listener)为指定事件注册一个监听器，接受一个字符串event和一个回调函数listener。
// EventEmitter.once(event, listener) 为指定事件注册一个单次监听器，即监听器最多只会触发一次，触发后立刻解除该监听器。
// EventEmitter.emit(event, [arg1], [arg2], [...]) 发射 event 事件，传递若干可选参数到事件监听器的参数表。
// EventEmitter.removeListener(event, listener) 移除指定事件的某个监听器，listener必须是该事件已经注册过的监听器。
// emitter.listeners(event)    返回这个事件的监听函数的数组
// emitter.setMaxListeners(n)     设置这个emitter实例的最大事件监听数，默认是10个，设置0为不限制
// emitter.removeAllListeners(event)      删除所有对这个事件的监听函数

// 注意：
// 大多数时候我们不会直接使用 EventEmitter，而是在对象中继承它。包括 fs、net、 http 在内的，只要是支持事件响应的核心模块都是 EventEmitter 的子类。
// 为什么要这样做呢？原因有两点：
// 1)具有某个实体功能的对象实现事件符合语义， 事件的监听和发射应该是一个对象的方法。
// 2)JavaScript 的对象机制是基于原型的，支持 部分多重继承，继承 EventEmitter 不会打乱对象原有的继承关系。
// Events(事件)模块是Node.js的核心，许多其他模块用它来围绕着事件架构功能。由于Node.js运行在单一的线程中，任何同步代码都是阻塞的，所以如果有长时间运行的代码的话事件循环便会被阻塞。为了有效地使用Node.js编写代码，必须仔细思考自己的变成风格并遵循一些简单的规则。
// 那么，如何将事件添加到你的javascript对象中呢？首先需要通过在对象实例中调用events.EventEmitter.call(this)来在对象中继承EventEmitter功能，还需要把events.EventEmitter.prototype添加到对象的原型中，如：
// function myObj(){
//     Events.EventEmitter.call(this);
// }
// myObj.prototype._proto_=evnets.EventEmitter.prototype;
// 然后从对象实例中发出事件：
// var newObj=new myObj();
// newObj.emit('someEvent');

// 根据输出可以猜到：
//
// 1.process.nextTick(func)
//
// 永远在工作栈本轮执行完毕后执行；
//
// 2. setTimeout(func,0)
//
// 在下轮事件队列的前面
//
// 3. setImmediate(func)
//
// 在下轮事件队列的最后面
//
// 4.异步的信号事件
//
// 没做试验，不出意外在setTimeout与setImmediate之间响应

var events = require('events');
var util = require('util');
function myObj() {
    events.EventEmitter.call(this);
}
util.inherits(myObj, events.EventEmitter);

var newObj = new myObj();
newObj.on('someEvent', eventCallBack);
function eventCallBack() {
    console.log('someEvent happen!');
}
newObj.emit('someEvent');
newObj.removeListener('someEvent', eventCallBack);
newObj.emit('someEvent');

function a() {
    console.log('aaa');
}
function b() {
    console.log('bbb');
}
function c() {
    console.log('ccc');
    clearInterval(ddd);
}
function d() {
    console.log('ddd');
}

setImmediate(d);
var ddd = setInterval(c, 0);
setTimeout(b, 0);
process.nextTick(a);
