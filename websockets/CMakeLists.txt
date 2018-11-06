cmake_minimum_required(VERSION 3.6)

set(lib_name websockets)
set(target_name ext_${lib_name})

project(${lib_name})

include(../cmake/CocosExternalConfig.cmake)

add_library(${target_name} STATIC IMPORTED GLOBAL)

set_target_properties(${target_name} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/${platform_name}"
)
set_target_properties(${target_name} PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "LWS_WITH_LIBUV"
)

set_property(TARGET ${target_name} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "ext_ssl")
set_property(TARGET ${target_name} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "ext_crypto")
set_property(TARGET ${target_name} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "ext_uv")

if(WINDOWS)
  set_target_properties(${target_name} PROPERTIES
    CC_DEPEND_DLLS "${platform_spec_path}/${lib_name}.dll"
    IMPORTED_LOCATION "${platform_spec_path}/${lib_name}.lib"
  )
else()
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/lib${lib_name}.a"
  )
endif()
