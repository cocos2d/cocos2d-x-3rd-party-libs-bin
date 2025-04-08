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

export class VectorHandle {
  passingVoidReturnVectorLong: () => Array<number>;
  passingVectorLongReturnVectorLong: (array: Array<number>) => Array<number>;
}

export const passingVoidReturnVectorLong: () => Array<number>;

export const passingVectorLongReturnVectorLong: (array: Array<number>) => Array<number>;

export const passingInt8ArrayReturnInt8Array: (buff: Int8Array) => ArrayBuffer;

export const passingUint8ArrayReturnUint8Array: (buff: Uint8Array) => ArrayBuffer;

export const passingArrayBufferReturnArrayBuffer: (buff: ArrayBuffer) => ArrayBuffer;

export const passingInt16ArrayReturnInt16Array: (buff: Int16Array) => ArrayBuffer;

export const passingUint16ArrayReturnUint16Array: (buff: Uint16Array) => ArrayBuffer;

export const passingInt32ArrayReturnInt32Array: (buff: Int32Array) => ArrayBuffer;

export const passingUint32ArrayReturnUint32Array: (buff: Uint32Array) => ArrayBuffer;

export const passingBigInt64ArrayReturnBigInt64Array: (buff: BigInt64Array) => ArrayBuffer;

export const passingBigUint64ArrayReturnBigUint64Array: (buff: BigUint64Array) => ArrayBuffer;

export const asyncTaskReturnArrayBufferWithCommit: () => Promise<ArrayBuffer>;

export const PassingArrayBufferReturnInt16Array: (buff: ArrayBuffer) => Int16Array;

export const PassingArrayBufferReturnInt8Array: (buff: ArrayBuffer) => Int8Array;

export const PassingArrayBufferReturnVoid: (buff: ArrayBuffer) => void;


export class ArrayBufferHandler {
  buf: Uint8Array;
}

export const asyncTaskArrayBufferReturnArrayBuffer: (uint8buff: Uint8Array) => Promise<ArrayBuffer>;

export class TaskRunnerData {
  name: string;
}

export class TaskRunner {
  DoTaskReturnVoid: () => Promise<void>;
  DoTask: () => Promise<number>;
  DoTaskReturnData: () => Promise<TaskRunnerData>;
}

export const AsyncTaskReturnVoid: () => Promise<object>;

export const AsyncTaskLongLongFunctionReturnLong: (min: number, max: number, func: (a: number, b: number, c: string) => number) => Promise<number>;

export const AsyncTaskLongReturnLong: (a: number) => Promise<number>;


export const CallbackInvoke: (func: () => void) => void;

export const CallbackInvokeFromThread: (func: () => void) => void;

export const CallbackReturnVoid: (func: () => void) => void;

export const SafetyCallbackReturnVoid: (func: () => void) => void;

export const CallbackReturnBool_True: (func: (value: boolean) => boolean) => boolean;

export const SafetyCallbackReturnBool_True: (func: (value: boolean) => boolean) => boolean;

export const CallbackReturnInt_Int: (func: (value: number) => number) => number;

export const CallbackReturnString_String: (func: (value: string) => string) => string;

export const SafetyCallbackReturnString_String: (func: (value: string) => string) => string;

export const CallbackReturnDouble_Double: (func: (value: number) => number) => number;

export const SafetyCallbackReturnDouble_Double: (func: (value: number) => number) => number;

export const SafetyCallbackReturnDouble_Double_Num_X2: (func: (value: number) => number) => number;


export class CallbackObject {
  onInvoke: () => void
  onResponse: (func: (value: string) => string) => void
  onResponseReturnStr: (func: (value: string) => string) => void
  InvokeOnResponseReturnStr: () => void
  static InvokeOnInvoke: (obj: CallbackObject) => void
  static InvokeOnResponse: (obj: CallbackObject) => void
}


export const PassingBoolReturnBool: (param: boolean) => boolean;

export const PassingInt32ReturnInt32: (param: number) => number;

export const PassingInt64ReturnInt64: (param: number) => number;

export const PassingDoubleReturnDouble: (param: number) => number;

export const PassingFloatReturnFloat: (param: number) => number;

export const PassingStringReturnString: (param: string) => string;

export const PassingConstStringRefReturnString: (param: string) => string;

export const PassingConstCStrPtrReturnConstCStrPtr: (param: string) => string;

export const PassingCStrPtrReturnConstCStrPtr: (param: string) => string;

export const PassingCStrPtrReturnCStrPtr: (param: string) => string;

export const PassingNoneReturnBool: () => boolean;

export const callJSFunctionReturnVoid: () => string;

export const PassingVectorIntReturnBool: (param: Array<number>) => boolean;

export const P_PassingIntReturnInt: (param: number) => Promise<number>;

export const PassingVectorIntReturnVectorInt: (param: Array<number>) => Array<number>;

export const passingArrayStrReturnArrayStr: (param: Array<string>) => Array<string>;

export const passingArrayIntReturnArrayInt: (param: Array<number>) => Array<number>;

export const PassingVectorUint8ReturnVectorUint8: (param: Array<number>) => Array<number>;

export const passingArrayIntReturnBool: (param: Array<number>) => boolean;

export const PassingVectorFloatReturnVectorFloat: (param: Array<number>) => Array<number>;

export const PassingVectorBoolReturnVectorBool: (param: Array<boolean>) => Array<boolean>;

export const PassingConstStringRef2ReturnString: (param1: string, param2: string) => string;

