
## AKI hybrid Node-API 混合开发

`AKI` 支持与 Node-API 混合开发。接口 `aki::BindSymbols` 用于绑定使用 `AKI` 的 Native 符号表给指定的 napi_value 对象。

如下示例：

examples/ohos/4_hybrid_napi/entry/src/main/hello.cpp
```C++
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        ...
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    
    exports = aki::BindSymbols(env, exports); // aki::BindSymbols 函数传入 js 对象绑定符号
    return exports;
}
EXTERN_C_END
```