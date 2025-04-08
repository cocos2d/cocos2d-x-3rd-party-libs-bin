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

uint8_t PassingUint8ReturnUint8(uint8_t num) {
    return num;
}

int8_t PassingInt8ReturnInt8(int8_t num) {
    return num;
}

uint16_t PassingUint16ReturnUint16(uint16_t num) {
    return num;
}

int16_t PassingInt16ReturnInt16(int16_t num) {
    return num;
}

short PassingShortReturnShort(short num) {
    return num;
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(PassingUint8ReturnUint8, "passingUint8ReturnUint8");
    JSBIND_FUNCTION(PassingInt8ReturnInt8, "passingInt8ReturnInt8");
    JSBIND_FUNCTION(PassingUint16ReturnUint16, "passingUint16ReturnUint16");
    JSBIND_FUNCTION(PassingInt16ReturnInt16, "passingInt16ReturnInt16");
    JSBIND_FUNCTION(PassingShortReturnShort, "passingShortReturnShort");
}