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

#ifndef AKI_SETTER_BINDER_H
#define AKI_SETTER_BINDER_H
#include "binder.h"

namespace aki {

/**
 * @brief: 类属性访问器Set函数类型Binder，定义所有类属性访问器Set函数回调类型为：void (C::*)(P)的回调Binder
 */
template <typename BinderType, typename C, typename M, typename R, typename P>
class SetterBinder : public TemplatedBinder<BinderType, M, R, P> {
public:
    // | static |
    /**
     * @brief: 根据ClassType::Method注册时的Invoker Id获取调用器对象进行函数实体调用
     * @param: receiver: 类实例对象
     *         binderInfo: invoker索引ID
     *         arg: 参数
     * @Note: 注意入参必须是引用，如果传值前是指针，需要解指针
     */
    template<typename Arg>
    static R InnerWrapper(C& receiver, aki::BindInfo* bindInfo, Arg&& arg)
    {
        const auto& invokerInfo = BinderType::GetInvoker(bindInfo->setterNumber);
        return Invoker<R (*)(P)>::InvokeMethod(receiver, invokerInfo.invoker, std::forward<Arg>(arg));
    }

    static constexpr auto type = Binder::Type::Setter;

};
} // namespace aki
#endif //AKI_SETTER_BINDER_H
