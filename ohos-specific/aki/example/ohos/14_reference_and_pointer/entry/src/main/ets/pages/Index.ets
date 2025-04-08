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
            let ref1 = new libAddon.Reference(0);
            libAddon.GrowUpByReference(ref1);
            hilog.info(0x0000, 'AKI', 'after GrowUpByReference ref1 count = %{public}d', ref1.count);
            libAddon.GrowUpByPointer(ref1);
            hilog.info(0x0000, 'AKI', 'after GrowUpByPointer ref1 count = %{public}d', ref1.count);

            let ref2 = new libAddon.Reference(-1);
            ref2.ChangeByReference(ref1);
            hilog.info(0x0000, 'AKI', 'after ChangeByReference ref1 count = %{public}d', ref1.count);
            hilog.info(0x0000, 'AKI', 'after ChangeByReference ref2 count = %{public}d', ref2.count);
            ref2.ChangeByPointer(ref1);
            hilog.info(0x0000, 'AKI', 'after ChangeByPointer ref1 count = %{public}d', ref1.count);
            hilog.info(0x0000, 'AKI', 'after ChangeByPointer ref2 count = %{public}d', ref2.count);
            libAddon.Reference.MultiCountByReference(ref1, 2);
            hilog.info(0x0000, 'AKI', 'after MultiCountByReference ref1 count = %{public}d', ref1.count);
            libAddon.Reference.MultiCountByPointer(ref2, 2);
            hilog.info(0x0000, 'AKI', 'after MultiCountByPointer ref2 count = %{public}d', ref2.count);
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
