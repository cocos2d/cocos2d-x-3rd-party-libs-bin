## Example 6: *structure*

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

使用 `AKI` 封装 C++ 业务插件，`AKI` 支持绑定 Native 对象：构造函数、类静态函数、类成员函数、类属性访问器等特性。

本例介绍绑定 Native 对象/结构体用于函数参数传递:

```c++
struct Person {
    // 构造函数，用于JS侧 new 对象
    Person(std::string name) : name(name) {}
    
    // Get 用于做属性访问，JS侧无需访问类对象，可不定义
    std::string GetName() {
        return name;
    }
    
    // Set 用于做属性访问，JS侧无需访问类对象，可不定义
    void SetName(std::string name) {
        this->name = name;
    }
    std::string name;
};

JSBIND_CLASS(Person) {
    JSBIND_CONSTRUCTOR<std::string>(); // 绑定构造函数
    JSBIND_FIELD("name", GetName, SetName); // Get / Set 用于做属性访问，JS侧无需访问类对象，可不定义
}

Person foo(Person person) {
    person.name += " for Ark.";
    return person;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(foo);
}
```