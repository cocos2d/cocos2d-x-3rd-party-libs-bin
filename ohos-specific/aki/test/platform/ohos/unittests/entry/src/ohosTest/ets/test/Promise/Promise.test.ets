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

export default function promiseTest() {
  describe('PromiseTest', ()=> {
    it('ReturnPromiseResolveImmediately', 0, async (done:Function)=> {
      let promise = libaki.ReturnPromiseResolveImmediately();
      promise.then(ret => {
        expect(ret).assertEqual('aki promise');
        done();
      })
    })
    it('ReturnPromiseResolveLater', 0, async (done:Function)=> {
      libaki.JSBind.initTaskRunner('main');
      let promise = libaki.ReturnPromiseResolveLater();
      promise.then(ret => {
        expect(ret).assertEqual('aki promise');
        done();
      })
    })
  })
}