cmake_minimum_required(VERSION 3.6)

set(lib_name OggDecoder)
set(target_name ext_${lib_name})

project(${lib_name})

include(../cmake/CocosExternalConfig.cmake)

if(WINDOWS)
  add_library(${target_name} SHARED IMPORTED GLOBAL)
elseif(LINUX)
  add_library(${target_name} STATIC IMPORTED GLOBAL)
endif()

set_target_properties(${target_name} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WINDOWS)
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/win32/libogg.dll"
    IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/win32/libogg.lib"
  )
elseif(LINUX)
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/linux/64-bit/libogg.a"
  )
endif()

# internal link depend
if(WINDOWS)
  set_property(TARGET ${target_name} APPEND PROPERTY 
    INTERFACE_LINK_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/win32/libvorbis.lib"
  )
  set_property(TARGET ${target_name} APPEND PROPERTY 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/win32/libvorbis.dll"
  )
  set_property(TARGET ${target_name} APPEND PROPERTY 
  INTERFACE_LINK_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/win32/libvorbisfile.lib"
  )
  set_property(TARGET ${target_name} APPEND PROPERTY 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/win32/libvorbisfile.dll"
  )

elseif(LINUX)
  add_library(ogg STATIC IMPORTED)
  set_target_properties(ogg PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/linux/64-bit/libogg.a"
  )
  add_library(vorbis STATIC IMPORTED)
  set_target_properties(vorbis PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/linux/64-bit/libvorbis.a"
  )
  add_library(vorbisfile STATIC IMPORTED)
  set_target_properties(vorbisfile PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/linux/64-bit/libvorbisfile.a"
  )

  set_property(TARGET vorbis APPEND PROPERTY INTERFACE_LINK_LIBRARIES "ogg")
  set_property(TARGET vorbis APPEND PROPERTY INTERFACE_LINK_LIBRARIES "vorbisfile")

  set_property(TARGET vorbisfile APPEND PROPERTY INTERFACE_LINK_LIBRARIES "ogg")
  set_property(TARGET vorbisfile APPEND PROPERTY INTERFACE_LINK_LIBRARIES "vorbis")

  set_property(TARGET ${target_name} APPEND PROPERTY
    INTERFACE_LINK_LIBRARIES "vorbis"
  )
endif()

