cmake_minimum_required(VERSION 2.8.11)
project(NexusEngine)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

#CMAKE_MODULES
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

### LIBRARY NAME
set(LIBRARY_NAME "NexusEngine")

### COMPILATOR OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### USEFUL VARS
set(ENGINE_DIR ${PROJECT_SOURCE_DIR}/Engine)
set(INCLUDES_DIR ${ENGINE_DIR}/includes)

### OUTPUT DIRECTORY
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY        ${ENGINE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG  ${ENGINE_DIR}/lib)

if (WIN32)
  set(DLLOADER_INCLUDE_PATH /Linux/)
elseif(UNIX AND NOT APPLE)
  set(DLLOADER_INCLUDE_PATH /Windows/)
endif()

### BOOST
set(Boost_USE_STATIC_LIBS   OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_DEBUG off)

find_package(Boost 1.54.0 COMPONENTS system serialization filesystem thread REQUIRED)

if(NOT Boost_FOUND)
    message("Boost >= 1.54.0 is needed for build")
    return()
endif()

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

include_directories(
  ${INCLUDES_DIR}
  ${INCLUDES_DIR}/dlLoader/${DLLOADER_INCLUDE_PATH}
  ${Boost_INCLUDE_DIRS}
)

file(GLOB_RECURSE HEADER_CLIENT_FILES   ${INCLUDES_DIR}/Nexus/*.hpp)
file(GLOB_RECURSE SOURCE_CLIENT_FILES		${ENGINE_DIR}/src/*.cpp)
list(REMOVE_ITEM HEADER_CLIENT_FILES ${ENGINE_DIR}/dlLoader/${DLLOADER_INCLUDE_PATH}/DLLoader.hpp)
add_library(${LIBRARY_NAME} STATIC ${SOURCE_CLIENT_FILES} ${HEADER_CLIENT_FILES})

target_compile_definitions(${LIBRARY_NAME} PRIVATE -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK)
target_link_libraries(${LIBRARY_NAME} ${Boost_LIBRARIES})

file(COPY ${ENGINE_DIR}/frameworks DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

if (UNIX AND NOT APPLE AND NOT FSLIB_STATIC)
  set(FSLIB_STATIC "/usr/lib/gcc/x86_64-linux-gnu/5/libstdc++fs.a")
endif()
  ### LIBCSTD++FS (UNIX)
if (UNIX AND NOT APPLE)
  add_library(stdc++fs UNKNOWN IMPORTED)
  set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION ${FSLIB_STATIC})
  target_link_libraries(${LIBRARY_NAME} stdc++fs)
  target_link_libraries(${LIBRARY_NAME} dl)
endif()

# CMake instructions to test exemple using the static lib in debug mode
if (CMAKE_BUILD_TYPE MATCHES Debug)
  message("Preparing to build tests for debug mode...")
  set(APP_EXE "engine_test")
  set(TEST_DIR ${ENGINE_DIR}/test/)
  
  if (UNIX AND NOT APPLE)
	file(COPY ${ENGINE_DIR}/frameworks DESTINATION ${CMAKE_BINARY_DIR})
  elseif (WIN32)
	file(COPY ${ENGINE_DIR}/frameworks DESTINATION ${CMAKE_BINARY_DIR}/Debug)
  endif()

  file(GLOB_RECURSE SOURCE_TEST_FILES		${TEST_DIR}/*.cpp)
  file(GLOB_RECURSE HEADER_TEST_FILES		${TEST_DIR}/*.hpp)

  add_executable(${APP_EXE} ${SOURCE_TEST_FILES} ${HEADER_TEST_FILES})

  target_link_libraries(${APP_EXE} ${LIBRARY_NAME})
else()
  message("Ignoring tests...")
endif()