export const PassingConstStringRef3ReturnString: (param1: string, param2: string, param3: string) => string;

export const PassingConstStringRef4ReturnString: (param1: string, param2: string, param3: string, param4: string) => string;

export const PassingConstStringRef5ReturnString: (param1: string, param2: string, param3: string, param4: string, param5: string) => string;

export const PassingConstStringRef6ReturnString: (param1: string, param2: string, param3: string, param4: string, param5: string, param6: string) => string;

export const PassingConstStringRef7ReturnString: (param1: string, param2: string, param3: string, param4: string, param5: string, param6: string, param7: string) => string;

export const PassingConstStringRef8ReturnString: (param1: string, param2: string, param3: string, param4: string, param5: string, param6: string, param7: string, param8: string) => string;

export class JSBind {
  static bindFunction: (param: string, func: (value: string) => string) => void

  static initTaskRunner(param: string)
}

export class TestObject {
  constructor()

  constructor(param: number)

  static MultiplyObject:(obj1: object, obj2: object)=>object

  static MultiplyObjectPtr:(obj1: object, obj2: object)=>object

  static MultiplyObjectConstPtr:(obj1: object, obj2: object)=>object

  static MultiplyObjectSmartPtr:(obj1: object, obj2: object)=>object

  static MultiplyObjectSmartPtrReturnSmartPtr:(obj: object)=>TestObject

  P_PassingIntReturnInt: (param: number) => Promise<number>

  static P_StaticPassingIntReturnInt: (param: number) => Promise<number>

  value: number

  fake: number

  PlusOne: () => number

  GetFake: () => number

  GetValue: () => number

  Multiply: (param: number) => number

  SetValue: (param: number) => void

  static CreateObject(): CreateObjectClass

  static CreateObjectPtr(): CreateObjectClass
}


export class CreateObjectClass {
  value: number
}


export class EquivalenceTest {
  static ShowByValue: (obj: object) => number
}

export const passingVoidReturnMapLong: () => Map<string, number>;

export const passingMapLongReturnMapLong: (map: object) => Map<string, number>;

export class JsonObjectHandle {
  passingVoidReturnMapLong: () => Map<string, number>;

  passingMapLongReturnMapLong: (map: object) => Map<string, number>;
}

export const passingNapiNumReturnNum: (param: number) => number;

export const passingUint8ReturnUint8: (param: number) => number;

export const passingInt8ReturnInt8: (param: number) => number;

export const passingUint16ReturnUint16: (param: number) => number;

export const passingInt16ReturnInt16: (param: number) => number;

export const passingShortReturnShort: (param: number) => number;

export const ReturnPromiseResolveImmediately: () => Promise<string>;

export const ReturnPromiseResolveLater: () => Promise<string>;


export class NestedOne {
  GetNested: () => string
}

export class NestedTwo {
  GetNested: () => string
}

export class NestedThree {
  GetNested: () => string
}


export class OverloaderTest {
  constructor(param: boolean)

  constructor(param: boolean, param2: number)

  constructor(param: boolean, param2: number, param3: string)

  value1: boolean
  value2: boolean
  value3: boolean
}

export const MakePerson: () => Person;

export class Person {
   age: number
   name: string
   weight: number
}


export class Reference {
  count: number;
  constructor(count:number);
  ChangeByReference:(ref: Reference) => void;
  ChangeByPointer:(ref: Reference) => void;
  static MultiCountByReference:(ref: Reference,num:number) => void;
  static MultiCountByPointer:(ref: Reference,num:number) => void;
}

export const GrowUpByReference:(ref: Reference) => void;

export const GrowUpByPointer:(ref: Reference) => void;

export const PassingValueAsString:(param:string) => string;

export const PassingValueAsStringReturnValue:(param:string) => string;

export const PassingArrayValueReturnValue:(param:Array<string>) => string;

export const PassingArrayValueReturnArrayValue:(param: Array<string>) => string;

export const PassingArrayValueThenSetValue:(param: Array<string>) => void;

export const PassingValueAsBool:(param:boolean) => string;

export const PassingValueAsBoolReturnValue:(param:boolean) => string;

export const PassingValueAsInt:(param:number) => number;

export const PassingValueAsIntReturnValue:(param:number) => number;

export const PassingValueAsFunction:(func: (value: string) => string) => string;

export const PassingValueAsJsonObject:(param:object) => string;

export const PassingValueCheckIsNull:(param:object) => string;

export const PassingValueCheckIsUndefined:(param?:object) => string;

export const PassingValueCheckIsBool:(param:boolean) => boolean;

export const PassingValueCheckIsNumber:(param:number) => boolean;

export const PassingValueCheckIsString:(param:string) => boolean;

export const PassingValueCheckIsArray:(param:Array<string>) => boolean;

export const PassingValueCheckIsFunction:(param:Function) => boolean;

export const FromGlobalBundleManager:() => string;

export const ValueFromGlobalAsString:() => string;

export const FromGlobalJSONStringify:(param:object) => string;

export const FromGlobalJSONParse:(param:string) => string;

export const PassingValueAsUint8:(param:number) => number;

export const PassingValueAsInt8:(param:number) => number;

export const PassingValueAsUint16:(param:number) => number;

export const PassingValueAsInt16:(param:number) => number;

export const PassingValueAsInt64:(param:number) => number;

export const PassingValueAsFloat:(param:number) => number;

export const PassingValueAsDouble:(param:number) => number;

export class AkiValueData {

  value:Array<string>;
  SetValueFromNative: () => void;
}




