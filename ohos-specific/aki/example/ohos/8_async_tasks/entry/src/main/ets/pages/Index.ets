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
import libAddon from 'libasync_tasks.so'

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
            let taskRunner = new libAddon.TaskRunner();
            taskRunner.DoTask().then(res => {
              console.log('[AKI] DoTask: ' + res)
            });

            taskRunner.DoTaskReturnData().then(res => {
              console.log('[AKI] DoTaskReturnData: ' + res.name)
            });

            libAddon.AsyncTaskLongLongFunctionReturnLong(-2147483648, 2147483647, (a, b, c) => {
              console.log('[AKI] AsyncTaskLongLongFunctionReturnLong callback: ' + c);
              return a + b;
            }).then(res => {
              console.log('[AKI] AsyncTaskLongLongFunctionReturnLong: ' + res)
            });

            libAddon.AsyncTaskReturnVoid().then(res => {
              console.log('[AKI] AsyncTaskReturnVoid: ' + res)
            });
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
