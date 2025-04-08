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
import testNapi from "libunittest.so"

export default function overloaderTest() {
  describe('OverloaderTest', ()=> {
    it('001_OverloaderTest_bool', 0, ()=> {
      let obj = new testNapi.OverloaderTest(false);
      expect(obj.value1).assertEqual(false);
    })
    it('002_OverloaderTest_bool_int', 0, ()=> {
      let obj = new testNapi.OverloaderTest(false, 666);
      expect(obj.value1).assertEqual(false);
      expect(obj.value2).assertEqual(666);
    })
    it('003_OverloaderTest_bool_int_string', 0, ()=> {
      let obj = new testNapi.OverloaderTest(false, 666, "guozhenxiong");
      expect(obj.value1).assertEqual(false);
      expect(obj.value2).assertEqual(666);
      expect(obj.value3).assertEqual("guozhenxiong");
    })
  })
}