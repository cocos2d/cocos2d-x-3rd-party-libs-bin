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

const enum TypePlaceHolder {
    FLAG = 1,
    NUM = FLAG,
    STR = NUM << 3,
    REF = STR << 3,
    TYPE = REF << 3
}

export const enum TypeFlag {
    NONE            = 0,

    NUM_MASK        = TypePlaceHolder.NUM * 0B1111,
    IS_UNSIGNED     = TypePlaceHolder.NUM << 0,
    IS_CHAR         = TypePlaceHolder.NUM << 1,
    IS_FLOAT        = TypePlaceHolder.NUM << 2,

    STR_MASK        = TypePlaceHolder.STR * 0B111,
    IS_C_STRING     = TypePlaceHolder.STR << 0,
    IS_STD_STRING   = TypePlaceHolder.STR << 1,

    REF_MASK        = TypePlaceHolder.REF * 0B111,
    IS_POINTER      = TypePlaceHolder.REF << 0,
    IS_SHARED_PTR   = TypePlaceHolder.REF << 1,

    TYPE_MASK       = TypePlaceHolder.TYPE * 0B11111111,
    IS_VOID         = TypePlaceHolder.TYPE << 0,
    IS_BOOLEAN      = TypePlaceHolder.TYPE << 1,
    IS_ARITHMETIC   = TypePlaceHolder.TYPE << 2,
    IS_STRING       = TypePlaceHolder.TYPE << 3,
    IS_CLASS        = TypePlaceHolder.TYPE << 4,
    IS_ARRAY        = TypePlaceHolder.TYPE << 5,
    IS_FUNCTION     = TypePlaceHolder.TYPE << 6,
    IS_OTHER        = TypePlaceHolder.TYPE << 7
}
