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

export default function arrayBufferTest() {
  describe('ArrayBufferTest', ()=> {
    it('passingArrayBufferReturnArrayBuffer', 0, ()=> {
      let arrayBuffer = new ArrayBuffer(8);
      let certificate = new Int8Array([-1, 0, 0, 0, 0, 0, 0, 1]);
      let certificate1 = new Int8Array(arrayBuffer);
      certificate1[0] = -1;
      let result = libaki.passingArrayBufferReturnArrayBuffer(arrayBuffer);
      let certificate2 = new Int8Array(result);
      expect(certificate.toString()).assertEqual(certificate2.toString());
    })
    it('passingInt8ArrayReturnInt8Array', 0, ()=> {
      const certificate1 = new Int8Array([-4, -3, -2, -1, 0, 1, 2, 3, 4]);
      const certificate2 = new Int8Array([4, 3, 2, 1, 0, -1, -2, -3, -4]);
      let result = libaki.passingInt8ArrayReturnInt8Array(certificate1);
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('passingUint8ArrayReturnUint8Array', 0, ()=> {
      let certificate1 = new Uint8Array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
      let certificate2 = new Uint8Array([10, 11, 12, 13, 14, 15, 16, 17, 18, 19]);
      let result = libaki.passingUint8ArrayReturnUint8Array(certificate1);
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('passingInt16ArrayReturnInt16Array', 0, ()=> {
      const certificate1 = new Int16Array([-4, -3, -2, -1, 0, 1, 2, 3, 4]);
      const certificate2 = new Int16Array([4, 3, 2, 1, 0, -1, -2, -3, -4]);
      let result = libaki.passingInt16ArrayReturnInt16Array(certificate1);
      console.log('gzx JSBind: ' + result)
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('passingUint16ArrayReturnUint16Array', 0, ()=> {
      let certificate1 = new Uint16Array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
      let certificate2 = new Uint16Array([10, 11, 12, 13, 14, 15, 16, 17, 18, 19]);
      let result = libaki.passingUint16ArrayReturnUint16Array(certificate1);
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('passingInt32ArrayReturnInt32Array', 0, ()=> {
      const certificate1 = new Int32Array([-4, -3, -2, -1, 0, 1, 2, 3, 4]);
      const certificate2 = new Int32Array([4, 3, 2, 1, 0, -1, -2, -3, -4]);
      let result = libaki.passingInt32ArrayReturnInt32Array(certificate1);
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('passingUint32ArrayReturnUint32Array', 0, ()=> {
      let certificate1 = new Uint32Array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
      let certificate2 = new Uint32Array([10, 11, 12, 13, 14, 15, 16, 17, 18, 19]);
      let result = libaki.passingUint32ArrayReturnUint32Array(certificate1);
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('passingBigInt64ArrayReturnBigInt64Array', 0, ()=> {
      const certificate1 = new BigInt64Array([BigInt(-4), BigInt(-3), BigInt(-2), BigInt(-1), BigInt(0), BigInt(1), BigInt(2), BigInt(3), BigInt(4)]);
      const certificate2 = new BigInt64Array([BigInt(4), BigInt(3), BigInt(2), BigInt(1), BigInt(0), BigInt(-1), BigInt(-2), BigInt(-3), BigInt(-4)]);
      let result = libaki.passingBigInt64ArrayReturnBigInt64Array(certificate1);
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('passingBigUint64ArrayReturnBigUint64Array', 0, ()=> {
      const certificate1 = new BigUint64Array([BigInt(0), BigInt(1), BigInt(2), BigInt(3), BigInt(4), BigInt(5), BigInt(6), BigInt(7), BigInt(8), BigInt(9)]);
      const certificate2 = new BigUint64Array([BigInt(10), BigInt(11), BigInt(12), BigInt(13), BigInt(14), BigInt(15), BigInt(16), BigInt(17), BigInt(18), BigInt(19)]);
      let result = libaki.passingBigUint64ArrayReturnBigUint64Array(certificate1);
      expect(certificate1.toString()).assertEqual(certificate2.toString());
      expect(result.toString()).assertEqual(certificate2.toString());
    })
    it('asyncTaskArrayBufferReturnArrayBuffer', 0, async (done: Function) => {
      let buff: ArrayBuffer = new ArrayBuffer(4);
      let uint8Buff: Uint8Array = new Uint8Array(buff);
      uint8Buff[0] = 0;
      uint8Buff[1] = 1;
      uint8Buff[2] = 2;
      uint8Buff[3] = 3;
      libaki.asyncTaskArrayBufferReturnArrayBuffer(uint8Buff).then(res => {
        let uint8Buff1 = new Uint8Array(res);
        expect(uint8Buff1.toString()).assertEqual(uint8Buff.toString());
        done();
      });
    })
    it('asyncTaskReturnArrayBufferWithCommit', 0, async (done: Function)=> {
      let buff: ArrayBuffer = new ArrayBuffer(4);
      let uint8Buff: Uint8Array = new Uint8Array(buff);
      uint8Buff[0] = 10;
      uint8Buff[1] = 20;
      uint8Buff[2] = 30;
      uint8Buff[3] = 40;
      libaki.asyncTaskReturnArrayBufferWithCommit().then(res => {
        let uint8Buff1 = new Uint8Array(res);
        expect(uint8Buff1.toString()).assertEqual(uint8Buff.toString());
        done();
      });
    })
    it('ArrayBufferHandler_PROPERTY', 0, ()=> {
      let buff: ArrayBuffer = new ArrayBuffer(4);
      let uint8Buff: Uint8Array = new Uint8Array(buff);
      uint8Buff[0] = 0;
      uint8Buff[1] = 1;
      uint8Buff[2] = 2;
      uint8Buff[3] = 3;
      let result = new libaki.ArrayBufferHandler();
      result.buf = uint8Buff;
      expect(uint8Buff.toString()).assertEqual(result.buf.toString());
    })
  })
}