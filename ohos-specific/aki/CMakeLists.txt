cmake_minimum_required(VERSION 3.16)

project(aki VERSION 1.2.3
    DESCRIPTION ""
    HOMEPAGE_URL ""
    LANGUAGES CXX)


option(AKI_BUILDING_SHARED "compile for shared library" ON)
option(AKI_ENABLE_NAPI "using node-api" ON)
option(AKI_ENABLE_INSTALL_OHOS "" OFF)
option(AKI_ENABLE_DECLARATION "" OFF)
option(AKI_ENABLE_TRACING "DO NOT USE THIS option !!!" OFF)

add_subdirectory(src)

if (AKI_ENABLE_UNITTEST)
    add_subdirectory(test)
endif()