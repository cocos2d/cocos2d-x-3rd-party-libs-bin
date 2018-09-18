# tmp test
set(CMAKE_BUILD_TYPE DEBUG)

# some libs existed debug and release both type
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type_folder)
# RelWithDebInfo is one of Visual Studio 2017 default build type
if(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    set(build_type_folder "debug")
endif()

# set platform specific path
if(IOS)
    set(platform_name ios)
    set(platform_spec_path ios)
elseif(ANDROID)
    set(platform_name android)
    set(platform_spec_path android/${TARGET_ARCH_ABI})
elseif(WINDOWS)
    set(platform_name win32)
    # win32/, win32/debug, win32/debug-lib 
    if(EXISTS win32/${build_type}-lib)
        set(platform_spec_path win32/${build_type}-lib)
    elseif(EXISTS win32/${build_type})
        set(platform_spec_path win32/${build_type})
    else()
        set(platform_spec_path win32)
    endif()
elseif(LINUX)
    set(platform_name linux)
    set(platform_spec_path linux/64-bit)
endif()

