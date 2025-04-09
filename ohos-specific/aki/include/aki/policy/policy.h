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

#ifndef AKI_POLICY_H
#define AKI_POLICY_H

#include <type_traits>
#include "aki/matcher/matcher.h"

namespace aki {

// 主模板处理无嵌套 ::type 成员的类型：
template< class, class = void >
struct HasMemberEquals : std::false_type { };

// 特化识别拥有嵌套 ::type 成员的类型：
template< class T >
struct HasMemberEquals<T, std::void_t<decltype(std::declval<T>().Equals(std::declval<Matcher>()))>> : std::true_type { };

template<typename T>
struct Equivalence {};

struct EquivalentPolicy {
    template <typename T>
    struct Transform {
        typedef Equivalence<T> Type;
    };
};

struct NoPolicy {
    template<typename T>
    struct Transform {
        typedef T Type;
    };
};

template <typename T, bool hasEquals>
struct PolicyCodec {
    typedef T Type;
};

template <typename T>
struct PolicyTyped {
};

template <typename T>
struct PolicyTyped<PolicyCodec<T, false>> {
    typedef NoPolicy Type;
};

template <typename T>
struct PolicyTyped<PolicyCodec<T, true>> {
    typedef EquivalentPolicy Type;
};


template <typename T>
struct DetectPolicies {
    typedef typename PolicyTyped<PolicyCodec<T, HasMemberEquals<T>::value>>::Type Policy;

    typedef typename Policy::template Transform<T>::Type Type;
};

} // namespace aki
#endif //AKI_POLICY_H
