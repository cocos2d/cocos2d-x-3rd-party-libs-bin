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

#ifndef AKI_LOG_SETTING_H
#define AKI_LOG_SETTING_H

#include <cstddef>
#include "aki/logging/log_level.h"

namespace aki {

struct LogSetting {
    static void SetLogSetting(const LogSetting& setting);

    static LogSetting GetLogSetting();

    static int GetMinLogLevel();

    static LogSetting logSetting;

    LogLevel minLogLevel = LOG_DEBUG;

    constexpr static size_t maxLogSize = 4096;
};

} // namespace aki


#endif //AKI_LOG_SETTING_H
