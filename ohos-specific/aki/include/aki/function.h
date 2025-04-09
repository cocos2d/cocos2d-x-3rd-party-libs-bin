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

#ifndef AKI_FUNCTION_H
#define AKI_FUNCTION_H

#include <vector>

#include "aki/binder/binder.h"

namespace aki {
class Function {
public:
    Function(const char* name, int32_t invokerId, Binder* binder);

    ~Function() = default;

    const char* GetName() const {return name_.c_str();}

    const Binder* GetBinder() const {return binder_;}

    inline int32_t GetInvokerId() const { return invokerId_; }

private:
    std::string name_;

    Binder* binder_;

    int32_t invokerId_ = -1;
};
} // namespace aki
#endif //AKI_FUNCTION_H
