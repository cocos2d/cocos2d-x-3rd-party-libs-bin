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

#include "common_benchmark.h"

void Foo()
{
}

bool PassingNoneReturnBool()
{
    return true;
}

std::string PassingStringReturnString(std::string str)
{
    return str;
}

void PassingFunctionReturnVoid(std::function<void ()> func)
{
    func();
}

void PassingCallbackReturnVoid(aki::Callback<void ()> func)
{
    func();
}

void PassingSafetyCallbackReturnVoid(aki::SafetyCallback<void ()> func)
{
    func();
}