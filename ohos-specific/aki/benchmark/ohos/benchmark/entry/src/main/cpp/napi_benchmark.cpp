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
#include <hilog/log.h>
#include "common_benchmark.h"

static napi_value NapiFoo(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t requireArgc = 0;
    size_t argc = 0;
    napi_value args[0] = {};

    status = napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_get_cb_info error");
        return nullptr;
    }

    Foo();

    return nullptr;

}

static napi_value NapiPassingNoneReturnBool(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t requireArgc = 0;
    size_t argc = 0;
    napi_value args[0] = {};

    status = napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_get_cb_info error");
        return nullptr;
    }

    auto temp = PassingNoneReturnBool();

    napi_value result;
    status = napi_get_boolean(env, temp, &result);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_get_boolean error");
        return nullptr;
    }

    return result;

}

static napi_value NapiPassingStringReturnString(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t requireArgc = 1;
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    status = napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_get_cb_info error");
        return nullptr;
    }
    
    size_t length = 0;
    status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &length);
    std::string buf(length, '\0');
    status = napi_get_value_string_utf8(env, args[0], buf.data(), length+1, &length);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_get_value_string_utf8 error");
        return nullptr;
    }

    auto temp = PassingStringReturnString(buf);

    napi_value result;
    status = napi_create_string_utf8(env, temp.data(), temp.size(), &result);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_create_string_utf8 error");
        return nullptr;
    }

    return result;

}

static napi_value PassingFunctionReturnVoid(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t requireArgc = 1;
    size_t argc = 1;
    napi_value cb = nullptr;

    status = napi_get_cb_info(env, info, &argc, &cb , nullptr, nullptr);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_get_cb_info error");
        return nullptr;
    }
    
    auto func = [cb, env] () -> void{
        napi_status status;
        napi_value undefined;
        status = napi_get_undefined(env, &undefined);
        
        napi_value result;
        status = napi_call_function(env,
                                    undefined,
                                    cb,
                                    0,
                                    nullptr,
                                    &result);
        if (status != napi_ok) {
            OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "NAPI", "napi_call_function error");
        }
    };
    
    PassingFunctionReturnVoid(func);

    return nullptr;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "Foo", nullptr, NapiFoo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "PassingNoneReturnBool", nullptr, NapiPassingNoneReturnBool, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "PassingStringReturnString", nullptr, NapiPassingStringReturnString, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "PassingFunctionReturnVoid", nullptr, PassingFunctionReturnVoid, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module napiBenchmarkModule = {
    .nm_version =1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "napi_benchmark",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterNapiBenchmarkModule(void)
{
    napi_module_register(&napiBenchmarkModule);
}
