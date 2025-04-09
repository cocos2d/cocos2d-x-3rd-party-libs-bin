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

#ifndef AKI_PERSISTENT_H
#define AKI_PERSISTENT_H

#include <node_api.h>

#include "aki/config.h"

namespace aki {
class AKI_EXPORT Persistent {
public:
    Persistent() = default;

    explicit Persistent(napi_value);

    Persistent(const Persistent&);

    Persistent& operator= (const Persistent&);

    ~Persistent();
    
    inline bool IsValid() const { return ref_ != nullptr; }

    napi_value GetValue() const;
private:
    napi_ref ref_ = nullptr;
};
} // namespace aki

#endif //AKI_PERSISTENT_H
