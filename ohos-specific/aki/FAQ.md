# AKI FAQ

## 问题反馈

### 1. C/C++ 的结构体对象，可以作为参数类型嘛？

- 问题描述：在C/C++侧定义的结构体，想通过FFI接口直接作为参数、返回值传递结构体对象。

- 可以，AKI 语法糖 JSBIND_CLASS 支持绑定C/C++定义的自定义结构体。被绑定的结构体可以直接作为参数或者返回值，用法如下：
	
	```C++
	#include <string>
	#include <aki/jsbind.h>

	struct Person {
		Person(std::string name);
		std::string GetName();
		void SetName(std::string name);
		std::string name;
		......
	};

	JSBIND_CLASS(Person) {
		JSBIND_CONSTRUCTOR<std::string>(); // 绑定构造函数
		JSBIND_FIELD("name", GetName, SetName); // Get / Set 用于做属性访问，JS侧无需访问类对象，可不定义
	}
	```
	可参考用例：[6_structure](https://gitee.com/openharmony-sig/aki/tree/master/examples/ohos/6_structure)