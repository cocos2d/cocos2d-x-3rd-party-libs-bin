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

#ifndef AKI_NAPI_METHOD_BINDER_H
#define AKI_NAPI_METHOD_BINDER_H
#include "aki/binder/method_binder.h"
#include "aki/config.h"

namespace aki {

template <typename C, typename M, typename R, typename... P>
class NapiMethodBinder : public MethodBinder<NapiMethodBinder<C, M, R, P...>, C, M, R, P...> {
public:
    typedef MethodBinder<NapiMethodBinder<C, M, R, P...>, C, M, R, P...> ParentType;

    static napi_value Wrapper (napi_env env, napi_callback_info info)
    {
        AKI_DLOG(DEBUG) << "NapiMethodBinder::Wrapper";
        if (!Checker<P...>::IsArityValid(env, info)) {
            std::string msg = std::string("JSBind: Wrong number of arguments, expected: ").append(std::to_string(sizeof...(P)));
            napi_throw_error(env, nullptr, msg.c_str());
            return nullptr;
        }
        if (!Checker<typename ValueDefiner<P>::RawType...>::TypesAreValid(env, info)) {
            std::string msg = Checker<typename ValueDefiner<P>::RawType...>::GetTypeError(env, info);
            napi_throw_type_error(env, "JSBind: Wrong type of arguments", msg.c_str());
            return nullptr;
        }
        return SafetyWrapper(env, info, std::make_index_sequence<sizeof...(P)>());
    }

private:
    template<size_t... Index>
    static napi_value SafetyWrapper(napi_env env, napi_callback_info info, std::index_sequence<Index...>)
    {
        napi_status status;
        aki::BindInfo* bindInfo = nullptr;
        size_t argc = sizeof...(Index);
        napi_value jsThis;

        std::array<napi_value, sizeof...(Index)> args;
        status = napi_get_cb_info(env, info, &argc, args.data(), &jsThis, ((void**)&bindInfo));
        AKI_DCHECK(status == napi_ok);
        AKI_DCHECK(bindInfo != nullptr);
        auto tuple = std::make_tuple(NapiValueMaker<typename ValueDefiner<P>::RawType>(env, args[Index])...);
        std::array<internal::Value*, sizeof...(P)> result = { static_cast<internal::Value*>(std::get<Index>(tuple))... };

        /// 获取ClassType对象实例
        C* receiver = ClassWrapper<C>::UnWrapper(env, jsThis);
        return WrapperForward(env, bindInfo, *receiver, result.data(), std::make_index_sequence<sizeof...(P)>());
    }

    template<size_t... Index>
    static napi_value WrapperForward(napi_env& env, aki::BindInfo* bindInfo, C& receiver, internal::Value* values[], std::index_sequence<Index...>)
    {
        if constexpr (std::is_void<R>::value) {
            ParentType::InnerWrapper(receiver, bindInfo, NapiValueTrait<P>::Cast(*values[Index])...);
            return nullptr;
        } else {
            return NapiValue<R>::ToNapiValue(env, ParentType::InnerWrapper(receiver, bindInfo, NapiValueTrait<P>::Cast(*values[Index])...));
        }
    }
};

} // namespace aki
#endif //AKI_NAPI_METHOD_BINDER_H
