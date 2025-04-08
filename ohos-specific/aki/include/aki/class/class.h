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

#ifndef AKI_CLASS_H
#define AKI_CLASS_H

#include "class_base.h"
#include "aki/overloader/napi/napi_overloader.h"

namespace aki {
template <class C>
class Class : public ClassBase {
public:
    Class() = default;

    ~Class() = default;

    static Class<C>& GetInstance()
    {
        static Class<C> instance;
        return instance;
    }

    void AddConstructor(Binder* binder)
    {
        binder_ = binder;
        NapiOverloader::AddMethod(wrapperConstructorGroupId_,
                                  binder->GetArity(),
                                  binder->GetWrapper());

        NapiOverloader::AddMethod(valueConstructorGroupId_,
                                  binder->GetArity(),
                                  binder->GetValueConstructor());
    }

    const napi_ref* GetClassRefs() override
    {
        return ref_;
    }

    void SetClassRefs(napi_ref* originalRef) override
    {
        ref_ = originalRef;
    }

private:
    napi_ref* ref_;
};
} // namespace aki

#endif //AKI_CLASS_H
