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
import bundleManager from '@ohos.bundle.bundleManager'

class ApplicationInfo {
  // 接受鸿蒙 ApplicationInfo 信息进行等价类的构造
  constructor(info: bundleManager.ApplicationInfo) {
    this.name = info.name;
    this.descriptionId = info.descriptionId;
    this.systemApp = info.systemApp;
    this.permissions = info.permissions;
  }

  private equals(matcher: (name: String, descriptionId: Number, systemApp: Boolean, permissions: Array<String>) => void) {
    try {
      // matcher 方法入参匹配 native 等价类的构造函数
      matcher(this.name, this.descriptionId, this.systemApp, this.permissions);
    } catch(e) {
      console.log(e)
    }
  }

  // 等价类成员变量
  name: String;
  descriptionId: Number;
  systemApp: Boolean;
  permissions: Array<String>;
}

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
            bundleManager.getBundleInfoForSelf(bundleManager.BundleFlag.GET_BUNDLE_INFO_DEFAULT)
              .then((bundleInfo) => {
                console.log('[AKI] bundleInfo: ' + JSON.stringify(bundleInfo));
                // let info = new ApplicationInfo(applicationInfo);
                // aki.ApplicationInfo.Init(info);
              })
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
