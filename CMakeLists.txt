cmake_minimum_required(VERSION 3.6)
project(external)

add_library(external empty.cpp)

add_subdirectory(Box2D)
add_subdirectory(chipmunk)
add_subdirectory(freetype2)
add_subdirectory(recast)
add_subdirectory(bullet)
add_subdirectory(jpeg)
add_subdirectory(openssl)
add_subdirectory(tiff)
add_subdirectory(uv)
add_subdirectory(webp)
add_subdirectory(websockets)
add_subdirectory(tinyxml2)
add_subdirectory(xxhash)
add_subdirectory(xxtea)
add_subdirectory(clipper)
add_subdirectory(edtaa3func)
add_subdirectory(ConvertUTF)
add_subdirectory(poly2tri)
add_subdirectory(md5)

target_link_libraries(external
    ext_box2d
    ext_chipmunk
    ext_freetype
    ext_recast
    ext_jpeg
    ext_uv
    ext_webp
    ext_bullet
    ext_ssl
    ext_crypto
    ext_tiff
    ext_websockets
    ext_tinyxml2
    ext_xxhash
    ext_xxtea
    ext_clipper
    ext_edtaa3func
    ext_convertUTF
    ext_poly2tri
    ext_md5
)

# use lua/js specific libs by property to prevent conflict
if(BUILD_JS_LIBS)
    add_subdirectory(spidermonkey)
    set_property(TARGET external APPEND PROPERTY
        CC_JS_DEPEND ext_spidermonkey
    )
endif()
if(BUILD_LUA_LIBS)
    add_subdirectory(lua/luajit)
    add_subdirectory(lua/tolua)
    add_subdirectory(lua/luasocket)
    set_property(TARGET external APPEND PROPERTY 
        CC_LUA_DEPEND ext_luajit ext_tolua ext_luasocket
    )
endif()

if(NOT LINUX)
    add_subdirectory(curl)
    add_subdirectory(png)
    target_link_libraries(external 
        ext_curl
        ext_png
    )
endif(NOT LINUX)
    
if(LINUX)
    add_subdirectory(linux-specific/fmod)
    target_link_libraries(external 
        ext_fmod
    )
endif()

if(ANDROID)
    add_subdirectory(android-specific/cpufeatures)
    add_subdirectory(android-specific/pvmp3dec)
    add_subdirectory(android-specific/tremolo)
    target_link_libraries(external 
        ext_cpufeatures 
        ext_pvmp3dec 
        ext_tremolo
    )
endif()

if(WINDOWS)
    # sqlite3 prebuilt only existed at windows
    add_subdirectory(sqlite3)
    add_subdirectory(win32-specific/gles)
    add_subdirectory(win32-specific/icon)
    add_subdirectory(win32-specific/MP3Decoder)
    add_subdirectory(win32-specific/OggDecoder)
    add_subdirectory(win32-specific/OpenalSoft)
    target_link_libraries(external 
        ext_sqlite3
        ext_gles
        ext_icon
        ext_MP3Decoder
        ext_OggDecoder
        ext_OpenalSoft
    )
endif()

if(WINDOWS OR MACOSX OR LINUX)
    add_subdirectory(glfw3)
    target_link_libraries(external 
        ext_glfw3
    )
endif()

if(MACOSX OR ANDROID OR WINDOWS)
    add_subdirectory(zlib)
    target_link_libraries(external 
        ext_zlib
    )
endif()

# unzip depend on zlib
add_subdirectory(unzip)
target_link_libraries(external ext_unzip)

# put "external" into External folder, too
set_target_properties(external
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "External"
)

