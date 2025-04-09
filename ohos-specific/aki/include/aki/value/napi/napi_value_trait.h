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

#ifndef AKI_NAPI_VALUE_TRAIT_H
#define AKI_NAPI_VALUE_TRAIT_H

#include <js_native_api.h>
#include <node_api.h>

#include "aki/value/napi/napi_value.h"
#include "aki/logging/logging.h"
#include "aki/binding.h"

namespace aki {

template<typename T>
class NapiValueMaker : public NapiValue<typename DetectPolicies<T>::Type> {
public:
    using NapiValue<typename DetectPolicies<T>::Type>::NapiValue;

    ~NapiValueMaker()
    {
    }
};

/**
 * @brief: NapiValueTrait::Cast 使用模板类函数，因为模板函数无法自动推导返回值
 */
template<typename T>
struct NapiValueTrait {
    static T Cast(internal::Value& value)
    {
        if constexpr (std::is_enum<T>::value) {
            NapiValue<T>& alphaValue = *(static_cast<NapiValue<T>*>(&value));
            return alphaValue.GetEnumeration();
        } else {
            return static_cast<T&>(value);
        }
    }
};

template<typename T>
struct NapiValueTrait<T&> {
    static T& Cast(internal::Value& value)
    {
        return static_cast<T&>(value);
    }
};

template<typename T>
struct NapiValueTrait<T*> {
    static T* Cast(internal::Value& value)
    {
        return static_cast<T*>(value);
    }
};

template<typename T>
struct NapiValueTrait<Equivalence<T>> {

