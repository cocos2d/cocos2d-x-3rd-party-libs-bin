# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(promise)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../)

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_subdirectory(${NATIVERENDER_ROOT_PATH} aki)
add_library(promise SHARED hello.cpp)
target_link_libraries(promise PUBLIC aki_jsbind)