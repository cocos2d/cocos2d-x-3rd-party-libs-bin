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

export default function checkerTest() {
  describe('CheckerTest', ()=> {
    it('001_Checker_Type_bool', 0, ()=> {
//      try {
//        jsBind.PassingBoolReturnBool(2)
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ boolean ]");
//      }
    })
    it('002_Checker_Type_number', 0, ()=> {
//      try {
//        jsBind.PassingInt32ReturnInt32("abc")
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ number ]");
//      }
//      try {
//        jsBind.PassingInt64ReturnInt64("abc")
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ number ]");
//      }
//      try {
//        jsBind.PassingDoubleReturnDouble("abc")
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ number ]");
//      }
//      try {
//        jsBind.PassingFloatReturnFloat("abc")
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ number ]");
//      }
    })
    it('003_Checker_Type_string', 0, ()=> {
//      try {
//        jsBind.PassingStringReturnString([])
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ string ]");
//      }
    })
    it('004_Checker_Type_string_string', 0, ()=> {
//      try {
//        jsBind.PassingConstStringRef2ReturnString("1", [])
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ true false ], expected: [ string string ]");
//      }
    })
    it('005_Checker_Type_function', 0, ()=> {
//      try {
//        jsBind.CallbackInvoke("error type")
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ function ]");
//      }
//      try {
//        jsBind.CallbackReturnVoid("error type")
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ function ]");
//      }
//      try {
//        jsBind.SafetyCallbackReturnVoid("error type")
//      } catch(error) {
//        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
//        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false ], expected: [ function ]");
//      }
      try {
       jsBind.JSBind.bindFunction(undefined, undefined)
      } catch(error) {
        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false false ], expected: [ string function ]");
      }
    })
    it('006_Checker_Type_object', 0, ()=> {
      try {
        jsBind.TestObject.MultiplyObject(undefined, undefined)
      } catch(error) {
        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false false ], expected: [ object object ]");
      }
      try {
        jsBind.TestObject.MultiplyObjectPtr(undefined, undefined)
      } catch(error) {
        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false false ], expected: [ object object ]");
      }
      try {
        jsBind.TestObject.MultiplyObjectConstPtr(undefined, undefined)
      } catch(error) {
        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false false ], expected: [ object object ]");
      }
      try {
        jsBind.TestObject.MultiplyObjectSmartPtr(undefined, undefined)
      } catch(error) {
        expect(error.code).assertEqual("JSBind: Wrong type of arguments");
        expect(error.message).assertEqual("JSBind: Arguments Type mismatch, flags: [ false false ], expected: [ object object ]");
      }
    })
  })
}