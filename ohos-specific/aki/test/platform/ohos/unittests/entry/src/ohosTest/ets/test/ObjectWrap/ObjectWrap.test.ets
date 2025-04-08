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

export default function objectWrapTest() {
  describe('ObjectWrapTest', ()=> {
    it('001_Constructor_Default', 0, ()=> {
      let obj = new testNapi.TestObject();
      expect(obj.value).assertEqual(-3.1415926);
    })
    it('002_FunctionConstructor_With_Error', 0, ()=> {
//      let error;
//      try {
//        testNapi.TestObject();
//      } catch (e) {
//        error = e;
//      } finally {
//        expect(error.code).assertEqual("JSBind Error: Class constructor cannot be invoked without 'new'");
//      }
    })
    it('003_Constructor_double_', 0, ()=> {
      let obj = new testNapi.TestObject(3.1415926);
      expect(obj.value).assertEqual(3.1415926);
    })
    it('004_Object_Method_PlusOne', 0, ()=> {
      let obj = new testNapi.TestObject(3.1415926);
      expect(obj.PlusOne()).assertEqual(3.1415926 + 1);
      expect(obj.PlusOne()).assertEqual(3.1415926 + 2);
      expect(obj.PlusOne()).assertEqual(3.1415926 + 3);
    })
    it('005_Object_Method_Multiply', 0, ()=> {
      let obj = new testNapi.TestObject(3.1415926);
      expect(obj.Multiply(1)).assertEqual(3.1415926);
      expect(obj.Multiply(10)).assertEqual(31.415926);
      expect(obj.Multiply(-1)).assertEqual(-31.415926);
    })
    it('006_Object_Static_Method_Multiply_Object', 0, ()=> {
      let obj1 = new testNapi.TestObject(3.1415926);
      let obj2 = new testNapi.TestObject(-10);
      expect(testNapi.TestObject.MultiplyObject(obj1, obj2)).assertEqual(-31.415926);
    })
    it('007_Object_Static_Method_Multiply_Object_Ptr', 0, ()=> {
      let obj1 = new testNapi.TestObject(3.1415926);
      let obj2 = new testNapi.TestObject(-100);
      expect(testNapi.TestObject.MultiplyObjectPtr(obj1, obj2)).assertEqual(-314.15926);
    })
    it('008_Object_Static_Method_Multiply_Object_Const_Ptr', 0, ()=> {
      let obj1 = new testNapi.TestObject(3.1415926);
      let obj2 = new testNapi.TestObject(-1000);
      expect(testNapi.TestObject.MultiplyObjectConstPtr(obj1, obj2)).assertEqual(-3141.5926);
    })
    it('009_Object_Static_Method_Multiply_Object_Smart_Ptr', 0, ()=> {
      let obj1 = new testNapi.TestObject(3.1415926);
      let obj2 = new testNapi.TestObject(-10000);
      expect(testNapi.TestObject.MultiplyObjectSmartPtr(obj1, obj2)).assertEqual(-31415.926);
      expect(obj1.value).assertEqual(-31415.926);
    })
    it('010_Object_Static_Method_Multiply_Object_Smart_Ptr_Return_Smart_Ptr', 0, ()=> {
      let obj1 = new testNapi.TestObject(-31415.926);
      let obj2 = testNapi.TestObject.MultiplyObjectSmartPtrReturnSmartPtr(obj1);
      expect(obj2.value).assertEqual(-31415.926);
    })
    it('011_Object_Static_Method_Create_Object', 0, ()=> {
      let obj = testNapi.TestObject.CreateObject();
      expect(obj.value).assertEqual(100.86);
    })
    it('012_Object_Static_Method_Create_Object', 0, ()=> {
      let obj = testNapi.TestObject.CreateObject();
      expect(obj.value).assertEqual(100.86);
    })
    it('013_Object_Static_Method_Create_Object_ptr', 0, ()=> {
      let obj = testNapi.TestObject.CreateObjectPtr();
      expect(obj.value).assertEqual(-100.86);
    })
    it('014_Object_bind_setter', 0, ()=> {
      let obj = new testNapi.TestObject();
      obj.fake = -1.1;
      expect(obj.GetFake()).assertEqual(-1.1);
    })
    it('015_Object_Get_Method', 0, ()=> {
      let obj = new testNapi.TestObject(3.14159261);
      expect(obj.GetValue()).assertEqual(3.14159261);
    })
    it('016_Object_Set_Method', 0, ()=> {
      let obj = new testNapi.TestObject(); // 默认值：-3.1415926
      obj.SetValue(31.4159261)
      expect(obj.value).assertEqual(31.4159261);
    })
    it('017_Object_P_PassingIntReturnInt', 0, async (done:Function) => {
      let obj = new testNapi.TestObject(); // 默认值：-3.1415926
      // 异步任务调用模式
      obj.P_PassingIntReturnInt(666).then(result => {
        expect(result).assertEqual(666);
        done();
      })
    })
    it('018_Object_P_StaticPassingIntReturnInt', 0, async (done:Function) => {
      // 异步任务调用模式
      testNapi.TestObject.P_StaticPassingIntReturnInt(888).then(result => {
        expect(result).assertEqual(888);
        done();
      })
    })
  })
}