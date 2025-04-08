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

import hilog from '@ohos.hilog';
import data_rdb from '@ohos.data.rdb';
import libAddon from 'libentry.so'

// OHOS 关系型数据库：https://docs.openharmony.cn/pages/v3.2Beta/zh-cn/application-dev/reference/apis/js-apis-data-rdb.md/#datardbgetrdbstore
class MyStorage {
  static rdbStore:data_rdb.RdbStore;

  static createTable(table: string, callback?: Function) {
    let rdbStore = MyStorage.rdbStore;
    console.log('createTable: ' + rdbStore)
    const SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS " + table + " (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT NOT NULL, AGE INTEGER, SALARY REAL, CODES BLOB)"
    rdbStore.executeSql(SQL_CREATE_TABLE, [], (err:object) => {
      if (err) {
        console.info("ExecuteSql failed, err: " + err)
        if (callback != undefined)
          callback("Create failed");
        return
      }
      console.info('Create table done.');
      if (callback != undefined)
        callback("Create Success");
    })
    return;
  }

  static insert(table: string, callback?: Function) {

    let rdbStore = MyStorage.rdbStore;
    console.log('insert: ' + rdbStore)
    rdbStore.insert(table, {
      "NAME": "Lisa",
      "AGE": 18,
      "SALARY": 100.5,
      "CODES": new Uint8Array([1, 2, 3, 4, 5]),
    }, (status, rowId) => {
      if (status) {
        console.log("Insert is failed");
        if (callback != undefined)
          callback("Insert failed");
        return;
      }
      console.log("Insert is successful, rowId = " + rowId);
      if (callback != undefined)
        callback("Insert Success");
    })
  }

  static query(table: string, callback?: Function) {
    let predicates = new data_rdb.RdbPredicates(table)
    predicates.equalTo("NAME", "Lisa")
    let rdbStore = MyStorage.rdbStore;
    console.log('query: ' + rdbStore)
    rdbStore.query(predicates, ["NAME", "AGE", "SALARY", "CODES"], (err, resultSet) => {
      if (err) {
        console.info("Query failed, err: " + err)
        if (callback != undefined)
          callback("Query failed");
        return
      }
      console.log("ResultSet column names: " + resultSet.columnNames)
      console.log("ResultSet column count: " + resultSet.columnCount)
      if (callback != undefined)
        callback("Query Success");
    })
  }
}

data_rdb.getRdbStore(getContext(this), { name: "RdbTest.db" }, 1, (err, rdbStore) => {
  if (err) {
    console.info("Get RdbStore failed, err: " + err)
    return
  }
  console.log("Get RdbStore successfully.")
  MyStorage.rdbStore = rdbStore;
});

// JS 侧绑定静态方法 (name: 方法名, function: 方法)
libAddon.JSBind.bindFunction("MyStorage.createTable", MyStorage.createTable);
libAddon.JSBind.bindFunction("MyStorage.insert", MyStorage.insert);
libAddon.JSBind.bindFunction("MyStorage.query", MyStorage.query);

@Entry
@Component
struct Index {
  @State message: string = 'DoSomethingFromNative'

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            libAddon.DoSomethingFromNative();
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
