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

export default function jsonObjectTest() {
  describe('JsonObjectTest', ()=> {
    it('001_passingVoidReturnMapLong', 0, ()=> {
      let result = libaki.passingVoidReturnMapLong();
      expect(JSON.stringify(result)).assertEqual('{"Monday":1,"Tuesday":2,"Wednesday":3}');
    })
    it('002_passingMapLongReturnMapLong', 0, ()=> {
      let result = libaki.passingMapLongReturnMapLong({
        'Monday': 1,
        'Tuesday': 2,
        'Wednesday': 3});
      expect(JSON.stringify(result)).assertEqual('{"Monday":1,"Thursday":4,"Tuesday":2,"Wednesday":3}');
    })
    it('003_JsonObjectHandle.passingVoidReturnMapLong', 0, ()=> {
      let  handle = new libaki.JsonObjectHandle();
      let result = handle.passingVoidReturnMapLong();
      expect(JSON.stringify(result)).assertEqual('{"Monday":1,"Tuesday":2,"Wednesday":3}');
    })
    it('004_JsonObjectHandle.passingMapLongReturnMapLong', 0, ()=> {
      let handle = new libaki.JsonObjectHandle();
      let result = handle.passingMapLongReturnMapLong({
        'Monday': 1,
        'Tuesday': 2,
        'Wednesday': 3});
      expect(JSON.stringify(result)).assertEqual('{"Monday":1,"Thursday":4,"Tuesday":2,"Wednesday":3}');
    })
  })
}