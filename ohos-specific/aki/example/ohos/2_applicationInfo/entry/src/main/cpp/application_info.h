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

#ifndef context_application_info_H
#define context_application_info_H
#include <string>
#include <vector>
#include <aki/jsbind.h>

struct ApplicationInfo {
    
    static void Init(ApplicationInfo info);
    
    ApplicationInfo() = default;
    
    ApplicationInfo(const std::string& name, int descriptionId, bool systemApp, std::vector<std::string> permissions);

    void Equals(aki::Matcher matcher) { }
    
    std::string name;
    
    int descriptionId;
    
    bool systemApp;
    
    std::vector<std::string> permissions;
};

#endif //context_application_info_H
