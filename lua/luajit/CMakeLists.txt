if(OHOS)
    cmake_minimum_required(VERSION 3.6)

    set(lib_name luajit)
    set(target_name ext_${lib_name})
    project(${lib_name}) 
    
    add_library(${target_name} STATIC IMPORTED GLOBAL)


    set_target_properties(${target_name} PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
    ) 
    set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/ohos/lib${lib_name}.a"
    ) 
else()
    cmake_minimum_required(VERSION 3.4.1)
    ENABLE_LANGUAGE(C ASM)

    project(luajit)

    file(GLOB luajit_source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
    list(APPEND luajit_source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/lj_vm.S)

    file(GLOB luajit_header_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

    message("luajit static lib build")
    add_library(${PROJECT_NAME} STATIC ${luajit_source_files} ${luajit_header_files})
    target_compile_definitions(${PROJECT_NAME} PUBLIC -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DLUA_MULTILIB=\"lib\")
    target_compile_options(${PROJECT_NAME} PUBLIC -fPIC -O2 -fomit-frame-pointer -Wall -fno-stack-protector)

endif()
