LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg_static
LOCAL_MODULE_FILENAME := jpeg_internal
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libjpeg.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android
include $(PREBUILT_STATIC_LIBRARY)

# CCModuleTIFF + jpeg.a
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_jpeg_static
LOCAL_MODULE_FILENAME := jpeg

LOCAL_SRC_FILES := $(LOCAL_PATH)/../../CCModuleJPEG.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := jpeg_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos \
                    $(LOCAL_PATH)/../../../../cocos/platform/android \
                    $(LOCAL_PATH)/../../include/android

include $(BUILD_STATIC_LIBRARY)

$(call import-module,jpeg/prebuilt/android)
