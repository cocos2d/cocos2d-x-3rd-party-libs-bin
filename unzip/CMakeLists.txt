set(UNZIP_SRC
  ioapi.cpp
  unzip.cpp
  ioapi_mem.cpp
)

if(BUILD_SHARED_LIBS)
    set (SHARED_OR_STATIC SHARED)
else()
    set (SHARED_OR_STATIC STATIC)
endif()

add_library(unzip ${SHARED_OR_STATIC}
  ${UNZIP_SRC}
)

set_target_properties(unzip
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "External"
)

