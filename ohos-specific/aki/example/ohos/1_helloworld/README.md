## Example 1: *Hello world*

环境依赖：
* IDE： DevEco Studio 3.1.0.500
* SDK：3.2.12.2

### 1. 依赖配置

- 本例使用源码依赖
  本例直接使用根目录源码作为依赖，实际工程使用时，需要`clone`源码到指定路径，如：
    ```bash
    cd entry/src/main/cpp
    git clone
    ```

  CMakeLists.txt 配置依赖
    ```cmake
    add_subdirectory(aki)
    target_link_libraries(entry PUBLIC aki_jsbind)
    ```

### 2. 用例说明

使用 `AKI` 封装 C++ 业务插件，JavaScript 使用如下代码直接完成调用：

```js
import libAddon from "libhello.so"
let message = libAddon.SayHello('hello world');
console.log(message); // message = 'hello world too.'
```

AKI 注册 `C++` 函数

```c++
std::string SayHello(std::string msg)
{
    return msg + " too.";
}

JSBIND_GLOBAL()
{
    JSBIND_FUNCTION(SayHello);
}

JSBIND_ADDON(hello) // 注册 AKI 插件名为: hello
```