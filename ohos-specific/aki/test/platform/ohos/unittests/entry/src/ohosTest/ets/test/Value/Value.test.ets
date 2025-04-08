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
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import libaki from "libunittest.so"
import {GlobalManager} from '../common/GlobalManager'

export default function valueTest() {
  describe('ValueTest', () => {
    it('PassingValueAsBool', 0, () => {
      let result = libaki.PassingValueAsBool(true);
      expect(result).assertEqual(true)
      result = libaki.PassingValueAsBool(false);
      expect(result).assertEqual(false)
    })
    it('PassingValueAsBoolReturnValue', 0, () => {
      let result = libaki.PassingValueAsBoolReturnValue(true);
      expect(result).assertEqual(true)
      result = libaki.PassingValueAsBoolReturnValue(false);
      expect(result).assertEqual(false)
    })
    it('PassingValueAsUint8', 0, () => {
      let result = libaki.PassingValueAsUint8(0);
      expect(result).assertEqual(0)
      result = libaki.PassingValueAsUint8(255);
      expect(result).assertEqual(255)
    })
    it('PassingValueAsInt8', 0, () => {
      let result = libaki.PassingValueAsInt8(127);
      expect(result).assertEqual(127)
      result = libaki.PassingValueAsInt8(-128);
      expect(result).assertEqual(-128)
    })
    it('PassingValueAsUint16', 0, () => {
      let result = libaki.PassingValueAsUint16(0);
      expect(result).assertEqual(0)
      result = libaki.PassingValueAsUint16(255);
      expect(result).assertEqual(255)
    })
    it('PassingValueAsInt16', 0, () => {
      let result = libaki.PassingValueAsInt16(127);
      expect(result).assertEqual(127)
      result = libaki.PassingValueAsInt16(-128);
      expect(result).assertEqual(-128)
    })
    it('PassingValueAsInt', 0, () => {
      let result = libaki.PassingValueAsInt(813);
      expect(result).assertEqual(813)
    })
    it('PassingValueAsIntReturnValue', 0, () => {
      let result = libaki.PassingValueAsIntReturnValue(813);
      expect(result).assertEqual(813)
    })
    it('PassingValueAsInt64', 0, () => {
      let result = libaki.PassingValueAsInt64(922337203685477580);
      expect(result).assertEqual(922337203685477580)
      result = libaki.PassingValueAsInt64(-922337203685477580);
      expect(result).assertEqual(-922337203685477580)
    })
    it('PassingValueAsFloat', 0, () => {
      let result = libaki.PassingValueAsFloat(1);
      expect(result).assertEqual(1)
      result = libaki.PassingValueAsFloat(-1);
      expect(result).assertEqual(-1)
    })
    it('PassingValueAsDouble', 0, () => {
      let result = libaki.PassingValueAsDouble(3.14);
      expect(result).assertEqual(3.14)
      result = libaki.PassingValueAsDouble(-3.14);
      expect(result).assertEqual(-3.14)
    })
    it('PassingValueAsString', 0, () => {
      let result = libaki.PassingValueAsString('akiString');
      expect(result).assertEqual('akiString')
    })
    it('PassingValueAsStringReturnValue', 0, () => {
      let result = libaki.PassingValueAsStringReturnValue('akiString');
      expect(result).assertEqual('akiString')
    })
    it('PassingArrayValueReturnValue', 0, () => {
      let result = libaki.PassingArrayValueReturnValue(['aki']);
      expect(result).assertEqual('aki')
    })
    it('PassingArrayValueReturnArrayValue', 0, () => {
      let result = libaki.PassingArrayValueReturnArrayValue(['aki']);
      expect(result.toString()).assertEqual(['aki', 'jsbind'].toString())
    })
    it('PassingArrayValueThenSetValue', 0, () => {
      let array = ['aki', 'aki']
      libaki.PassingArrayValueThenSetValue(array);
      expect(array.toString()).assertEqual(['jsbind', 'aki'].toString())
    })
    it('PassingValueAsFunction', 0, () => {
      let result = libaki.PassingValueAsFunction((str)=> {
          return str + ' and with javascript.'
        });
      expect(result).assertEqual('aki value from c++ and with javascript.')
    })
    it('PassingValueAsJsonObject', 0, () => {
      let result = libaki.PassingValueAsJsonObject({
        'name': 'aki',
        'age': 1});
      expect(JSON.stringify(result)).assertEqual('{"name":"aki"}')
    })
    it('PassingValueCheckIsNull', 0, () => {
      let result = libaki.PassingValueCheckIsNull(null);
      expect(result).assertEqual(true);
      result = libaki.PassingValueCheckIsNull(undefined);
      expect(result).assertEqual(false);
    })
    it('PassingValueCheckIsUndefined', 0, () => {
      let result = libaki.PassingValueCheckIsUndefined(undefined);
      expect(result).assertEqual(true);
      result = libaki.PassingValueCheckIsUndefined(null);
      expect(result).assertEqual(false);
    })
    it('PassingValueCheckIsBool', 0, () => {
      let result = libaki.PassingValueCheckIsBool(true);
      expect(result).assertEqual(true);
      result = libaki.PassingValueCheckIsBool(false);
      expect(result).assertEqual(true);
    })
    it('PassingValueCheckIsNumber', 0, () => {
      let result = libaki.PassingValueCheckIsNumber(1);
      expect(result).assertEqual(true);
    })
    it('PassingValueCheckIsString', 0, () => {
      let result = libaki.PassingValueCheckIsString('aki');
      expect(result).assertEqual(true);
    })
    it('PassingValueCheckIsArray', 0, () => {
      let result = libaki.PassingValueCheckIsArray(['aki', 'jsbind']);
      expect(result).assertEqual(true);
    })
    it('PassingValueCheckIsFunction', 0, () => {
      let result = libaki.PassingValueCheckIsFunction(() => {});
      expect(result).assertEqual(true);
    })
    it('ValueFromGlobalAsString', 0, () => {
      GlobalManager.setAkiString()
      let result = libaki.ValueFromGlobalAsString();
      expect(result).assertEqual('akiString')
    })
    it('FromGlobalBundleManager', 0, () => {
      GlobalManager.setBundleGlobal()
      libaki.FromGlobalBundleManager();
    })
    it('FromGlobalJSONStringify', 0, () => {
      let result = libaki.FromGlobalJSONStringify({
        'name': 'aki',
        'age': 1});
      expect(result).assertEqual('{"name":"aki","age":1}')
    })
    it('FromGlobalJSONParse', 0, () => {
      let str = '{"name":"aki","age":1}';
      let result = libaki.FromGlobalJSONParse(str);
      expect(JSON.stringify(result)).assertEqual(str)
    })
    it('AkiValueData', 0, () => {
      let result = new libaki.AkiValueData();
      expect(result.value).assertEqual(undefined)
    })
    it('AkiValueData_Assign', 0, () => {
      let result = new libaki.AkiValueData();
      result.value = ['aki', 'jsbind'];
      expect(result.value.toString()).assertEqual(['aki', 'jsbind'].toString())
    })
    it('AkiValueData_SetValueFromNative', 0, () => {
      let result = new libaki.AkiValueData();
      result.value = ['javascript'];
      result.SetValueFromNative()
      expect(result.value.toString()).assertEqual(['javascript', 'c++'].toString())
    })
  })
}