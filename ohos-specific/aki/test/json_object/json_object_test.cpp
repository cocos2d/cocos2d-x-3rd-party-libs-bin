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

#include <map>
#include <aki/jsbind.h>

class JsonObjectHandle {
  public:
    JsonObjectHandle() = default;
    std::map<std::string, long> PassingVoidReturnMapLong() {
        std::map<std::string, long> map = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}};
        return map;
    }

    std::map<std::string, long> PassingMapLongReturnMapLong(std::map<std::string, long> map) {
        map["Thursday"] = 4;
        return map;
    }
};

JSBIND_CLASS(JsonObjectHandle) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_METHOD(PassingVoidReturnMapLong, "passingVoidReturnMapLong");
    JSBIND_METHOD(PassingMapLongReturnMapLong, "passingMapLongReturnMapLong");
}

std::map<std::string, long> PassingVoidReturnMapLong() {
    std::map<std::string, long> map = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}};
    return map;
}

std::map<std::string, long> PassingMapLongReturnMapLong(std::map<std::string, long> map) {
    map["Thursday"] = 4;
    return map;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(PassingVoidReturnMapLong, "passingVoidReturnMapLong");
    JSBIND_FUNCTION(PassingMapLongReturnMapLong, "passingMapLongReturnMapLong");
}