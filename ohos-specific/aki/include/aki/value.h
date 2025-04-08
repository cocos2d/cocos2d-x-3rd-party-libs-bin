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

#ifndef AKI_VALUE_H
#define AKI_VALUE_H

#include <node_api.h>
#include <string>
#include "aki/value/value.h"
#include "aki/persistent/persistent.h"

namespace aki {
class AKI_EXPORT Value {
public:
    Value();

    Value(napi_value handle);

    template<typename T>
    explicit Value(T&& handle);

    static Value FromGlobal(const char* key = nullptr);

    static Value NewObject();

    napi_value GetHandle() const;

    Value operator[](const std::string& key) const;

    Value operator[](const size_t index) const;

    template<typename T>
    T As() const;

    template<typename V>
    void Set(const char* key, const V& value);

    template<typename V>
    void Set(const size_t index, V&& value);

    template<typename... Args>
    Value operator()(Args&&... args) const;

    template<typename... Args>
    Value CallMethod(const char* name, Args&&... args);

    bool IsUndefined() const;

    bool IsNull() const;

    bool IsBool() const;

    bool IsNumber() const;

    bool IsString() const;

    bool IsArray() const;

    bool IsFunction() const;

private:
    std::shared_ptr<internal::Value> handle_;
    
    Persistent persistent_;
};

} // namespace aki
#endif //AKI_VALUE_H
