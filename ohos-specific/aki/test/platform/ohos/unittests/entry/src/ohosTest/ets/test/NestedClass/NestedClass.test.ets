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

export default function nestedClassTest() {
  describe('NestedClassTest', ()=> {
    it('001_NestedOne', 0, ()=> {
      let obj = new testNapi.NestedOne();
      expect(obj.GetNested()).assertEqual("One");
    })
    it('002_NestedTwo', 0, ()=> {
      let obj = new testNapi.NestedTwo();
      expect(obj.GetNested()).assertEqual("Two::One");
    })
    it('002_NestedThree', 0, ()=> {
      let obj = new testNapi.NestedThree();
      expect(obj.GetNested()).assertEqual("Three::Two::One");
    })
  })
}