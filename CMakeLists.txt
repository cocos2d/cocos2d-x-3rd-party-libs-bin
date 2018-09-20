cmake_minimum_required(VERSION 3.6)
project(external)

add_library(external empty.cpp)

add_subdirectory(Box2D)
add_subdirectory(chipmunk)
add_subdirectory(freetype2)
add_subdirectory(recast)
add_subdirectory(zlib)
add_subdirectory(bullet)
add_subdirectory(curl)
add_subdirectory(glfw3)
add_subdirectory(jpeg)
add_subdirectory(openssl)
add_subdirectory(png)
add_subdirectory(tiff)
add_subdirectory(uv)
add_subdirectory(webp)
add_subdirectory(websockets)
add_subdirectory(tinyxml2)
add_subdirectory(unzip)
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
    ext_zlib
    ext_jpeg
    ext_uv
    ext_webp
    ext_bullet
    ext_curl
    ext_glfw3
    ext_ssl
    ext_crypto
    ext_png
    ext_tiff
    ext_websockets
    ext_tinyxml2
    ext_unzip
    ext_xxhash
    ext_xxtea
    ext_clipper
    ext_edtaa3func
    ext_convertUTF
    ext_poly2tri
    ext_md5
)

if(BUILD_LUA_LIBS)
    add_subdirectory(lua/lua)
    add_subdirectory(lua/luajit)
    add_subdirectory(lua/tolua)
    add_subdirectory(lua/luasocket)
    target_link_libraries(external
        ext_lua
        ext_luajit
        ext_tolua
        ext_luasocket
    )
endif()

if(BUILD_JS_LIBS)
    add_subdirectory(spidermonkey)
    target_link_libraries(external
        ext_spidermonkey
    )
endif()


if(ANDROID)
    add_subdirectory(android-specific/cpufeatures)
    add_subdirectory(android-specific/pvmp3dec)
    add_subdirectory(android-specific/tremolo)
    target_link_libraries(external 
        cpufeatures 
        ext_pvmp3dec 
        ext_tremolo
    )
endif()

if(WINDOWS)
    # sqlite3 prebuilt only existed at windows
    add_subdirectory(sqlite3)
    target_link_libraries(external 
        ext_sqlite3
    )
endif()