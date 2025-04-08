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
#include "aki/jsbind.h"
#include <hilog/log.h>

/**
 * @brief: 全局函数类型为：bool (*)()
 * @result: passed
 */
bool PassingNoneReturnBool() {
    return true;
}

/**
 * @brief: 全局函数类型为：bool (*)(bool)
 * @result: passed
 */
bool PassingBoolReturnBool(bool value) {
    return value;
}

/**
 * @brief: 全局函数类型为：int32_t (*)(int32_t)
 * @result: passed
 */
int32_t PassingInt32ReturnInt32(int32_t value) {
    return value;
}

/**
 * @brief: 全局函数类型为：uint32_t (*)(uint32_t)
 * @result: failed
 */
uint32_t PassingUint32ReturnUint32(uint32_t value) {
    return value;
}

/**
 * @brief: 全局函数类型为：int64_t (*)(int64_t)
 * @result: failed
 */
int64_t PassingInt64ReturnInt64(int64_t value) {
    return value;
}

/**
 * @brief: 全局函数类型为：std::string (*)(std::string)
 * @result: passed
 */
std::string PassingStringReturnString(std::string value) {
    return value;
}

/**
 * @brief: 全局函数类型为：std::string (*)(std::string&)
 * @result: passed
 */
//std::string PassingStringRefReturnString(std::string& value) {
//    return value;
//}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string&)
 * @result: passed
 */
std::string PassingConstStringRefReturnString(const std::string& value) {
    return value;
}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string& X2)
 * @result: passed
 */
std::string PassingConstStringRef2ReturnString(const std::string& value1, const std::string& value2) {
    return value1 + value2;
}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string& X3)
 * @result: passed
 */
std::string PassingConstStringRef3ReturnString(const std::string& value1, const std::string& value2, const std::string& value3) {
    return value1 + value2 + value3;
}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string& X4)
 * @result: passed
 */
std::string PassingConstStringRef4ReturnString(const std::string& value1, 
                                               const std::string& value2, 
                                               const std::string& value3, 
                                               const std::string& value4) {
    return value1 + value2 + value3 + value4;
}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string& X5)
 * @result: passed
 */
std::string PassingConstStringRef5ReturnString(const std::string& value1, 
                                               const std::string& value2, 
                                               const std::string& value3, 
                                               const std::string& value4, 
                                               const std::string& value5) {
    return value1 + value2 + value3 + value4 + value5;
}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string& X6)
 * @result: passed
 */
std::string PassingConstStringRef6ReturnString(const std::string& value1, 
                                               const std::string& value2, 
                                               const std::string& value3, 
                                               const std::string& value4, 
                                               const std::string& value5, 
                                               const std::string& value6) {
    return value1 + value2 + value3 + value4 + value5 + value6;
}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string& X7)
 * @result: passed
 */
std::string PassingConstStringRef7ReturnString(const std::string& value1, 
                                               const std::string& value2, 
                                               const std::string& value3, 
                                               const std::string& value4, 
                                               const std::string& value5, 
                                               const std::string& value6, 
                                               const std::string& value7) {
    return value1 + value2 + value3 + value4 + value5 + value6 + value7;
}

/**
 * @brief: 全局函数类型为：std::string (*)(const std::string& X8)
 * @result: passed
 */
std::string PassingConstStringRef8ReturnString(const std::string& value1, 
                                               const std::string& value2, 
                                               const std::string& value3, 
                                               const std::string& value4, 
                                               const std::string& value5, 
                                               const std::string& value6, 
                                               const std::string& value7, 
                                               const std::string& value8) {
    return value1 + value2 + value3 + value4 + value5 + value6 + value7 + value8;
}

/**
 * @brief: 全局函数类型为：const char* (*)(const char*)
 * @result: passed
 */
const char* PassingConstCStrPtrReturnConstCStrPtr(const char* value) {
    return value;
}

/**
 * @brief: 全局函数类型为：const char* (*)(char*)
 * @result: passed
 */
const char* PassingCStrPtrReturnConstCStrPtr(char* value) {
    return value;
}

/**
 * @brief: 全局函数类型为：char* (*)(char*)
 * @result: passed
 */
char* PassingCStrPtrReturnCStrPtr(char* value) {
    return value;
}

/**
 * @brief: 全局函数类型为：double (*)(double)
 * @result: passed
 */
double PassingDoubleReturnDouble(double value) {
    return value+1;
}

/**
 * @brief: 全局函数类型为：float (*)(float)
 * @result: passed
 */
float PassingFloatReturnFloat(float value) {
    return value+1.1;
}

bool PassingVectorIntReturnBool(std::vector<int> vec)
{
    std::vector<int> verify = {0, 1, 2, 3};
    return vec == verify;
}

