cmake_minimum_required(VERSION 3.15...3.31)

project(pycppgen_test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CURRENT_BINARY_DIR "../intermediate")
set(CMAKE_CXX_STANDARD 20)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB PROJ_SOURCES "*.cpp")
file(GLOB PROJ_HEADERS "*.h")

add_executable(pycppgen_test ${PROJ_SOURCES} ${PROJ_HEADERS})
