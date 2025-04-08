### <a id="addon_register"> 插件注册 </a>

#### JSBIND_ADDON(addonName)

使用`JSBIND_ADDON`注册OpenHarmony Native 插件，可从 JavaScript `import` 导入插件。

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| addonName   | -        | Y       | 注册的OpenHarmony native 插件名，可从 JavaScript `import lib${addonName}.so` 导入插件，插件名必须符合函数命名规则。 |

**示例：**
- C++

``` C++
#include <string>
#include <aki/jsbind.h>

JSBIND_ADDON(addon0)

```

- JavaScript

``` JavaScript
import addon from 'libaddon0.so' // 插件名为：addon0
```

#### JSBIND_ADDON_X(addonName constructorAlias)
用法与`JSBIND_ADDON`相似，用于支持插件名有特殊符号的场景，如包含'-'；

**参数：**

|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| addonName   | -        | Y       | 注册的OpenHarmony native 插件名，可从 JavaScript `import lib${addonName}.so` 导入插件，插件名可包含特殊符号，如：'-'。 |
| constructorAlias   | -        | Y       | 插件预构造函数名，只需填写符合函数命名规则名称即可，无其他特殊含义 |

**示例：**
- C++

``` C++
#include <string>
#include <aki/jsbind.h>

JSBIND_ADDON(hello-world, HelloWorld)

```

- JavaScript

``` JavaScript
import addon from 'libhello-world.so' // 插件名为：hello-world
```
