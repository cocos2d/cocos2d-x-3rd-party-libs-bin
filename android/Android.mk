#config for chipmunk
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_chipmunk_static
LOCAL_MODULE_FILENAME := chipmunk
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libchipmunk.a
include $(PREBUILT_STATIC_LIBRARY)

#config for box2d
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_box2d_static
LOCAL_MODULE_FILENAME := box2d
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libbox2d.a
include $(PREBUILT_STATIC_LIBRARY)

#config for cjson
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_cjson_static
LOCAL_MODULE_FILENAME := cjson
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libcjson.a
include $(PREBUILT_STATIC_LIBRARY)

#config for convertutf
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_convertutf_static
LOCAL_MODULE_FILENAME := convertutf
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libconvertutf.a
include $(PREBUILT_STATIC_LIBRARY)

#config for curl
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_curl_static
LOCAL_MODULE_FILENAME := curl
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libcurl.a
LOCAL_STATIC_LIBRARIES += cocos_ssl_static
LOCAL_STATIC_LIBRARIES += cocos_crypto_static
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_crypto_static
LOCAL_MODULE_FILENAME := crypto
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE := cocos_ssl_static
LOCAL_MODULE_FILENAME := ssl
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

#edtaa3func
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_edtaa3func_static
LOCAL_MODULE_FILENAME := edtaa3func
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libedtaa3func.a
include $(PREBUILT_STATIC_LIBRARY)

#freetype2
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_freetype2_static
LOCAL_MODULE_FILENAME := freetype2
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libfreetype.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/freetype
include $(PREBUILT_STATIC_LIBRARY)

#jpeg
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_jpeg_static
LOCAL_MODULE_FILENAME := jpeg
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)

#png
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_png_static
LOCAL_MODULE_FILENAME := png
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libpng.a
include $(PREBUILT_STATIC_LIBRARY)

#tiff
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_tiff_static
LOCAL_MODULE_FILENAME := tiff
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libtiff.a
include $(PREBUILT_STATIC_LIBRARY)

#tinyxml
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_tinyxml2_static
LOCAL_MODULE_FILENAME := tinyxml2
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libtinyxml2.a
include $(PREBUILT_STATIC_LIBRARY)

#minizip
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_minizip_static
LOCAL_MODULE_FILENAME := minizip
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libminizip.a
include $(PREBUILT_STATIC_LIBRARY)

#webp
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_webp_static
LOCAL_MODULE_FILENAME := webp
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libwebp.a
include $(PREBUILT_STATIC_LIBRARY)

#websockets
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_websockets_static
LOCAL_MODULE_FILENAME := websockets
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libwebsockets.a
include $(PREBUILT_STATIC_LIBRARY)

#xxhash
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_xxhash_static
LOCAL_MODULE_FILENAME := xxhash
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libxxhash.a
include $(PREBUILT_STATIC_LIBRARY)

##xxtea
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_xxtea_static
LOCAL_MODULE_FILENAME := xxtea
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libxxtea.a
include $(PREBUILT_STATIC_LIBRARY)

##zlib
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_zlib_static
LOCAL_MODULE_FILENAME := zlib
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libz.a
include $(PREBUILT_STATIC_LIBRARY)

##luasocket
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_luasocket_static
LOCAL_MODULE_FILENAME := luasocket
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libluasocket.a
include $(PREBUILT_STATIC_LIBRARY)

##luajit
# jit only when not using mips
# non-jit for mips
include $(CLEAR_VARS)
ifneq ($(TARGET_ARCH_ABI),mips)
LOCAL_MODULE := cocos_luajit_static
LOCAL_MODULE_FILENAME := luajit
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libluajit.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/luajit
else
LOCAL_MODULE := cocos_lua_static
LOCAL_MODULE_FILENAME := lua
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/liblua.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/luajit
endif
include $(PREBUILT_STATIC_LIBRARY)

###jsb
# only when not using mips
# jsb not available yet on mips
ifneq ($(TARGET_ARCH_ABI),mips)
include $(CLEAR_VARS)
LOCAL_MODULE    := spidermonkey_static
LOCAL_MODULE_FILENAME := js_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libs/libjs_static.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/spidermonkey
LOCAL_CPPFLAGS := -D__STDC_LIMIT_MACROS=1 -Wno-invalid-offsetof
LOCAL_EXPORT_CPPFLAGS := -D__STDC_LIMIT_MACROS=1 -Wno-invalid-offsetof
include $(PREBUILT_STATIC_LIBRARY)
endif
