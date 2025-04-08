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

#include "equivalence_test.h"

#include <hilog/log.h>

// | static |
int EquivalenceTest::ShowByValue(EquivalenceTest obj) {
    return obj.value_;
}

EquivalenceTest::EquivalenceTest()
    : value_(-11)
{
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "JSBind", "EquivalenceTest::EquivalenceTest");
}

EquivalenceTest::EquivalenceTest(int value)
    : value_(value)
{
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "JSBind", "EquivalenceTest::EquivalenceTest: %{public}d", value);
}

EquivalenceTest::~EquivalenceTest()
{
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "JSBind", "EquivalenceTest::~EquivalenceTest: %{public}d", value_);
}

int EquivalenceTest::GetValue() const {
    return value_;
}

void EquivalenceTest::SetValue(int value)
{
    value_ = value;
}

void EquivalenceTest::Equals(aki::Matcher matcher) {
    // 功能暂不开放
    return;
}

JSBIND_CLASS(EquivalenceTest)
{
    JSBIND_CONSTRUCTOR<>();
    JSBIND_CONSTRUCTOR<int>();
    JSBIND_METHOD(ShowByValue);
    JSBIND_FIELD("value", GetValue, SetValue);
}