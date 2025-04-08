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

#ifndef AKI_PROMISE_H
#define AKI_PROMISE_H

#include <future>
#include <node_api.h>
#include "aki/config.h"

namespace aki {
class AKI_EXPORT Promise {
public:
    Promise();

    Promise(napi_value promise) : promise_(promise) {}

    ~Promise() = default;

    template<typename T>
    void Resolve(T&& t) const;

    napi_value GetHandle() { return promise_; }

private:
    napi_value promise_;

    napi_deferred deferred_;
};
} // namespace aki

#endif //AKI_PROMISE_H
