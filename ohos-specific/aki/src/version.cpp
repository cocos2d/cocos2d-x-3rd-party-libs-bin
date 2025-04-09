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

#include "aki/version.h"

namespace aki {
const char* Version::versionString_ = JSB_VERSION_STRING;
int Version::major_ = JSB_MAJOR_VERSION;
int Version::minor_ = JSB_MINOR_VERSION;
int Version::patch_ = JSB_PATCH_LEVEL;
} // namespace aki
