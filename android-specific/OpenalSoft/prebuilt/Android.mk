LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := openal_shared
LOCAL_MODULE_FILENAME := libopenal
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libopenal.so
include $(PREBUILT_SHARED_LIBRARY)
