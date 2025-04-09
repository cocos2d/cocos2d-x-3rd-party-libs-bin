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

#ifndef AKI_CALLBACK_H
#define AKI_CALLBACK_H

#include <node_api.h>
#include "aki/config.h"

namespace aki {
template<typename T>
class Callback;

template<typename R, typename... P>
class Callback<R (P...)> {
public:
    explicit Callback(const napi_env env, const napi_value cb)
        : env_(env), cb_(cb) {}

    template<typename... Args>
    R operator() (Args&&... args) const
    {
        return(Call(std::forward<Args>(args)...));
    }

    template<typename... Args>
    R Call(Args&&... args) const;

    template<typename... Args>
    R CallMethod(napi_env env, napi_value target, Args&&... args) const;

protected:
    napi_env env_;

    napi_value cb_;
};
} // namespace aki
#endif //AKI_CALLBACK_H
