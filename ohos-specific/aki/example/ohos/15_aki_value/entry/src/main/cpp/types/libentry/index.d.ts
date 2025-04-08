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

export const PassingValueAsString:(param:string) => string;

export const PassingValueAsStringReturnValue:(param:string) => string;

export const PassingArrayValueReturnValue:(param:Array<string>) => string;

export const PassingArrayValueReturnArrayValue:(param: Array<string>) => string;

export const PassingArrayValueThenSetValue:(param: Array<string>) => void;

export const PassingValueAsBool:(param:boolean) => string;

export const PassingValueAsBoolReturnValue:(param:boolean) => string;

export const PassingValueAsInt:(param:number) => number;

export const PassingValueAsIntReturnValue:(param:number) => number;

export const PassingValueAsFunction:(param:Function) => string;

export const PassingValueAsJsonObject:(param:object) => string;

export const PassingValueCheckIsNull:(param:object) => string;

export const PassingValueCheckIsUndefined:(param?:object) => string;

export const PassingValueCheckIsBool:(param:boolean) => string;

export const PassingValueCheckIsNumber:(param:number) => string;

export const PassingValueCheckIsString:(param:string) => string;

export const PassingValueCheckIsArray:(param:Array<string>) => string;

export const PassingValueCheckIsFunction:(param:Function) => string;

export const FromGlobalBundleManager:() => string;

export const FromGlobalJSONStringify:(param:object) => string;

export const FromGlobalJSONParse:(param:string) => string;

export class AkiValueData {

    value:Array<string>;
    SetValueFromNative: () => void;
}

