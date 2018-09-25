cmake_minimum_required(VERSION 3.6)

set(lib_name OggDecoder)
set(target_name ext_${lib_name})

project(${lib_name})

include(../../cmake/CocosExternalConfig.cmake)

add_library(${target_name} STATIC IMPORTED GLOBAL)

set_target_properties(${target_name} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(${target_name} PROPERTIES
  CC_DEPEND_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libogg.dll"
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libogg.lib"
)

# internal link depend
 set_property(TARGET ${target_name} APPEND PROPERTY 
  INTERFACE_LINK_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libvorbis.lib"
)
set_property(TARGET ${target_name} APPEND PROPERTY 
  CC_DEPEND_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libvorbis.dll"
)
set_property(TARGET ${target_name} APPEND PROPERTY 
  INTERFACE_LINK_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libvorbisfile.lib"
)
set_property(TARGET ${target_name} APPEND PROPERTY 
  CC_DEPEND_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libvorbisfile.dll"
)

