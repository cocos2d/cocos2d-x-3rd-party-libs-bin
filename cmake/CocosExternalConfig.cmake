# tmp test
set(CMAKE_BUILD_TYPE DEBUG)

# some libs existed debug and release both type
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type_folder)
# RelWithDebInfo is one of Visual Studio 2017 default build type
if(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    set(build_type_folder "debug")
endif()

 #Please use them everywhere
 #WINDOWS   =   Windows Desktop
 #ANDROID    =  Android
 #IOS    =  iOS
 #MACOSX    =  MacOS X
 #LINUX      =   Linux
 if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
     set(WINDOWS TRUE)
     set(SYSTEM_STRING "Windows Desktop")
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
     set(SYSTEM_STRING "Android")
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
     if(ANDROID)
         set(SYSTEM_STRING "Android")
     else()
         set(LINUX TRUE)
         set(SYSTEM_STRING "Linux")
     endif()
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     if(IOS)
         set(APPLE TRUE)
         set(SYSTEM_STRING "IOS")
     else()
         set(APPLE TRUE)
         set(MACOSX TRUE)
         set(SYSTEM_STRING "Mac OSX")
     endif()
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
elseif(MACOSX)
    set(platform_name mac)
    set(platform_spec_path mac)
elseif(LINUX)
    set(platform_name linux)
    set(platform_spec_path linux/64-bit)
endif()

