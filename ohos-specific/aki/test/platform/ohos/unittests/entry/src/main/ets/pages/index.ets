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

import hilog from '@ohos.hilog';
import libaki from "libunittest.so"
//function EquivalenceTest(value) {
//  this.value = value;
//}

// EquivalenceTest.prototype.fromJS = function(output) {
//  console.log('gzx fromJS: ')
//  try {
//    output(this.value);
//  } catch(e) {
//    console.log(e)
//  }
// }
@Entry
@Component
struct Index {
  @State message: string = 'Hello World'

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let result = libaki.PassingValueAsInt64(9223372036854775807);
//            var obj1 = new testNapi.TestObject(3.1415926);
//            var obj2 = new testNapi.TestObject(-10);
//            testNapi.TestObject.MultiplyObject(obj1, obj2);
//            var value = new EquivalenceTest(250);
//            let xx = testNapi.EquivalenceTest.ShowByValue(value);
//            console.log('gzx: ' + xx)
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
