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

#ifndef AKI_CLASS_DEFINER_H
#define AKI_CLASS_DEFINER_H

#include "aki/binding.h"
#if JSBIND_USING_NAPI
# include "aki/binder/napi/napi_constructor_binder.h"
# include "aki/binder/napi/napi_pfunction_binder.h"
# include "aki/binder/napi/napi_method_binder.h"
# include "aki/binder/napi/napi_pmethod_binder.h"
# include "aki/binder/napi/napi_getter_binder.h"
# include "aki/binder/napi/napi_setter_binder.h"
#endif

namespace aki {
template <class C>
class ClassDefiner {
public:
    ClassDefiner(const char* name)
    {
#if JSBIND_USING_NAPI
        class_ = &Class<C>::GetInstance();
        class_->Init(name);
        NapiOverloader::SetExternalWrapper(class_->GetWrapperConstructorGroupId(), ClassWrapper<C>::ExternalWrapper);
#endif

        Binding::RegisterClass(class_);
    }

    ~ClassDefiner() = default;

    template <typename... P>
    void AddConstructor()
    {
#if JSBIND_USING_NAPI
        typedef NapiConstructorBinder<C, P...> BinderType;
#endif

        class_->AddConstructor(&BinderType::GetInstance());
    }

    template<typename SetterType>
    void AddSetter(const char* name, SetterType (C::*setter))
    {
#if JSBIND_USING_NAPI
        AddMethodMaybeConst<NapiSetterBinder>(name, setter);
#endif
    }

    template<typename GetterType, typename SetterType>
    void AddField(const char* name, GetterType (C::*getter), SetterType (C::*setter))
    {
#if JSBIND_USING_NAPI
        AddMethodMaybeConst<NapiGetterBinder>(name, getter);
        AddMethodMaybeConst<NapiSetterBinder>(name, setter);
#endif
    }

    template<typename PropertyType>
    void AddProperty(const char* name, PropertyType C::*property)
    {
#if JSBIND_USING_NAPI
        AddMethod<NapiGetterBinder<C, decltype(property), PropertyType>>(name, property);
        AddMethod<NapiSetterBinder<C, decltype(property), void, PropertyType>>(name, property);
#endif
    }

    // bind for member method
    template<typename MethodType>
    void AddMethod(const char* name, MethodType (C::*method))
    {
#if JSBIND_USING_NAPI
        AddMethodMaybeConst<NapiMethodBinder>(name, method);
#endif
    }

    // bind for member method
    template<typename MethodType>
    void AddPMethod(const char* name, MethodType (C::*method))
    {
#if JSBIND_USING_NAPI
        AddMethodMaybeConst<NapiPMethodBinder>(name, method);
#endif
    }

    // bind for static method
    template <typename R, typename... Args>
    void AddMethod(const char* name, R(*method)(Args...))
    {
#if JSBIND_USING_NAPI
        AddMethod<NapiFunctionBinder<decltype(method), R, Args...>>(name, method);
#endif
    }

    // bind for static method
    template <typename R, typename... Args>
    void AddPMethod(const char* name, R(*method)(Args...))
    {
#if JSBIND_USING_NAPI
        AddMethod<NapiPFunctionBinder<decltype(method), R, Args...>>(name, method);
#endif
    }

private:

    /// 成员方法类型可能为const
    template <template <class, typename, typename...> class BinderType,
              typename R,
              typename... P>
    void AddMethodMaybeConst(const char* name, R(C::*method)(P...))
    {
        AddMethod<BinderType<C, decltype(method), R, P...>, decltype(method)>(name, method);
    }

    /// 成员方法类型可能为const
    template <template <class, typename, typename...> class BinderType,
            typename R,
            typename... P>
    void AddMethodMaybeConst(const char* name, R(C::*method)(P...) const)
    {
        AddMethod<BinderType<C, decltype(method), R, P...>, decltype(method)>(name, method);
    }

    template <typename BinderType, typename M>
    void AddMethod(const char* name, M method)
    {
        class_->AddMethod(name,
                          BinderType::AddInvoker(method),
                          &BinderType::GetInstance());
    }


    Class<C>* class_;
};
} // namespace aki
#endif //AKI_CLASS_DEFINER_H