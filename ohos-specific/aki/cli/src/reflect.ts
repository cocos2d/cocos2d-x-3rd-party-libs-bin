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

import { TypeMeta } from './type_meta';
import { TypeFlag } from './type_flag';
import { BindFunction } from './bind_function';

export class Reflect {
    constructor(addon: any) {
        this.addon = addon;

        addon.JSBind.reflect(this.outputBuildInType.bind(this), this.outputFunction.bind(this));
    }

    formatTypeName(meta: TypeMeta, tplParams?: number[]): string {
        const flags = meta.flag;
        const kind = flags & TypeFlag.TYPE_MASK;

        let result: string;

        switch (kind) {
            case TypeFlag.IS_VOID:
                result = 'void';
                break;
            case TypeFlag.IS_BOOLEAN:
                result = 'boolean';
                break;
            case TypeFlag.IS_ARITHMETIC:
                result = 'number';
                break;
            case TypeFlag.IS_STRING:
                result = 'string';
                break;
            case TypeFlag.IS_ARRAY:
                if (tplParams !== undefined && typeof tplParams[0] === 'number') {
                    result = this.typeIdTbl[tplParams[0]].name + '[]';
                } else {
                    result = 'any';
                }
                break;
            case TypeFlag.IS_FUNCTION:
                console.info('function: ' + tplParams);
                if (tplParams !== undefined) {
                    const rtn: number = tplParams[0];
                    const params: number[] = tplParams.slice(1);
                    result = (
                        '(' + params.map(
                            (typeId: number, index: number) => 'a' + index + ': ' + this.typeIdTbl[typeId].name
                        ).join(', ') + ')'
                    );
                    result += ' => ' + this.typeIdTbl[rtn].name;
                } else {
                    result = 'function';
                }
                break;
            default:
                result = 'any';
        }
        return result;
    }

    outputBuildInType(id: number, flag: number) {
        console.info('outputBuildInType: ' + id + ', ' + flag);
        const meta: TypeMeta = {id, flag};
        meta.name = this.formatTypeName(meta);
        console.info('outputBuildInType meta: ' + meta.name);
        this.typeIdTbl[id] = meta;
    }

    outputFunction(name: string, params: number[]) {
        console.info('outputFunction: ' + name + ', ' + params);
        const typeList = params.map((id: number) => {
            if (this.typeIdTbl[id]) {
                console.info(this.typeIdTbl[id].name);
            } else {
                let flag: TypeFlag = TypeFlag.NONE;
                let params: number[] = [];
                this.addon.JSBind.queryType(id, (nativeFlag: number, nativeParams: number[]) => {
                    console.info('flag from native: ' + nativeFlag);
                    flag = nativeFlag;
                    params = nativeParams;
                });
                const meta: TypeMeta = {id, flag};
                meta.name = this.formatTypeName(meta, params);
                this.typeIdTbl[id] = meta;
                console.info(this.typeIdTbl[id].name);
            }
            return this.typeIdTbl[id];
        });

        const bindFunction = new BindFunction(
            name,
            typeList[0],
            typeList.slice(1),
            true);

        this.functionTbl.push(bindFunction);
    }

    addon: any;

    typeIdTbl: { [id: number]: TypeMeta } = {};

    functionTbl: BindFunction[] = [];
}
