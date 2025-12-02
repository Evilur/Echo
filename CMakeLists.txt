CMAKE_MINIMUM_REQUIRED(VERSION 4.0)
SET(CMAKE_CXX_STANDARD 23)
PROJECT(Echo)

# Set build types
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "-g3 -O0")
ELSE ()
    SET(CMAKE_CXX_FLAGS "-g0 -O2")
ENDIF ()

# Search header files in the 'src' directory
INCLUDE_DIRECTORIES(src)

# Build all *.cpp files
FILE(GLOB_RECURSE SOURCES "src/*.cpp")
ADD_EXECUTABLE(Echo ${SOURCES})

# Copy assets directory
add_custom_command(TARGET Echo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Echo>/assets
)

# Link all dependencies
TARGET_LINK_LIBRARIES(Echo
    Ultralight
    UltralightCore
    WebCore
    AppCore)