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

#ifndef AKI_INVOKER_H
#define AKI_INVOKER_H

#include <memory>

#include "aki/value/value_trait.h"

namespace aki {

template<typename F>
struct InvokerInfo {
    InvokerInfo(F f) : invoker(f) {}

    const F invoker;
};

template<typename>
struct Invoker {
};

template<typename R, typename... P>
struct Invoker<R (*)(P...)> {
    template <typename F, typename... Args>
    static R InvokeFunction(F func, Args&&... args)
    {
        return (*func)(std::forward<P>(args)...);
    }

    template <class C, typename M, typename... Args>
    static R InvokeMethod(C &receiver, M method, Args&&... args) noexcept(false)
    {
        return (receiver.*method)(std::forward<P>(args)...);
    }

    template <class C>
    static R InvokeMethod(C &receiver, R C::*property) noexcept(false)
    {
        return receiver.*property;
    }
};

template<typename... P>
struct Invoker<void (*)(P...)> {
    template <typename F, typename... Args>
    static void InvokeFunction(F func, Args&&... args)
    {
        (*func)(std::forward<P>(args)...);
        return;
    }

    template <class C, typename M, typename... Args>
    static void InvokeMethod(C &receiver, M method, Args&&... args) noexcept(false)
    {
        (receiver.*method)(std::forward<Args>(args)...);
        return;
    }

    template <class C, typename Arg>
    static void InvokeMethod(C &receiver, Arg C::*property, Arg arg) noexcept(false)
    {
        receiver.*property = std::forward<Arg>(arg);
        return;
    }
};

} // namespace aki
#endif //AKI_INVOKER_H
