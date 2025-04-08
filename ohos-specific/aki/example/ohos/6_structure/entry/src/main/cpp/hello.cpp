/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>

#include <aki/jsbind.h>

struct Person {
    // 构造函数，用于JS侧 new 对象
    Person(std::string name, int age) : name(name), age(age) {}
    
    // Get 用于做属性访问，JS侧无需访问类对象，可不定义
    std::string GetName() {
        return name;
    }
    
    // Set 用于做属性访问，JS侧无需访问类对象，可不定义
    void SetName(std::string name) {
        this->name = name;
    }
    
    std::string name;
    int age;
    
};

JSBIND_CLASS(Person) {
    JSBIND_CONSTRUCTOR<std::string, int>(); // 绑定构造函数
    JSBIND_PROPERTY(age);                   // 绑定成员属性
    JSBIND_FIELD("name", GetName, SetName); // Get / Set 用于做属性访问，JS侧无需访问类对象，可不定义
}

Person foo(Person person) {
    person.name += " for Ark.";
    person.age += 10;
    return person;
}

void GrowUp(Person* person) {
    person->age++;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(foo);
    JSBIND_FUNCTION(GrowUp, "growUp");
}

JSBIND_ADDON(entry)