## Example 3: *callback*

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

使用 `AKI` 封装 C++ 业务插件，JS 调用Native函数时，有时候需要传入Function类型参数作为回调：

```js
import callback from "libcallback.so"
callback.CallJsbCallbackReturnVoid(() => {
  hilog.info(0x0000, 'callback-js', 'aki::Callback callback from js');
})
```

`AKI`触发回调的方式很简单，当绑定的Native方法带有参数类型std::function, aki::Callback, aki::SafetyCallback，即可接受JS 回调作为入参。用户只需按照std::function用法使用，即可触发回调：
```c++
void CallFunctionReturnVoid(std::function<void()> func) {
    func();
}
```