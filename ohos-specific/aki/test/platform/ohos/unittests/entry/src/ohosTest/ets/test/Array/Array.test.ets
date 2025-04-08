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

export default function arrayTest() {
  describe('ArrayTest', ()=> {
    it('001_PassingVoidReturnVectorLong', 0, ()=> {
      let result = libaki.passingVoidReturnVectorLong();
      expect(result.toString()).assertEqual([1, 2, 3].toString());
    })
    it('001_passingVectorLongReturnVectorLong', 0, ()=> {
      let array = [1, 2, 3];
      let result = libaki.passingVectorLongReturnVectorLong(array);
      expect(result.toString()).assertEqual([1, 2, 3, 4].toString());
    })
    it('002_VectorHandle.PassingVoidReturnVectorLong', 0, ()=> {
      let handle = new libaki.VectorHandle();
      let result = handle.passingVoidReturnVectorLong();
      expect(result.toString()).assertEqual([1, 2, 3].toString());
    })
    it('002_VectorHandle.passingVectorLongReturnVectorLong', 0, ()=> {
      let array = [1, 2, 3];
      let handle = new libaki.VectorHandle();
      let result = handle.passingVectorLongReturnVectorLong(array);
      expect(result.toString()).assertEqual([1, 2, 3, 4].toString());
    })
  })
}