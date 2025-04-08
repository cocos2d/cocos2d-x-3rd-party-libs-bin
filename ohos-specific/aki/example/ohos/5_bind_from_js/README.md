## Example 5: *Bind From JS*

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

本例使用 `AKI` 绑定 JavaScript 鸿蒙 [关系型数据库](https://docs.openharmony.cn/pages/v3.2Beta/zh-cn/application-dev/reference/apis/js-apis-data-rdb.md/#datardbgetrdbstore) 业务函数。

```js
class MyStorage {
    static createTable(table: string, callback?: Function) {...}

    static insert(table: string, callback?: Function) {...}

    static query(table: string, callback?: Function) {...}
};
// JS 侧绑定静态方法 (name: 方法名, function: 方法)
libAddon.JSBind.bindFunction("MyStorage.createTable", MyStorage.createTable);
libAddon.JSBind.bindFunction("MyStorage.insert", MyStorage.insert);
libAddon.JSBind.bindFunction("MyStorage.query", MyStorage.query);
```

`C++` 可使用如下代码直接调用被绑定的 `JavaScript` 函数：

```C
// aki::JSBind::GetJSFunction 获取 JS 函数句柄
auto createTable = aki::JSBind::GetJSFunction("MyStorage.createTable");
int result = createTable->Invoke<int>("MYSTORE"); // 返回值类型 int，入参类型 string

auto insert = aki::JSBind::GetJSFunction("MyStorage.insert");
insert->Invoke<void>("MYSTORE"); // 无返回值，入参类型 string

auto query = aki::JSBind::GetJSFunction("MyStorage.query");
query->Invoke<void>("MYSTORE"); // 无返回值，入参类型 string

// 支持跨线程调用JS函数
std::thread t([] () {
    auto createTable = aki::JSBind::GetJSFunction("MyStorage.createTable");
    int result = createTable->Invoke<int>("MYSTORE"); // 阻塞式调用，JS执行结束时返回。
});

// 如有异步转同步需求，可使用std::promise
std::threadt([] () {
    std::promise<std::string> promise;
    std::function<void (std::string)> callback = [&promise] (std::string message) {
        promise.set_value(message);// 回调在JS线程被执行
    }
    auto insert = aki::JSBind::GetJSFunction("MyStorage.insert");
    insert->Invoke<void>("MYSTORE", callback);
    std::string msg = promise.get_future().get(); // 子线程阻塞，直到promise.set_value
});

```