/**
 * @file 如何实现继承
 * @author yaoxinyu
 * @date 2017/12/25
 */

const util = require('util');

/**
 * 父类构造函数
 * @constructor
 */
function ParentClass() {
    // 成员变量
    this.name = 'aaa';
}
ParentClass.prototype = {
    functionA: function () {
        console.log('call function A');
    },
    functionB: function () {
        console.log('call function B');
    }
}

/**
 * 子类构造函数
 * @constructor
 */
function ChildClass() {
    // 继承父类成员变量
    ParentClass.call(this);

    // 修改成员
    // this.name = 'AAA';
}
// 继承父类原型成员函数
util.inherits(ChildClass, ParentClass);

// 测试
var child = new ChildClass();
child.functionA();
child.functionB();
console.log(child.name);