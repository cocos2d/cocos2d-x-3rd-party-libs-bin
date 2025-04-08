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

#ifndef AKI_OBJECT_WRAP_H
#define AKI_OBJECT_WRAP_H
#include <memory>
class TestObject {
public:
    TestObject();
    
    explicit TestObject(double);
    
    ~TestObject() = default;

    static TestObject CreateObject();

    static TestObject* CreateObjectPtr();
    
    static double MultiplyObject(TestObject obj1, TestObject obj2);
    
    static double MultiplyObjectPtr(TestObject* obj1, TestObject* obj2);

    static double MultiplyObjectConstPtr(const TestObject* obj1, const TestObject* obj2);

    static double MultiplyObjectSmartPtr(std::shared_ptr<TestObject> obj1, std::shared_ptr<TestObject> obj2);

    static std::shared_ptr<TestObject> MultiplyObjectSmartPtrReturnSmartPtr(std::shared_ptr<TestObject> obj);

    static int P_StaticPassingIntReturnInt(int value);
    
    double GetValue() const;

    void SetValue(double value);

    void SetFake(double fake);

    double GetFake();
    
    double PlusOne();
    
    double Multiply(double mult);

    int P_PassingIntReturnInt(int value);

private:
    double value_;
    double fake_;
};

#endif //AKI_OBJECT_WRAP_H
