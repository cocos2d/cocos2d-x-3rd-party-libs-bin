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
import jsBind from "libunittest.so"

export default function callbackTest() {
  describe('CallbackTest', () => {
    it('001_Callback_For_Invoke', 0, async (done:Function)=> {
      jsBind.CallbackInvoke(() => {
        done();
      });
    })
    it('002_Callback_For_Invoke_From_Thread', 0, async (done:Function)=> {
      jsBind.CallbackInvokeFromThread(() => {
        done();
      });
    })
    it('003_Callback_For_Invoke_Passing_function', 0, async (done:Function)=> {
      jsBind.CallbackInvoke(() => {
        done();
      });
    })
    it('004_Callback_For_Invoke_Passing_Object_function', 0, async (done:Function)=> {
      let cb = () => {
        done();
      }
      jsBind.CallbackInvoke(cb);
    })
    it('001.2_CallbackReturnVoid', 0, async (done:Function)=> {
      jsBind.CallbackReturnVoid(() => {
        done();
      });
    })
    it('001.3_SafetyCallbackReturnVoid', 0, async (done:Function)=> {
      jsBind.SafetyCallbackReturnVoid(() => {
        done();
      });
    })
    it('002.2_CallbackReturnBool_True', 0, () => {
      let value = jsBind.CallbackReturnBool_True((value) => {
        return value;
      });
      expect(value).assertTrue();
    })
    it('002.3_SafetyCallbackReturnBool_True', 0, async (done:Function)=> {
      let value = jsBind.SafetyCallbackReturnBool_True((value) => {
        expect(value).assertTrue();
        done();
        return value;
      });
      expect(value).assertTrue();
    })
    it('003.2_CallbackReturnInt_Int', 0, () => {
      let value = jsBind.CallbackReturnInt_Int((value) => {
        return value;
      });
      expect(value).assertEqual(10086);
    })
    it('004.2_CallbackReturnString_String', 0, () => {
      let value = jsBind.CallbackReturnString_String((value) => {
        return "Hello " + value;
      });
      expect(value).assertEqual("Hello JSBind");
    })
    it('004.3_SafetyCallbackReturnString_String', 0, () => {
      let value = jsBind.SafetyCallbackReturnString_String((value) => {
        return "Hello " + value;
      });
      expect(value).assertEqual("JSBind");
    })
    it('005.2_CallbackReturnDouble_Double', 0, () => {
      let value = jsBind.CallbackReturnDouble_Double((value) => {
        return value;
      });
      expect(value).assertEqual(3.1415926);
    })
    it('005.3_SafetyCallbackReturnDouble_Double', 0, () => {
      let value = jsBind.SafetyCallbackReturnDouble_Double((value) => {
        return value;
      });
      expect(value).assertEqual(3.1415926);
    })
    it('005.4_SafetyCallbackReturnDouble_Double_Num_X2', 0, async (done:Function)=> {
      let count = 0;
      let value = jsBind.SafetyCallbackReturnDouble_Double_Num_X2((value) => {
        count++;
        console.log(' JSBind ' + count)
        if (count == 2) {
          done();
        }
        return value;
      });
      expect(value).assertEqual(3.1415926);
    })
  })
}