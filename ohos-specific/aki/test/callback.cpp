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

#include "napi/native_api.h"
#include <chrono>
#include <thread>
#include "aki/jsbind.h"
#include <hilog/log.h>

/**
 * @brief: 回调类型为：void (*)(void)
 * @result: passed
 */
void CallbackInvoke(std::function<void()> callback) {
    callback();
}

/**
 * @brief: 回调类型为：void (*)(void)
 * @result: passed
 */
void CallbackInvokeInt(std::function<void(int)> callback) {
    callback(1);
}

/**
 * @brief: 回调类型为：void (*)(void)
 * @result: passed
 */
void CallbackInvokeIntReturnStr(std::function<std::string (int)> callback) {
    std::string result = callback(1);
}

/**
 * @brief: 回调类型为：void (*)(void)
 * @result: passed
 */
void CallbackInvokeFromThread(std::function<void()> callback) {
    static std::thread t([callback = std::move(callback)] () {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 工作线程 sleep 1 秒
        callback();
    });
}

JSBIND_GLOBAL()
{
    JSBIND_FUNCTION(CallbackInvoke);
    JSBIND_FUNCTION(CallbackInvokeInt);
    JSBIND_FUNCTION(CallbackInvokeFromThread);
    JSBIND_FUNCTION(CallbackInvokeIntReturnStr);
}