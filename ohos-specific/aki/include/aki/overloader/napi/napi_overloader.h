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

#ifndef AKI_NAPI_OVERLOADER_H
#define AKI_NAPI_OVERLOADER_H

#include <vector>
#include <node_api.h>

#include "aki/arg_storage/arg_storage.h"
#include "aki/config.h"

namespace aki {
typedef void (*FuncPtr)();
class AKI_EXPORT NapiOverloader {
public:
    typedef void (*CreateValueHandler)(napi_env env, napi_callback_info info, ArgStorage &storage);
    struct OverloadGroup {
        std::vector<FuncPtr> methods;
        napi_callback externalWrapper;
    };

    static napi_value Wrapper(napi_env env, napi_callback_info info);

    static napi_value CreateValue(napi_env env, napi_callback_info info);

    static int32_t AddGroup();

    static void AddMethod(int32_t groupId, int32_t arity, FuncPtr method);

    static inline OverloadGroup &GetGroup(int32_t groupId) {
        return (GetOverloaderGroups()[groupId]);
    }

    static void SetExternalWrapper(int32_t groupId, napi_callback externalWrapper) {
        GetGroup(groupId).externalWrapper = externalWrapper;
    }

    static std::vector<OverloadGroup>& GetOverloaderGroups();
};
} // namespace aki

#endif //AKI_NAPI_OVERLOADER_H