    static T Cast(internal::Value& value)
    {
        return static_cast<T&>(value);
    }
};

template<>
struct NapiValueTrait<bool> {
    static bool Cast(internal::Value& value)
    {
        return static_cast<bool>(value);
    }
};

template<>
struct NapiValueTrait<uint8_t> {
    static uint8_t Cast(internal::Value& value)
    {
        return static_cast<uint8_t>(value);
    }
};

template<>
struct NapiValueTrait<int8_t> {
    static int8_t Cast(internal::Value& value)
    {
        return static_cast<int8_t>(value);
    }
};

template<>
struct NapiValueTrait<uint16_t> {
    static uint16_t Cast(internal::Value& value)
    {
        return static_cast<uint16_t>(value);
    }
};

template<>
struct NapiValueTrait<int16_t> {
    static int16_t Cast(internal::Value& value)
    {
        return static_cast<int16_t>(value);
    }
};

template<>
struct NapiValueTrait<int> {
    static int Cast(internal::Value& value)
    {
        return static_cast<int>(value);
    }
};

template<>
struct NapiValueTrait<int64_t> {
    static int64_t Cast(internal::Value& value)
    {
        return static_cast<int64_t>(value);
    }
};

template<>
struct NapiValueTrait<double> {
    static double Cast(internal::Value& value)
    {
        return static_cast<double>(value);
    }
};

template<>
struct NapiValueTrait<float> {
    static float Cast(internal::Value& value)
    {
        return static_cast<float>(value);
    }
};

template<>
struct NapiValueTrait<std::string> {
    static std::string Cast(internal::Value& value)
    {
        return static_cast<std::string>(value);
    }
};

template<>
struct NapiValueTrait<const std::string&> {
    static std::string Cast(internal::Value& value)
    {
        return static_cast<std::string>(value);
    }
};

template<typename T>
struct NapiValueTrait<std::shared_ptr<T>> {
    static std::shared_ptr<T> Cast(internal::Value& value)
    {
        return value.SharedReference<T>();
    }
};

template<typename R, typename... P>
struct NapiValueTrait<std::function<R (P...)>> {
    static std::function<R (P...)> Cast(internal::Value& value)
    {
        return value.FunctionReference<R, P...>();
    }
};

template<typename R, typename... P>
struct NapiValueTrait<Callback<R (P...)>> {
    static Callback<R (P...)> Cast(internal::Value& value)
    {
        NapiValue<Callback<R (P...)>>& alphaValue = *(static_cast<NapiValue<Callback<R (P...)>>*>(&value));
        return alphaValue.GetFunction();
    }
};

template<typename R, typename... P>
struct NapiValueTrait<SafetyCallback<R (P...)>> {
    static SafetyCallback<R (P...)> Cast(internal::Value& value)
    {
        NapiValue<SafetyCallback<R (P...)>>& alphaValue = *(static_cast<NapiValue<SafetyCallback<R (P...)>>*>(&value));
        return alphaValue.GetFunction();
    }
};

template<>
struct NapiValueTrait<ArrayBuffer> {
    static ArrayBuffer Cast(internal::Value& value)
    {
        return static_cast<ArrayBuffer>(value);
    }
};

template<>
struct NapiValueTrait<Promise> {
    static Promise Cast(internal::Value& value)
    {
        return static_cast<Promise>(value);
    }
};

template<typename T>
struct NapiValueTrait<std::map<std::string, T>> {
    static std::map<std::string, T> Cast(internal::Value& value)
    {
        return value.MapReference<T>();
    }
};

template<typename T>
struct NapiValueTrait<std::vector<T>> {
    static std::vector<T> Cast(internal::Value& value)
    {
        return value.VectorReference<T>();
    }
};

template<typename T, std::size_t N>
struct NapiValueTrait<std::array<T, N>> {
    static std::array<T, N> Cast(internal::Value& value)
    {
        return value.ArrayReference<T, N>();
    }
};

template<>
struct NapiValueTrait<JSFunction> {
    static JSFunction Cast(internal::Value& value)
    {
        NapiValue<JSFunction>& alphaValue = *(static_cast<NapiValue<JSFunction>*>(&value));
        return alphaValue.GetJSFunction();
    }
};

template<>
struct NapiValueTrait<napi_value> {
    static napi_value Cast(internal::Value& value)
    {
        NapiValue<napi_value>& alphaValue = *(static_cast<NapiValue<napi_value>*>(&value));
        return alphaValue.GetNapiValue();
    }
};

template<>
struct NapiValueTrait<Value> {
    static Value Cast(internal::Value& value)
    {
        NapiValue<napi_value>& alphaValue = *(static_cast<NapiValue<napi_value>*>(&value));
        return Value(alphaValue.GetNapiValue());
    }
};

// NapiValue<std::vector<T>>
template<typename T>
std::vector<T> NapiValue<std::vector<T>>::GetVector()
{
    napi_status status;
    napi_env env = env_;
    std::vector<T> result;
    uint32_t length;
    status = napi_get_array_length(env, value_, &length);
    AKI_DCHECK(status == napi_ok);
    for (uint32_t i = 0; i < length; i++) {
        napi_value element;
        status = napi_get_element(env, value_, i, &element);
        AKI_DCHECK(status == napi_ok);
        auto napiValue = NapiValue<typename ValueDefiner<T>::RawType>(env, element);
        T t = NapiValueTrait<typename ValueDefiner<T>::RawType>::Cast(napiValue);
        result.push_back(t);
    }

    return result;
}
// std::array
template<typename T, size_t N>
std::array<T, N> NapiValue<std::array<T, N>>::GetArray()
{
    napi_status status;
    napi_env env = env_;
    std::array<T, N> result;
    uint32_t length;
    status = napi_get_array_length(env, value_, &length);
    AKI_DCHECK(status == napi_ok);
    for (uint32_t i = 0; i < length; i++) {
        napi_value element;
        status = napi_get_element(env, value_, i, &element);
        AKI_DCHECK(status == napi_ok);
        auto napiValue = NapiValueMaker<T>(env, element);
        T t = ValueTrait<typename ValueDefiner<T>::RawType>::Cast(napiValue);
        result[i] = std::move(t);
    }

    return result;
}

template<typename T>
std::map<std::string, T> NapiValue<std::map<std::string, T>>::GetMapObject()
{
    napi_status status;
    napi_env env = env_;
    napi_value names;

    status = napi_get_property_names(env, value_, &names); 
    AKI_DCHECK(status == napi_ok);

    std::map<std::string, T> result;

    uint32_t length;
    status = napi_get_array_length(env, names, &length);
    AKI_DCHECK(status == napi_ok);

    for (auto index = 0; index < length; index++) {
        napi_value keyNapi;
        status = napi_get_element(env, names, index, &keyNapi); 
        AKI_DCHECK(status == napi_ok);
        NapiValue<std::string> keyNapiValue(env, keyNapi);
        std::string keyStr = keyNapiValue.GetString();
        napi_value valueNapi;
        status = napi_get_property(env, value_, keyNapi, &valueNapi);
        AKI_DCHECK(status == napi_ok);
        auto valueNapiValue = NapiValueMaker<T>(env, valueNapi);
        T t = NapiValueTrait<typename ValueDefiner<T>::RawType>::Cast(valueNapiValue);
        result[keyStr] = t;
    }

    return result;
}

template<typename R, typename... P>
template<typename... Args>
R Callback<R (P...)>::Call(Args&&... args) const
{
    napi_status status;
    napi_env env = env_;
    napi_value cb = cb_;
    size_t argc = sizeof...(P);
    std::array<napi_value, sizeof...(P)> argv = {NapiValue<typename ValueDefiner<Args>::RawType>::ToNapiValue(env, std::forward<Args>(args))...};

    napi_value undefined;
    status = napi_get_undefined(env, &undefined);
    AKI_DCHECK(status == napi_ok) << "status: " << status;

    napi_value result;
    status = napi_call_function(env,
                                undefined,
                                cb,
                                argc,
                                argv.data(),
                                &result);
    AKI_DCHECK(status == napi_ok) << "status: " << status;

    if constexpr (std::is_void<R>::value) {
        return;
    } else if constexpr (std::is_same<R, napi_value>::value) {
        return result;
    } else {
        AKI_CHECK(NapiValue<R>::CheckType(env, result)) << "should return type with: " << NapiValue<R>::ExpectedType();
        auto napiValue = NapiValueMaker<R>(env, result);
        return NapiValueTrait<R>::Cast(napiValue);
    }
}

template<typename R, typename... P>
template<typename... Args>
R Callback<R (P...)>::CallMethod(napi_env env, napi_value recv, Args&&... args) const
{
    size_t argc = sizeof...(P);
    std::array<napi_value, sizeof...(P)> argv = {NapiValue<typename ValueDefiner<Args>::RawType>::ToNapiValue(env, std::forward<Args>(args))...};

    napi_value result;
    napi_status status;
    status = napi_call_function(env,
                                recv,
                                cb_,
                                argc,
                                argv.data(),
                                &result);
    AKI_DCHECK(status == napi_ok) << "status: " << status;

    if constexpr (std::is_void<R>::value) {
        return;
    } else if constexpr (std::is_same<R, napi_value>::value) {
        return result;
    } else {
        AKI_CHECK(NapiValue<R>::CheckType(env, result)) << "should return type with: " << NapiValue<R>::ExpectedType();
        auto napiValue = NapiValueMaker<R>(env, result);
        return NapiValueTrait<R>::Cast(napiValue);
    }
}

template<typename R, typename... P>
template<size_t... Index>
napi_value NapiCallbackBinder<R, P...>::SafetyWrapper(napi_env& env, napi_callback_info info, std::index_sequence<Index...>)
{
    AKI_DLOG(DEBUG) << "NapiCallbackBinder::SafetyWrapper";
    napi_status status;
    void* invoker = nullptr;
    size_t argc = sizeof...(Index);
    std::array<napi_value, sizeof...(Index)> args;

    status = napi_get_cb_info(env, info, &argc, args.data(), nullptr, &invoker);
    AKI_DCHECK(status == napi_ok);
    AKI_DCHECK(invoker != nullptr);
    auto tuple = std::make_tuple(NapiValueMaker<typename ValueDefiner<P>::RawType>(env, args[Index])...);
    auto valueTuple = std::make_tuple(NapiValueTrait<typename ValueDefiner<P>::RawType>::Cast(std::get<Index>(tuple))...);

    return WrapperForward(env, invoker, std::get<Index>(valueTuple)...);
}
    
    

    
template<typename R, typename... P>
template<typename... Args>
napi_value NapiCallbackBinder<R, P...>::WrapperForward(napi_env& env, void* invoker, Args&&... args)
{
    AKI_DLOG(DEBUG) << "NapiCallbackBinder::WrapperForward";

    if constexpr (std::is_void<R>::value) {
        ParentType::InnerWrapper(reinterpret_cast<std::function<R (P...)>*>(invoker), std::forward<Args>(args)...);
        return nullptr;
    } else {
        R r = ParentType::InnerWrapper(reinterpret_cast<std::function<R (P...)>*>(invoker), std::forward<Args>(args)...);
        return NapiValue<R>::ToNapiValue(env, std::forward<R>(r));
    }
}


template<typename T>
Value::Value(T&& value)
{
    napi_env env = aki::Binding::GetScopedEnv();
    napi_value handle = NapiValue<T>::ToNapiValue(env, std::forward<T>(value));
    
    internal::Value* ival = new NapiValueMaker<napi_value>(env, handle);
    handle_.reset(ival);
    persistent_ = Persistent(handle);
}

template<typename T>
T Value::As() const {
    return NapiValueTrait<T>::Cast(*handle_);
}

template<typename V>
void Value::Set(const char* key, const V& value) {
    napi_status status;
    napi_value result;
    napi_env env = aki::Binding::GetScopedEnv();
    napi_value recv = persistent_.GetValue();

    napi_value nv = NapiValue<V>::ToNapiValue(env, value);
    status = napi_set_named_property(env, recv, key, nv);
    AKI_DCHECK(status == napi_ok);
}

template<typename V>
void Value::Set(const size_t index, V&& value)
{
    napi_status status;
    napi_value result;
    napi_env env = aki::Binding::GetScopedEnv();
    napi_value recv = persistent_.GetValue();

    napi_value nv = NapiValue<V>::ToNapiValue(env, value);
    status = napi_set_element(env, recv, index, nv);
    AKI_DCHECK(status == napi_ok);
}

template<typename... Args>
Value Value::operator()(Args&&... args) const {
    Callback<napi_value (Args...)> jsCallback = NapiValueTrait<Callback<napi_value (Args...)>>::Cast(*handle_);
    return Value(jsCallback(std::forward<Args>(args)...));
}

template<typename... Args>
Value Value::CallMethod(const char* name, Args&&... args)
{
    napi_env env = aki::Binding::GetScopedEnv();
    napi_value recv = this->GetHandle();
    aki::Value funcV((*this)[name].GetHandle());
    Callback<napi_value (Args...)> jsCallback(env, funcV.GetHandle());
    return Value(jsCallback.CallMethod(env, recv, std::forward<Args>(args)...));
}

template<typename T>
void Promise::Resolve(T&& t) const
{
    napi_env env = aki::Binding::GetScopedEnv();
    napi_value result = NapiValue<typename ValueDefiner<T>::RawType>::ToNapiValue(env, std::forward<T>(t));

    napi_resolve_deferred(env, deferred_, result);
}
} // namespace aki
#endif //AKI_NAPI_VALUE_TRAIT_H
