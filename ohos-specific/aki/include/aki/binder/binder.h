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

#ifndef AKI_BINDER_H
#define AKI_BINDER_H

#include <vector>
#include <memory>

#include "aki/invoker/invoker.h"
#include "aki/bind_info.h"
#include "aki/config.h"

#if JSBIND_SUPPORT_DECLARATION
# include "aki/reflect/type_meta.h"
#endif

namespace aki {
typedef void (*FuncPtr)();

/**
 * @brief: 前端回调关系抽象层
 */
class Binder {
public:
    enum class Type: unsigned int {
        None = 0,
        Func,           // 全局函数回调
        Constructor,    // 类构造函数回调
        Method,         // 类成员方法回调
        Getter,         // 类属性访问器回调 Get
        Setter,         // 类属性访问器回调 Set
        Overload        // 重载函数回调：识别不同参数个数，不识别参数类型
    };
#if JSBIND_SUPPORT_DECLARATION
    Binder(Binder::Type type, FuncPtr wrapper, int32_t arity, std::vector<const TypeMeta*> typeList)
        : type_(type),
          wrapper_(wrapper),
          arity_(arity),
          typeList_(typeList),
          valueConstructor_(nullptr){}
#else
    Binder(Binder::Type type, FuncPtr wrapper, int32_t arity)
        : type_(type),
          wrapper_(wrapper),
          arity_(arity),
          valueConstructor_(nullptr){}
#endif
        
    virtual ~Binder() = default;

    /// 获取回调地址
    const FuncPtr GetWrapper() const { return wrapper_; }

    /// 获取回调类型
    Type GetType() const { return type_; }

    int32_t GetArity() const { return(arity_); }

    FuncPtr GetValueConstructor() const { return(valueConstructor_); }

    void SetValueConstructor(FuncPtr valueConstructor)
    {
        this->valueConstructor_ = valueConstructor;
    }

#if JSBIND_SUPPORT_DECLARATION
    const std::vector<const TypeMeta*>& GetTypeList() const { return typeList_; }
#endif

private:
    const Binder::Type type_;

    FuncPtr wrapper_;

    const int32_t arity_;

    FuncPtr valueConstructor_;

#if JSBIND_SUPPORT_DECLARATION
    std::vector<const TypeMeta*> typeList_;
#endif

};

/**
 * @brief: Binder模板，对应：Function、Constructor、Method、Field等类型的binder
 */
template <class BinderType, typename I, typename R, typename... P>
class TemplatedBinder : public Binder {
public:
    typedef InvokerInfo<I> InvokerInfoType;
#if JSBIND_SUPPORT_DECLARATION
    TemplatedBinder()
        : Binder(BinderType::type,
                 reinterpret_cast<FuncPtr>(BinderType::Wrapper),
                 sizeof...(P),
                 { TypeTrait<R>::GetTypeMeta(), TypeTrait<P>::GetTypeMeta()... })
    {
    }
#else
    TemplatedBinder()
        : Binder(BinderType::type,
                 reinterpret_cast<FuncPtr>(BinderType::Wrapper),
                 sizeof...(P))
    {
    }
#endif
    ~TemplatedBinder() = default;

    // | static |
    static BinderType& GetInstance()
    {
        static BinderType instance;
        return(instance);
    }

    // | static |
    static const InvokerInfoType& GetInvoker(int32_t id) { return GetInstance().invokers_[id]; }

    // | static |
    static int32_t AddInvoker(InvokerInfoType invoker)
    {
        auto& invokers = GetInstance().invokers_;
        invokers.emplace_back(std::move(invoker));
        return static_cast<int32_t>(invokers.size() - 1);
    }

private:
    /// 所有Native函数类型为：R(*)(P...)的函数都由同一个Binder转发，因此需要用Invoker Id区分，
    /// 并且考虑索引性能，使用数组存储Invoker对象。
    std::vector<InvokerInfoType> invokers_;
};
} // namespace aki

#endif //AKI_BINDER_H
