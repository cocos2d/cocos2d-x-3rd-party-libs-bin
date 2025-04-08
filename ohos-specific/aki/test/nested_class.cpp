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

#include "nested_class.h"

#include "aki/jsbind.h"

std::string NestedOne::GetNested() const
{
    return "One";
}

std::string NestedTwo::GetNested() const
{
    return "Two::" + sub_.GetNested();
}

std::string NestedThree::GetNested() const
{
    return "Three::" + sub_.GetNested();
}

JSBIND_CLASS(NestedOne) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_METHOD(GetNested);
}

JSBIND_CLASS(NestedTwo) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_METHOD(GetNested);
}

JSBIND_CLASS(NestedThree) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_METHOD(GetNested);
}