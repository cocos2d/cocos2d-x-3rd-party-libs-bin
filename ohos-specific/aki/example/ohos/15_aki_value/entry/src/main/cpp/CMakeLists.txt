# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(aki_value)

# 本例直接使用根目录源码作为依赖，实际工程使用时，需要`clone`源码到指定路径
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../)

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(aki_value SHARED hello.cpp)
add_subdirectory(${NATIVERENDER_ROOT_PATH} aki)
target_link_libraries(aki_value PUBLIC aki_jsbind)