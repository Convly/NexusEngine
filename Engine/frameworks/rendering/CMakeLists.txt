cmake_minimum_required(VERSION 2.6)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(Rendering)
set(LIBRARY_NAME "rendering")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions

if (WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
	### COMPILATOR OPTIONS
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)

	### INCLUDES
	include_directories(
		${SFML_INCLUDE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/gui
		${CMAKE_CURRENT_SOURCE_DIR}/graphics
		../../includes/
	)

	### OUTPUT DIRECTORY
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY        ${CMAKE_CURRENT_SOURCE_DIR}/)
	file(GLOB_RECURSE HEADER_LIB_FILES   	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
	file(GLOB_RECURSE SOURCE_LIB_FILES		${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
	file(GLOB_RECURSE SOURCE_ENGINE_FILES	../../include/Nexus/engine.hpp)
	add_library(${LIBRARY_NAME} SHARED ${SOURCE_LIB_FILES} ${HEADER_LIB_FILES} ${SOURCE_ENGINE_FILES})
	set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")

	target_link_libraries(${LIBRARY_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Install target
install(TARGETS ${LIBRARY_NAME} DESTINATION bin)