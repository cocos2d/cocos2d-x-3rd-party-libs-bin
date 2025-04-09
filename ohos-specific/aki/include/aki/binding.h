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

#ifndef AKI_BINDING_H
#define AKI_BINDING_H

#include <forward_list>
#include <unordered_map>
#include <memory>

#include "aki/enumeration/enumeration_base.h"
#include "aki/invoker/invoker.h"
#include "aki/function.h"
#include "aki/class/class.h"
#include "aki/config.h"
#include "aki/value/napi/js_function.h"

#if JSBIND_SUPPORT_DECLARATION
#include "aki/reflect/type_meta.h"
#endif

namespace aki {

class AKI_EXPORT Binding {
public:
    static void SetScopedEnv(napi_env env);

    static napi_env GetScopedEnv();

    static std::forward_list<Function>& GetFunctionList();

    static std::forward_list<Function>& GetFunctionList(const char* module);

    static void RegisterFunction(const char *name, int32_t invokerId, Binder* binder);

    static void RegisterFunction(const char* module, const char *name, int32_t invokerId, Binder* binder);

    static std::forward_list<ClassBase*>& GetClassList();

    static void RegisterClass(ClassBase* xlass);

    static std::forward_list<EnumerationBase *>& GetEnumerationList();

    static void RegisterEnumeration(EnumerationBase* enumeration);

    static std::unordered_map<std::string, std::unique_ptr<JSFunction>>& GetJSFunctionMap();

    static int RegisterJSFunction(const std::string& name, std::unique_ptr<JSFunction> func);

#if JSBIND_SUPPORT_DECLARATION
    static std::forward_list<const TypeMeta*>& GetBuildInTypeList();
#endif

private:
    Binding() = delete;

    Binding(const Binding&) = delete;
    
    static std::unordered_map<const char*, std::forward_list<Function>> funcListMap;
};
} // namespace aki

#endif //AKI_BINDING_H
