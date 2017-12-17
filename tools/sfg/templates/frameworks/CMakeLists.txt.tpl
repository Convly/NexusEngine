cmake_minimum_required(VERSION 2.8.11)
project(${__NX_BASE_SYSTEM__})

set(LIBRARY_NAME "${__NX_LOWER_SYSTEM__}")

### COMPILATOR OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### INCLUDES
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ../../includes/
)

### OUTPUT DIRECTORY
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY        ${CMAKE_CURRENT_SOURCE_DIR}/)

file(GLOB_RECURSE HEADER_LIB_FILES   	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_LIB_FILES		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(${LIBRARY_NAME} SHARED ${SOURCE_LIB_FILES} ${HEADER_LIB_FILES})
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES PREFIX "")