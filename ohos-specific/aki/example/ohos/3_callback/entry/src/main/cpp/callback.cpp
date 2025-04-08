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

#include <functional>
#include <aki/jsbind.h>

void CallFunctionReturnVoid(std::function<void()> func) {
    func();
}

short CallFunctionPassingShortReturnShort(short num, std::function<short(short)> func) {
    short result = func(num);
    return result;
}

void CallFunctionReturnString(std::function<std::string()> func) {
    auto str = func();
    AKI_LOG(INFO) << "std::function callback return from Js: " << str;
}

void CallJsbCallbackReturnVoid(aki::Callback<void()> func) {
    func();
}

void CallJsbCallbackReturnString(aki::Callback<std::string()> func) {
    auto str = func();
    AKI_LOG(INFO) << "aki::Callback callback return from Js: " << str;
}

void CallJsbSafetyCallbackReturnVoid(aki::SafetyCallback<void()> func) {
    func();
}

void CallJsbSafetyCallbackReturnString(aki::SafetyCallback<std::string()> func) {
    auto str = func();
    AKI_LOG(INFO) << "aki::SafetyCallback callback return from Js: " << str;
}

void InvokeFuncWithCallbackReturnNumber() {
    if (auto func = aki::JSBind::GetJSFunction("funcWithCallbackReturnNumber")) {
        std::function<int (int)> cb = [](int result) {
            AKI_LOG(INFO) << "InvokeFuncWithCallbackReturnNumber: " << result;
            return result;
        };
        func->Invoke<void>(1, 2, cb); // 无返回值，入参类型 string
    }
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(CallFunctionReturnVoid);
    JSBIND_FUNCTION(CallFunctionPassingShortReturnShort);
    JSBIND_FUNCTION(CallFunctionReturnString);
    JSBIND_FUNCTION(CallJsbCallbackReturnVoid);
    JSBIND_FUNCTION(CallJsbCallbackReturnString);
    JSBIND_FUNCTION(CallJsbSafetyCallbackReturnVoid);
    JSBIND_FUNCTION(CallJsbSafetyCallbackReturnString);
    JSBIND_FUNCTION(InvokeFuncWithCallbackReturnNumber);
}

JSBIND_ADDON(callback) // 注册 AKI 插件名为: callback