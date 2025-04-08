# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(async_tasks)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../)

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(async_tasks SHARED hello.cpp)
add_subdirectory(${NATIVERENDER_ROOT_PATH} aki)
target_link_libraries(async_tasks PUBLIC aki_jsbind)