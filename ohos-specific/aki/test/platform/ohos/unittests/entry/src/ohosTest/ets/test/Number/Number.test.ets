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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import libaki from "libunittest.so"

export default function numberTest() {
  describe('NumberTest', ()=> {
    it('001_passingUint8ReturnUint8', 0, ()=> {
      let result = libaki.passingUint8ReturnUint8(0);
      expect(result).assertEqual(0);
      result = libaki.passingUint8ReturnUint8(255);
      expect(result).assertEqual(255);
    })
    it('002_passingInt8ReturnInt8', 0, ()=> {
      let result = libaki.passingInt8ReturnInt8(-128);
      expect(result).assertEqual(-128);
      result = libaki.passingInt8ReturnInt8(127);
      expect(result).assertEqual(127);
    })
    it('003_passingUint16ReturnUint16', 0, ()=> {
      let result = libaki.passingUint16ReturnUint16(0);
      expect(result).assertEqual(0);
      result = libaki.passingUint16ReturnUint16(65535);
      expect(result).assertEqual(65535);
    })
    it('004_passingInt16ReturnInt16', 0, ()=> {
      let result = libaki.passingInt16ReturnInt16(-32768);
      expect(result).assertEqual(-32768);
      result = libaki.passingInt16ReturnInt16(32767);
      expect(result).assertEqual(32767);
    })
    it('passingShortReturnShort', 0, ()=> {
      let result = libaki.passingShortReturnShort(-32768);
      expect(result).assertEqual(-32768);
      result = libaki.passingShortReturnShort(32767);
      expect(result).assertEqual(32767);
    })
  })
}