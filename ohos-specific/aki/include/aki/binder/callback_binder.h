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

#ifndef AKI_CALLBACK_BINDER_H
#define AKI_CALLBACK_BINDER_H
#include <functional>
#include <unordered_map>

#include "binder.h"
#include "aki/logging/logging.h"

namespace aki {
template <typename BinderType, typename R, typename... P>
class CallbackBinder : public Binder {
public:
#if JSBIND_SUPPORT_DECLARATION
    CallbackBinder()
        : Binder(type,
                 reinterpret_cast<FuncPtr>(BinderType::Wrapper),
                 sizeof...(P), {})
    { }
#else
    CallbackBinder()
        : Binder(type,
                 reinterpret_cast<FuncPtr>(BinderType::Wrapper),
                 sizeof...(P))
    { }
#endif
    ~CallbackBinder() = default;
    
    template<typename... Args>
    static R InnerWrapper(std::function<R (P...)>* invoker, Args&&... args)
    {
        AKI_DLOG(DEBUG) << "NapiCallbackBinder::InnerWrapper";
        
        return (*invoker)(std::forward<Args>(args)...);
    }
    
    static constexpr auto type = Binder::Type::Func;
};
} // namespace aki
#endif //AKI_CALLBACK_BINDER_H
