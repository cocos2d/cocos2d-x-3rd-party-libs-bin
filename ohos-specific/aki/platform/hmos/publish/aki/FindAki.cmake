
if(NOT AKI_ROOT_PATH)
    message(FATAL_ERROR "-- [JSBIND]: AKI_ROOT_PATH must be setted up at first.")
endif()

set(AKI_SEARCH_PATH ${AKI_ROOT_PATH})
set(CMAKE_CXX_STANDARD 17)
# find base path
find_path(AKI_PATH
    NAMES include/aki/jsbind.h
    PATHS ${AKI_SEARCH_PATH}
    CMAKE_FIND_ROOT_PATH_BOTH
    )

# find includes
if(NOT AKI_INCLUDE_DIRS)
    find_path(AKI_INCLUDE_DIR
        NAMES aki/jsbind.h
        PATHS ${AKI_PATH}
        PATH_SUFFIXES include
        CMAKE_FIND_ROOT_PATH_BOTH
    )

    set(AKI_INCLUDE_DIRS
        ${AKI_INCLUDE_DIR})
endif()

# find link directories
if(NOT AKI_LINK_DIRS)
    # AKI 库文件链接路径
    find_path(AKI_JSBIND_LINK_DIRS
        NAMES libaki_jsbind.so
        PATHS "${AKI_PATH}"
        PATH_SUFFIXES "libs/${CMAKE_OHOS_ARCH_ABI}"
        CMAKE_FIND_ROOT_PATH_BOTH
    )

    set(AKI_LINK_DIRS
        ${AKI_JSBIND_LINK_DIRS})

endif()

# find librarys
if(NOT AKI_LIBRARIS)
    # AKI 库文件
    find_library(AKI_LIBRARY
        NAMES aki_jsbind
        PATHS "${AKI_PATH}"
        PATH_SUFFIXES "libs/${CMAKE_OHOS_ARCH_ABI}"
        CMAKE_FIND_ROOT_PATH_BOTH
    )

    set(AKI_LIBRARIS
        aki_jsbind
        ace_napi.z
        hilog_ndk.z
        uv)

endif()

# 编译宏
if(NOT AKI_DEFINITIONS)
    if(OHOS)
        set(AKI_DEFINITIONS ${AKI_DEFINITIONS} "AKI_ENABLE_NAPI=1")
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AKI DEFAULT_MSG
    AKI_INCLUDE_DIRS
    AKI_LIBRARIS
)

if(AKI_FOUND AND NOT TARGET Aki::libjsbind)
    # 创建接口lib
    add_library(Aki::libjsbind INTERFACE IMPORTED)

    # 设置target 头文件依赖
    target_include_directories(Aki::libjsbind INTERFACE ${AKI_INCLUDE_DIRS})

    # 设置target link依赖路径
    target_link_directories(Aki::libjsbind INTERFACE ${AKI_LINK_DIRS})

    # 设置target lib依赖
    target_link_libraries(Aki::libjsbind INTERFACE ${AKI_LIBRARIS})

    # 设置target 编译宏
    target_compile_definitions(Aki::libjsbind INTERFACE ${AKI_DEFINITIONS})

    # 安全编译选项 NO Rpath 规则
    set(CMAKE_SKIP_RPATH TRUE)
endif()