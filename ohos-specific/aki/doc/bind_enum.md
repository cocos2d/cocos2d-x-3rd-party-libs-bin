### <a id="bind_enum"> 绑定枚举类型 </a>

`JSBind`语法糖`JSBIND_ENUM`、`JSBIND_ENUM_VALUE`支持绑定 C/C++ 枚举类型，映射为 JavaScript 的Number类型。

- C/C++侧默认枚举类型为POD中的int32_t；
- JavaScript侧对应的枚举类型属性为`readonly`；

#### JSBIND_ENUM(enum)

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| enum        | enum  | Y       | 被绑定的`C++`枚举类型。 |

#### JSBIND_ENUM_VALUE(value)

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| value        | enum::value  | Y       | 被绑定的`C++`枚举值。 |

**示例：**
- C++

``` C++
#include <string>
#include <aki/jsbind.h>

enum TypeFlags {
    NONE,
    NUM,
    STRING,
    BUTT = -1
};

JSBIND_ENUM(TypeFlags) {
    JSBIND_ENUM_VALUE(NONE);
    JSBIND_ENUM_VALUE(NUM);
    JSBIND_ENUM_VALUE(STRING);
}

TypeFlags Passing(TypeFlags flag) {
    return flag;
}

JSBIND_GLOBAL()
{
    JSBIND_FUNCTION(Passing);
}

JSBIND_ADDON(enumeration);
```

- JavaScript

``` JavaScript
import libAddon from 'libenumeration.so' // 插件名


console.log('AKI libAddon.TypeFlags.NONE = ' + libAddon.TypeFlags.NONE);
console.log('AKI libAddon.TypeFlags.NUM = ' + libAddon.TypeFlags.NUM);
console.log('AKI libAddon.TypeFlags.Passing() = ' + libAddon.Foo(libAddon.TypeFlags.STRING));
try {
  libAddon.TypeFlags.NUM = 10; // TypeError: Cannot set readonly property
} catch (error) {
  console.error('AKI catch: ' + error);
}
```