### <a id="aki_value"> aki::Value <sup> v1.2.0 </sup> </a>

JavaScript 是弱类型语言，可用泛型`any`表示任意类型。C/C++使用`aki::Value`映射 JavaScript 的`any`类型

#### <a id="aki_value_from_global"> aki::Value::FromGlobal </a>

```C++
static Value FromGlobal(const char* key = nullptr)
```

用于获取 JS 侧`globalThis`下的属性。

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| key   | string        | Y       | 需要读取的属性名。 |

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| aki::Value | 对应属性的 JS 对象句柄。 |

**示例：**
```C++
  // 获取globalThis.JSON
  aki::Value json = aki::Value::FromGlobal("JSON");
  json["stringify"](obj);
```

#### <a id="aki_value_as"> aki::Value::As </a>

```C++
template<typename T>
T As() const;
```
模板函数，用于将 JS 对象转化为 C/C++ 指定数据类型

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| T   | any        | Y       | 需要被转化的 C/C++ 数据类型。 |

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| T | 对应类型的值。 |

**示例：**
```C++
  value.As<bool>(); // 将 JS 对象 value 转化为 bool
  value.As<int>(); // 将 JS 对象 value 转化为 int
  value.As<std::string>(); // 将 JS 对象 value 转化为 string
```

#### <a id="aki_value_get_handle"> aki::Value::GetHandle </a>

```C++
napi_value GetHandle() const
```
用于获取 JS 对象的 napi_value 句柄。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| napi_value | JS 对象的 napi_value 句柄。 |

#### <a id="aki_value_call_method"> aki::Value::CallMethod </a>

```C++
template<typename... Args>
Value CallMethod(const char* name, Args&&... args)
```

调用 JS 对象的成员函数。

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| name   | string        | Y       | 函数名。 |
| args   | any        | N       | 成员函数接收的参数。 |

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| aki::Value | 返回泛型对象。 |

**示例：**
```C++
  // value 映射为 JS 数组对象 let value = ['aki'];
  // 调用 value.push('jsbind');
  value.CallMethod("push", "jsbind");
```

#### aki::Value::operator[]

```C++    
Value operator[](const std::string& key) const;
Value operator[](const size_t index) const;
```
`aki::Value`对象的下标运算符

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| key   | string        | Y       | 属性名下标。 |
| index   | size_t        | Y       | 数组下标。 |

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| aki::Value | 返回泛型对象。 |

**示例：**
```C++
  // value 映射为 JS 数组对象 let value = ['aki', 'jsbind'];
  // 访问下标为0的值：'aki';
  aki::Value str = value[0]; // str = "aki"

  // 调用 JSON.stringify(...);
  aki::Value::FromGlobal("JSON")["stringify"](...);
```

#### aki::Value::operator()

```C++    
template<typename... Args>
Value operator()(Args&&... args) const;
```
`aki::Value`对象的函数调用运算符

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| args   | any        | N       | 函数所接收入参。 |

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| aki::Value | 返回泛型对象。 |

**示例：**
```C++
  // 调用 JSON.parse({'aki': 'jsinbd'});
  aki::Value::FromGlobal("JSON")["parse"]({"aki": "jsinbd"});
```

#### aki::Value::Set

```C++
template<typename V>
void Set(const char* key, const V& value);
```
用于给`aki::Value`泛型对象属性设值。

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| key   | string        | Y       | 属性名。 |
| value   | any        | Y       | 属性值。 |

**示例：**
```C++
  // value 为 JS 对象;
    value.Set("name", "aki");
```

#### aki::Value::NewObject

```C++
static Value NewObject();
```
创建`aki::Value`泛型对象。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| aki::Value | 返回泛型对象。 |

**示例：**
```C++
  aki::Value val = aki::Value::NewObject();
  val.Set("name", "aki"); // {'name': 'aki'};
```

#### aki::Value::IsUndefined

```C++
bool IsUndefined() const
```

判断 JS 对象类型是否为`undefined`。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| bool | true or false。 |

#### aki::Value::IsNull

```C++
bool IsNull() const
```

判断 JS 对象类型是否为`null`。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| bool | true or false。 |

#### aki::Value::IsBool

```C++
bool IsBool() const
```

判断 JS 对象类型是否为`boolean`。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| bool | true or false。 |

#### aki::Value::IsNumber

```C++
bool IsNumber() const
```

判断 JS 对象类型是否为`number`。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| bool | true or false。 |

#### aki::Value::IsString

```C++
bool IsString() const
```

判断 JS 对象类型是否为`string`。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| bool | true or false。 |

#### aki::Value::IsArray

```C++
bool IsArray() const
```

判断 JS 对象类型是否为数组`[]`。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| bool | true or false。 |

#### aki::Value::IsFunction

```C++
bool IsFunction() const
```

判断 JS 对象类型是否为`function`。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| bool | true or false。 |


#### C/C++ 调用 @ohos.bundle.bundleManager (bundleManager模块)特性

示例：

- 期望在 C++ 调用如下@ohos.bundle.bundleManager (bundleManager模块) 特性：
  
  如下`ArkTS`代码为[@ohos.bundle.bundleManager 示例](https://docs.openharmony.cn/pages/v3.2/zh-cn/application-dev/reference/apis/js-apis-bundleManager.md/)
  ```JavaScript
  import bundleManager from '@ohos.bundle.bundleManager';
  import hilog from '@ohos.hilog';
  let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_DEFAULT;
  try {
      bundleManager.getBundleInfoForSelf(bundleFlags).then((data) => {
          hilog.info(0x0000, 'testTag', 'getBundleInfoForSelf successfully. Data: %{public}s', JSON.stringify(data));
      }).catch(err => {
          hilog.error(0x0000, 'testTag', 'getBundleInfoForSelf failed. Cause: %{public}s', err.message);
      });
  } catch (err) {
      hilog.error(0x0000, 'testTag', 'getBundleInfoForSelf failed: %{public}s', err.message);
  }
  ```
  使用如下`C++`代码实现上述功能
  ```C++
    /* 要求在ArkTS侧执行如下代码：
    * import bundleManager from '@ohos.bundle.bundleManager';
    * globalThis.bundleManager = bundleManager;
    */
    aki::Value bundleManager = aki::Value::FromGlobal("bundleManager");
    
    /* 如下 C++ 代码等同于 JS 代码:
    * let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_DEFAULT;
    * bundleManager.getBundleInfoForSelf(bundleFlags).then((data) => {
    *   console.log('getBundleInfoForSelf successfully. Data:', JSON.stringify(data));
    * })
    */
    std::function<void(aki::Value)> thenFunc = [](aki::Value data) {
        AKI_LOG(INFO) << aki::Value::FromGlobal("JSON")["stringify"](data).As<std::string>();
    };
    int bundleFlags = bundleManager["BundleFlag"]["GET_BUNDLE_INFO_DEFAULT"].As<int>();
    bundleManager["getBundleInfoForSelf"](bundleFlags).CallMethod("then", thenFunc);
  ```

- [Example](https://gitee.com/openharmony-sig/aki/tree/master/example/ohos/15_aki_value)