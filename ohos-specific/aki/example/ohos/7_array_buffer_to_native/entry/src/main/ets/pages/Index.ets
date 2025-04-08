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
import libAddon from 'libarraybuffer2native.so'

@Entry
@Component
struct Index {
  @State message1: string = 'PassingArrayBufferReturnVoid'
  @State message2: string = 'PassingArrayBufferReturnArrayBuffer'
  @State message3: string = 'PassingArrayBufferReturnInt8Array'
  @State message4: string = 'PassingArrayBufferReturnInt16Array'
  @State message5: string = 'ArrayBufferHandler'
  @State message6: string = 'AsyncTaskArrayBufferReturnArrayBuffer'

  build() {
    Row() {
      Column() {
        Text(this.message1)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let buff: ArrayBuffer = new ArrayBuffer(8);
            let uint8Buff1: Uint8Array = new Uint8Array(buff);
            uint8Buff1[0] = 0;
            uint8Buff1[1] = 1;
            uint8Buff1[2] = 2;
            uint8Buff1[3] = 3;
            libAddon.PassingArrayBufferReturnVoid(buff);
            this.message1 = uint8Buff1.toString();
          })
        Text(this.message2)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let buff: ArrayBuffer = new ArrayBuffer(8);
            let uint8Buff1: Uint8Array = new Uint8Array(buff);
            uint8Buff1[0] = 0;
            uint8Buff1[1] = 1;
            uint8Buff1[2] = 2;
            uint8Buff1[3] = 3;
            let result: ArrayBuffer = libAddon.PassingArrayBufferReturnArrayBuffer(buff);
            uint8Buff1 = new Uint8Array(result);
            this.message2 = uint8Buff1.toString();
          })
        Text(this.message3)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let buff: ArrayBuffer = new ArrayBuffer(8);
            let int8Buff: Int8Array = new Int8Array(buff);
            int8Buff[0] = 0;
            int8Buff[1] = 1;
            int8Buff[2] = 2;
            int8Buff[3] = 3;
            let result: Int8Array = libAddon.PassingArrayBufferReturnInt8Array(buff);
            this.message3 = result.toString();
          })
        Text(this.message4)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let buff: ArrayBuffer = new ArrayBuffer(16);
            let int16Buff: Int16Array = new Int16Array(buff);
            int16Buff[0] = 0;
            int16Buff[1] = 1;
            int16Buff[2] = 2;
            int16Buff[3] = 3;
            let result: Int16Array = libAddon.PassingArrayBufferReturnInt16Array(buff);
            this.message4 = result.toString();
          })
        Text(this.message5)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let buff: ArrayBuffer = new ArrayBuffer(4);
            let uint8Buff: Uint8Array = new Uint8Array(buff);
            uint8Buff[0] = 0;
            uint8Buff[1] = 1;
            uint8Buff[2] = 2;
            uint8Buff[3] = 3;
            let result = new libAddon.ArrayBufferHandler();
            result.buf = uint8Buff;
            this.message5 = result.buf.toString();
          })
        Text(this.message6)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let buff: ArrayBuffer = new ArrayBuffer(4);
            let uint8Buff: Uint8Array = new Uint8Array(buff);
            uint8Buff[0] = 0;
            uint8Buff[1] = 1;
            uint8Buff[2] = 2;
            uint8Buff[3] = 3;
            libAddon.asyncTaskArrayBufferReturnArrayBuffer(uint8Buff).then(res => {
              let uint8Buff1 = new Uint8Array(res);
              this.message6 = uint8Buff1.toString();
            });
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
