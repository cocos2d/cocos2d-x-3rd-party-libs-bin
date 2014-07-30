LOCAL_PATH := $(call my-dir)

# tiff
include $(CLEAR_VARS)
LOCAL_MODULE := tiff_static
LOCAL_MODULE_FILENAME := tiff_internal
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libtiff.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android
include $(PREBUILT_STATIC_LIBRARY)

# CCModuleTIFF + tiff.a
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_tiff_static
LOCAL_MODULE_FILENAME := tiff

LOCAL_SRC_FILES := $(LOCAL_PATH)/../../CCModuleTIFF.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := tiff_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos \
                    $(LOCAL_PATH)/../../../../cocos/platform/android \
                    $(LOCAL_PATH)/../../include/android

include $(BUILD_STATIC_LIBRARY)

$(call import-module,tiff/prebuilt/android)
