/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef AKI_ENUMERATION_BASE_H
#define AKI_ENUMERATION_BASE_H

#include <string>
#include <map>

namespace aki {
class EnumerationBase {
public:
    EnumerationBase() = default;
    
    const char* GetName() {
        return name_.c_str();
    }
    
    void SetName(const char* name) {
        name_ = name;
    }
    
    std::map<std::string, int32_t>& GetValue() {
        return values_;
    }
    
    void SetValue(const char* key, int32_t value) {
        values_[key] = value;
    }
    
private:
    std::string name_;

    std::map<std::string, int32_t> values_;
};
}
#endif //AKI_ENUMERATION_BASE_H
