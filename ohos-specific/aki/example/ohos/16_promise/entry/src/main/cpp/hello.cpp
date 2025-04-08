/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 
#include <aki/jsbind.h>
#include <future>
#include <chrono>

aki::Promise ReturnPromiseResolveImmediately() {
    aki::Promise promise;
    std::string result;
    promise.Resolve("aki promise");
    return promise;
}

aki::Promise ReturnPromiseResolveLater() {
    aki::Promise promise;
    
    std::thread t([promise] () {
        aki::TaskRunner::PostTask("main", [promise] () {
            promise.Resolve(1);
        });
    });
    t.detach();
    return promise;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(ReturnPromiseResolveImmediately);
    JSBIND_FUNCTION(ReturnPromiseResolveLater);
}

JSBIND_ADDON(promise)