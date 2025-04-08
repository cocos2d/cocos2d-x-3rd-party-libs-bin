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

#ifndef AKI_TYPE_FLAG_H
#define AKI_TYPE_FLAG_H
namespace aki {

struct TypePlaceHolder {
    static constexpr uint32_t FLAG = 1;
    static constexpr uint32_t NUM = FLAG;
    static constexpr uint32_t STR = NUM << 3;
    static constexpr uint32_t REF = STR << 3;
    static constexpr uint32_t TYPE = REF << 3;
};

enum class TypeFlag : uint32_t {
    NONE = 0,

    NUM_MASK        = TypePlaceHolder::NUM * 0B1111,        // 0000 0000 0000 0000 0000 0000 0000 0111
    IS_UNSIGNED     = TypePlaceHolder::NUM << 0,
    IS_CHAR         = TypePlaceHolder::NUM << 1,
    IS_FLOAT        = TypePlaceHolder::NUM << 2,

    STR_MASK        = TypePlaceHolder::STR * 0B111,         // 0000 0000 0000 0000 0000 0000 0011 1000
    IS_C_STRING     = TypePlaceHolder::STR << 0,
    IS_STD_STRING   = TypePlaceHolder::STR << 1,

    REF_MASK        = TypePlaceHolder::REF * 0B111,         // 0000 0000 0000 0000 0000 0001 1100 0000
    IS_POINTER      = TypePlaceHolder::REF << 0,
    IS_SHARED_PTR   = TypePlaceHolder::REF << 1,

    TYPE_MASK       = TypePlaceHolder::TYPE * 0B11111111,   // 0000 0000 0000 0000 1111 1110 0000 0000
    IS_VOID         = TypePlaceHolder::TYPE << 0,
    IS_BOOLEAN      = TypePlaceHolder::TYPE << 1,
    IS_ARITHMETIC   = TypePlaceHolder::TYPE << 2,
    IS_STRING       = TypePlaceHolder::TYPE << 3,
    IS_CLASS        = TypePlaceHolder::TYPE << 4,
    IS_ARRAY        = TypePlaceHolder::TYPE << 5,
    IS_FUNCTION     = TypePlaceHolder::TYPE << 6,
    IS_OTHER        = TypePlaceHolder::TYPE << 7,

    ALL_MASK = 0XFFFFFFFF
};

inline TypeFlag operator& (TypeFlag a, TypeFlag b)
{
    return(static_cast<TypeFlag>(
        static_cast<uint32_t>(a) & static_cast<uint32_t>(b)
    ));
}
inline TypeFlag operator| (TypeFlag a, TypeFlag b)
{
    return(static_cast<TypeFlag>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b)
    ));
}

} // namespace aki
#endif //AKI_TYPE_FLAG_H
