# The root directory
cmake_minimum_required(VERSION 2.8)

project(HestonModelSimulations)
add_executable(HestonModelSimulations main)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")

add_subdirectory(library) 

include_directories(${PROJECT_SOURCE_DIR}/library)

target_link_libraries(HestonModelSimulations HestonModel NormalRandomNumberGenerator dataExport)
