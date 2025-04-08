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

#ifndef AKI_INTERNAL_VALUE_H
#define AKI_INTERNAL_VALUE_H

#include <string>
#include <map>
#include <vector>
#include <array>

#include "aki/value/array_buffer.h"
#include "aki/value/promise.h"

namespace aki {
namespace internal {
class Value {
public:
    virtual ~Value() = default;

    operator bool() { return GetBool(); }

    operator uint8_t() { return GetUint8(); }

    operator int8_t() { return GetInt8(); }

    operator uint16_t() { return GetUint16(); }

    operator int16_t() { return GetInt16(); }

    operator int() { return GetInt(); }

    operator int64_t() { return GetInt64(); }

    operator double() { return GetDouble(); }

    operator float() { return GetFloat(); }

    virtual operator char*() { return nullptr; }

    virtual operator const char*() { return nullptr; }

    operator std::string() { return GetString(); }

    operator ArrayBuffer() { return GetArrayBuffer(); }

    operator Promise() { return GetPromise(); }

    template<typename T>
    operator T&()
    {
        return *(reinterpret_cast<T*>(GetDataReference()));
    }

    template<typename T>
    operator T*()
    {
        return reinterpret_cast<T*>(GetDataReference());
    }

    virtual operator Value*() = 0;

    virtual bool GetBool() const { return std::numeric_limits<bool>::quiet_NaN(); }

    virtual uint8_t GetUint8() const { return std::numeric_limits<uint8_t>::quiet_NaN(); }

    virtual int8_t GetInt8() const { return std::numeric_limits<int8_t>::quiet_NaN(); }

    virtual uint16_t GetUint16() const { return std::numeric_limits<uint16_t>::quiet_NaN(); }

    virtual int16_t GetInt16() const { return std::numeric_limits<int16_t>::quiet_NaN(); }

    virtual int32_t GetInt() const { return std::numeric_limits<int32_t>::quiet_NaN(); }

    virtual int64_t GetInt64() const { return std::numeric_limits<int64_t>::quiet_NaN(); }

    virtual double GetDouble() const { return std::numeric_limits<double>::quiet_NaN(); };

    virtual float GetFloat() const { return std::numeric_limits<float>::quiet_NaN(); };

    virtual std::string GetString() const { return std::string(); }

    virtual char* GetCString() { return nullptr; }

    virtual ArrayBuffer GetArrayBuffer() { return ArrayBuffer(nullptr, 0); }

    virtual Promise GetPromise() { return Promise(); }
    
    virtual int Refresh() { return 0; }
    
    template<typename T>
    std::shared_ptr<T>& SharedReference ()
    {
        typedef std::shared_ptr<T> S;
        return *(reinterpret_cast<S*>(GetDataReference()));
    }

    template<typename R, typename... P>
    std::function<R (P...)> FunctionReference() 
    {
        typedef std::function<R (P...)> F;
        return *(reinterpret_cast<F*>(GetDataReference()));
    }
    
    template<typename T>
    std::map<std::string, T>& MapReference ()
    {
        typedef std::map<std::string, T> M;
        return *(reinterpret_cast<M*>(GetDataReference()));
    }
    
    template<typename T>
    std::vector<T>& VectorReference ()
    {
        typedef std::vector<T> V;
        return *(reinterpret_cast<V*>(GetDataReference()));
    }
    
    template<typename T, std::size_t N>
    std::array<T, N>& ArrayReference ()
    {
        typedef std::array<T, N> A;
        return *(reinterpret_cast<A*>(GetDataReference()));
    }

    virtual bool IsUndefined() const { return false; }

    virtual bool IsNull() const { return false; }

    virtual bool IsBool() const { return false; }

    virtual bool IsNumber() const { return false; }

    virtual bool IsString() const { return false; }

    virtual bool IsArray() const { return false; }

    virtual bool IsFunction() const { return false; }

protected:
    virtual void* GetDataReference() = 0;
};
} // namespace internal
} // namespace aki
#endif //AKI_INTERNAL_VALUE_H
