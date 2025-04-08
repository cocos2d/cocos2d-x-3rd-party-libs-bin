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

#ifndef AKI_NAPI_VALUE_BASE_H
#define AKI_NAPI_VALUE_BASE_H

#include "aki/value/value.h"
#include "aki/config.h"

#if JSBIND_USING_TRACING
# include <tracing/trace.h>
#else
# define FUNCTION_DTRACE()
#endif // JSBIND_USING_TRACING

namespace aki {

class AKI_EXPORT NapiValueBase : public internal::Value {
public:
    NapiValueBase() = default;

    NapiValueBase(napi_env env, napi_value value) : env_(env), value_(value) {}

    virtual ~NapiValueBase() = default;

    static bool CheckUndefinedType(napi_env env, napi_value value);

    static bool CheckNullType(napi_env env, napi_value value);

    static bool CheckBoolType(napi_env env, napi_value value);

    static bool CheckNumberType(napi_env env, napi_value value);

    static bool CheckStringType(napi_env env, napi_value value);

    static bool CheckObjectType(napi_env env, napi_value value);

    static bool CheckArrayType(napi_env env, napi_value value);

    static bool CheckFunctionType(napi_env env, napi_value value); 

    // TODO: napi_create_external方法的3、4个入参是必选，与Node.js规范不一致，已提单跟踪，当前临时规避
    static void FinalizeTest(napi_env env, void* nativeInstance, void* finalizeHint);

    bool GetBool() const override;

    uint8_t GetUint8() const override;

    int8_t GetInt8() const override;

    uint16_t GetUint16() const override;

    int16_t GetInt16() const override;

    int32_t GetInt() const override;

    int64_t GetInt64() const override;

    float GetFloat() const override;

    double GetDouble() const override;

    std::string GetString() const override;

    napi_value GetNapiValue() const;

    // 获取对象引用
    void* GetDataReference() override;

    Promise GetPromise() override;

    bool IsUndefined() const override;

    bool IsNull() const override;

    bool IsBool() const override;

    bool IsNumber() const override;

    bool IsString() const override;

    bool IsArray() const override;

    bool IsFunction() const override;

    operator internal::Value*() override { return this; }

    operator char* () override
    {
        return GetCString();
    }

    operator const char* () override
    {
        return GetCString();
    }

protected:

    napi_env env_ = nullptr;

    napi_value value_ = nullptr;
};

} // namespace aki

#endif //AKI_NAPI_VALUE_BASE_H