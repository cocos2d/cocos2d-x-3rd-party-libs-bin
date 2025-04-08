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

#include <napi/native_api.h>
#include <rawfile/raw_file_manager.h>
#include <aki/jsbind.h>

std::vector<std::string> GetFileList(napi_value rawFile, std::string dirName)
{
    napi_env env = aki::JSBind::GetScopedEnv();
    NativeResourceManager *mNativeResMgr = OH_ResourceManager_InitNativeResourceManager(env, rawFile);
    
    // 获取对应的rawDir指针对象
    RawDir* rawDir = OH_ResourceManager_OpenRawDir(mNativeResMgr, dirName.c_str());
    
    // 获取rawDir下文件及文件夹数量
    int count = OH_ResourceManager_GetRawFileCount(rawDir);
    
    // 遍历获取文件名称，并保存
    std::vector<std::string> tempArray;
    for(int i = 0; i < count; i++) {
        std::string filename = OH_ResourceManager_GetRawFileName(rawDir, i);
        tempArray.emplace_back(filename);
    }
    
    // 关闭打开的指针对象
    OH_ResourceManager_CloseRawDir(rawDir);
    OH_ResourceManager_ReleaseNativeResourceManager(mNativeResMgr);
    return tempArray;
}
JSBIND_GLOBAL(){
    JSBIND_FUNCTION(GetFileList, "getFileList");
}
JSBIND_ADDON(raw_file);