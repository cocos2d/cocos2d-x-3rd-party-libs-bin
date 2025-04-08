# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(array_buffer_to_native)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../)

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(arraybuffer2native SHARED hello.cpp)
add_subdirectory(${NATIVERENDER_ROOT_PATH} aki)
target_link_libraries(arraybuffer2native PUBLIC aki_jsbind)