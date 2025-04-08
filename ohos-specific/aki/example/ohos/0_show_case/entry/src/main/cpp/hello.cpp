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
#include <hilog/log.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <aki/jsbind.h>
#include <sys/mman.h>


void OnSurfaceCreatedCB(OH_NativeXComponent *component, void *window) {
    AKI_LOG(INFO) << "OnSurfaceCreatedCB";
    uint64_t width;
    uint64_t height;
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width, &height);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        AKI_LOG(ERROR) << "OH_NativeXComponent_GetXComponentSize failed";
    }
    // 设置 OHNativeWindowBuffer 的宽高
    int32_t code = SET_BUFFER_GEOMETRY;
    // 这里的nativeWindow是从上一步骤中的回调函数中获得的
    OHNativeWindow* nativeWindow = reinterpret_cast<OHNativeWindow*>(window);
    ret = OH_NativeWindow_NativeWindowHandleOpt(nativeWindow, code, width, height);
    // 设置 OHNativeWindowBuffer 的步长
    code = SET_STRIDE;
    int32_t stride = 0x8;
    ret = OH_NativeWindow_NativeWindowHandleOpt(nativeWindow, code, stride);
    
    OHNativeWindowBuffer* buffer = nullptr;
    int fenceFd;
    // 通过 OH_NativeWindow_NativeWindowRequestBuffer 获取 OHNativeWindowBuffer 实例
    OH_NativeWindow_NativeWindowRequestBuffer(nativeWindow, &buffer, &fenceFd);
    // 通过 OH_NativeWindow_GetBufferHandleFromNative 获取 buffer 的 handle
    BufferHandle* bufferHandle = OH_NativeWindow_GetBufferHandleFromNative(buffer);
    if (bufferHandle == nullptr) {
        AKI_LOG(ERROR) << "get buffer failed";
    }
    
    AKI_LOG(INFO) << "bufferHandle size: " << bufferHandle->size;
    // 使用系统mmap接口拿到bufferHandle的内存虚拟地址
    void* mappedAddr = mmap(bufferHandle->virAddr, bufferHandle->size, PROT_READ | PROT_WRITE, MAP_SHARED, bufferHandle->fd, 0);
    if (mappedAddr == MAP_FAILED) {
        AKI_LOG(ERROR) << "mmap failed";
        return;
    }
    
    AKI_LOG(INFO) << "begin to set data to buffer";
    static uint32_t value = 0x00;
     value++;
     uint32_t *pixel = static_cast<uint32_t *>(mappedAddr); // 使用mmap获取到的地址来访问内存
     for (uint32_t x = 0; x < width; x++) {
         for (uint32_t y = 0;  y < height; y++) {
             *pixel++ = value;
         }
     }
    
    // 设置刷新区域，如果Region中的Rect为nullptr,或者rectNumber为0，则认为OHNativeWindowBuffer全部有内容更改。
    Region region{nullptr, 0};
    // 通过OH_NativeWindow_NativeWindowFlushBuffer 提交给消费者使用，例如：显示在屏幕上。
    OH_NativeWindow_NativeWindowFlushBuffer(nativeWindow, buffer, fenceFd, region);
    
    // 内存使用完记得去掉内存映射
    int result = munmap(mappedAddr, bufferHandle->size);
    if (result == -1) {
        // munmap failed
    }
}

void OnSurfaceChangedCB(OH_NativeXComponent *component, void *window) {
    AKI_LOG(INFO) << "OnSurfaceChangedCB";
}
void OnSurfaceDestroyedCB(OH_NativeXComponent *component, void *window) {
    AKI_LOG(INFO) << "OnSurfaceDestroyedCB";
}
void DispatchTouchEventCB(OH_NativeXComponent *component, void *window) {
    AKI_LOG(INFO) << "DispatchTouchEventCB";
}
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_value exportInstance = nullptr;
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        AKI_LOG(ERROR) << "Export: napi_get_named_property fail";
        return exports;
    }

    OH_NativeXComponent *nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void **>(&nativeXComponent)) != napi_ok) {
        AKI_LOG(ERROR) << "Export: napi_unwrap fail";
        return exports;
    }
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        AKI_LOG(ERROR) << "Export: OH_NativeXComponent_GetXComponentId fail";
        return exports;
    }
    AKI_LOG(INFO) << "Export: OH_NativeXComponent_GetXComponentId: " << idStr;

    OH_NativeXComponent_Callback renderCallback;
    renderCallback.OnSurfaceCreated = OnSurfaceCreatedCB;
    renderCallback.OnSurfaceChanged = OnSurfaceChangedCB;
    renderCallback.OnSurfaceDestroyed = OnSurfaceDestroyedCB;
    renderCallback.DispatchTouchEvent = DispatchTouchEventCB;
    OH_NativeXComponent_RegisterCallback(nativeXComponent, &renderCallback);

    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "nativerender",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) {
    napi_module_register(&demoModule);
}
