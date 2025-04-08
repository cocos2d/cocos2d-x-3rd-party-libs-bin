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


#include "aki/overloader/napi/napi_overloader.h"
#include "aki/bind_info.h"
#include "aki/logging/logging.h"

namespace aki {

// | static |
napi_value NapiOverloader::Wrapper(napi_env env, napi_callback_info info)
{
    AKI_DLOG(DEBUG) << "NapiOverloader::Wrapper";
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    BindInfo* bindInfo = nullptr;
    status = napi_get_cb_info(env, info, &argc, args, nullptr, ((void**)&bindInfo));
    const OverloadGroup& group = NapiOverloader::GetGroup(bindInfo->overloadData);

    // arity == 2 could be special for external type value
    if (argc == 2) {
        napi_valuetype type;
        status = napi_typeof(env, args[0], &type);
        if (type == napi_external) {
            return group.externalWrapper(env, info);
        }
    }

    napi_callback constructorWrapper = reinterpret_cast<napi_callback>(group.methods[argc]);

    return constructorWrapper(env, info);
}

// | static |
napi_value NapiOverloader::CreateValue(napi_env env, napi_callback_info info)
{
    AKI_DLOG(DEBUG) << "NapiOverloader::CreateValue";
    napi_status status;
    ArgStorage *storage = nullptr;
    size_t argc = 0;
    status = napi_get_cb_info(env, info, &argc, nullptr, nullptr, ((void **) &storage));
    static std::vector<OverloadGroup> &overloads = GetOverloaderGroups();
    OverloadGroup &group = overloads[storage->GetOverloadGroupId()];

    std::vector<FuncPtr> &methods = group.methods;

    auto specializedCall = reinterpret_cast<CreateValueHandler>(methods[argc]);

    if (specializedCall != nullptr) {
        specializedCall(env, info, *storage);
        return nullptr;
    }
    return nullptr;
}

// | static |
int32_t NapiOverloader::AddGroup()
{
    std::vector<OverloadGroup> &overloadGroups = GetOverloaderGroups();
    int32_t num = static_cast<int32_t>(overloadGroups.size());

    // Add a new group of overloaded methods.
    overloadGroups.resize(num + 1);

    return (num);
}

// | static |
void NapiOverloader::AddMethod(int32_t groupId, int32_t arity, FuncPtr method)
{
    OverloadGroup &def = GetGroup(groupId);

    // Get methods in overloaded group.
    std::vector<FuncPtr> &methods = def.methods;

    int32_t oldArity = static_cast<int32_t>(methods.size()) - 1;

    // Grow list of methods if new arity doesn't fit.
    if (arity > oldArity) methods.resize(arity + 1);

    methods[arity] = method;
}

// | static |
std::vector<NapiOverloader::OverloadGroup> &NapiOverloader::GetOverloaderGroups()
{
    static std::vector<OverloadGroup> overloadGroups;
    return (overloadGroups);
}
} // namespace aki