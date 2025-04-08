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

#ifndef AKI_CALLBACK_OBJECT_H
#define AKI_CALLBACK_OBJECT_H

#include <functional>

class CallbackObject {
public:
    CallbackObject();

    static void InvokeOnInvoke(CallbackObject*);

    void OnInvoke();

    void SetOnInvoke(std::function<void ()>);

    bool GetOnInvoke() const;

    static void InvokeOnResponse(CallbackObject*);

    void OnResponse(const std::string&);

    void SetOnResponse(std::function<void (const std::string&)>);

    bool GetOnResponse() const;

    void SetOnResponseReturnStr(std::function<std::string (const std::string&)>);

    bool GetOnResponseReturnStr() const;

    std::string InvokeOnResponseReturnStr();

private:
    std::function<void ()> onInvoke_;

    std::function<void (const std::string&)> onResponse_;

    std::function<std::string (const std::string&)> onResponseReturnStr_;
};

#endif //AKI_CALLBACK_OBJECT_H
