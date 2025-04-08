## Example 4: *hybrid_napi*

环境依赖：
* IDE： DevEco Studio 3.1.0.500
* SDK：3.2.12.2

### 1. 依赖配置

- 本例使用源码依赖

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

使用 `AKI` 封装 C++ 业务插件，AKI 支持与 Node-API 混合开发。接口 aki::BindSymbols 用于绑定使用 AKI 的 Native 符号表给指定的 napi_value 对象:

```c++
static napi_value Init(napi_env env, napi_value exports)
{
    ......
    exports = aki::JSBind::BindSymbols(env, exports); // aki::BindSymbols 函数传入 js 对象绑定符号
    return exports;
}
```