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

export default function reference4ObjectTest() {
  describe('Reference4ObjectTest', ()=> {
    it('001_UseReferenceOnFunction', 0, ()=> {
      let ref = new libaki.Reference(0);
      expect(ref.count).assertEqual(0);
      libaki.GrowUpByReference(ref);
      expect(ref.count).assertEqual(1);
      libaki.GrowUpByReference(ref);
      expect(ref.count).assertEqual(2);
      libaki.GrowUpByReference(ref);
      expect(ref.count).assertEqual(3);
    })
    it('002_UsePointerOnFunction', 0, ()=> {
      let ref = new libaki.Reference(0);
      expect(ref.count).assertEqual(0);
      libaki.GrowUpByPointer(ref);
      expect(ref.count).assertEqual(1);
      libaki.GrowUpByPointer(ref);
      expect(ref.count).assertEqual(2);
      libaki.GrowUpByPointer(ref);
      expect(ref.count).assertEqual(3);
    })
    it('003_UseReferenceOnMethod', 0, ()=> {
      let ref1 = new libaki.Reference(1);
      expect(ref1.count).assertEqual(1);
      let ref2 = new libaki.Reference(-1);
      expect(ref2.count).assertEqual(-1);
      ref2.ChangeByReference(ref1);
      expect(ref1.count).assertEqual(-1);
      expect(ref2.count).assertEqual(1);
    })
    it('004_UsePointerOnMethod', 0, ()=> {
      let ref1 = new libaki.Reference(1);
      expect(ref1.count).assertEqual(1);
      let ref2 = new libaki.Reference(-1);
      expect(ref2.count).assertEqual(-1);
      ref2.ChangeByPointer(ref1);
      expect(ref1.count).assertEqual(-1);
      expect(ref2.count).assertEqual(1);
    })
  })
}