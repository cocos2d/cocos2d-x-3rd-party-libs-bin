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

#ifndef AKI_FUNCTION_DEFINER_H
#define AKI_FUNCTION_DEFINER_H

#include "aki/binding.h"
#include "aki/config.h"

#if JSBIND_USING_NAPI
# include "aki/binder/napi/napi_function_binder.h"
# include "aki/binder/napi/napi_pfunction_binder.h"
#endif
namespace aki {
class FunctionDefiner {
public:
    template <typename R, typename... Args>
    FunctionDefiner(const char* name, R(*func)(Args...))
    {
#if JSBIND_USING_NAPI
        typedef NapiFunctionBinder<
                decltype(func), 
                R,
                Args...
        > Binder;
#endif

        Binding::RegisterFunction(name,
                                  Binder::AddInvoker(func),
                                  &Binder::GetInstance());
    }

    template <typename R, typename... Args>
    FunctionDefiner(const char* module, const char* name, R(*func)(Args...))
    {
#if JSBIND_USING_NAPI
        typedef NapiFunctionBinder<
                decltype(func), 
                R,
                Args...
        > Binder;
#endif

        Binding::RegisterFunction(module,
                                  name,
                                  Binder::AddInvoker(func),
                                  &Binder::GetInstance());
    }

    ~FunctionDefiner() = default;
};

class PFunctionDefiner {
public:
    template <typename R, typename... Args>
    PFunctionDefiner(const char* name, R(*func)(Args...))
    {
#if JSBIND_USING_NAPI
        typedef NapiPFunctionBinder<
            decltype(func), 
            R,
            Args...
        > Binder;
#endif

        Binding::RegisterFunction(name,
                                  Binder::AddInvoker(func),
                                  &Binder::GetInstance());
    }

    ~PFunctionDefiner() = default;
};
} // namespace aki

#endif //AKI_FUNCTION_DEFINER_H
