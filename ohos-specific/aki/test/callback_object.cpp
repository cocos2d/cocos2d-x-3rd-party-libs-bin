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

#include "callback_object.h"
#include <aki/jsbind.h>

CallbackObject::CallbackObject()
    : onInvoke_(nullptr), onResponse_(nullptr)
{}

// | static |
void CallbackObject::InvokeOnInvoke(CallbackObject* callback)
{
    callback->OnInvoke();
}

void CallbackObject::OnInvoke()
{
    if (onInvoke_) {
        onInvoke_();
    }
}

void CallbackObject::SetOnInvoke(std::function<void ()> cb)
{
    onInvoke_ = cb;
}

bool CallbackObject::GetOnInvoke() const
{
    return false;
}

// | static |
void CallbackObject::InvokeOnResponse(CallbackObject* callback)
{
    callback->OnResponse("hello AKI");
}

void CallbackObject::OnResponse(const std::string& data)
{
    if (onResponse_) {
        onResponse_(data);
    }
}

void CallbackObject::SetOnResponse(std::function<void (const std::string&)> cb)
{
    onResponse_ = cb;
}

bool CallbackObject::GetOnResponse() const
{
    return false;
}

void CallbackObject::SetOnResponseReturnStr(std::function<std::string (const std::string&)> cb)
{
    onResponseReturnStr_ = cb;
}

bool CallbackObject::GetOnResponseReturnStr() const
{
    return false;
}

std::string CallbackObject::InvokeOnResponseReturnStr()
{
    std::string result;
    if (onResponseReturnStr_) {
        result = onResponseReturnStr_("hello AKI");
    }
    return result;
}

JSBIND_CLASS(CallbackObject)
{
    JSBIND_CONSTRUCTOR<>();
    JSBIND_FIELD("onInvoke", GetOnInvoke, SetOnInvoke);
    JSBIND_FIELD("onResponse", GetOnResponse, SetOnResponse);
    JSBIND_FIELD("onResponseReturnStr", GetOnResponseReturnStr, SetOnResponseReturnStr);
    JSBIND_METHOD(InvokeOnInvoke);
    JSBIND_METHOD(InvokeOnResponse);
    JSBIND_METHOD(InvokeOnResponseReturnStr);
}