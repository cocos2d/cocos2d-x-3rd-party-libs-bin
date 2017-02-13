LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_flatbuffers_static

LOCAL_MODULE_FILENAME := flatbuffers

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
flatc.cpp \
flathash.cpp \
idl_gen_cpp.cpp \
idl_gen_fbs.cpp \
idl_gen_general.cpp \
idl_gen_go.cpp \
idl_gen_js.cpp \
idl_gen_php.cpp \
idl_gen_python.cpp \
idl_gen_text.cpp \
idl_parser.cpp \
reflection.cpp \
util.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..\

LOCAL_CPPFLAGS += -fexceptions
                                 
include $(BUILD_STATIC_LIBRARY)
