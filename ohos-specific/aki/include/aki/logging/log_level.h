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

#ifndef AKI_LOG_LEVEL_H
#define AKI_LOG_LEVEL_H
namespace aki {

using LogLevel = int;

constexpr LogLevel LOG_DEBUG = 0;
constexpr LogLevel LOG_INFO = 1;
constexpr LogLevel LOG_WARNING = 2;
constexpr LogLevel LOG_ERROR = 3;
constexpr LogLevel LOG_FATAL = 4;
constexpr LogLevel LOG_LEVELS = 5;

#ifdef NDEBUG
const LogLevel LOG_DFATAL = LOG_ERROR;
#else
const LogLevel LOG_DFATAL = LOG_FATAL;
#endif

} // namespace aki
#endif //AKI_LOG_LEVEL_H
