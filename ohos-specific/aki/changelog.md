# 更新日志

## 1.2.3 (2023-09-20)

### fixed
* 修复异步接口 napi_value 生命周期未被GC托管

## 1.2.2 (2023-09-10)

### fixed
* 修复 ArrayBuffer 在工作线程支持

## 1.2.0 (2023-08-20)

### feat
* 支持 JS 类型 any 映射 C++ 类型 aki::Value

## 1.1.1 (2023-08-15)

### fixed
* 修复 JSBIND_ENUM 找不到头文件问题

## 1.1.0 (2023-08-10)

### feat
* 支持uint8_t/int8_t/uint16_t/int16_t 转为 number
* 支持传递对象引用

### fixed
* 修复 callback 在 C++ 侧时，带返回值类型；

### deprecated
* C++侧对于std::vector<uint8_t> 不再被解析成 JS 侧的 Uint8Array。即std::vector<T>类型全部视为数组，如需使用TypedArray，请使用C++ 的 aki::ArrayBuffer 类型进行映射

### example
* 3_callback 增加示例: callback 实现在 cpp 侧，并支持callback带返回值
* 6_structure 更新 JSBIND_PROPERTY 用例 + 对象指针用例
* 14_reference_and_pointer 对象引用用例

### docs

* README.md 文档更新

## 1.0.8 (2023-07-27)

### docs

* README.md 文档更新

### fixed

* 修复 JSBind 绑定 std::vector<long> 类型必现编译出错；

### example
* 新增arrar_to_native 数组用例

## 1.0.7 (2023-07-24)

### feat

* 支持 JSBIND_PROPERTY，无需定义Get/Set函数，即可绑定类成员属性

## 1.0.6 (2023-07-16)

### feat

* 支持传参napi_value类型

### fixed

- README.md锚点跳转

## 1.0.5 (2023-07-11)

## 1.0.4 (2023-07-10)

### fixed

* JSBIND_PFUNCTION 绑定返回值为void类型函数编译报错

## 1.0.3 (2023-07-09)

### feat

* 支持类型转换：map<std::string, T>  <---> object；

### fixed

* JSBIND_PFUNCTION 绑定返回值为long类型编译错误

## 1.0.2 (2023-07-06)

### feat

* 新增枚举类型绑定特性；

## 1.0.1 (2023-07-05)

### fixed

* 修复PMETHOD宏绑定异步接口返回值为类对象时编译报错；

## 1.0.0 (2023-06-29)

