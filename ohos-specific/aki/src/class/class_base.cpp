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

#include "aki/class/class_base.h"
#include "aki/overloader/napi/napi_overloader.h"

namespace aki {

ClassBase::ClassBase()
    : name_(nullptr),
      binder_(nullptr),
      wrapperConstructorGroupId_(NapiOverloader::AddGroup()),
      valueConstructorGroupId_(NapiOverloader::AddGroup())
{}

void ClassBase::Init(const char *name)
{
    name_ = name;
}

void ClassBase::AddMethod(const char* name, int32_t invokerId, Binder* binder)
{
    methods_.emplace_front(name, invokerId, binder);
}
} // namespace aki