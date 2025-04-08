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

#ifndef AKI_CONSTRUCTOR_BINDER_H
#define AKI_CONSTRUCTOR_BINDER_H
#include "binder.h"

namespace aki {

/**
 * @brief: 类构造函数类型Binder，定义所有类构造函数回调类型为：C(P...)的回调Binder
 */
template <typename BinderType, typename C, typename... P>
class ConstructorBinder : public TemplatedBinder<BinderType, void*, C, P...> {
public:

    // | static |
    template<typename... Args>
    static std::unique_ptr<internal::Value> InnerWrapper(aki::BindInfo* bindInfo, Args&&... args)
    {
        return nullptr;
    }

    static constexpr auto type = Binder::Type::Constructor;

};
} // namespace aki
#endif //AKI_CONSTRUCTOR_BINDER_H
