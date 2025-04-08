/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#include <aki/jsbind.h>

namespace {
struct Reference {
    explicit Reference(int count) : count(count) {}
    
    static void MultiCountByReference(Reference& ref, int num)
    {
        ref.count *= num;
    }
    
    static void MultiCountByPointer(Reference* ptr, int num)
    {
        ptr->count *= num;
    }
    
    void ChangeByReference(Reference& ref)
    {
        int temp = ref.count;
        ref.count = this->count;
        this->count = temp;
    }
    
    void ChangeByPointer(Reference* ptr)
    {
        int temp = ptr->count;
        ptr->count = this->count;
        this->count = temp;
    }
    
    int count;
};
}

JSBIND_CLASS(Reference) {
    JSBIND_CONSTRUCTOR<int>(); // 绑定构造函数
    JSBIND_PROPERTY(count);    // 绑定成员属性
    JSBIND_METHOD(ChangeByReference);
    JSBIND_METHOD(ChangeByPointer);
    JSBIND_METHOD(MultiCountByReference);
    JSBIND_METHOD(MultiCountByPointer);
}

namespace {
void GrowUpByReference(Reference& ref)
{
    ref.count++;
}

void GrowUpByPointer(Reference* ptr)
{
    ptr->count++;
}
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(GrowUpByReference);
    JSBIND_FUNCTION(GrowUpByPointer);
}

JSBIND_ADDON(entry);
