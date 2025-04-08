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

#include "application_info.h"

#include <hilog/log.h>

void ApplicationInfo::Init(ApplicationInfo info)
{
    static ApplicationInfo applicationInfo(info);
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "AKI", "ApplicationInfo::Init applicationInfo name: %{public}s", applicationInfo.name.c_str());
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "AKI", "ApplicationInfo::Init applicationInfo descriptionId: %{public}d", applicationInfo.descriptionId);
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "AKI", "ApplicationInfo::Init applicationInfo systemApp: %{public}s", applicationInfo.systemApp ? "true" : "false");
    for (auto permission : applicationInfo.permissions) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "AKI", "ApplicationInfo::Init applicationInfo permission: %{public}s", permission.c_str());
    }
}

ApplicationInfo::ApplicationInfo(const std::string& name, 
                                 int descriptionId, 
                                 bool systemApp, 
                                 std::vector<std::string> permissions)
    : name(name), 
      descriptionId(descriptionId),
      systemApp(systemApp),
      permissions(permissions)
{
}

JSBIND_CLASS(ApplicationInfo)
{
    JSBIND_CONSTRUCTOR<const std::string&, int, bool, std::vector<std::string>>();
    JSBIND_METHOD(Init);
}

JSBIND_ADDON(context) // 注册 AKI 插件名为: context