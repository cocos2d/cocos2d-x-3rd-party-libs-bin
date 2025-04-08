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

#ifndef AKI_CONFIG_H
#define AKI_CONFIG_H

#ifdef AKI_ENABLE_NAPI
# if AKI_ENABLE_NAPI
#  define JSBIND_USING_NAPI 1
# endif
#endif

#ifdef AKI_BUILDING_SHARED
# if AKI_BUILDING_SHARED
#  define AKI_EXPORT __attribute__ ((visibility("default")))
# else
#  define AKI_EXPORT
# endif
#else
# define AKI_EXPORT
#endif

#ifdef AKI_ENABLE_DECLARATION
# define JSBIND_SUPPORT_DECLARATION 1
#endif

#ifdef AKI_ENABLE_TRACING
# define JSBIND_USING_TRACING 1
#endif

#endif //AKI_CONFIG_H
