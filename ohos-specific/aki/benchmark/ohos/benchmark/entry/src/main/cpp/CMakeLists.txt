# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(benchmark)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../)

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_subdirectory(${NATIVERENDER_ROOT_PATH} aki)

add_library(napi_benchmark SHARED napi_benchmark.cpp)
target_link_libraries(napi_benchmark PUBLIC
    libace_napi.z.so
    common_benchmark
    hilog_ndk.z)

add_library(jsbind_benchmark SHARED jsbind_benchmark.cpp)
target_link_libraries(jsbind_benchmark PUBLIC
    libace_napi.z.so
    aki_jsbind
    common_benchmark)

add_library(common_benchmark SHARED common_benchmark.cpp)

target_link_libraries(common_benchmark PUBLIC
    aki_jsbind)