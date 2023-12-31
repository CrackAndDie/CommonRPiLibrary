﻿cmake_minimum_required (VERSION 3.8)

project (CommonRPiLibrary VERSION 1.0.1)

find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include(UseJava)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER gcc)

# Add your source files here
set(SOURCES
    src/CommonRPiLibrary.c
    src/SPI.c
    src/USB.c
    # Add more source files as needed
    src/CommonRPiLibraryJavaWrapper.c
)

# Add header files directory
include_directories(include)
# include_directories(${JAVA_INCLUDE_PATH})
# include_directories(${JAVA_INCLUDE_PATH}/linux)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${JNI_INCLUDE_DIRS})

# Create a shared library from the sources
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${JAVA_JVM_LIBRARY})

# JAVA
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/classes")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${Java_JAVAC_EXECUTABLE}" -d classes ${CMAKE_CURRENT_SOURCE_DIR}/java/*.java
    COMMAND "${Java_JAR_EXECUTABLE}" -cfM JavaNative.jar -C classes .)

# Set library version
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# Install library and header files
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})

# Print information
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "Project Source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Project Binary dir: ${CMAKE_CURRENT_BINARY_DIR}")
