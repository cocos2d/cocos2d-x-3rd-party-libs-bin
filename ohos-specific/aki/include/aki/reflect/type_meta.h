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

#ifndef AKI_TYPE_META_H
#define AKI_TYPE_META_H

#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include "aki/type/type_flag.h"
#include "aki/config.h"
#include "aki/logging/logging.h"

namespace aki {
struct AKI_EXPORT TypeMeta;
template<typename T>
struct IsString {
    static constexpr bool value = std::is_same<T, std::string>::value ||
                                  std::is_same<T, char*>::value ||
                                  std::is_same<T, const char*>::value;
};

template<typename>
inline constexpr bool isArray = false;

template<typename T, std::size_t N>
inline constexpr bool isArray<std::array<T, N>> = true;

template<typename T>
inline constexpr bool isArray<std::vector<T>> = true;

template<typename T>
struct IsArray {
    static constexpr bool value = std::is_array<T>::value || isArray<T>;
};

template<typename>
inline constexpr bool isFunction = false;

template<typename M>
inline constexpr bool isFunction<std::function<M>> = true;

template<typename T>
struct IsFunction {
    static constexpr bool value = isFunction<T>;
};

template <typename T>
struct TplParams {
    static const void* Get()
    {
        return nullptr;
    }
};

struct ArrayTplParams {
    const TypeMeta* member;
    const size_t size;
};

struct FunctionTplParams {
    std::vector<const TypeMeta*> params;
};

struct TypeMeta {
    TypeMeta(const char* name);

    TypeMeta(const char* name, TypeFlag flag);

    TypeMeta(const char* name, TypeFlag flag, const void* params);

    ~TypeMeta() = default;

    static int32_t nextTypeId;

    int32_t id;

    const char* name;

    TypeFlag flag;

    union {
        const void* tplParams;
        const ArrayTplParams* arrayParams;
        const FunctionTplParams* functionParams;
    };

    template<typename T>
    static TypeMeta MakeTypeMeta();

private:
    TypeMeta(const TypeMeta&) = delete;
    TypeMeta(TypeMeta&&) = delete;
    TypeMeta& operator=(const TypeMeta&) = delete;
    TypeMeta& operator=(TypeMeta&&) = delete;
};

template<typename T>
struct TypeTrait {
    static constexpr const char* GetDescriptor()
    {
        return "<unknown>";
    }

