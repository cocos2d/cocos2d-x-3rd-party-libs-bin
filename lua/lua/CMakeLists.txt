cmake_minimum_required(VERSION 3.6)

set(lib_name lua)
set(target_name ext_${lib_name})

project(${lib_name})

if(IOS)
  include(../../cmake/CocosExternalConfig.cmake)

  add_library(${target_name} STATIC IMPORTED GLOBAL)

  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/ios/lib${lib_name}.a"
  )
else()
  set(${target_name}_src
    lapi.c
    lauxlib.c
    lbaselib.c
    lcode.c
    ldblib.c
    ldebug.c
    ldo.c
    ldump.c
    lfunc.c
    lgc.c
    linit.c
    liolib.c
    llex.c
    lmathlib.c
    lmem.c
    loadlib.c
    lobject.c
    lopcodes.c
    loslib.c
    lparser.c
    lstate.c
    lstring.c
    lstrlib.c
    ltable.c
    ltablib.c
    ltm.c
    lundump.c
    lvm.c
    lzio.c
    print.c
  )

  add_library(${target_name} STATIC
    ${${target_name}_src}
  )

  target_include_directories(${target_name} INTERFACE .)

  set_target_properties(${target_name}
      PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      FOLDER "External"
  )

endif()