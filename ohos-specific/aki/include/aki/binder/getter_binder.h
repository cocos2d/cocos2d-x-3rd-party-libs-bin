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

#ifndef AKI_GETTER_BINDER_H
#define AKI_GETTER_BINDER_H
#include "binder.h"

namespace aki {

/**
 * @brief: 类属性访问器Get函数类型Binder，定义所有类属性访问器Get函数回调类型为：R (C::*)()的回调Binder
 */
template <typename BinderType, typename C, typename M, typename R>
class GetterBinder : public TemplatedBinder<BinderType, M, R> {
public:
    // | static |
    /**
     * @brief: 根据ClassType::Method注册时的Invoker Id获取调用器对象进行函数实体调用
     * @param: receiver: 类实例对象
     *         binderInfo: invoker索引ID
     * @Note: 注意入参必须是引用，如果传值前是指针，需要解指针
     */
    static R InnerWrapper(C& receiver, aki::BindInfo* bindInfo)
    {
        const auto& invokerInfo = BinderType::GetInvoker(bindInfo->getterNumber);
        return Invoker<R (*)()>::InvokeMethod(receiver, invokerInfo.invoker);
    }

    static constexpr auto type = Binder::Type::Getter;

};
} // namespace aki
#endif //AKI_GETTER_BINDER_H
