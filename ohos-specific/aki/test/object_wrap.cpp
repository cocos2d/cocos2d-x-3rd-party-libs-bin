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

#include "object_wrap.h"

#include "aki/jsbind.h"
/**
 * @brief: 默认构造函数
 * @result: passed
 */
TestObject::TestObject()
    : value_(-3.1415926) 
{}
    
/**
 * @brief: 带参构造函数Constructor<double>
 * @result: passed
 */
TestObject::TestObject(double value)
    : value_(value) 
{}

/**
 * @brief: 类静态方法 TestObject (*)()
 * @result: passed
 */
TestObject TestObject::CreateObject()
{
    return TestObject(100.86);
}

/**
 * @brief: 类静态方法 TestObject (*)()
 * @result: passed
 */
TestObject* TestObject::CreateObjectPtr()
{
    return new TestObject(-100.86);
}

/**
 * @brief: 类静态方法 double (*)(Object, Object)
 * @result: passed
 */
double TestObject::MultiplyObject(TestObject obj1, TestObject obj2)
{
    return obj1.value_ * obj2.value_;
}
     
/**
 * @brief: 类静态方法 double (*)(Object*, Object*)
 * @result: passed
 */
double TestObject::MultiplyObjectPtr(TestObject* obj1, TestObject* obj2)
{
    return obj1->value_ * obj2->value_;
}

double TestObject::MultiplyObjectConstPtr(const TestObject* obj1, const TestObject* obj2)
{
    return obj1->value_ * obj2->value_;
}

double TestObject::MultiplyObjectSmartPtr(std::shared_ptr<TestObject> obj1, std::shared_ptr<TestObject> obj2)
{
    double result = obj1->value_ * obj2->value_;
    obj1->value_ *= obj2->value_;
    return result;
}

std::shared_ptr<TestObject> TestObject::MultiplyObjectSmartPtrReturnSmartPtr(std::shared_ptr<TestObject> obj)
{
    return obj;
}
    
/**
 * @brief: 属性访问器 getter const
 * @result: passed
 */
double TestObject::GetValue() const
{
    return value_;
}
    
/**
 * @brief: 属性访问器 setter
 * @result: passed
 */
void TestObject::SetValue(double value)
{
    value_ = value;
}

void TestObject::SetFake(double fake)
{
    fake_ = fake;
}

double TestObject::GetFake()
{
    return fake_;
}
 
/**
 * @brief: 属类成员方法 double(*)()
 * @result: passed
 */
double TestObject::PlusOne() {
    return ++value_;
}
 
/**
 * @brief: 属类成员方法 double(*)(double)
 * @result: passed
 */
double TestObject::Multiply(double mult) {
    value_ *= mult;
    return value_;
}

int TestObject::P_StaticPassingIntReturnInt(int value)
{
    AKI_DLOG(DEBUG) << "should be non-js-thread";
    return value;
}

int TestObject::P_PassingIntReturnInt(int value)
{
    AKI_DLOG(DEBUG) << "should be non-js-thread";
    return value;
}

JSBIND_CLASS(TestObject) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_CONSTRUCTOR<double>();
    JSBIND_FIELD("value", GetValue, SetValue);
    JSBIND_SETTER("fake", SetFake);
    JSBIND_METHOD(GetFake);
    JSBIND_METHOD(PlusOne);
    JSBIND_METHOD(Multiply);
    JSBIND_METHOD(MultiplyObject);
    JSBIND_METHOD(MultiplyObjectPtr);
    JSBIND_METHOD(MultiplyObjectConstPtr);
    JSBIND_METHOD(MultiplyObjectSmartPtr);
    JSBIND_METHOD(GetValue);
    JSBIND_METHOD(SetValue);
    JSBIND_METHOD(MultiplyObjectSmartPtrReturnSmartPtr);
    JSBIND_METHOD(CreateObject);
    JSBIND_METHOD(CreateObjectPtr);
    JSBIND_PMETHOD(P_PassingIntReturnInt);
    JSBIND_PMETHOD(P_StaticPassingIntReturnInt);
}