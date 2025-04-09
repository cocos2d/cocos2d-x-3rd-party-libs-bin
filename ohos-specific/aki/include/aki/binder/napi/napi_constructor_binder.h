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

#ifndef AKI_NAPI_CONSTRUCTOR_BINDER_H
#define AKI_NAPI_CONSTRUCTOR_BINDER_H
#include "aki/binder/constructor_binder.h"
#include "aki/class/class_base.h"
#include "aki/logging/logging.h"

namespace aki {
template <typename C, typename... P>
class NapiConstructorBinder : public ConstructorBinder<NapiConstructorBinder<C, P...>,
                                                       C,
                                                       P...> {
public:
    typedef ConstructorBinder<NapiConstructorBinder<C, P...>, C, P...> ParentType;

    NapiConstructorBinder()
    {
        this->SetValueConstructor(reinterpret_cast<FuncPtr>(CreateValue));
    }

    static napi_value Wrapper (napi_env env, napi_callback_info info)
    {
        AKI_DLOG(DEBUG) << "ConstructorBinder::Wrapper";
        return SafetyWrapper(env, info, std::make_index_sequence<sizeof...(P)>());
    }

    static void CreateValue(napi_env env, napi_callback_info info, ArgStorage& storage)
    {
        AKI_DLOG(DEBUG) << "ConstructorBinder::CreateValue";
        CreateValueInner(env, info, storage, std::make_index_sequence<sizeof...(P)>());
    }

    template<size_t... Index>
    static napi_value SafetyWrapper(napi_env& env, napi_callback_info info, std::index_sequence<Index...>)
    {
        AKI_DLOG(DEBUG) << "ConstructorBinder::SafetyWrapper";
        napi_status status;
        napi_value target;
        status = napi_get_new_target(env, info, &target);
        AKI_DCHECK(status == napi_ok);
        if (target != nullptr) {
            // 以构造函数形式调用：new Class(...)
            constexpr int ARGS_SIZE = sizeof...(P);
            size_t argc = ARGS_SIZE;
            napi_value args[ARGS_SIZE];
            napi_value jsThis;
            status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
            AKI_DCHECK(status == napi_ok);

            auto tuple = std::make_tuple(NapiValueMaker<typename ValueDefiner<P>::RawType>(env, args[Index])...);
            auto valueTuple = std::make_tuple(NapiValueTrait<typename ValueDefiner<P>::RawType>::Cast(std::get<Index>(tuple))...);

            ClassWrapper<C>::ConstructorWrapper(env, jsThis, std::get<Index>(valueTuple)...);
            return jsThis;
        } else {
            // 禁止使用非new指令的构造函数
            napi_throw_error(env, "JSBind Error: Class constructor cannot be invoked without 'new'", "JSBind Error: Class constructor cannot be invoked without 'new'");
            return nullptr;
        }
    }

private:
    template<size_t... Index>
    static void CreateValueInner(napi_env env, napi_callback_info info, ArgStorage& storage, std::index_sequence<Index...>)
    {
        napi_status status;
        size_t argc = sizeof...(P);
        std::array<napi_value, sizeof...(P)> args;
        status = napi_get_cb_info(env, info, &argc, args.data(), nullptr, nullptr);

        auto tuple = std::make_tuple(NapiValueMaker<typename ValueDefiner<P>::RawType>(env, args[Index])...);
        auto valueTuple = std::make_tuple(NapiValueTrait<typename ValueDefiner<P>::RawType>::Cast(std::get<Index>(tuple))...);

        TemplatedArgStorage<C>* argStorage = static_cast<TemplatedArgStorage<C>*>(storage.GetTemplate());

        argStorage->Init(std::get<Index>(valueTuple)...);
    }

};
} // namespace aki
#endif //AKI_NAPI_CONSTRUCTOR_BINDER_H
