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

import { Reflect } from './reflect';
import { TypeMeta } from './type_meta';

const typedNameTbl: { [key: string]: [string] } = {
    'std::string': ['string']
};

export class JSBind {

    private static dump( reflect: Reflect ): string {
        const functionList = reflect.functionTbl;
        const functionCodeList = [];

        for (const func of functionList) {
            const args = (
                '(' + func.argTypeList.map(
                    (typeMeta: TypeMeta, num: number) => 'p' + num + ': ' + typeMeta.name
                ).join(', ') + ')'
            );

            const funcCode = (
                'export declare function ' + func.name + args + ': ' + func.returnType.name + ';');
            functionCodeList.push(funcCode);
            console.info(funcCode);
        }

        return functionCodeList.join('\n\n') + '\n';
    }

    public static fetchSymbols(addon: any): Reflect {
        const reflect = new Reflect(addon);

        return reflect;
    }

    public static dumpDTS(addon: any): string {
        const symbols = this.fetchSymbols(addon);

        return this.dump(symbols);
    }
}
