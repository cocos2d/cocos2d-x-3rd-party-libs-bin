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

export default function asyncTasksTest() {
  describe('AsyncTasksTest', ()=> {
    it('AsyncTaskReturnVoid', 0, async (done:Function)=> {
      libaki.AsyncTaskReturnVoid().then(() => {
        done();
      })
    })
    it('AsyncTaskLongReturnLongMin', 0, async (done:Function)=> {
      libaki.AsyncTaskLongReturnLong(-2147483648).then((result) => {
        expect(result).assertEqual(-2147483648);
        done();
      })
    })
    it('AsyncTaskLongReturnLongMax', 0, async (done:Function)=> {
      libaki.AsyncTaskLongReturnLong(2147483647).then((result) => {
        expect(result).assertEqual(2147483647);
        done();
      })
    })
    it('AsyncTaskLongLongFunctionReturnLong', 0, async (done:Function)=> {
      libaki.AsyncTaskLongLongFunctionReturnLong(-2147483648, 2147483647, (a, b, c) => {
        expect(c).assertEqual('aki from c++');
        return a + b;
      }).then((result) => {
        expect(result).assertEqual(-1);
        done();
      })
    })
    it('TaskRunner_DoTask', 0, async (done:Function)=> {
      let taskRunner = new libaki.TaskRunner();
      taskRunner.DoTask().then(res => {
        expect(res).assertEqual(1);
        done();
      });
    })
    it('TaskRunner_DoTaskReturnVoid', 0, async (done:Function)=> {
      let taskRunner = new libaki.TaskRunner();
      taskRunner.DoTaskReturnVoid().then(() => {
        done();
      });
    })
    it('TaskRunner_DoTaskReturnData', 0, async (done:Function)=> {
      let taskRunner = new libaki.TaskRunner();
      taskRunner.DoTaskReturnData().then(res => {
        expect(res.name).assertEqual('aki');
        done();
      });
    })
  })
}