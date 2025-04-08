# API参考

### <a id="napi_env"> napi_env 获取 </a>

```C++
static napi_env aki::JSBind::GetScopedEnv();
```

线程安全函数，用于获取当前线程的 napi_env 对象。当在非 JS 线程调用时，返回 nullptr。

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| key   | string        | Y       | 需要读取的属性名。 |

**示例：**
```C++
// 在 JS 线程执行
napi_value obj;
napi_env env = aki::JSBind::GetScopedEnv();
napi_create_object(env, &obj);
```

### aki::ArrayBuffer

#### constructor
* 当在非 JS 线程使用 aki::ArrayBuffer，需要关注数据字节流生命周期，并考虑是否需要结合`Commit()`函数使用。

```C++
ArrayBuffer(uint8_t* ptr, size_t len, Typed typed = BUFF)
```

**参数：**
|  **参数名**  | **类型** | **必填** | **说明** |
| ----------- | -------- | ------- | ------------------------ | 
| ptr         | uint8_t* | Y       | 构造 ArrayBuffer 的数据字节流内存地址。 |
| len         | size_t | Y       | 构造 ArrayBuffer 的数据字节流内存长度。 |
| typed         | aki::ArrayBuffer::Typed | N       | 构造的 ArrayBuffer \| TypedArray 类型，默认为 ArrayBuffer。 |

**示例：**
```C++
uint8_t temp[4] = {10, 20, 30, 40};
aki::ArrayBuffer arrayBuffer(temp, 4);
```

#### GetData
```C++
uint8_t* GetData()
```
获取 ArrayBuffer 的数据字节流内存地址。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| uint8_t* | ArrayBuffer 的数据字节流内存地址。 |

#### GetLength
```C++
size_t GetLength()
```
获取 ArrayBuffer 的数据字节流内存长度。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| size_t | ArrayBuffer 的数据字节流内存长度。 |

#### Commit
```C++
void Commit()
```
当在非 JS 线程使用 ArrayBuffer 时，如果数据字节流的内存生命周期在 ArrayBuffer 使用前结束，则需要暂存。

**返回值：**
| **类型** | **说明** |
| -------- | ------------------------ | 
| size_t | ArrayBuffer 的数据字节流内存长度。 |

**示例：**
```C++
// 非 JS 线程
aki::ArrayBuffer AsyncTaskReturnArrayBufferWithCommit() {
    uint8_t temp[4] = {10, 20, 30, 40};
    aki::ArrayBuffer arrayBuffer(temp, 4);
    arrayBuffer.Commit();
    return arrayBuffer;
}
```

