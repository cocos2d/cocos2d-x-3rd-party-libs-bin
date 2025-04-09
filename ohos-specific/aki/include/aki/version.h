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

#ifndef AKI_VERSION_H
#define AKI_VERSION_H

#include "aki/config.h"

#define JSB_MAJOR_VERSION 1
#define JSB_MINOR_VERSION 2
#define JSB_PATCH_LEVEL 3

#define JSB_SX(x) #x
#define JSB_S(x) JSB_SX(x)

#define JSB_VERSION_STRING                                        \
    JSB_S(JSB_MAJOR_VERSION)                                         \
    "." JSB_S(JSB_MINOR_VERSION) \
    "." JSB_S(JSB_PATCH_LEVEL)


namespace aki {
class AKI_EXPORT Version {
public:
    static const char* GetVersion() { return versionString_; }

private:
    static const char* versionString_;
    static int major_;
    static int minor_;
    static int patch_;
};
} // namespace aki

#endif //AKI_VERSION_H
