set(TARGET_NAME ${PROJECT_NAME}_jsbind)

set(AKI_SRC
    binding.cpp
    function.cpp
    jsbind.cpp
    version.cpp
    value.cpp
    )

set(CMAKE_SKIP_RPATH TRUE)

if (AKI_BUILDING_SHARED)
    add_library(${TARGET_NAME} SHARED ${AKI_SRC})
    target_compile_definitions(${TARGET_NAME} PUBLIC AKI_BUILDING_SHARED=1)
else()
    add_library(${TARGET_NAME} STATIC ${AKI_SRC})
endif()

# 编译选项
target_compile_options(${TARGET_NAME} PRIVATE -Werror -Wno-unused-command-line-argument)

# add_subdirectory(bind_info)
add_subdirectory(class)
add_subdirectory(invoker)
add_subdirectory(logging)
add_subdirectory(value)
add_subdirectory(status)
add_subdirectory(task_runner)
add_subdirectory(persistent)

if (AKI_ENABLE_NAPI)
    add_subdirectory(napi)
    add_subdirectory(overloader)
    target_compile_definitions(${TARGET_NAME} PUBLIC JSBIND_USING_NAPI=1)
endif()

if(AKI_ENABLE_UNITTESTS)
    target_compile_definitions(${TARGET_NAME} PUBLIC AKI_ENABLE_UNITTESTS)
    target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/)
    target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/third_party/jsonwrapper/include)
endif()

if(AKI_ENABLE_DECLARATION)
    target_compile_definitions(${TARGET_NAME} PUBLIC AKI_ENABLE_DECLARATION)
    add_subdirectory(reflect)
endif()

if(AKI_ENABLE_TRACING)
    target_compile_definitions(${TARGET_NAME} PUBLIC AKI_ENABLE_TRACING)
    target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/tracing/include/)
    target_link_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/tracing/libs/${OHOS_ARCH})
    target_link_libraries(${TARGET_NAME} PUBLIC libtracing.so)
endif()

target_link_libraries(${TARGET_NAME} PUBLIC libace_napi.z.so libhilog_ndk.z.so uv)

target_include_directories(${TARGET_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR})

if (AKI_ENABLE_INSTALL_OHOS)
    set(AKI_INSTALL_PATH "${CMAKE_SOURCE_DIR}/platform/ohos/publish/aki")
    message("AKI_INSTALL_PATH defined ${AKI_INSTALL_PATH}")
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        #COMMAND ${CMAKE_COMMAND} -E remove_directory ${AKI_INSTALL_PATH}/include
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/include ${AKI_INSTALL_PATH}/include
    )
endif()

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_link_options(${TARGET_NAME} PUBLIC -s)
endif()