    static const TypeMeta* GetTypeMeta()
    {
        static TypeMeta meta(GetDescriptor());
        return &meta;
    }
};

template <typename T, std::size_t N>
struct TplParams<std::array<T, N>> {
    static const ArrayTplParams* Get()
    {
        static ArrayTplParams params = {TypeTrait<T>::GetTypeMeta(), N};
        return &params;
    }
};

template <typename T>
struct TplParams<std::vector<T>> {
    static const ArrayTplParams* Get()
    {
        static ArrayTplParams params = {TypeTrait<T>::GetTypeMeta()};
        return &params;
    }
};

template <typename R, typename... P>
struct TplParams<std::function<R (P...)>> {
    static const FunctionTplParams* Get()
    {
        static FunctionTplParams params = { {TypeTrait<R>::GetTypeMeta(), TypeTrait<P>::GetTypeMeta()...} };
        return &params;
    }
};

template<typename T>
TypeMeta TypeMeta::MakeTypeMeta()
{
    if constexpr (std::is_same<T, bool>::value) {
        return TypeMeta(TypeTrait<T>::GetDescriptor(),
                        (TypeFlag::IS_BOOLEAN));
    } else if (std::is_void<T>::value) {
        return TypeMeta(TypeTrait<T>::GetDescriptor(),
                        (TypeFlag::IS_VOID));
    } else if (std::is_arithmetic<T>::value) {
        return TypeMeta(TypeTrait<T>::GetDescriptor(),
                        (TypeFlag::IS_ARITHMETIC |
                         (std::is_unsigned<T>::value ? TypeFlag::IS_UNSIGNED : TypeFlag::NONE) |
                         (std::is_same<T, char>::value ? TypeFlag::IS_CHAR : TypeFlag::NONE) |
                         (std::is_floating_point<T>::value ? TypeFlag::IS_FLOAT : TypeFlag::NONE)
                        ));
    } else if (IsString<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::value) {
        return TypeMeta(TypeTrait<T>::GetDescriptor(),
                        (TypeFlag::IS_STRING |
                        (std::is_same<T, std::string>::value ? TypeFlag::IS_STD_STRING : TypeFlag::IS_C_STRING)
                        ));
    } else if (IsArray<T>::value) {
        return TypeMeta(TypeTrait<T>::GetDescriptor(),
                        TypeFlag::IS_ARRAY,
                        TplParams<T>::Get());
    } else if (IsFunction<T>::value) {
        return TypeMeta(TypeTrait<T>::GetDescriptor(),
                        TypeFlag::IS_FUNCTION,
                        TplParams<T>::Get());
    } else {
        return TypeMeta(TypeTrait<T>::GetDescriptor(), TypeFlag::IS_OTHER);
    }
}

#define TYPE_DESCRIPTOR_MACRO_(_type_) \
    template<> class aki::TypeTrait<_type_> { \
    public: \
        static const char* GetDescriptor() { return #_type_; } \
        static const TypeMeta* GetTypeMeta() { \
            static TypeMeta meta = TypeMeta::MakeTypeMeta<_type_>(); \
            return &meta; \
        } \
    }

#define TYPE_DESCRIPTOR_MACRO_T(_type_, ...) \
    template<typename __VA_ARGS__> class aki::TypeTrait<_type_<__VA_ARGS__>> { \
    public: \
        static const char* GetDescriptor() { return #_type_; } \
        static const TypeMeta* GetTypeMeta() { \
            static TypeMeta meta = TypeMeta::MakeTypeMeta<_type_<__VA_ARGS__>>(); \
            return &meta; \
        } \
    }

#define TYPE_DESCRIPTOR_MACRO_FOR_VOID(_type_)
#define TYPE_DESCRIPTOR_MACRO_FOR_POD(_type_) TYPE_DESCRIPTOR_MACRO_(_type_)

#define TYPE_DESCRIPTOR(_type_, ...) \
    TYPE_DESCRIPTOR_MACRO_(_type_); \
    TYPE_DESCRIPTOR_MACRO_(_type_*); \
    TYPE_DESCRIPTOR_MACRO_(const _type_*); \
    TYPE_DESCRIPTOR_MACRO_##__VA_ARGS__(_type_&); \
    TYPE_DESCRIPTOR_MACRO_##__VA_ARGS__(const _type_&)

#define TYPE_DESCRIPTOR_T(_type_, ...) \
    TYPE_DESCRIPTOR_MACRO_T(_type_, __VA_ARGS__)

TYPE_DESCRIPTOR(void, FOR_VOID);
TYPE_DESCRIPTOR(bool);
TYPE_DESCRIPTOR(nullptr_t);
TYPE_DESCRIPTOR(unsigned char);
TYPE_DESCRIPTOR(signed char);
TYPE_DESCRIPTOR(char);
TYPE_DESCRIPTOR(unsigned short);
TYPE_DESCRIPTOR(signed short);
TYPE_DESCRIPTOR(unsigned int);
TYPE_DESCRIPTOR(signed int);
TYPE_DESCRIPTOR(unsigned long);
TYPE_DESCRIPTOR(signed long);
TYPE_DESCRIPTOR(unsigned long long);
TYPE_DESCRIPTOR(signed long long);
TYPE_DESCRIPTOR(float);
TYPE_DESCRIPTOR(double);
TYPE_DESCRIPTOR(std::string);
TYPE_DESCRIPTOR_T(std::function, M);
TYPE_DESCRIPTOR_T(std::vector, T);

template<typename T, std::size_t N>
class aki::TypeTrait<std::array<T, N>> {
public:
    static const char* GetDescriptor() { return "std::array"; }
    static const TypeMeta* GetTypeMeta()
    {
        static TypeMeta meta = TypeMeta::MakeTypeMeta<std::array<T, N>>();
        return &meta;
    }
};

} // namespace aki

#endif //AKI_TYPE_META_H
