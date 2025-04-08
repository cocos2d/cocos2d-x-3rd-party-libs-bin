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

#ifndef AKI_ARRAY_BUFFER_H
#define AKI_ARRAY_BUFFER_H

#include <cstdint>
#include <vector>
#include <node_api.h>
#include "aki/config.h"
#include "aki/persistent/persistent.h"

namespace aki {
class AKI_EXPORT ArrayBuffer {
public:
    enum Typed: uint8_t {
        INT8,       // Int8Array
        UINT8,      // Uint8Array
        UINT8_C,    // Uint8ClampedArray
        INT16,      // Int16Array
        UINT16,     // Uint16Array
        INT32,      // Int32Array
        UINT32,     // Uint32Array
        FLOAT32,    // Float32Array
        FLOAT64,    // Float64Array
        BIG_INT64,  // BigInt64Array
        BIG_UINT64, // BigUint64Array
        BUFF,       // ArrayBuffer
    };

    ArrayBuffer() = default;

    ArrayBuffer(uint8_t* ptr, size_t len, Typed typed = BUFF);

    ArrayBuffer(napi_value arrayBuffer, uint8_t* ptr, size_t len, Typed typed = BUFF);

    ~ArrayBuffer() = default;

    void Commit();

    // 缓冲区数据地址
    inline uint8_t* GetData() { return data(); }

    // 缓冲区数据大小/byte
    inline size_t GetLength() const { return len_; }

    // 类型化
    inline Typed GetTyped() const { return typed_; }

    inline size_t GetCount() const
    {
        size_t count = 0;
        switch (typed_) {
            case INT8:
            case UINT8:
            case UINT8_C:
                count = len_;
                break;
            case INT16:
            case UINT16:
                count = len_ / sizeof (uint16_t);
                break;
            case INT32:
            case UINT32:
                count = len_ / sizeof (uint32_t);
                break;
            case FLOAT32:
                count = len_ / sizeof (float);
                break;
            case FLOAT64:
                count = len_ / sizeof (double);
                break;
            case BIG_INT64:
            case BIG_UINT64:
                count = len_ / sizeof (uint64_t);
                break;
            default:
                count = len_;
                break;
        }
        return count;
    }

    napi_value GetHandle();

private:
    inline uint8_t* data() { return staging_.empty() ? data_ : staging_.data(); }

    uint8_t* data_ = nullptr;

    size_t len_ = 0;

    std::vector<uint8_t> staging_;

    Typed typed_ = BUFF;

    Persistent persistent_;
};
} // namespace aki

#endif //AKI_ARRAY_BUFFER_H
