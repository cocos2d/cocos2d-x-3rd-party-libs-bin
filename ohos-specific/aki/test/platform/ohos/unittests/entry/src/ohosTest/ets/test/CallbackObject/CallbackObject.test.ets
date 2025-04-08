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

export default function callbackObjectTest() {
  describe('callbackObjectTest', ()=> {
    it('001_callbackObjectTest_Invoke', 0, async (done:Function)=> {
      let callback = new testNapi.CallbackObject();
      callback.onInvoke =  () => {
        done();
      };
      testNapi.CallbackObject.InvokeOnInvoke(callback);
    })
    it('002_callbackObjectTest_InvokeOnResponse', 0, async (done:Function)=> {
      let callback = new testNapi.CallbackObject();
      callback.onResponse =  (data) => {
        expect(data).assertEqual("hello AKI");
        done();
      };
      testNapi.CallbackObject.InvokeOnResponse(callback);
    })
    it('003_callbackObjectTest_InvokeOnResponseReturnStr', 0, async (done:Function)=> {
      let callback = new testNapi.CallbackObject();
      callback.onResponseReturnStr =  (data) => {
        expect(data).assertEqual("hello AKI");
        return "003_callbackObjectTest_InvokeOnResponseReturnStr"
      };

      // 异步任务调用模式
      let result = callback.InvokeOnResponseReturnStr();
      expect(result).assertEqual("003_callbackObjectTest_InvokeOnResponseReturnStr");
      done();
    })
  })
}