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
import callback from 'libcallback.so'

@Entry
@Component
struct Index {
  build() {
    Row() {
      Column() {
        Button('std::function without return')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            callback.CallFunctionReturnVoid(() => {
              hilog.info(0x0000, 'callback-js', 'std::function callback from js');
            })
          })

        Button('std::function<short (short)>')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            let result = callback.CallFunctionPassingShortReturnShort(-32768, (num) => {
              return num;
            })
            hilog.info(0x0000, 'callback-js', 'std::function<short (short)> result: ' + result);
          })

        Button('std::function return string')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            callback.CallFunctionReturnString((): string => {
              hilog.info(0x0000, 'callback-js', 'js call CallFunctionReturnString');
              return "js call CallFunctionReturnString"
            })
          })

        Button('aki::Callback without return')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            callback.CallJsbCallbackReturnVoid(() => {
              hilog.info(0x0000, 'callback-js', 'aki::Callback callback from js');
            })
          })

        Button('aki::Callback return string')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            callback.CallJsbCallbackReturnString((): string => {
              hilog.info(0x0000, 'callback-js', 'js call CallJsbCallbackReturnString');
              return "js call CallJsbCallbackReturnString"
            })
          })

        Button('aki::SafetyCallback without return')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            callback.CallJsbSafetyCallbackReturnVoid(() => {
              hilog.info(0x0000, 'callback-js', 'aki::SafetyCallback callback from js');
            })
          })

        Button('aki::SafetyCallback return string')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            callback.CallJsbSafetyCallbackReturnString((): string => {
              hilog.info(0x0000, 'callback-js', 'js call CallJsbSafetyCallbackReturnString');
              return "js call CallJsbSafetyCallbackReturnString"
            })
          })

        Button('callback at js return number')
          .height(30)
          .fontSize(20)
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            callback.JSBind.bindFunction("funcWithCallbackReturnNumber", (a: number, b:number, callback:(result:number) =>void) => {
              let result = callback(a + b);
              hilog.info(0x0000, 'callback-js', 'AKI:'+result);
            });
            callback.InvokeFuncWithCallbackReturnNumber();
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
