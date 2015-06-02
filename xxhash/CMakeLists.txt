set(XXHASH
  xxhash.c
)

if(BUILD_SHARED_LIBS)
    set (SHARED_OR_STATIC SHARED)
else()
    set (SHARED_OR_STATIC STATIC)
endif()

add_library(xxhash ${SHARED_OR_STATIC}
  ${XXHASH}
)

set_target_properties(xxhash
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