std::vector<int> PassingVectorIntReturnVectorInt(std::vector<int> vec) {
    vec.push_back(4);
    return vec;
}

/**
 * @brief: 全局函数类型为：std::vector<uint8_t> (*)(std::vector<uint8_t>)
 * @result: passed
 */
std::vector<uint8_t> PassingVectorUint8ReturnVectorUint8(std::vector<uint8_t> vec) {
    vec.push_back(4);
    return vec;
}

/**
 * @brief: 全局函数类型为：std::vector<bool> (*)(std::vector<bool>)
 * @result: passed
 */
std::vector<bool> PassingVectorBoolReturnVectorBool(std::vector<bool> vec) {
    vec.push_back(true);
    return vec;
}

/**
 * @brief: 全局函数类型为：std::vector<float> (*)(std::vector<float>)
 * @result: passed
 */
std::vector<float> PassingVectorFloatReturnVectorFloat(std::vector<float> vec) {
    vec.push_back(4.4);
    return vec;
}

/**
 * @brief: 全局函数类型为：bool (*)(std::array<int 4>)
 * @result: passed
 */
bool PassingArrayIntReturnBool(std::array<int, 4> array) {
    std::array<int, 4> verify = {0, 1, 2, 3};
    return array == verify;
}

/**
 * @brief: 全局函数类型为：(std::array<int, 5> (*)(std::array<int, 4>)
 * @result: passed
 */
std::array<int, 5> PassingArrayIntReturnArrayInt(std::array<int, 4> array) {
    std::array<int, 5> result;
    for (int i = 0; i < 4; i++) {
        result[i] = array[i];
    }
    result[4] = 4;
    return result;

}

/**
 * @brief: 全局函数类型为：(std::array<std::string, 5> (*)(std::array<std::string, 4>)
 * @result: passed
 */
std::array<std::string, 5> PassingArrayStrReturnArrayStr(std::array<std::string, 4> array) {
    std::array<std::string, 5> result;
    for (int i = 0; i < 4; i++) {
        result[i] = array[i];
    }
    result[4] = "4";
    return result;

}

int P_PassingIntReturnInt(int value)
{
    AKI_DLOG(DEBUG) << "should be non-js-thread";
    return value;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(PassingDoubleReturnDouble);
    JSBIND_FUNCTION(PassingNoneReturnBool);
    JSBIND_FUNCTION(PassingBoolReturnBool);
    JSBIND_FUNCTION(PassingInt32ReturnInt32);
    JSBIND_FUNCTION(PassingUint32ReturnUint32);
    JSBIND_FUNCTION(PassingInt64ReturnInt64);
    JSBIND_FUNCTION(PassingStringReturnString);
    // JSBIND_FUNCTION(PassingStringRefReturnString);
    JSBIND_FUNCTION(PassingConstStringRefReturnString);
    JSBIND_FUNCTION(PassingConstStringRef2ReturnString);
    JSBIND_FUNCTION(PassingConstStringRef3ReturnString);
    JSBIND_FUNCTION(PassingConstStringRef4ReturnString);
    JSBIND_FUNCTION(PassingConstStringRef5ReturnString);
    JSBIND_FUNCTION(PassingConstStringRef6ReturnString);
    JSBIND_FUNCTION(PassingConstStringRef7ReturnString);
    JSBIND_FUNCTION(PassingConstStringRef8ReturnString);
    JSBIND_FUNCTION(PassingConstCStrPtrReturnConstCStrPtr);
    JSBIND_FUNCTION(PassingCStrPtrReturnConstCStrPtr);
    JSBIND_FUNCTION(PassingCStrPtrReturnCStrPtr);
    JSBIND_FUNCTION(PassingFloatReturnFloat);
    JSBIND_FUNCTION(PassingVectorIntReturnBool);
    JSBIND_FUNCTION(PassingVectorIntReturnVectorInt);
    JSBIND_FUNCTION(PassingVectorUint8ReturnVectorUint8);
    JSBIND_FUNCTION(PassingVectorBoolReturnVectorBool);
    JSBIND_FUNCTION(PassingVectorFloatReturnVectorFloat);
    JSBIND_FUNCTION(PassingArrayIntReturnBool, "passingArrayIntReturnBool");
    JSBIND_FUNCTION(PassingArrayIntReturnArrayInt, "passingArrayIntReturnArrayInt");
    JSBIND_FUNCTION(PassingArrayStrReturnArrayStr, "passingArrayStrReturnArrayStr");
    JSBIND_PFUNCTION(P_PassingIntReturnInt);
}

JSBIND_ADDON(unittest)