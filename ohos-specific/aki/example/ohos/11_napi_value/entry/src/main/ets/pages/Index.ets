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
import libraw_file from 'libraw_file.so'
import resourceManager from '@ohos.resourceManager';

@Entry
@Component
struct Index {
  @State message: string = 'Hello World'
  private resmgr = getContext().resourceManager;  // 获取js的资源对象

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let rawfilelist = libraw_file.getFileList(this.resmgr, ""); //传入资源对象，以及访问的rawfile文件夹名称
            console.log("[AKI] rawfilelist" + rawfilelist);
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
