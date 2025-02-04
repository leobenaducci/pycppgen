cmake_minimum_required(VERSION 3.15...3.31)

include(FetchContent)

FetchContent_Populate(
    chaiscript
    URL https://github.com/ChaiScript/ChaiScript/archive/refs/heads/develop.zip
    SOURCE_DIR ../chaiscript
    )

project(pycppgen_test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CURRENT_BINARY_DIR "../intermediate")
set(CMAKE_CXX_STANDARD 20)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB PROJ_SOURCES "lib/*.cpp")
file(GLOB PROJ_HEADERS "lib/*.h")

add_library(lib STATIC ${PROJ_SOURCES} ${PROJ_HEADERS})

file(GLOB PROJ_SOURCES "app/*.cpp")
file(GLOB PROJ_HEADERS "app/*.h")

add_executable(app ${PROJ_SOURCES} ${PROJ_HEADERS})
target_include_directories(app PUBLIC lib)

target_include_directories(app PUBLIC chaiscript/include)

