if(OHOS)
cmake_minimum_required(VERSION 3.6)

set(lib_name luasocket)
set(target_name ext_${lib_name})

project(${lib_name})

set(${target_name}_src
  buffer.c
  io.c
  timeout.c
  select.c
  udp.c
  mime.c
  tcp.c
  auxiliar.c
  inet.c
  luasocket.c
  except.c
  options.c
)
  list(APPEND ${target_name}_src 
    unix.c
    usocket.c
    serial.c
  )
add_library(${target_name} STATIC ${${target_name}_src} )


target_include_directories(${target_name} 
  INTERFACE ..
  PRIVATE ../luajit/include
)

set_target_properties(${target_name}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "External"
)

endif()