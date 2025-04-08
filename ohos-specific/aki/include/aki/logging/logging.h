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

#ifndef AKI_LOGGING_H
#define AKI_LOGGING_H
#include <sstream>

#include "log_level.h"
#include "aki/config.h"

namespace aki {

class EatLogMessage {
public:
    void operator&(std::ostream&) {}
};

class AKI_EXPORT ScopedLogMessage {
public:
    ScopedLogMessage(LogLevel level,
               const char* file,
               int line,
               const char* condition);
    ~ScopedLogMessage();

    std::ostream& stream() { return stream_; }

private:
    std::ostringstream stream_;
    const LogLevel level_;

    ScopedLogMessage(const ScopedLogMessage&) = delete;
    ScopedLogMessage& operator=(const ScopedLogMessage&) = delete;
};

AKI_EXPORT bool ShouldCreateLogMessage(LogLevel level);

[[noreturn]] void KillProcess();

} // namespace aki

#define AKI_LOG_STREAM(level) \
  ::aki::ScopedLogMessage(level, __FILE__, __LINE__, nullptr).stream()

#define AKI_LAZY_STREAM(stream, condition) \
  !(condition) ? (void)0 : ::aki::EatLogMessage() & (stream)

#define AKI_EAT_STREAM_PARAMETERS(ignored) \
    true || (ignored)                        \
        ? (void)0                            \
        : ::aki::EatLogMessage() &       \
            ::aki::ScopedLogMessage(::aki::LOG_FATAL, 0, 0, nullptr).stream()

#define AKI_LOG_IS_ON(level) \
    (::aki::ShouldCreateLogMessage(level))

#define AKI_LOG(level) \
    AKI_LAZY_STREAM(AKI_LOG_STREAM(::aki::LOG_##level), AKI_LOG_IS_ON(::aki::LOG_##level))

#define AKI_CHECK(condition)                                              \
    AKI_LAZY_STREAM(                                                        \
        ::aki::ScopedLogMessage(::aki::LOG_FATAL, __FILE__, __LINE__, #condition) \
            .stream(),                                                      \
            !(condition))

#ifndef NDEBUG
#define AKI_DLOG AKI_LOG
#define AKI_DCHECK(condition) AKI_CHECK(condition)
#else
#define AKI_DLOG(level) AKI_EAT_STREAM_PARAMETERS(true)
#define AKI_DCHECK(condition) AKI_EAT_STREAM_PARAMETERS(condition)
#endif

#endif //AKI_LOGGING_H
