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

#include "aki/jsbind.h"

namespace {
bool PassingValueAsBool(aki::Value value)
{
    return value.As<bool>();
}

aki::Value PassingValueAsBoolReturnValue(aki::Value value)
{
    return aki::Value(value.As<bool>());
}

uint8_t PassingValueAsUint8(aki::Value value)
{
    return value.As<uint8_t>();
}

int8_t PassingValueAsInt8(aki::Value value)
{
    return value.As<int8_t>();
}

uint16_t PassingValueAsUint16(aki::Value value)
{
    return value.As<uint16_t>();
}

int16_t PassingValueAsInt16(aki::Value value)
{
    return value.As<int16_t>();
}

int PassingValueAsInt(aki::Value value)
{
    return value.As<int>();
}

aki::Value PassingValueAsIntReturnValue(aki::Value value)
{
    return aki::Value(value.As<int>());
}

int64_t PassingValueAsInt64(aki::Value value)
{
    return value.As<int64_t>();
}

float PassingValueAsFloat(aki::Value value)
{
    return value.As<float>();
}

double PassingValueAsDouble(aki::Value value)
{
    return value.As<double>();
}

std::string PassingValueAsString(aki::Value value)
{
    return value.As<std::string>();
}

aki::Value PassingValueAsStringReturnValue(aki::Value value)
{
    return aki::Value(value.As<std::string>());
}

aki::Value PassingArrayValueReturnValue(aki::Value value)
{
    return value[0];
}

aki::Value PassingArrayValueReturnArrayValue(aki::Value value)
{
    value.CallMethod("push", "jsbind");
    return value;
}

void PassingArrayValueThenSetValue(aki::Value value)
{
    value.Set(0, std::string("jsbind"));
    return;
}

std::string PassingValueAsFunction(aki::Value value)
{
    return value("aki value from c++").As<std::string>();
}

aki::Value PassingValueAsJsonObject(aki::Value value)
{
    aki::Value val = aki::Value::NewObject();
    val.Set("name", value["name"].As<std::string>());
    return val;
}

aki::Value PassingValueCheckIsUndefined(aki::Value value)
{
    return aki::Value(value.IsUndefined());
}

aki::Value PassingValueCheckIsNull(aki::Value value)
{
    return aki::Value(value.IsNull());
}

aki::Value PassingValueCheckIsBool(aki::Value value)
{
    return aki::Value(value.IsBool());
}

aki::Value PassingValueCheckIsNumber(aki::Value value)
{
    return aki::Value(value.IsNumber());
}

aki::Value PassingValueCheckIsString(aki::Value value)
{
    return aki::Value(value.IsString());
}

aki::Value PassingValueCheckIsArray(aki::Value value)
{
    return aki::Value(value.IsArray());
}

aki::Value PassingValueCheckIsFunction(aki::Value value)
{
    return aki::Value(value.IsFunction());
}

std::string ValueFromGlobalAsString()
{
    AKI_LOG(INFO) << "123";
    aki::Value value = aki::Value::FromGlobal("akiString");
    return value.As<std::string>();
}

void FromGlobalBundleManager()
{
    /* 要求在ArkTS侧执行如下代码：
     * import bundleManager from '@ohos.bundle.bundleManager';
     * globalThis.bundleManager = bundleManager;
     */
     aki::Value bundleManager = aki::Value::FromGlobal("bundleManager");

    /* 如下 C++ 代码等同于 JS 代码:
     * let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_DEFAULT;
     * bundleManager.getBundleInfoForSelf(bundleFlags).then((data) => {
     *   console.log('getBundleInfoForSelf successfully. Data:', JSON.stringify(data));
     * })
     */
    std::function<void(aki::Value)> thenFunc = [](aki::Value data) {
        AKI_LOG(INFO) << aki::Value::FromGlobal("JSON")["stringify"](data).As<std::string>();
    };
    int bundleFlags = bundleManager["BundleFlag"]["GET_BUNDLE_INFO_DEFAULT"].As<int>();
    bundleManager["getBundleInfoForSelf"](bundleFlags).CallMethod("then", thenFunc);
}

aki::Value FromGlobalJSONStringify(aki::Value obj)
{
    aki::Value json = aki::Value::FromGlobal("JSON");
    return json["stringify"](obj);
}

aki::Value FromGlobalJSONParse(aki::Value obj)
{
    aki::Value json = aki::Value::FromGlobal("JSON");
    return json["parse"](obj);
}
}

JSBIND_GLOBAL()
{
    JSBIND_FUNCTION(PassingValueAsBool);
    JSBIND_FUNCTION(PassingValueAsBoolReturnValue);
    JSBIND_FUNCTION(PassingValueAsUint8);
    JSBIND_FUNCTION(PassingValueAsInt8);
    JSBIND_FUNCTION(PassingValueAsUint16);
    JSBIND_FUNCTION(PassingValueAsInt16);
    JSBIND_FUNCTION(PassingValueAsInt);
    JSBIND_FUNCTION(PassingValueAsIntReturnValue);
    JSBIND_FUNCTION(PassingValueAsInt64);
    JSBIND_FUNCTION(PassingValueAsFloat);
    JSBIND_FUNCTION(PassingValueAsDouble);
    JSBIND_FUNCTION(PassingValueAsString);
    JSBIND_FUNCTION(PassingValueAsStringReturnValue);
    JSBIND_FUNCTION(PassingArrayValueReturnValue);
    JSBIND_FUNCTION(PassingArrayValueReturnArrayValue);
    JSBIND_FUNCTION(PassingArrayValueThenSetValue);
    JSBIND_FUNCTION(PassingValueAsFunction);
    JSBIND_FUNCTION(PassingValueAsJsonObject);
    JSBIND_FUNCTION(PassingValueCheckIsUndefined);
    JSBIND_FUNCTION(PassingValueCheckIsNull);
    JSBIND_FUNCTION(PassingValueCheckIsBool);
    JSBIND_FUNCTION(PassingValueCheckIsNumber);
    JSBIND_FUNCTION(PassingValueCheckIsString);
    JSBIND_FUNCTION(PassingValueCheckIsArray);
    JSBIND_FUNCTION(PassingValueCheckIsFunction);
    JSBIND_FUNCTION(ValueFromGlobalAsString);
    JSBIND_FUNCTION(FromGlobalBundleManager);
    JSBIND_FUNCTION(FromGlobalJSONStringify);
    JSBIND_FUNCTION(FromGlobalJSONParse);
}

struct AkiValueData {
    AkiValueData() = default;
    void SetValueFromNative()
    {
        value.CallMethod("push", "c++");
    }
    aki::Value value;
};

JSBIND_CLASS(AkiValueData) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_METHOD(SetValueFromNative);
    JSBIND_PROPERTY(value);
}