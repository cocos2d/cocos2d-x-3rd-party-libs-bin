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

#ifndef AKI_FUNCTION_BINDER_H
#define AKI_FUNCTION_BINDER_H

#include "binder.h"
#if JSBIND_USING_TRACING
# include <tracing/trace.h>
#else
# define FUNCTION_DTRACE()
#endif // JSBIND_USING_TRACING
namespace aki {

/**
 * @brief: Function类型Binder，定义所有全局函数回调类型为：R(*)(P...)的回调Binder。
 *         类静态方法也通过此Binder定义回调。
 */
template <typename BinderType, typename F, typename R, typename... P>
class FunctionBinder : public TemplatedBinder<BinderType, F, R, P...> {
public:
    // | static |
    /**
     * @brief: 根据ClassType::Method注册时的Invoker Id获取调用器对象进行函数实体调用
     * @param: binderInfo: invoker索引ID
     *         args: 扩展参数包
     */
    template<typename... Args>
    static R InnerWrapper(aki::BindInfo* bindInfo, Args&&... args)
    {
        FUNCTION_DTRACE();
        const auto& invokerInfo = BinderType::GetInvoker(bindInfo->functionNumber);
        
        return Invoker<R (*)(P...)>::InvokeFunction(invokerInfo.invoker, std::forward<Args>(args)...);
    }

    static constexpr auto type = Binder::Type::Func;

};
} // namespace aki

#endif //AKI_FUNCTION_SIGNATURE_H
