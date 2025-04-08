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

#include "overloader_test.h"

#include <aki/jsbind.h>

OverloaderTest::OverloaderTest(bool value1)
    : value1_(value1) {}

OverloaderTest::OverloaderTest(bool value1, int value2)
    : value1_(value1), value2_(value2) {}

OverloaderTest::OverloaderTest(bool value1, int value2, std::string value3)
    : value1_(value1), value2_(value2), value3_(value3) {}

void OverloaderTest::SetValue1(bool value)
{
    value1_ = value;
}

bool OverloaderTest::GetValue1()
{
    return value1_;
}

void OverloaderTest::SetValue2(int value)
{
    value2_ = value;
}

int OverloaderTest::GetValue2()
{
    return value2_;
}

void OverloaderTest::SetValue3(std::string value)
{
    value3_ = value;
}

std::string OverloaderTest::GetValue3()
{
    return value3_;
}

JSBIND_CLASS(OverloaderTest)
{
    JSBIND_CONSTRUCTOR<>();
    JSBIND_CONSTRUCTOR<bool>();
    JSBIND_CONSTRUCTOR<bool, int>();
    JSBIND_CONSTRUCTOR<bool, int, std::string>();
    JSBIND_FIELD("value1", GetValue1, SetValue1);
    JSBIND_FIELD("value2", GetValue2, SetValue2);
    JSBIND_FIELD("value3", GetValue3, SetValue3);
}