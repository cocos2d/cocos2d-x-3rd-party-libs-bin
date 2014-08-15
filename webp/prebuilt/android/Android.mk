LOCAL_PATH := $(call my-dir)

# webp lib
include $(CLEAR_VARS)
LOCAL_MODULE := webp_static
LOCAL_MODULE_FILENAME := webp_internal
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libwebp.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android

LOCAL_STATIC_LIBRARIES := cpufeatures

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS := -DHAVE_NEON=1
endif

include $(PREBUILT_STATIC_LIBRARY)

# webp module
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_webp_static
LOCAL_MODULE_FILENAME := libwebp
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../CCModuleWEBP.cpp

LOCAL_STATIC_LIBRARIES := webp_static
LOCAL_STATIC_LIBRARIES += cocos2dx_static

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos \
                    $(LOCAL_PATH)/../../../../cocos/platform/android \
                    $(LOCAL_PATH)/../../include/android

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../..

include $(BUILD_STATIC_LIBRARY)

$(call import-module,tiff/prebuilt/android)
$(call import-module, android/cpufeatures) # needed by webp lib
