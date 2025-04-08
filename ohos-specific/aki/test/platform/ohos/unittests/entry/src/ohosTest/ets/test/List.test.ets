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

import functionArgumentsTest from './FunctionArguments/FunctionArguments.test'
import objectWrapTest from './ObjectWrap/ObjectWrap.test'
import nestedClassTest from './NestedClass/NestedClass.test'
import callbackTest from './Callback/Callback.test'
import callbackObjectTest from './CallbackObject/CallbackObject.test'
import equivalenceTest from './EquivalenceTest/Equivalence.test'
import overloaderTest from './Overloader/Overloader.test'
import checkerTest from './Checker/Checker.test'
import propertyTest from './Property/Property.test'
import arrayTest from './Array/Array.test'
import jsonObjectTest from './JsonObject/JsonObject.test'
import numberTest from './Number/Number.test'
import jsFunctionTest from './JSFunction/JSFunction.test'
import napiTest from './Napi/Napi.test'
import reference4ObjectTest from './Reference4Object/Reference4Object.test'
import valueTest from './Value/Value.test'
import asyncTasksTest from './AsyncTasks/AsyncTasks.test'
import arrayBufferTest from './ArrayBuffer/ArrayBuffer.test'
import promiseTest from './Promise/Promise.test'
export default function testsuite() {
  functionArgumentsTest();
  objectWrapTest();
  nestedClassTest();
  callbackTest();
  callbackObjectTest();
  equivalenceTest();
  overloaderTest();
  checkerTest();
  propertyTest();
  arrayTest();
  jsonObjectTest();
  numberTest();
  jsFunctionTest();
  napiTest();
  reference4ObjectTest();
  valueTest();
  asyncTasksTest();
  arrayBufferTest();
  promiseTest();
}