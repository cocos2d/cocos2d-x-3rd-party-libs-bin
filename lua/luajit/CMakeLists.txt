cmake_minimum_required(VERSION 3.4.1)
set(lib_name luajit)

if(WINDOWS)
    add_library(${lib_name} SHARED IMPORTED GLOBAL)
else()
    add_library(${lib_name} STATIC IMPORTED GLOBAL)
endif()


set(_path_prefix ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/)
if(IOS)
    set(platform_name ios)
    set(platform_spec_path ios)
elseif(ANDROID)
    set(platform_name android)
    set(platform_spec_path android/${ANDROID_ABI})
elseif(OHOS)
    set(platform_name ohos)
    set(platform_spec_path ohos)   # TBD ohos need ABI?
elseif(WINDOWS)
    set(platform_name win32)
    set(platform_spec_path win32)
elseif(MACOSX)
    set(platform_name mac)
    set(platform_spec_path mac)
elseif(LINUX)
    set(platform_name linux)
    set(platform_spec_path linux/64-bit)
endif()

set(platform_spec_path "${_path_prefix}${platform_spec_path}")


set_target_properties(${lib_name} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
        )
if(WINDOWS)
    set_target_properties(${lib_name} PROPERTIES
            IMPORTED_LOCATION "${platform_spec_path}/lua51.dll"
            IMPORTED_IMPLIB "${platform_spec_path}/lua51.lib"
            )
else()
    set_target_properties(${lib_name} PROPERTIES
            IMPORTED_LOCATION "${platform_spec_path}/lib${lib_name}.a"
            )
endif()