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

#ifndef AKI_VALUE_TRAIT_H
#define AKI_VALUE_TRAIT_H

#include "value.h"

namespace aki {

/**
 * @brief: Value对象转型模板
 */
template<typename T>
struct ValueTrait {
    static T Cast(internal::Value& value)
    {
        return static_cast<T&>(value);
    }
};

// int 手动特化
template<>
struct ValueTrait<int> {
    static int Cast(internal::Value& value)
    {
        return static_cast<int>(value);
    }
};

// double 手动特化
template<>
struct ValueTrait<double> {
    static double Cast(internal::Value& value)
    {
        return static_cast<double>(value);
    }
};

// string 手动特化
template<>
struct ValueTrait<std::string> {
    static std::string Cast(internal::Value& value)
    {
        return value.operator std::string();
    }
};

template<typename T>
struct ValueDefiner {
    typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type RawType;
};

template<typename T>
struct ValueMaker : public ValueDefiner<T>::Type {
    ValueMaker() = default;
    ValueMaker(T t) : ValueDefiner<T>::Type(std::forward<T>(t)) {}
};

} // namespace aki
#endif //AKI_VALUE_TRAIT_H
