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


/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
void PassingArrayBufferReturnVoid(aki::ArrayBuffer origin) {

    int8_t* data = reinterpret_cast<int8_t *>(origin.GetData());
    data[4] = 4;
    data[5] = 5;
    data[6] = 6;
    data[7] = 7;

    return;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingArrayBufferReturnArrayBuffer(aki::ArrayBuffer origin) {
    aki::ArrayBuffer buff(origin.GetData(), origin.GetCount());
    uint8_t* data = buff.GetData();
    data[4] = 4;
    data[5] = 5;
    data[6] = 6;
    data[7] = 7;

    return buff;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingArrayBufferReturnInt8Array(aki::ArrayBuffer origin) {
    aki::ArrayBuffer buff(origin.GetData(), origin.GetCount(), aki::ArrayBuffer::INT8);
    int8_t* data = reinterpret_cast<int8_t*>(buff.GetData());
    data[4] = -4;
    data[5] = -5;
    data[6] = -6;
    data[7] = -7;

    return buff;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingArrayBufferReturnInt16Array(aki::ArrayBuffer origin) {
    aki::ArrayBuffer buff(origin.GetData(), origin.GetCount(), aki::ArrayBuffer::INT16);
    int16_t* data = reinterpret_cast<int16_t*>(buff.GetData());
    data[4] = -40;
    data[5] = -50;
    data[6] = -60;
    data[7] = -70;

    return buff;
}

aki::ArrayBuffer AsyncTaskArrayBufferReturnArrayBuffer(aki::ArrayBuffer input) {
    aki::ArrayBuffer arrayBuffer(input.GetData(), input.GetLength());
    return arrayBuffer;
}

aki::ArrayBuffer AsyncTaskReturnArrayBufferWithCommit() {
    uint8_t temp[4] = {10, 20, 30, 40};
    aki::ArrayBuffer arrayBuffer(temp, 4);
    arrayBuffer.Commit();
    return arrayBuffer;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(PassingArrayBufferReturnVoid);
    JSBIND_FUNCTION(PassingArrayBufferReturnArrayBuffer);
    JSBIND_FUNCTION(PassingArrayBufferReturnInt8Array);
    JSBIND_FUNCTION(PassingArrayBufferReturnInt16Array);
    JSBIND_PFUNCTION(AsyncTaskArrayBufferReturnArrayBuffer, "asyncTaskArrayBufferReturnArrayBuffer");
    JSBIND_PFUNCTION(AsyncTaskReturnArrayBufferWithCommit, "asyncTaskReturnArrayBufferWithCommit");
}

struct ArrayBufferHandler {
    aki::ArrayBuffer buf;
};

JSBIND_CLASS(ArrayBufferHandler) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_PROPERTY(buf);
}

JSBIND_ADDON(arraybuffer2native)