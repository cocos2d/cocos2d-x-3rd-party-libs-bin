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

export default function functionArgumentsTest() {
  describe('FunctionArgumentsTest', ()=> {
    it('001_PassingBoolReturnBool_True', 0, ()=> {
      expect(testNapi.PassingBoolReturnBool(true)).assertTrue()
    })
    it('002_PassingBoolReturnBool_False', 0, ()=> {
      expect(testNapi.PassingBoolReturnBool(false)).assertFalse()
    })
    it('003_PassingInt32ReturnInt32_10086', 0, ()=> {
      expect(testNapi.PassingInt32ReturnInt32(10086)).assertEqual(10086)
    })
    it('004_PassingInt32ReturnInt32_10086', 0, ()=> {
      expect(testNapi.PassingInt32ReturnInt32(-10086)).assertEqual(-10086)
    })
//    it('005_PassingUint32ReturnUint32_1314', 0, ()=> {
//      expect(testNapi.passingUint32ReturnUint32(1314)).assertEqual(1314) TODO 需要添加支持 uint32_t 特性
//    })
    it('006_PassingInt64ReturnInt64_2022', 0, ()=> {
      expect(testNapi.PassingInt64ReturnInt64(922337203685477580)).assertEqual(922337203685477580)
      expect(testNapi.PassingInt64ReturnInt64(-922337203685477580)).assertEqual(-922337203685477580)
    })
    it('007_PassingStringReturnString', 0, ()=> {
      expect(testNapi.PassingStringReturnString("AKI")).assertEqual("AKI")
    })
//    it('008_PassingStringRefReturnString', 0, ()=> {
//      expect(testNapi.PassingStringRefReturnString("AKI")).assertEqual("AKI")
//    })
    it('009_PassingConstStringRefReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRefReturnString("AKI")).assertEqual("AKI")
    })
    it('010_PassingConstStringRef2ReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRef2ReturnString("AKI", " JSBIND")).assertEqual("AKI JSBIND")
    })
    it('011_PassingConstStringRef3ReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRef3ReturnString("AKI", " ", "JSBIND")).assertEqual("AKI JSBIND")
    })
    it('012_PassingConstStringRef4ReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRef4ReturnString("AKI", " ", "JS", "BIND")).assertEqual("AKI JSBIND")
    })
    it('013_PassingConstStringRef5ReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRef5ReturnString("A", "KI", " ", "JS", "BIND")).assertEqual("AKI JSBIND")
    })
    it('014_PassingConstStringRef6ReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRef6ReturnString("A", "K", "I", " ", "JS", "BIND")).assertEqual("AKI JSBIND")
    })
    it('015_PassingConstStringRef7ReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRef7ReturnString("A", "K", "I", " ", "J", "S", "BIND")).assertEqual("AKI JSBIND")
    })
    it('016_PassingConstStringRef8ReturnString', 0, ()=> {
      expect(testNapi.PassingConstStringRef8ReturnString("A", "K", "I", " ", "J", "S", "B", "IND")).assertEqual("AKI JSBIND")
    })
    it('017_PassingConstCStrPtrReturnConstCStrPtr', 0, ()=> {
      expect(testNapi.PassingConstCStrPtrReturnConstCStrPtr("hello AKI")).assertEqual("hello AKI")
    })
    it('018_PassingCStrPtrReturnConstCStrPtr', 0, ()=> {
      expect(testNapi.PassingCStrPtrReturnConstCStrPtr("hello AKI")).assertEqual("hello AKI")
    })
    it('019_PassingCStrPtrReturnCStrPtr', 0, ()=> {
      expect(testNapi.PassingCStrPtrReturnCStrPtr("hello AKI")).assertEqual("hello AKI")
    })
    it('020_PassingNoneReturnBool', 0, ()=> {
      expect(testNapi.PassingNoneReturnBool()).assertEqual(true)
    })
    it('021_PassingDoubleReturnDouble_4.14', 0, ()=> {
      expect(testNapi.PassingDoubleReturnDouble(3.14)).assertLess(5)
    })
    it('022_PassingDoubleReturnDouble_5.14', 0, ()=> {
      expect(testNapi.PassingDoubleReturnDouble(4.14)).assertEqual(5.14)
    })
    it('023_PassingFloatReturnFloat', 0, ()=> {
    let num = testNapi.PassingFloatReturnFloat(4.14); // add 1.1
      expect(num).assertLarger(5.23999); // float存在精度丢失
      expect(num).assertLess(5.24);
    })
    it('024_PassingVectorIntReturnBool', 0, ()=> {
      let array = [0, 1, 2, 3];
      let result = testNapi.PassingVectorIntReturnBool(array);
      expect(result).assertEqual(true);
    })
    it('025_PassingVectorIntReturnVectorInt', 0, ()=> {
      let array = [0, 1, 2, 3];
      let result = testNapi.PassingVectorIntReturnVectorInt(array);
      expect(result.toString()).assertEqual([0, 1, 2, 3, 4].toString());
    })
    it('026_PassingVectorUint8ReturnVectorUint8', 0, ()=> {
      let array = [0, 1, 2, 3];
      let result = testNapi.PassingVectorUint8ReturnVectorUint8(array);
      expect(result.toString()).assertEqual([0, 1, 2, 3, 4].toString());
    })
    it('027_PassingVectorBoolReturnVectorBool', 0, ()=> {
      let array = [false, false, false];
      let result = testNapi.PassingVectorBoolReturnVectorBool(array);
      expect(result.toString()).assertEqual([false, false, false, true].toString());
    })
    it('028_PassingVectorFloatReturnVectorFloat', 0, ()=> {
      let array = [1.1, 2.2, 3.3];
      let result = testNapi.PassingVectorFloatReturnVectorFloat(array);
      expect(result[3]).assertLarger(4.4); // float存在精度丢失
      expect(result[3]).assertLess(4.4000001);
    })
    it('029_PassingArrayIntReturnBool', 0, ()=> {
      let array = [0, 1, 2, 3];
      let result = testNapi.passingArrayIntReturnBool(array);
      expect(result).assertEqual(true);
    })
    it('030_PassingArrayIntReturnArrayInt', 0, ()=> {
      let array = [0, 1, 2, 3];
      let result = testNapi.passingArrayIntReturnArrayInt(array);
      expect(result.toString()).assertEqual([0, 1, 2, 3, 4].toString());
    })
    it('031_passingArrayStrReturnArrayStr', 0, ()=> {
      let array = ["0", "1", "2", "3"];
      let result = testNapi.passingArrayStrReturnArrayStr(array);
      expect(result.toString()).assertEqual(["0", "1", "2", "3", "4"].toString());
    })
    it('041_P_PassingIntReturnInt', 0, async (done:Function) => {
      // 异步任务调用模式
      testNapi.P_PassingIntReturnInt(888).then(result => {
        expect(result).assertEqual(888);
        done();
      })
    })
  })
}