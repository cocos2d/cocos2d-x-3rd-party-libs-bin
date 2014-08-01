LOCAL_PATH := $(call my-dir)

# wep lib
include $(CLEAR_VARS)
LOCAL_MODULE := webp_static
LOCAL_MODULE_FILENAME := webp_internal
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libwebp.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android

LOCAL_WHOLE_STATIC_LIBRARIES := cpufeatures

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS := -DHAVE_NEON=1
endif

include $(PREBUILT_STATIC_LIBRARY)

$(call import-module, android/cpufeatures)

# web module
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_webp_static
LOCAL_MODULE_FILENAME := webp
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../CCModuleWEP.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos \
                    $(LOCAL_PATH)/../../../../cocos/platform/android \
                    $(LOCAL_PATH)/../../include/android

include $(BUILD_STATIC_LIBRARY)
