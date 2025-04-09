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

#ifndef AKI_JSBIND_H
#define AKI_JSBIND_H

#include <string>

#include "aki/definer/function_definer.h"
#include "aki/definer/class_definer.h"
#include "aki/definer/enumeration_definer.h"
#include "aki/callback/napi/callback.h"
#include "aki/task_runner/task_runner.h"

namespace aki {
class AKI_EXPORT JSBind {
public:
#if JSBIND_USING_NAPI
    static napi_value BindSymbols(napi_env env, napi_value exports);

    static napi_value BindSymbols(const char* module);

    static void SetScopedEnv(napi_env env);

    static napi_env GetScopedEnv();
#endif // JSBIND_USING_NAPI

    static int bindFunction(const std::string& name, JSFunction func);

    static void InitTaskRunner(const std::string& name);

#if JSBIND_SUPPORT_DECLARATION
    static void Reflect(aki::Callback<void (intptr_t, int32_t)> outputBuildInType,
                        aki::Callback<void (std::string, std::vector<intptr_t>)> outputFunction);
    static void QueryType(intptr_t typeId,
                          aki::Callback<void (int32_t, std::vector<intptr_t>)> outputType);
#endif

    static const JSFunction* GetJSFunction(const std::string& name);
private:
};

template <typename... Aliases>
const char *AliasName(const char *name, Aliases... aliases)
{
    return(name);
}

template <typename... Aliases>
const char *AliasName(const char *name, const char *alias, Aliases... aliases)
{
    return(alias);
}
} // namespace aki

#define JSBIND_CONCAT(a, b) a ## b

#define JSBIND_UNIQUE(name, line) JSBIND_CONCAT(name, line)

#define JSBIND_ALIAS(name, alias) alias

#define JSBIND_FUNCTION(__name, ...) aki::FunctionDefiner JSBIND_UNIQUE(definer, __LINE__)(aki::AliasName(#__name, ##__VA_ARGS__), &__name)

#define JSBIND_PFUNCTION(__name, ...) aki::PFunctionDefiner JSBIND_UNIQUE(definer, __LINE__)(aki::AliasName(#__name, ##__VA_ARGS__), &__name)

#define JSBIND_GLOBAL() namespace

#define JSBIND_SCOPED_FUNCTION(__scoped, __name, ...) aki::FunctionDefiner JSBIND_UNIQUE(definer, __LINE__)(__scoped, aki::AliasName(#__name, ##__VA_ARGS__), &__name)

#define JSBIND_CLASS(__class)                                                                                 \
template<class C> struct ClassDefiner##__class {                                                \
    ClassDefiner##__class();                                                                            \
    aki::ClassDefiner<__class> definer;                                                                \
};                                                                                                      \
static struct ClassDefiner##__class<__class> classDefiner##__class;                                     \
template<class C> ClassDefiner##__class<C>::ClassDefiner##__class():definer(#__class)

#define JSBIND_CONSTRUCTOR definer.AddConstructor

#define JSBIND_SETTER(__name, __setter) definer.AddSetter(__name, &C::__setter)

#define JSBIND_FIELD(__name, __getter, __setter) definer.AddField(__name, &C::__getter, &C::__setter)

#define JSBIND_PROPERTY(__property) definer.AddProperty(#__property, &C::__property)

#define JSBIND_METHOD(__method, ...) definer.AddMethod(aki::AliasName(#__method, ##__VA_ARGS__), &C::__method)

#define JSBIND_PMETHOD(__method, ...) definer.AddPMethod(aki::AliasName(#__method, ##__VA_ARGS__), &C::__method)

#define JSBIND_ENUM(__enum)                                                                             \
template<typename E> struct EnumerationDefiner##__enum {                                                \
    EnumerationDefiner##__enum();                                                                       \
    aki::EnumerationDefiner<__enum> definer;                                                            \
};                                                                                                      \
static struct EnumerationDefiner##__enum<__enum> enumerationDefiner##__class;                           \
template<typename E> EnumerationDefiner##__enum<E>::EnumerationDefiner##__enum():definer(#__enum)

#define JSBIND_ENUM_VALUE(__value) definer.SetValue(#__value, E::__value)

#define JSBIND_ADDON_LAZY(addonName)                                                                               \
EXTERN_C_START                                                                                                \
static napi_module _module = {                                                                                \
    .nm_version =1,                                                                                           \
    .nm_flags = 0,                                                                                            \
    .nm_filename = nullptr,                                                                                   \
    .nm_register_func = aki::JSBind::BindSymbols,                                                             \
    .nm_modname = #addonName,                                                                                 \
    .nm_priv = ((void*)0),                                                                                    \
    .reserved = { 0 },                                                                                        \
};                                                                                                            \
extern "C" __attribute__((constructor)) void Register##addonName(void) {                                      \
    napi_module_register(&_module);                                                                             \
    AKI_LOG(INFO) << "register AKI addon: " << #addonName;                                                   \
}    \
EXTERN_C_END

#define JSBIND_ADDON(addonName)                                          \
JSBIND_ADDON_LAZY(addonName)

#define JSBIND_ADDON_X(addonName, constructorAlias)                                                             \
EXTERN_C_START                                                                                                \
static napi_module _module = {                                                                                \
    .nm_version =1,                                                                                           \
    .nm_flags = 0,                                                                                            \
    .nm_filename = nullptr,                                                                                   \
    .nm_register_func = aki::JSBind::BindSymbols,                                                             \
    .nm_modname = #addonName,                                                                                 \
    .nm_priv = ((void*)0),                                                                                    \
    .reserved = { 0 },                                                                                        \
};                                                                                                            \
extern "C" __attribute__((constructor)) void Register##constructorAlias(void) {                               \
    napi_module_register(&_module);                                                                             \
    AKI_LOG(INFO) << "register AKI addon: " << #addonName;                                                   \
}    \
EXTERN_C_END

#endif //AKI_JSBIND_H
