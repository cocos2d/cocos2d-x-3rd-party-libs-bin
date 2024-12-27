if(OHOS)
cmake_minimum_required(VERSION 3.4.1)


set(lib_name luajit)
add_library(${lib_name} STATIC IMPORTED GLOBAL)


set_target_properties(${lib_name} PROPERTIES 
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/ohos/libluajit.a
    )
endif()