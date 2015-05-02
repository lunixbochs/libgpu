cmake_minimum_required(VERSION 2.6)
project(libgpu)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_definitions(-std=c99)
add_subdirectory(src)
