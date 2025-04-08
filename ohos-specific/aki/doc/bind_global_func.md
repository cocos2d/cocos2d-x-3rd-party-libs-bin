### <a id="bind_global_func"> 绑定全局函数 </a>

#### JSBIND_GLOBAL

用于圈定需要绑定的全局函数 scope。

#### JSBIND_FUNCTION(func, alias)

在`JSBIND_GLOBAL`作用域下使用`JSBIND_FUNCTION`绑定 C++ 全局函数后，可从 JavaScript 直接调用。

* 调度线程为 JS 线程；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| func        | 函数指针  | Y       | 被绑定的`C++`函数指针，当alias未被指定时，`JavaScript`与`C++`函数名相同。 |
| alias       | string   | N       | 函数别名 |


**示例：**
- C++

``` C++
#include <string>
#include <aki/jsbind.h>

std::string SayHello(std::string msg)
{
    return msg + " too.";
}

JSBIND_GLOBAL()
{
    JSBIND_FUNCTION(SayHello);
}

JSBIND_ADDON(hello);
```

- JavaScript

``` JavaScript
import aki from 'libhello.so' // 插件名

let message = aki.SayHello("hello world");
```

#### JSBIND_PFUNCTION(func, alias)

使用`JSBIND_PFUNCTION`绑定 C++ 全局函数后，从 JavaScript 使用同Promise方式相同的异步调用。

* 调度线程为工作线程，由 ArkCompiler Runtime 决定；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| func        | 函数指针  | Y       | 被绑定的`C++`函数指针。   |
| alias       | string   | N       | 函数别名 |


**示例：**
- C++

``` C++

void AsyncTaskReturnVoid() {
    // Do something;
}

JSBIND_GLOBAL() {
    JSBIND_PFUNCTION(AsyncTaskReturnVoid);
}

JSBIND_ADDON(async_tasks);
```

- JavaScript

``` JavaScript
import libAddon from 'libasync_tasks.so'

libAddon.AsyncTaskReturnVoid().then(res => {
  console.log('[AKI] AsyncTaskReturnVoid: ' + res)
});

```