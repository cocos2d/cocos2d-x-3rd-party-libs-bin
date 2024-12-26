cmake_minimum_required(VERSION 3.6)
if(OHOS)
set(lib_name openssl)

project(${lib_name})
# -----macro: set openssl sub target-----
macro(set_openssl_sub_target sub_lib_name)
  
  set(sub_target_name ext_${sub_lib_name})
  add_library(${sub_target_name} STATIC IMPORTED GLOBAL)

  set_target_properties(${sub_target_name} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/${platform_name}"
  )
  set_target_properties(${sub_target_name} PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/ohos/lib${sub_lib_name}.a")
endmacro()

# -----sub target 1: ssl-----
set(target_name ssl)
set_openssl_sub_target(${target_name})

# -----sub target 2: crypto-----
set(target_name crypto)
set_openssl_sub_target(${target_name})
endif()
