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
aki::ArrayBuffer PassingArrayBufferReturnArrayBuffer(aki::ArrayBuffer arrayBuffer) {
    const std::array<int8_t, 8> certificate = {-1, 0, 0, 0, 0, 0, 0, 1};

    if (arrayBuffer.GetLength() != certificate.size()) {
        return arrayBuffer;
    }
    int8_t* data = reinterpret_cast<int8_t *>(arrayBuffer.GetData());
    data[7] = 1;

    // JS 侧下发的arrayBuffer.typed()类型为ArrayBuffer，返回时也为ArrayBuffer
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingInt8ArrayReturnInt8Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<int8_t, 9> certificate1 = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    const std::array<int8_t, 9> certificate2 = {4, 3, 2, 1, 0, -1, -2, -3, -4};

    if (arrayBuffer.GetLength() != certificate1.size()) {
        return arrayBuffer;
    }

    int8_t* data = reinterpret_cast<int8_t *>(arrayBuffer.GetData());
    for(int i = 0; i < arrayBuffer.GetLength(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 Int8Array，返回时也为 Int8Array
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingUint8ArrayReturnUint8Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<int8_t, 10> certificate1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::array<uint8_t, 10> certificate2 = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    if (arrayBuffer.GetLength() != certificate1.size()) {
        return arrayBuffer;
    }

    uint8_t* data = reinterpret_cast<uint8_t *>(arrayBuffer.GetData());
    for(int i = 0; i < arrayBuffer.GetLength(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 Uint8Array，返回时也为 Uint8Array
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingInt16ArrayReturnInt16Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<int16_t, 9> certificate1 = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    const std::array<int16_t, 9> certificate2 = {4, 3, 2, 1, 0, -1, -2, -3, -4};

    if ((arrayBuffer.GetLength() / sizeof(int16_t)) != certificate1.size()) {
        return arrayBuffer;
    }

    int16_t* data = reinterpret_cast<int16_t *>(arrayBuffer.GetData());
    for(int i = 0; i < certificate1.size(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 Int16Array，返回时也为 Int16Array
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingUint16ArrayReturnUint16Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<uint16_t, 10> certificate1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::array<uint16_t, 10> certificate2 = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    if ((arrayBuffer.GetLength() / sizeof(uint16_t)) != certificate1.size()) {
        return arrayBuffer;
    }

    uint16_t* data = reinterpret_cast<uint16_t *>(arrayBuffer.GetData());
    for(int i = 0; i < certificate1.size(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 Uint16Array，返回时也为 Uint16Array
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingInt32ArrayReturnInt32Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<int32_t, 9> certificate1 = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    const std::array<int32_t, 9> certificate2 = {4, 3, 2, 1, 0, -1, -2, -3, -4};

    if ((arrayBuffer.GetLength() / sizeof(int32_t)) != certificate1.size()) {
        return arrayBuffer;
    }

    int32_t* data = reinterpret_cast<int32_t *>(arrayBuffer.GetData());
    for(int i = 0; i < certificate1.size(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 Int32Array，返回时也为 Int32Array
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingUint32ArrayReturnUint32Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<uint32_t, 10> certificate1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::array<uint32_t, 10> certificate2 = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    if ((arrayBuffer.GetLength() / sizeof(uint32_t)) != certificate1.size()) {
        return arrayBuffer;
    }

    uint32_t* data = reinterpret_cast<uint32_t *>(arrayBuffer.GetData());
    for(int i = 0; i < certificate1.size(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 Uint32Array，返回时也为 Uint32Array
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingBigInt64ArrayReturnBigInt64Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<int64_t, 9> certificate1 = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    const std::array<int64_t, 9> certificate2 = {4, 3, 2, 1, 0, -1, -2, -3, -4};

    if ((arrayBuffer.GetLength() / sizeof(int64_t)) != certificate1.size()) {
        return arrayBuffer;
    }

    int64_t* data = reinterpret_cast<int64_t *>(arrayBuffer.GetData());
    for(int i = 0; i < certificate1.size(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 BigInt64Array，返回时也为 BigInt64Array
    return arrayBuffer;
}

/**
 * @brief: 全局函数类型为：aki::ArrayBuffer (*)(aki::ArrayBuffer)
 * @result: passed
 */
aki::ArrayBuffer PassingBigUint64ArrayReturnBigUint64Array(aki::ArrayBuffer arrayBuffer) {
    const std::array<uint64_t, 10> certificate1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::array<uint64_t, 10> certificate2 = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    if ((arrayBuffer.GetLength() / sizeof(uint64_t)) != certificate1.size()) {
        return arrayBuffer;
    }

    uint64_t* data = reinterpret_cast<uint64_t *>(arrayBuffer.GetData());
    for(int i = 0; i < certificate1.size(); i++) {
        if (data[i] != certificate1[i]) {
            return arrayBuffer;
        }
        data[i] = certificate2[i];
    }

    // JS 侧下发的arrayBuffer.typed()类型为 BigUint64Array，返回时也为 BigUint64Array
    return arrayBuffer;
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
    JSBIND_FUNCTION(PassingArrayBufferReturnArrayBuffer, "passingArrayBufferReturnArrayBuffer");
    JSBIND_FUNCTION(PassingInt8ArrayReturnInt8Array, "passingInt8ArrayReturnInt8Array");
    JSBIND_FUNCTION(PassingUint8ArrayReturnUint8Array, "passingUint8ArrayReturnUint8Array");
    JSBIND_FUNCTION(PassingInt16ArrayReturnInt16Array, "passingInt16ArrayReturnInt16Array");
    JSBIND_FUNCTION(PassingUint16ArrayReturnUint16Array, "passingUint16ArrayReturnUint16Array");
    JSBIND_FUNCTION(PassingInt32ArrayReturnInt32Array, "passingInt32ArrayReturnInt32Array");
    JSBIND_FUNCTION(PassingUint32ArrayReturnUint32Array, "passingUint32ArrayReturnUint32Array");
    JSBIND_FUNCTION(PassingBigInt64ArrayReturnBigInt64Array, "passingBigInt64ArrayReturnBigInt64Array");
    JSBIND_FUNCTION(PassingBigUint64ArrayReturnBigUint64Array, "passingBigUint64ArrayReturnBigUint64Array");
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
