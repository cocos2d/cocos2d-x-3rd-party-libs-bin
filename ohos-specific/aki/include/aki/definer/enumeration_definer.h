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

#ifndef AKI_ENUMERATION_DEFINER_H
#define AKI_ENUMERATION_DEFINER_H

#include "aki/binding.h"
#include "aki/enumeration/enumeration.h"
namespace aki {
template <typename E>
class EnumerationDefiner {
public:
    EnumerationDefiner(const char* name) {
        enum_ = &Enumeration<E>::GetInstance();
        enum_->SetName(name);
        Binding::RegisterEnumeration(enum_);
    }
    
    void SetValue(const char* key, int32_t value) {
        enum_->SetValue(key, value);
    }
    
    Enumeration<E>* enum_;
};
} // namespace aki
#endif //AKI_ENUMERATION_DEFINER_H
