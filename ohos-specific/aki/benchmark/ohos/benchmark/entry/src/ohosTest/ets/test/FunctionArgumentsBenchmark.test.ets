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
import jsbind_benchmark from "libjsbind_benchmark.so"
import napi_benchmark from "libnapi_benchmark.so"

export default function functionArgumentsBenchmark() {
  describe('FunctionArgumentsBenchmark',() => {
    it('1.1.a_JSBIND_Foo', 0, () => {
      for (let i = 0; i < 10000; i++) {
        jsbind_benchmark.Foo();
      }
    })
    it('1.1.b_NAPI_Foo', 0, () => {
      for (let i = 0; i < 10000; i++) {
        napi_benchmark.Foo();
      }
    })
    it('1.2.a_JSBIND_PassingNoneReturnBool', 0, () => {
      let result = false;
      for (let i = 0; i < 10000; i++) {
        result = jsbind_benchmark.PassingNoneReturnBool();
      }
      expect(result).assertTrue();
    })
    it('1.2.b_NAPI_PassingNoneReturnBool', 0, () => {
      let result = false;
      for (let i = 0; i < 10000; i++) {
        result = napi_benchmark.PassingNoneReturnBool();
      }
      expect(result).assertTrue();
    })
    it('1.3.a_JSBIND_PassingStringReturnString', 0, () => {
      let result = "JSBIND";
      for (let i = 0; i < 10000; i++) {
        result = jsbind_benchmark.PassingStringReturnString(result);
      }
      expect(result).assertEqual("JSBIND");
    })
    it('1.3.b_NAPI_PassingStringReturnString', 0, () => {
      let result = "NAPI";
      for (let i = 0; i < 10000; i++) {
        result = napi_benchmark.PassingStringReturnString(result);
      }
      expect(result).assertEqual("NAPI");
    })
    it('1.4.a_JSBIND_PassingFunctionReturnVoid', 0, () => {
      let count = 0;
      for (let i = 0; i < 10000; i++) {
        jsbind_benchmark.PassingFunctionReturnVoid(() => {
          count++;
          // do nothing
        });
      }
      expect(count).assertEqual(10000);
    })
    it('1.4.b_NAPI_PassingFunctionReturnVoid', 0, () => {
      let count = 0;
      for (let i = 0; i < 10000; i++) {
        napi_benchmark.PassingFunctionReturnVoid(() => {
          count++;
          // do nothing
        });
      }
      expect(count).assertEqual(10000);
    })
    it('1.4.c_JSBIND_PassingCallbackReturnVoid', 0, () => {
      let count = 0;
      for (let i = 0; i < 10000; i++) {
        jsbind_benchmark.PassingCallbackReturnVoid(() => {
          count++;
          // do nothing
        });
      }
      expect(count).assertEqual(10000);
    })
    it('1.4.d_JSBIND_PassingSafetyCallbackReturnVoid', 0, () => {
      let count = 0;
      for (let i = 0; i < 10000; i++) {
        jsbind_benchmark.PassingSafetyCallbackReturnVoid(() => {
          count++;
          // do nothing
        });
      }
      expect(count).assertEqual(10000);
    })
  })
}