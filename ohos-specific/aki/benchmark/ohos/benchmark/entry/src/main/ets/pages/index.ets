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
import jsbind_benchmark from "libjsbind_benchmark.so"

@Entry
@Component
struct Index {
  @State message1: string = 'call from napi'
  @State message2: string = 'call from jsbind'

  build() {
    Row() {
      Column() {
        Text(this.message1)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            hilog.isLoggable(0x0000, 'AKI', hilog.LogLevel.INFO);
            jsbind_benchmark.PassingNoneReturnBool();
          })
        Text(this.message2)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            console.log('gzx 3')
            jsbind_benchmark.PassingFunctionReturnVoid(() => {
              console.log('gzx 4')
            })
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
