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
#include <aki/jsbind.h>

/**
 * @brief: 1.2 回调类型为：void (*)(void)
 * @result: passed
 */
void CallbackReturnVoid(aki::Callback<void (void)> callback)
{
    callback();
}

/**
 * @brief: 1.3异步回调类型为：void (*)(void)
 * @result: passed
 */
void SafetyCallbackReturnVoid(aki::SafetyCallback<void ()> callback) {
    std::thread t([callback = std::move(callback)] () {
        AKI_DLOG(DEBUG) << "should be non-js-thread";
        callback();
    });
    t.detach();
}

/**
 * @brief: 2.2 回调类型为：bool (*)(bool)
 * @result: passed
 */
bool CallbackReturnBool_True(aki::Callback<bool (bool)> callback)
{
    return callback(true);
}

/**
 * @brief: 2.3异步回调类型为：bool (*)(bool)
 * @result: passed
 */
bool SafetyCallbackReturnBool_True(aki::SafetyCallback<bool (bool)> callback) {
    std::thread t([callback = std::move(callback)] () {
        AKI_DLOG(DEBUG) << "should be non-js-thread";
        bool result = callback(true);
        AKI_DCHECK(result == true); // true 原路返回
    });
    t.detach();

    return true;
}

/**
 * @brief: 3.2 回调类型为：int (*)(int)
 * @result: passed
 */
int CallbackReturnInt_Int(aki::Callback<int (int)> callback)
{
    return callback(10086);
}

/**
 * @brief: 4.2 回调类型为：std::string (*)(std::string)
 * @result: passed
 */
std::string CallbackReturnString_String(aki::Callback<std::string (std::string)> callback)
{
    return callback("JSBind");
}

/**
 * @brief: 4.3 异步回调类型为：std::string (*)(std::string)
 * @result: passed
 */
std::string SafetyCallbackReturnString_String(aki::SafetyCallback<std::string (std::string)> callback)
{
    std::thread t([callback = std::move(callback)] () {
        AKI_DLOG(DEBUG) << "should be non-js-thread";
        std::string result = callback("JSBind");
        AKI_DCHECK(result == "Hello JSBind"); // 返回 "Hello JSBind"
    });
    t.detach();

    return "JSBind";
}

/**
 * @brief: 5.2 回调类型为：double (*)(double)
 * @result: passed
 */
double CallbackReturnDouble_Double(aki::Callback<double (double)> callback)
{
    return callback(3.1415926);
}

/**
 * @brief: 5.3 异步回调类型为：double (*)(double)
 * @result: passed
 */
double SafetyCallbackReturnDouble_Double(aki::SafetyCallback<double(double)> callback)
{
    std::thread t([callback = std::move(callback)] () {
        AKI_DLOG(DEBUG) << "should be non-js-thread";
        double result = callback(3.1415926);
        AKI_DCHECK(result == 3.1415926); // 3.1415926 原路返回
    });
    t.detach();

    return 3.1415926;
}

/**
 * @brief: 5.4 异步回调类型为：double (*)(double) N次调用
 * @result: passed
 */
double SafetyCallbackReturnDouble_Double_Num_X2(aki::SafetyCallback<double(double)> callback)
{
    // js 线程
    static std::thread t([callback = std::move(callback)] () {
        // 工作线程
        AKI_DLOG(DEBUG) << "should be non-js-thread";
        int i = 0;
        for (; i < 2; i++) {
            double result = callback(3.1415926);
            AKI_DCHECK(result == 3.1415926); // 3.1415926 原路返回
        }
    });
    t.detach();

    return 3.1415926;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(CallbackReturnVoid);
    JSBIND_FUNCTION(SafetyCallbackReturnVoid);
    JSBIND_FUNCTION(CallbackReturnBool_True);
    JSBIND_FUNCTION(SafetyCallbackReturnBool_True);
    JSBIND_FUNCTION(CallbackReturnInt_Int);
    JSBIND_FUNCTION(CallbackReturnString_String);
    JSBIND_FUNCTION(SafetyCallbackReturnString_String);
    JSBIND_FUNCTION(CallbackReturnDouble_Double);
    JSBIND_FUNCTION(SafetyCallbackReturnDouble_Double);
    JSBIND_FUNCTION(SafetyCallbackReturnDouble_Double_Num_X2);
}