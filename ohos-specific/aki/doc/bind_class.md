### <a id="bind_class_struct"> 绑定类/结构体 </a>

`AKI` 提供 `JSBIND_CLASS` 对 C++ `类/结构体`进行绑定，在`JSBIND_CLASS`作用域下可绑定：类构造函数、类成员函数、类成员属性的类特性。

#### <a id="bind_class"> JSBIND_CLASS(class) </a>

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| class        | class/struct  | Y       | 被绑定的C++`类对象/结构体`，`JavaScript`与`C++`类名相同。 |

#### <a id="bind_class_cons"> JSBIND_CONSTRUCTOR\<T\>() </a>

在`JSBIND_CLASS`作用域下使用绑定 C++ 类/结构体构造函数，其中为了支持多态，可通过类型模板指定构造函数参数类型。
- `JSBIND_CONSTRUCTOR` 需要在`JSBIND_CLASS`的作用域下；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| T        | any  | N       | 构造函数参数类型，可变类型参数。 |

**示例：**
- C++

``` C++
#include <string>
#include <aki/jsbind.h>

class TestObject {
public:
    TestObject();
    
    explicit TestObject(double) {
        // ...
    }
    
    ~TestObject() = default;
} // TestObject

JSBIND_CLASS(TestObject)
{
    JSBIND_CONSTRUCTOR<>();
    JSBIND_CONSTRUCTOR<double>();
}
JSBIND_ADDON(hello);
```

- JavaScript

``` JavaScript
import aki from 'libhello.so' // 插件名

var obj1 = new aki.TestObject();
var obj2 = new aki.TestObject(3.14);
```

### <a id="bind_class_method"> 绑定类成员函数 </a>

#### JSBIND_METHOD(method)

`AKI` 使用 `JSBIND_METHOD` 对C++ 的3种类成员函数进行绑定：类静态函数、类成员函数、const 类成员函数。
* `JSBIND_METHOD` 需要在`JSBIND_CLASS`的作用域下；
* 调度线程为 JS 线程；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| method        | R (C::*)(P...)  | Y       | 同时支持类静态函数、类成员函数、const 类成员函数。 |

**示例：**

使用 `AKI` 对C++类成员函数绑定
``` C++
#include <string>
#include <aki/jsbind.h>

class TestObject {
public:
    TestObject();
    
    explicit TestObject(double) {
        // ...
    }
    
    ~TestObject() = default;
    
    static double MultiplyObject(TestObject obj1, TestObject obj2) {
        return obj1.value_ * obj2.value_;
    }
    
    double Multiply(double mult) {
        value_ *= mult;
        return value_;
    }

private:
    double value_;
} // TestObject

JSBIND_CLASS(TestObject)
{
    JSBIND_CONSTRUCTOR<>();
    JSBIND_CONSTRUCTOR<double>();
    JSBIND_METHOD(MultiplyObject);
    JSBIND_METHOD(Multiply);
}
JSBIND_ADDON(hello);
```

例：JavaScript 侧调用绑定的C++类成员函数

``` JavaScript
import aki from 'libhello.so' // 插件名

var obj1 = new aki.TestObject();
var obj2 = new aki.TestObject(3.14);
obj1.Multiply(-1);
aki.TestObject.MultiplyObject(obj1, obj2) // 静态方法
```

#### JSBIND_PMETHOD(method)

`JSBIND_PMETHOD`用于绑定 C++ 类成员函数，从 JavaScript 使用同Promise方式相同的异步调用。

* 调度线程为工作线程，由 ArkCompiler Runtime 决定；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| method       | 类成员函数指针  | Y       | 被绑定的`C++`类成员函数指针。   |

**示例：**

- C++

``` C++

class TaskRunner {
public:
    TaskRunner() = default;
    void DoTask() {
      // Do something;
    }
};

JSBIND_CLASS(TaskRunner) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_PMETHOD(DoTask);
}

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

let taskRunner = new libAddon.TaskRunner();
taskRunner.DoTask().then(res => {
  console.log('[AKI] DoTask: ' + res)
});

libAddon.AsyncTaskReturnVoid().then(res => {
  console.log('[AKI] AsyncTaskReturnVoid: ' + res)
});

```

### <a id="bind_class_property"> 绑定类成员属性 </a>

#### JSBIND_PROPERTY(property) <sup>new in 1.0.7</sup>

`AKI` 使用`JSBIND_PROPERTY`、`JSBIND_FIELD` 对 C++ 的类成员属性、类成员属性访问器进行绑定
- `JSBIND_PROPERTY`需要在`JSBIND_CLASS`的作用域下；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| property    |     T    | Y       | 类成员属性名。 |

**示例：**

``` C++
#include <string>
#include <aki/jsbind.h>

class TestObject {
public:    
    explicit TestObject(double) {
        // ...
    }
    
    ~TestObject() = default;

private:
    double value_;
} // TestObject

JSBIND_CLASS(TestObject)
{
    JSBIND_CONSTRUCTOR<double>();
    JSBIND_PROPERTY(value);
}
```

- JavaScript

``` JavaScript
import aki from 'libhello.so' // 插件名

var obj = new aki.TestObject(3.14);
obj.value = 1;
let value = obj.value;
```

#### JSBIND_FIELD(field, getter, setter)

`AKI` 使用`JSBIND_FIELD` 对 C++ 的类成员属性进行监听

* `JSBIND_FIELD` 需要在`JSBIND_CLASS`的作用域下；

* 调度线程为 JS 线程；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| field    | T  | Y       | 类成员属性名。 |
| getter    | T (void)  | Y       | get属性访问器。 |
| setter    | void (T)  | Y       | set属性访问器。 |

**示例：**
- C++

``` C++
#include <string>
#include <aki/jsbind.h>

class TestObject {
public:    
    explicit TestObject(double) {
        // ...
    }
    
    ~TestObject() = default;
    
    double GetValue() const {
        return value_;
    }

    void SetValue(double value) {
        value_ = value;
    }

private:
    double value_;
} // TestObject

JSBIND_CLASS(TestObject)
{
    JSBIND_CONSTRUCTOR<double>();
    JSBIND_FIELD("value", GetValue, SetValue);
}
```

- JavaScript

``` JavaScript
import aki from 'libhello.so' // 插件名

var obj = new aki.TestObject(3.14);
obj.value = 1;
let value = obj.value;
```