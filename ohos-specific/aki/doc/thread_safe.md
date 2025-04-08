### <a id="thread_safe"> 线程安全函数 </a>

使用`AKI`的线程安全特性，绑定 JavaScript 的业务函数后，可由`native`直接调用。

- **线程安全**：使用`AKI`线程安全绑定的 JavaScript 函数是线程安全的，可在非JS线程直接调用。最终会由框架调度JS线程执行业务；
- **阻塞式调用**：C++ 触发调用 JavaScript 函数的调用是阻塞式的，对于在JS线程执行业务这点没有疑义。但当C++触发 JavaScript 业务调用的线程是非JS线程时，就存在跨线程任务调度。此时由框架进行了阻塞式调用，即 C++ 会等待 JavaScript 函数执行结束后返回；

#### JSBind.bindFunction(name: string, func: function)

在 JavaScript 使用 `JSBind.bindFunction` 绑定 JavaScript 全局函数后，可从 C++ 直接调用。

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| name        | string   | Y       | 指定绑定的`JavaScript`函数名，用于Native索引。 |
| func        | function | Y       | 被绑定的`JavaScript`函数 |

**返回值：**

| **类型** | **说明** |
| ----------- | -------- |
| number      | 当前被绑定的函数下标索引   |

``` JavaScript
// name: 指定函数名，func: JavaScript 全局函数
libAddon.JSBind.bindFunction(name: string, func: Function);
```

C++ 使用aki::JSBind::GetJSFunction获取指定 JavaScript 函数句柄后，使用Invoke触发调用

``` C++
auto jsFunc = aki::JSBind::GetJSFunction("xxx"); // 获取指定函数句柄
auto result = jsFunc->Invoke<T>(...); // 调用JavaScript函数，Invoke<T>指定返回值类型
```

- JavaScript

``` JavaScript
import libAddon from 'libhello.so' // 插件名

function sayHelloFromJS (value) {
  console.log('what do you say: ' + value);
  return "hello from JS"
}

libAddon.JSBind.bindFunction("sayHelloFromJS", sayHelloFromJS);
```

- C++

``` C++
#include <string>
#include <aki/jsbind.h>

void DoSomething() {
    // 索引 JS 函数句柄
    auto jsFunc = aki::JSBind::GetJSFunction("sayHelloFromJS");

    // Invoke 指定 JS 方法的返回值类型
    auto result = jsFunc->Invoke<std::string>("hello from C++"); // 可在非JS线程执行
    // result == "hello from JS"
}
```

查看示例：[bind_from_js](https://gitee.com/openharmony-sig/aki/tree/master/example/ohos/5_bind_from_js)