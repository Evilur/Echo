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

# Enable auto Qt file generation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Get all *.cpp files
FILE(GLOB_RECURSE SOURCES "src/*.cpp")

# Get all *.qrc files
FILE(GLOB_RECURSE SOURCES_QRC "assets/*.qrc")

# Build all *.cpp and *.qrc files
ADD_EXECUTABLE(Echo ${SOURCES} ${SOURCES_QRC})

# Build all *.cpp files for tests
FILE(GLOB_RECURSE SOURCES_TEST "test/*.cpp")
ADD_EXECUTABLE(Test ${SOURCES_TEST}
        src/util/hash.cpp
)

# Copy tests directory
ADD_CUSTOM_COMMAND(TARGET Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/test/units $<TARGET_FILE_DIR:Echo>/test/units
)

# Link all dependencies
FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml QuickControls2)
TARGET_LINK_LIBRARIES(Echo PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::Qml
        Qt6::QuickControls2
)
