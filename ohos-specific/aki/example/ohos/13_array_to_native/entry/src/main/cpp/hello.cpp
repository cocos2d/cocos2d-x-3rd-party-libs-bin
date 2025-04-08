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

#include <vector>
#include <aki/jsbind.h>

namespace {
class VectorHandle {
public:
    VectorHandle() = default;
    std::vector<long> PassingVoidReturnVectorLong()
    {
        std::vector<long> v = {1, 2, 3};
        return v;
    }
    std::vector<long> PassingVectorLongReturnVectorLong(std::vector<long> v)
    {
        constexpr int num = 4;
        v.push_back(num);
        return v;
    }
};

JSBIND_CLASS(VectorHandle) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_METHOD(PassingVoidReturnVectorLong, "passingVoidReturnVectorLong");
    JSBIND_METHOD(PassingVectorLongReturnVectorLong, "passingVectorLongReturnVectorLong");
}

std::vector<long> PassingVoidReturnVectorLong()
{
    std::vector<long> v = {1, 2, 3};
    return v;
}

std::vector<long> PassingVectorLongReturnVectorLong(std::vector<long> v)
{
    constexpr int num = 4;
    v.push_back(num);
    return v;
}
}
JSBIND_GLOBAL() {
    JSBIND_FUNCTION(PassingVoidReturnVectorLong, "passingVoidReturnVectorLong");
    JSBIND_FUNCTION(PassingVectorLongReturnVectorLong, "passingVectorLongReturnVectorLong");
}

JSBIND_ADDON(array_to_native);