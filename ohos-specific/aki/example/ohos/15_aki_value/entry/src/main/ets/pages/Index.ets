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
import libaki from 'libaki_value.so'
import {BundleManager} from './BundleManager'
let map = new Map<string,Object>()

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
            BundleManager.setBundleGlobal()
            let result = libaki.PassingValueAsString('akiString');
            console.log('AKI', 'PassingValueAsString', result);
            result = libaki.PassingValueAsStringReturnValue('akiString');
            console.log('AKI', 'PassingValueAsStringReturnValue', result);
            result = libaki.PassingArrayValueReturnValue(['aki']);
            console.log('AKI', 'PassingArrayValueReturnValue', result);
            result = libaki.PassingArrayValueReturnArrayValue(['aki']);
            console.log('AKI', 'PassingArrayValueReturnArrayValue', result);
            let array = ['aki', 'aki'];
            libaki.PassingArrayValueThenSetValue(array);
            console.log('AKI', 'PassingArrayValueThenSetValue', array);
            result = libaki.PassingValueAsBool(false);
            console.log('AKI', 'PassingValueAsBool', result);
            result = libaki.PassingValueAsBoolReturnValue(false);
            console.log('AKI', 'PassingValueAsBoolReturnValue', result);
            let result2 = libaki.PassingValueAsInt(5566);
            console.log('AKI', 'PassingValueAsInt', result2);
            result2 = libaki.PassingValueAsIntReturnValue(7788);
            console.log('AKI', 'PassingValueAsIntReturnValue', result2);
            result = libaki.PassingValueAsFunction((str:string)=> {
              return str + ' and with javascript.'
            });
            console.log('AKI', 'PassingValueAsFunction', result);
            result = libaki.PassingValueAsJsonObject({
              'name':'aki',
              'age':1
            });
            console.log('AKI', 'PassingValueAsJsonObject', JSON.stringify(result));
            result = libaki.PassingValueCheckIsNull(null);
            console.log('AKI', 'PassingValueCheckIsNull', result);
            result = libaki.PassingValueCheckIsUndefined(undefined);
            console.log('AKI', 'PassingValueCheckIsUndefined', result);
            result = libaki.PassingValueCheckIsBool(false);
            console.log('AKI', 'PassingValueCheckIsBool', result);
            result = libaki.PassingValueCheckIsNumber(1);
            console.log('AKI', 'PassingValueCheckIsNumber', result);
            result = libaki.PassingValueCheckIsString('aki');
            console.log('AKI', 'PassingValueCheckIsString', result);
            result = libaki.PassingValueCheckIsArray(['aki', 'jsbind']);
            console.log('AKI', 'PassingValueCheckIsArray', result);
            result = libaki.PassingValueCheckIsFunction(() => {});
            console.log('AKI', 'PassingValueCheckIsFunction', result);
            libaki.FromGlobalBundleManager();
            result = libaki.FromGlobalJSONStringify(map);
            console.log('AKI', 'FromGlobalJSONStringify', result);
            result = libaki.FromGlobalJSONParse(result);
            console.log('AKI', 'FromGlobalJSONParse', JSON.stringify(result));

            let result3 = new libaki.AkiValueData();
            result3.value = ['aki', 'jsbind']
            console.log('AKI', 'AkiValueData::GetValue', result3.value);
            result3.SetValueFromNative();
            console.log('AKI', 'AkiValueData::SetValueFromNative', result3.value);
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
