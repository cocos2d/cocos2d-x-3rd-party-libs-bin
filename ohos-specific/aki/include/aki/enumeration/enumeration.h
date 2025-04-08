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

#ifndef AKI_ENUMERATION_H
#define AKI_ENUMERATION_H


#include "aki/enumeration/enumeration_base.h"

namespace aki {
template <typename E>
class Enumeration : public EnumerationBase {
public:
    using EnumerationBase::EnumerationBase;
    
    ~Enumeration() = default;

    static Enumeration<E>& GetInstance()
    {
        static Enumeration<E> instance;
        return instance;
    }
};
} // namespace aki
#endif //AKI_ENUMERATION_H
