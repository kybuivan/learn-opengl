cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(learn_opengl)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/cmake/external)

option( BUILD_EXAMPLES "Build examples" ON )

add_subdirectory(base)
add_subdirectory(examples)