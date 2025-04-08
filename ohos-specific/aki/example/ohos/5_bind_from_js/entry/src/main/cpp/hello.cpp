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

#include <thread>

#include "aki/jsbind.h"
#include "aki/logging/logging.h"
bool DoSomethingFromNative() {

    if (auto createTable = aki::JSBind::GetJSFunction("MyStorage.createTable")) {
        createTable->Invoke<void>("MYSTORE"); // 返回值类型 int，入参类型 string
    }

    if (auto insert = aki::JSBind::GetJSFunction("MyStorage.insert")) {
        insert->Invoke<void>("MYSTORE"); // 无返回值，入参类型 string
    }

    if (auto query = aki::JSBind::GetJSFunction("MyStorage.query")) {
        query->Invoke<void>("MYSTORE"); // 无返回值，入参类型 string
    }

    // 跨线程调用场景可使用 std::promise 异步转同步
    std::thread subThread([]() {
        // 子线程
        if (auto insert = aki::JSBind::GetJSFunction("MyStorage.insert")) {
            std::promise<std::string> insertPromise;
            std::function<void(std::string)> insertCallback = [&insertPromise](std::string message) {
                AKI_DLOG(INFO) << "callback will be invoked in JS Thread.";
                insertPromise.set_value(message);
            };
            insert->Invoke<void>("MYSTORE", insertCallback); // 返回值类型 int，入参类型 string, function
            AKI_DLOG(INFO) << "wait until promise set value.";
            std::string message = insertPromise.get_future().get(); // 子线程阻塞
            AKI_DLOG(INFO) << "insert with message: " << message;
        }
    });
    subThread.detach();

    return true;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(DoSomethingFromNative);
}

JSBIND_ADDON(entry) // 注册 AKI 插件名为: entry