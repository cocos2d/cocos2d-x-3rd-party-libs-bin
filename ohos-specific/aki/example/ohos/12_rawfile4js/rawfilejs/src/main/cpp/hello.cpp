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

#include <aki/jsbind.h>
#include <rawfile/raw_file_manager.h>

namespace {
struct Descriptor {
    int32_t fd;
    int64_t offset;
    int64_t length;
};

int GetFileCount(napi_value rsmgr, std::string dir)
{
    napi_env env = aki::JSBind::GetScopedEnv();
    NativeResourceManager *mNativeResMgr = OH_ResourceManager_InitNativeResourceManager(env, rsmgr);
    
    // 获取对应的rawDir指针对象
    RawDir* rawDir = OH_ResourceManager_OpenRawDir(mNativeResMgr, dir.c_str());
    
    // 获取rawDir下文件及文件夹数量
    return OH_ResourceManager_GetRawFileCount(rawDir);
}

std::vector<std::string> GetFileList(napi_value rsmgr, std::string dir)
{
    napi_env env = aki::JSBind::GetScopedEnv();
    NativeResourceManager *mNativeResMgr = OH_ResourceManager_InitNativeResourceManager(env, rsmgr);
    
    // 获取对应的rawDir指针对象
    RawDir* rawDir = OH_ResourceManager_OpenRawDir(mNativeResMgr, dir.c_str());
    
    // 获取rawDir下文件及文件夹数量
    int count = OH_ResourceManager_GetRawFileCount(rawDir);
    std::vector<std::string> tempArray;
    for (int i = 0; i < count; i++) {
        std::string filename = OH_ResourceManager_GetRawFileName(rawDir, i);
        tempArray.emplace_back(filename);
    }
    
    return tempArray;
}

Descriptor GetRawFileDescriptor(napi_value rsmgr, std::string filename)
{
    napi_env env = aki::JSBind::GetScopedEnv();
    NativeResourceManager *mNativeResMgr = OH_ResourceManager_InitNativeResourceManager(env, rsmgr);
    
    // 获取rawfile指针对象
    RawFile *rawFile = OH_ResourceManager_OpenRawFile(mNativeResMgr, filename.c_str());
    if (rawFile != nullptr) {
        AKI_LOG(INFO) << "OH_ResourceManager_OpenRawFile success";
    }
    
    // 获取rawfile的描述符RawFileDescriptor {fd, offset, length}
    RawFileDescriptor descriptor;
    OH_ResourceManager_GetRawFileDescriptor(rawFile, descriptor);
    // 关闭打开的指针对象
    OH_ResourceManager_CloseRawFile(rawFile);
    OH_ResourceManager_ReleaseNativeResourceManager(mNativeResMgr);
    
    Descriptor desc = {descriptor.fd, descriptor.start, descriptor.length};
    
    return desc;
}
}

JSBIND_GLOBAL() {
    JSBIND_FUNCTION(GetFileCount, "getFileCount");
    JSBIND_FUNCTION(GetFileList, "getFileList");
    JSBIND_FUNCTION(GetRawFileDescriptor, "getRawFileDescriptor");
}

JSBIND_CLASS(Descriptor) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_PROPERTY(fd);
    JSBIND_PROPERTY(offset);
    JSBIND_PROPERTY(length);
}

JSBIND_ADDON(rawfilejs);
