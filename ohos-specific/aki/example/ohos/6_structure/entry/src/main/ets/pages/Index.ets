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
import libAddon from 'libentry.so'

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
            let person = new libAddon.Person("jsbind", 8);
            libAddon.growUp(person)
            hilog.info(0x0000, 'AKI', 'Person name = %{public}s, age = %{public}d', person.name, person.age);
            let other = libAddon.foo(person);
            hilog.info(0x0000, 'AKI', 'Person name = %{public}s, age = %{public}d', person.name, person.age);
            hilog.info(0x0000, 'AKI', 'Person name = %{public}s, age = %{public}d', other.name, other.age);
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
