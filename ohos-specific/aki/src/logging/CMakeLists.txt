
SET(LOGGING_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/log_setting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp)

target_sources(${TARGET_NAME} PRIVATE ${LOGGING_SRC})
