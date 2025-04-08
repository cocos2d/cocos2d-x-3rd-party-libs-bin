# 数据类型

|  **JavaScript**  | **C++** | 
| ---------------- | ------------------------ | 
| Boolean          | `bool`  <br> [参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/type-conversion.md#boolean)                                     |
| Number           | `uint8_t`, `int8_t`, `uint16_t`, `int16_t`, `short`, `int32`, `uint32`, `int64`, `float`, `double`, `enum` <br> [参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/type-conversion.md#number) |
| String           | `const char*`, `std::string` <br> [参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/type-conversion.md#string)                |
| Array            | `std::vector<T>`, `std::array<T, N>` <br> [参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/type-conversion.md#array)            |
| Function         | `std::function<R (P...)>` <br> `aki::Callbackn<R (P...)>` <br> `aki::SafetyCallbackn<R (P...)>` <br> [参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/type-conversion.md#function) |
| Class Object      | `class`                                     |
| JsonObject       | `std::map<std::string,T>` <br> [参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/type-conversion.md#jsonobject)                                  |
| ArrayBuffer, <br> TypedArray      | `aki::ArrayBuffer` <br> [参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/type-conversion.md#arrarbuffer)  |
| Promise          | `JSBIND_PFUNCTION`, `JSBIND_PMETHOD` |
| any          | `aki::Value`, `napi_value` |

`AKI`框架使用声明式类型转换，开发者无需手动对 **JavaScript** 和 **C++** 类型进行转换，只需声明接口需要传递的参数类型，框架层自动转换。

### Boolean
如下示例，开发者直接声明函数入参及返回值类型，使用`AKI`绑定后，框架自适应对 C/C++ 的 `bool` 及 JavaScript 的 `Boolean` 类型进行转化。

**示例：**

- C++

  ``` C++
  #include <aki/jsbind.h>
  bool Foo(bool flag) {
    ...
    return true;
  }
  JSBIND_GLOBAL() {
      JSBIND_FUNCTION(Foo, "foo");
  }
  JSBIND_ADDON(hello)
  ```

- JavaScript

  ``` JavaScript
  import libAddon from 'libhello.so'
  let flag = libAddon.foo(true);
  ```

### Number

如下示例，开发者直接声明函数入参及返回值类型，使用`AKI`绑定后，框架自适应对 C/C++ 的 `uint8_t`, `int8_t`, `uint16_t`, `int16_t`, `short`, `int32`, `uint32`, `int64`, `float`, `double`, `enum` 及 JavaScript 的 `Number` 类型进行转化。

* `float:` 浮点型转换时存在精度丢失，对于高精度场景，请使用 `double`；
* `enum:` 枚举类型的转化请[参考](https://gitee.com/openharmony-sig/aki/blob/master/doc/bind_enum.md)

**示例：**

- C++

  ``` C++
  #include <aki/jsbind.h>
  int Foo(int num) {
    ...
    return 666;
  }
  JSBIND_GLOBAL() {
      JSBIND_FUNCTION(Foo, "foo");
  }
  JSBIND_ADDON(hello)
  ```

- JavaScript

  ``` JavaScript
  import libAddon from 'libhello.so'
  let num = libAddon.foo(888);
  ```

### String

如下示例，开发者直接声明函数入参及返回值类型，使用`AKI`绑定后，框架自适应对 C/C++ 的 `const char*`, `std::string` 及 JavaScript 的 `String` 类型进行转化。

* `const char*` 是以引用方式传递参数，如遇到异步操作，请使用传值方式：std::string；

**示例：**

- C++

  ``` C++
  #include <aki/jsbind.h>
  std::string Foo(const char* c_str, std::string str) {
    ...
    return "AKI 666";
  }
  JSBIND_GLOBAL() {
      JSBIND_FUNCTION(Foo, "foo");
  }
  JSBIND_ADDON(hello)
  ```

- JavaScript

  ``` JavaScript
  import libAddon from 'libhello.so'
  let str = libAddon.foo("AKI", "666");
  ```

### Array

如下示例，开发者直接声明函数入参及返回值类型，使用`AKI`绑定后，框架自适应对 C/C++ 的 `std::vector<T>`, `std::array<T, N>` 及 JavaScript 的 `[]` 类型进行转化。

* 数组类型仅支持**同种类型**的数组声明；

**示例：**

- C++

  ``` C++
  #include <aki/jsbind.h>
  std::vector<double> Foo(std::array<int, 3>) {
    std::vector<double> result;
    ...
    return result;
  }
  JSBIND_GLOBAL() {
      JSBIND_FUNCTION(Foo, "foo");
  }
  JSBIND_ADDON(hello)
  ```

- JavaScript

  ``` JavaScript
  import libAddon from 'libhello.so'
  let array = libAddon.foo([1, 2, 3]);
  ```

### ArrarBuffer

二进制数据缓冲区`ArrayBuffer`, `TypedArray` 是 JavaScript AKI 提供了内建结构体：`aki::ArrayBuffer`用来支持该特性：

- `GetData()*` 获取 ArrayBuffer 数组缓冲区地址，aki::ArrayBuffer 本身不申请数据内存，data 都来源于JavaScript引擎分配的内存，也无需做内存生命周期管理，**禁止对该内存进行危险的释放**。

- `GetLength()` 获取 ArrayBuffer 数组缓冲区长度，以单字节为计量单位。

- `GetTyped()` 获取 ArrayBuffer 数组缓冲区的类型化类型。

- `GetCount()` 获取 ArrayBuffer 数组缓冲区的类型化数据元素个数。

**示例：**

- C++

``` C++
#include <aki/jsbind.h>
aki::ArrayBuffer PassingArrayBufferReturnArrayBuffer(aki::ArrayBuffer origin) {
    aki::ArrayBuffer buff(origin.GetData(), origin.GetCount());
    uint8_t* data = buff.GetData();
    data[4] = 4;
    data[5] = 5;
    data[6] = 6;
    data[7] = 7;

    return buff;
}
```

- JavaScript

``` JavaScript
import libAddon from 'libarraybuffer2native.so'

let buff: ArrayBuffer = new ArrayBuffer(8);
let uint8Buff1: Uint8Array = new Uint8Array(buff);
uint8Buff1[0] = 0;
uint8Buff1[1] = 1;
uint8Buff1[2] = 2;
uint8Buff1[3] = 3;
let result: ArrayBuffer = libAddon.PassingArrayBufferReturnArrayBuffer(buff);
uint8Buff1 = new Uint8Array(result);
let message: String = uint8Buff1.toString();
```

### 对象引用&指针
C++ 对象作为参数和返回类型，在 C++ & JavaScript 代码中可以使用如下形式进行传递：
- 值传递；
- 引用（T&）与指针（T*）传递；
- [Example](https://gitee.com/openharmony-sig/aki/tree/master/example/ohos/14_reference_and_pointer)

### JsonObject

JavaScript支持使用`JsonObject`表示key-value结构的数据类型，如：
```javascript
{
  name: 'hanmeimei',
  age: '17',
  date: '1999-02-02'
}
```
`AKI`支持使用C/C++的`std::map<std::string, T>`映射JavaScript的`JsonObject`。

  - 与`std::map<std::string, T>`对应的`JsonObject`必须约束value类型一致

- [Example](https://gitee.com/openharmony-sig/aki/tree/master/example/ohos/10_map_for_object)

- C++

``` C++
void Foo(std::map<std::string, int> obj)
{
    for (auto& iter : obj) {
        ......; // key: iter.first; value: iter.second
    }
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(Foo);
}
```

- JavaScript

``` JavaScript
import libmap_for_object from 'libmap_for_object.so'

let a = {age: 100};
libmap_for_object.Foo(a);
```

### Function

Function是JS的一种基本数据类型，当JS传入Function作为参数时，Native可在适当的时机调用触发回调。`AKI` 支持如下3中C++数据类型作为参数处理回调：

- aki::Callback<R (P...)>：指定回调类型为`R (*)(P...)`的**高性能**回调。**非线程安全，禁止在非JS线程使用**，否则会发生异常；
- aki::SafetyCallback<R (P...)>：指定回调类型为`R (*)(P...)`的线程安全回调。因为需要创建线程安全资源，所以性能不如aki::Callback；
- std::function<R (P...)>：用法与aki::SafetyCallback一致；
