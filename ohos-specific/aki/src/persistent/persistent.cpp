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

#include <node_api.h>

#include "aki/persistent/persistent.h"
#include "aki/jsbind.h"
#include "status/status.h"

namespace aki {
Persistent::Persistent(napi_value value)
{
    napi_env env = JSBind::GetScopedEnv();    
    napi_status status;
    status = napi_create_reference(env, value, 1, &ref_);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
}

Persistent::Persistent(const Persistent& that)
{
    napi_env env = JSBind::GetScopedEnv();
    if (that.ref_ != nullptr && env!= nullptr) {
        ref_ = that.ref_;
    
        napi_status status;
        uint32_t count;
        status = napi_reference_ref(env, ref_, &count);
        AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    }
}

Persistent& Persistent::operator= (const Persistent& that)
{
    napi_env env = JSBind::GetScopedEnv();
    if (that.ref_ != nullptr && env!= nullptr) {
        ref_ = that.ref_;
    
        napi_status status;
        uint32_t count;
        status = napi_reference_ref(env, ref_, &count);
        AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    }

    return *this;
}

Persistent::~Persistent()
{
    if (ref_ != nullptr) {
        napi_env env = JSBind::GetScopedEnv(); 
        napi_status status;
        uint32_t count;
        status = napi_reference_unref(env, ref_, &count);
        AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
        if (count == 0) {
            status = napi_delete_reference(env, ref_);
            AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
        }
        ref_ = nullptr;
    }
}

napi_value Persistent::GetValue() const
{
    napi_env env = JSBind::GetScopedEnv();    
    napi_status status;
    napi_value value;

    status = napi_get_reference_value(env, ref_, &value);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
    return value;
}
} // namespace aki