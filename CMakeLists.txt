# The root directory
cmake_minimum_required(VERSION 2.8)

project(HestonModelSimulations)
add_executable(HestonModelSimulations main)

#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS "-g -std=c++11 -Wall -O2 -mtune=native")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(Threads)

FIND_PACKAGE(GSL)
IF (GSL_FOUND)
	MESSAGE(STATUS "GSL found.")
	ADD_DEFINITIONS(-DHAVE_GSL)
	SET(HAVE_GSL 1)
ELSE (GSL_FOUND)
	MESSAGE(STATUS "GSL missing: needed for the AtomSpace.")
ENDIF (GSL_FOUND)

add_subdirectory(library) 

include_directories(${PROJECT_SOURCE_DIR}/library)

target_link_libraries(HestonModelSimulations HestonModel NormalRandomNumberGenerator dataExport Options MonteCarloSimulation ${CMAKE_THREAD_LIBS_INIT} ${GSL_LIBRARIES})
