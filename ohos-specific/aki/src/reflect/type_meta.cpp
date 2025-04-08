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

#include "aki/reflect/type_meta.h"

namespace aki {

int32_t TypeMeta::nextTypeId = 1;

TypeMeta::TypeMeta(const char* name)
    : name(name)
{
    id = nextTypeId++;
}

TypeMeta::TypeMeta(const char* name, TypeFlag flag)
    : name(name),
      id(nextTypeId++),
      flag(flag) {}

TypeMeta::TypeMeta(const char* name, TypeFlag flag, const void* params)
    : name(name),
      flag(flag),
      tplParams(params),
      id(nextTypeId++) {}
} // namespace aki