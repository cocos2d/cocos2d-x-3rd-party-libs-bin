/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
import libaddon from 'libarray_to_native.so'

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
            let handle = new libaddon.VectorHandle();
            let result = handle.passingVoidReturnVectorLong();
            console.log('AKI VectorHandle.PassingVoidReturnVectorLong: ' + result)
            let array = [1, 2, 3];
            result = handle.passingVectorLongReturnVectorLong(array);
            console.log('AKI VectorHandle.passingVectorLongReturnVectorLong: ' + result)

            result = libaddon.passingVoidReturnVectorLong();
            console.log('AKI PassingVoidReturnVectorLong: ' + result)
            result = libaddon.passingVectorLongReturnVectorLong(array);
            console.log('AKI passingVectorLongReturnVectorLong: ' + result)
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
