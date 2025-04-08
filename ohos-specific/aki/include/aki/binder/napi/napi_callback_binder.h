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

#ifndef AKI_NAPI_CALLBACK_BINDER_H
#define AKI_NAPI_CALLBACK_BINDER_H

#include <node_api.h>

#include "aki/binder/callback_binder.h"
#include "aki/logging/logging.h"
#include "aki/value/napi/napi_value_trait.h"

namespace aki {

template<typename R, typename... P>
class NapiCallbackBinder : public CallbackBinder<NapiCallbackBinder<R, P...>, R, P...> {
public:
    typedef CallbackBinder<NapiCallbackBinder<R, P...>, R, P...> ParentType;
    static napi_value Wrapper (napi_env env, napi_callback_info info)
    {
        AKI_DLOG(DEBUG) << "NapiCallbackBinder::Wrapper";
        return SafetyWrapper(env, info, std::make_index_sequence<sizeof...(P)>());
    }

private:
    template<size_t... Index>
    static napi_value SafetyWrapper(napi_env& env, napi_callback_info info, std::index_sequence<Index...>);

    template<typename... Args>
    static napi_value WrapperForward(napi_env& env, void* invoker, Args&&... args);
};
} // namespace aki
#endif //AKI_NAPI_CALLBACK_BINDER_H
