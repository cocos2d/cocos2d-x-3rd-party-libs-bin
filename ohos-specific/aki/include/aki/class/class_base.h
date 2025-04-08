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

#ifndef AKI_XLASS_H
#define AKI_XLASS_H

#include <forward_list>

#include "aki/binder/binder.h"
#include <node_api.h>
#include "aki/function.h"

namespace aki {

class AKI_EXPORT ClassBase {
public:
    ClassBase();

    virtual ~ClassBase() = default;

    void Init(const char *name);

    virtual const napi_ref* GetClassRefs() = 0;

    virtual void SetClassRefs(napi_ref* originalRef) = 0;

    void AddMethod(const char* name, int32_t invokerId, Binder* binder);

    const char* GetName() {return name_;}

    const Binder* GetBinder() const {return binder_;}

    std::forward_list<Function>& GetMethods() { return methods_;}

    int32_t GetWrapperConstructorGroupId() const { return wrapperConstructorGroupId_; }

    int32_t GetValueConstructorGroupId() const { return valueConstructorGroupId_; }

protected:
    const char* name_;

    Binder* binder_;

    int32_t wrapperConstructorGroupId_;

    int32_t valueConstructorGroupId_;

    std::forward_list<Function> methods_;
};
} // namespace aki

#endif //AKI_XLASS_H
