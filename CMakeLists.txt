cmake_minimum_required(VERSION 2.8.11)
project(NexusEngine)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

### COMPILATOR OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### USEFUL VARS
set(ENGINE_DIR ${PROJECT_SOURCE_DIR}/Engine)
set(INCLUDES_DIR ${ENGINE_DIR}/includes)

### OUTPUT DIRECTORY
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY        ${ENGINE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG  ${ENGINE_DIR}/lib)

include_directories(
  ${INCLUDES_DIR}
  ${ENGINE_DIR}/src/standalone/errors/
)

file(GLOB_RECURSE HEADER_CLIENT_FILES   ${INCLUDES_DIR}/Nexus/*.hpp)
file(GLOB_RECURSE SOURCE_CLIENT_FILES		${ENGINE_DIR}/src/*.cpp)
add_library(NexusEngine STATIC ${SOURCE_CLIENT_FILES} ${HEADER_CLIENT_FILES})

# CMake instructions to test exemple using the static lib in debug mode
if (CMAKE_BUILD_TYPE MATCHES Debug)
  message("Preparing to build tests for debug mode...")
  set(APP_EXE "engine_test")
  set(TEST_DIR ${ENGINE_DIR}/test/)

  file(GLOB_RECURSE SOURCE_TEST_FILES		${TEST_DIR}/*.cpp)
  file(GLOB_RECURSE HEADER_TEST_FILES		${TEST_DIR}/*.hpp)

  add_executable(${APP_EXE} ${SOURCE_TEST_FILES} ${HEADER_TEST_FILES})

  target_link_libraries(${APP_EXE} NexusEngine)
else()
  message("Ignoring tests...")
endif()
