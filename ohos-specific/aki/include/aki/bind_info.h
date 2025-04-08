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

#ifndef AKI_BIND_INFO_H
#define AKI_BIND_INFO_H

#include <cstdint>

namespace aki {
struct BindInfo {
    int32_t functionNumber;

    void * classBase;

    int32_t getterNumber;

    int32_t setterNumber;

    int32_t methodNumber;

    int32_t overloadData;
};
} // namespace aki

#endif //AKI_BIND_INFO_H
