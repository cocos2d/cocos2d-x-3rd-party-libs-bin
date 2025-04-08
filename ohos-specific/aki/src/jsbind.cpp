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

#include "aki/jsbind.h"
#include "aki/logging/logging.h"

namespace aki {

// | static |
int JSBind::bindFunction(const std::string& name, JSFunction func)
{
    return Binding::RegisterJSFunction(name, std::make_unique<JSFunction>(std::move(func)));
}

#if JSBIND_SUPPORT_DECLARATION
// | static |
void JSBind::Reflect(aki::Callback<void (intptr_t, int32_t)> outputBuildInType,
                     aki::Callback<void (std::string, std::vector<intptr_t>)> outputFunction)
{
    AKI_LOG(ERROR) << "Reflect";
    for (auto& type : Binding::GetBuildInTypeList()) {
        AKI_LOG(ERROR) << "Reflect buildIn: " << type->name << ", " << type->id;
        outputBuildInType((intptr_t)type,
                          static_cast<int32_t>(type->flag));
    }

    for (auto& function : aki::Binding::GetFunctionList()) {
        auto* binder = function.GetBinder();
        auto& typeList = binder->GetTypeList();
        std::vector<intptr_t> params;
        for (auto type : typeList) {
            AKI_LOG(ERROR) << "Reflect id: " << type->name;
                AKI_LOG(ERROR) << "flag: " << (int)(type->flag);
                AKI_LOG(ERROR) << "array flag id: " << (int)TypeFlag::IS_ARRAY;
            if ((type->flag & TypeFlag::TYPE_MASK) ==  TypeFlag::IS_ARRAY) {
                const ArrayTplParams* params = type->arrayParams;
                AKI_LOG(ERROR) << "array params id: " << params->member->name;
            }
            params.push_back((intptr_t)type);
        }
        outputFunction(function.GetName(), params);
    }
}

// | static |
void JSBind::QueryType(intptr_t typeId,
                       aki::Callback<void (int32_t, std::vector<intptr_t>)> outputType)
{
    const TypeMeta* type = (TypeMeta*)typeId;
    std::vector<intptr_t> params;
    switch (type->flag) {
        case TypeFlag::IS_ARRAY:
            params.push_back((intptr_t)(type->arrayParams->member));
            outputType(static_cast<int32_t>(type->flag),
                       params);
            break;
        case TypeFlag::IS_FUNCTION:
            for (auto item: type->functionParams->params) {
                params.push_back((intptr_t)(item));
            }
            outputType(static_cast<int32_t>(type->flag),
                       params);
            break;
        default:
            ;
    }
}
#endif

// | static |
const JSFunction* JSBind::GetJSFunction(const std::string& name)
{
    auto iter = Binding::GetJSFunctionMap().find(name);
    if (iter != Binding::GetJSFunctionMap().end()) {
        return iter->second.get();
    } else {
        return nullptr;
    }
}

// | static |
void JSBind::SetScopedEnv(napi_env env)
{
    Binding::SetScopedEnv(env);
}

// | static |
napi_env JSBind::GetScopedEnv()
{
    return Binding::GetScopedEnv();
}
} // namespace aki