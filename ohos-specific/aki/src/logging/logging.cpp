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

#include "aki/logging/logging.h"

#include <algorithm>
#include <iostream>

#include <hilog/log.h>

#include "log_setting.h"

namespace aki {
namespace {

constexpr const char* kLogLevelNames[LOG_LEVELS] = {"DEBUG", "INFO", "WARNING",
                                                           "ERROR", "FATAL"};

const char* GetNameForLogLevel(LogLevel level)
{
    if (level >= LOG_DEBUG && level < LOG_LEVELS) {
        return kLogLevelNames[level];
    }
    return "UNKNOWN";
}

const char* StripPath(const char* path)
{
    auto* p = strrchr(path, '/');
    if (p) {
        return p + 1;
    }
    return path;
}

}  // namespace

ScopedLogMessage::ScopedLogMessage(LogLevel level, const char* file, int line, const char* condition)
    : level_(level)
{
    stream_ << "[" << GetNameForLogLevel(level) << ":" << StripPath(file) << "(" << line << ")] ";

    if (condition) {
        stream_ << "Check failed: " << condition << ". ";
    }
}

ScopedLogMessage::~ScopedLogMessage()
{
    stream_ << std::endl;

    ::LogLevel levelOH = ::LOG_WARN;
    switch (level_) {
        case aki::LOG_DEBUG:
            levelOH = ::LOG_DEBUG;
            break;
        case aki::LOG_INFO:
            levelOH = ::LOG_INFO;
            break;
        case aki::LOG_WARNING:
            levelOH = ::LOG_WARN;
            break;
        case aki::LOG_ERROR:
            levelOH = ::LOG_ERROR;
            break;
        case aki::LOG_FATAL:
            levelOH = ::LOG_FATAL;
            break;
    }

    OH_LOG_Print(LOG_APP, levelOH, LOG_DOMAIN, "AKI", "%{public}s", stream_.str().c_str());

    if (level_ >= aki::LOG_FATAL) {
        KillProcess();
    }
}

bool ShouldCreateLogMessage(LogLevel level)
{
    return level >= LogSetting::GetMinLogLevel();
}

void KillProcess()
{
    abort();
}

}  // namespace aki