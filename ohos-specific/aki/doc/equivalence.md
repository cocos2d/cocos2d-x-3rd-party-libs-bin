
# 等价类

等价类用于绑定 JavaScript && C++ 的类对象，在进行跨语言调用传值时，可保证两端类成员属性保持一致。

**约束**
1. C++ 侧**必须**给类对象显示加上成员函数 `void Equals(aki::Matcher matcher);` (函数暂不用实现);
   
2. JavaScript 侧**必须**给类对象加上成员函数 `equals(matcher: (...) => void)` ，并将matcher方法依次按照 C++ 构造函数形式传值；


- C++

``` C++
#include <aki/jsbind.h>

class EquivalenceTest {
public:

    EquivalenceTest(int value);

    static int ShowByValue(EquivalenceTest obj) {
        return obj.value_;
    }

    void Equals(aki::Matcher matcher) {
    // 暂不实现
    }

private:
    int value_;
};

JSBIND_CLASS(EquivalenceTest)
{
    JSBIND_CONSTRUCTOR<int>();
    JSBIND_METHOD(ShowByValue);
}
```

- JavaScript

``` JavaScript
import aki from 'libhello.so' // 插件名

class EquivalenceTest {
    constructor(value: Number) {
      this.value = value;
    }

    private equals(matcher: (v: Number) => void) {
      try {
        matcher(this.value);
      } catch(e) {
        console.log(e)
      }
    }

    value: Number;
}

var value = new EquivalenceTest(250);
var result = aki.EquivalenceTest.ShowByValue(value);
```
