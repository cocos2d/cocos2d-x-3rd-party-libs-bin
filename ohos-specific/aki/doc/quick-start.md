## <a id="quick_start"> 快速接入 </a>

- [1 依赖配置](#1-依赖配置)
- [2 用户自定义业务](#2-用户自定义业务)
- [3 使用 AKI](#3-使用-aki)
- [4 编译构建使用](#4-编译构建使用)

### **1 依赖配置（2选1）**
* **源码依赖（推荐）**

  指定cpp路径下（如：项目根路径/entry/src/main/cpp）
    ```
    cd entry/src/main/cpp
    git clone https://gitee.com/openharmony-sig/aki.git
    ```
  CMakeLists.txt添加依赖（假定编译动态库名为:libhello.so）:

    ```cmake
    add_subdirectory(aki)
    target_link_libraries(hello PUBLIC aki_jsbind)
    ```
    
* **ohpm har包依赖**

  指定路径下（如：项目根路径/entry），输入如下命令安装ohpm har包依赖
    ```
    cd entry
    ohpm install @ohos/aki
    ```
  CMakeLists.txt添加依赖（假定编译动态库名为:libhello.so）:

    ```cmake
    set(AKI_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../oh_modules/@ohos/aki) # 设置AKI根路径
    set(CMAKE_MODULE_PATH ${AKI_ROOT_PATH})
    find_package(Aki REQUIRED)

    ...

    target_link_libraries(hello PUBLIC Aki::libjsbind) # 链接二进制依赖 & 头文件
    ```


### **2 用户自定义业务**

用户业务 C++ 代码 hello.cpp:<br>
全程无感`node-API`

```C++
#include <string>

std::string SayHello(std::string msg)
{
  return msg + " too.";
}

```

### **3 使用 AKI**

使用`JSBind`工具宏声明需要被绑定的类、函数：

```C++
#include <aki/jsbind.h>

// Step 1 注册 AKI 插件
JSBIND_ADDON(hello) // 注册 AKI 插件名: 即为编译*.so名称，规则与NAPI一致

// Step 2 注册 FFI 特性
JSBIND_GLOBAL()
{
  JSBIND_FUNCTION(SayHello);
}
```

### **4 编译构建使用**

OpenHarmony工程代码调用:

```javascript
import aki from 'libhello.so' // 工程编译出来的*.so

aki.SayHello("hello world");
```