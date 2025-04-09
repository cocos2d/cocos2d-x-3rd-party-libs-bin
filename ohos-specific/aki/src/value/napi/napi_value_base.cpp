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

#include "aki/value/napi/napi_value_base.h"
#include "aki/logging/logging.h"
#include "status/status.h"
namespace aki {

// | static |
bool NapiValueBase::CheckUndefinedType(napi_env env, napi_value value)
{
    napi_status status;
    napi_valuetype type;
    status = napi_typeof(env, value, &type);
    AKI_DCHECK(status == napi_ok);
    return type == napi_undefined;
}

// | static |
bool NapiValueBase::CheckNullType(napi_env env, napi_value value)
{
    napi_status status;
    napi_valuetype type;
    status = napi_typeof(env, value, &type);
    AKI_DCHECK(status == napi_ok);
    return type == napi_null;
}

// | static |
bool NapiValueBase::CheckBoolType(napi_env env, napi_value value)
{
    napi_status status;
    napi_valuetype type;
    status = napi_typeof(env, value, &type);
    AKI_DCHECK(status == napi_ok);
    return type == napi_boolean;
}

// | static |
bool NapiValueBase::CheckNumberType(napi_env env, napi_value value)
{
    napi_status status;
    napi_valuetype type;
    status = napi_typeof(env, value, &type);
    AKI_DCHECK(status == napi_ok);
    return type == napi_number;
}

// | static |
bool NapiValueBase::CheckStringType(napi_env env, napi_value value)
{
    napi_status status;
    napi_valuetype type;
    status = napi_typeof(env, value, &type);
    AKI_DCHECK(status == napi_ok);
    return type == napi_string;
}

// | static |
bool NapiValueBase::CheckObjectType(napi_env env, napi_value value)
{
    napi_status status;
    napi_valuetype type;
    status = napi_typeof(env, value, &type);
    AKI_DCHECK(status == napi_ok);
    return type == napi_object;
}

// | static |
bool NapiValueBase::CheckArrayType(napi_env env, napi_value value)
{
    napi_status status;
    bool result;
    status = napi_is_array(env, value, &result);
    AKI_DCHECK(status == napi_ok);
    return result;
}

// | static |
bool NapiValueBase::CheckFunctionType(napi_env env, napi_value value)
{
    napi_status status;
    napi_valuetype type;
    status = napi_typeof(env, value, &type);
    AKI_DCHECK(status == napi_ok);
    return type == napi_function;
}

// | static |
// TODO: napi_create_external方法的3、4个入参是必选，与Node.js规范不一致，已提单跟踪，当前临时规避
void NapiValueBase::FinalizeTest(napi_env env, void* nativeInstance, void* finalizeHint)
{
    const char* hint = reinterpret_cast<const char*>(finalizeHint);
    AKI_DLOG(DEBUG) << "FinalizeTest: " << (hint == nullptr ? "unknonwn" : hint);
}

bool NapiValueBase::GetBool() const
{
    napi_status status;
    bool result = false;
    status = napi_get_value_bool(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return result;
}

uint8_t NapiValueBase::GetUint8() const
{
    napi_status status;
    uint32_t result;
    status = napi_get_value_uint32(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return static_cast<uint8_t>(result);
}

int8_t NapiValueBase::GetInt8() const
{
    napi_status status;
    int32_t result;
    status = napi_get_value_int32(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return static_cast<int8_t>(result);
}

uint16_t NapiValueBase::GetUint16() const
{
    napi_status status;
    uint32_t result;
    status = napi_get_value_uint32(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return static_cast<uint16_t>(result);
}

int16_t NapiValueBase::GetInt16() const
{
    napi_status status;
    int32_t result;
    status = napi_get_value_int32(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return static_cast<int16_t>(result);
}

int32_t NapiValueBase::GetInt() const
{
    napi_status status;
    int32_t result;
    status = napi_get_value_int32(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return result;
}

int64_t NapiValueBase::GetInt64() const
{
    napi_status status;
    int64_t result;
    status = napi_get_value_int64(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return result;
}

float NapiValueBase::GetFloat() const
{
    napi_status status;
    double result;
    status = napi_get_value_double(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return static_cast<float>(result);
}

double NapiValueBase::GetDouble() const
{
    napi_status status;
    double result;
    status = napi_get_value_double(env_, value_, &result);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return result;
}

std::string NapiValueBase::GetString() const
{
    FUNCTION_DTRACE();
    napi_status status;
    size_t length = 0;
    status = napi_get_value_string_utf8(env_, value_, nullptr, 0, &length);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    AKI_DCHECK((length+1) < std::numeric_limits<size_t>::max());
    std::string buf(length, '\0');
    status = napi_get_value_string_utf8(env_, value_, buf.data(), length+1, &length);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);

    return std::move(buf);
}

napi_value NapiValueBase::GetNapiValue() const
{
    return value_;
}

// 获取对象引用
void* NapiValueBase::GetDataReference()
{
    AKI_DCHECK(false);
    return nullptr;
}

Promise NapiValueBase::GetPromise()
{
    return Promise(value_);
}

bool NapiValueBase::IsUndefined() const
{
    return CheckUndefinedType(env_, value_);
}

bool NapiValueBase::IsNull() const
{
    return CheckNullType(env_, value_);
}

bool NapiValueBase::IsBool() const
{
    return CheckBoolType(env_, value_);
}

bool NapiValueBase::IsNumber() const
{
    return CheckNumberType(env_, value_);
}

bool NapiValueBase::IsString() const
{
    return CheckStringType(env_, value_);
}

bool NapiValueBase::IsArray() const
{
    return CheckArrayType(env_, value_);
}

bool NapiValueBase::IsFunction() const
{
    return CheckFunctionType(env_, value_);
}
} // namespace aki