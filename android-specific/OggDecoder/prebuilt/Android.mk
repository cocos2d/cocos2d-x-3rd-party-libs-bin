LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_ogg_static
LOCAL_MODULE_FILENAME := ogg
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libogg.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE := cocos_vorbis_static
LOCAL_MODULE_FILENAME := vorbis
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libvorbis.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE := cocos_vorbisfile_static
LOCAL_MODULE_FILENAME := vorbisfile
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libvorbisfile.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)
