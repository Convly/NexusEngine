cmake_minimum_required(VERSION 2.8.11)
project(NetworkClient)

set(LIBRARY_NAME "networkclient")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(Boost_DEBUG off)

### COMPILATOR OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS   OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.54.0 COMPONENTS system serialization filesystem REQUIRED)
find_package( Threads )

if(NOT Boost_FOUND)
    message("Boost >= 1.54.0 is needed for build")
    return()
endif()

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

### INCLUDES
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ../../includes/
  ${Boost_INCLUDE_DIRS}
)

### OUTPUT DIRECTORY
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY        ${CMAKE_CURRENT_SOURCE_DIR}/)

file(GLOB_RECURSE HEADER_LIB_FILES   	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_LIB_FILES		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE SOURCE_ENGINE_FILES	../../include/Nexus/engine.hpp ../../include/Nexus/standalone/network/serialization.hpp)

add_library(${LIBRARY_NAME} SHARED ${SOURCE_LIB_FILES} ${HEADER_LIB_FILES} ${SOURCE_ENGINE_FILES})
target_compile_definitions(${LIBRARY_NAME} PRIVATE -DBOOST_ALL_NO_LIB)
target_link_libraries(${LIBRARY_NAME} ${Boost_LIBRARIES})
target_link_libraries(${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT} )
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES PREFIX "")