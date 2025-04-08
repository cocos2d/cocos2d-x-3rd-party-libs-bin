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

#ifndef AKI_NAPI_CHECKER_H
#define AKI_NAPI_CHECKER_H

#include <node_api.h>

#include "aki/value/napi/napi_value.h"

namespace aki {

template<typename... P>
struct Checker {
    static bool IsArityValid(napi_env env, napi_callback_info info)
    {
        napi_status status;
        size_t argc = 0;
        status = napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr);
        AKI_DCHECK(status == napi_ok);
        return argc == sizeof...(P);
    }

    static bool TypesAreValid(napi_env env, napi_callback_info info)
    {
        napi_status status;
        size_t argc = sizeof...(P);
        std::array<napi_value, sizeof...(P)> args;
        status = napi_get_cb_info(env, info, &argc, args.data(), nullptr, nullptr);
        AKI_DCHECK(status == napi_ok);
        return TypesIsValid(env, args.data(), std::make_index_sequence<sizeof...(P)>());
    }

    static std::string GetTypeError(napi_env env, napi_callback_info info)
    {
        napi_status status;
        size_t argc = sizeof...(P);
        std::array<napi_value, sizeof...(P)> args;
        status = napi_get_cb_info(env, info, &argc, args.data(), nullptr, nullptr);
        AKI_DCHECK(status == napi_ok);
        return MakeTypeError(env, args.data(), std::make_index_sequence<sizeof...(P)>());
    }

private:
    template<size_t... Index>
    static bool TypesIsValid(const napi_env& env, napi_value args[], std::index_sequence<Index...>)
    {
        return(BooleanAnd(NapiValue<P>::CheckType(env, args[Index])..., true));
    }

    template<size_t... Index>
    static std::string GetExceptedTypes()
    {
        std::array<const char*, sizeof...(P)> typeList = { NapiValue<P>::ExpectedType()... };
        std::string excepted;
        for (size_t i = 0; i < sizeof...(P); i++) {
            excepted.append(" ").append(typeList[i]);
        }

        return excepted;
    }

    template<size_t... Index>
    static std::string MakeTypeError(napi_env env, napi_value args[], std::index_sequence<Index...>)
    {
        std::array<bool, sizeof...(P)> flagList = { NapiValue<P>::CheckType(env, args[Index])... };
        std::string flagMsg = "JSBind: Arguments Type mismatch, flags: [";

        for (size_t i = 0; i < flagList.size(); i++) {
            flagMsg.append(" ").append(flagList[i] ? "true" : "false");
        }
        flagMsg.append(" ], expected: [").append(GetExceptedTypes()).append(" ]");
        return flagMsg;
    }

    static bool BooleanAnd(bool flag)
    {
        return(flag);
    }

    template <typename... Rest>
    static bool BooleanAnd(bool flag, Rest... rest)
    {
        return(flag & BooleanAnd(rest...));
    }
};

} // namespace aki
#endif //AKI_NAPI_CHECKER_H
