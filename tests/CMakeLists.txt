cmake_minimum_required(VERSION 3.15...3.31)

include(FetchContent)

project(pycppgen_test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_TLS_VERIFY FALSE)

FetchContent_Declare(
    chaiscript
    URL https://github.com/ChaiScript/ChaiScript/archive/refs/heads/develop.zip
    URL_HASH SHA256=D6F5F942E553841CDC6547A8D3E3D0C4580E9EE282818C2CFED5EF6BA60CB4A7
    SOURCE_DIR ../3rdparty/chaiscript
    )
FetchContent_GetProperties(chaiscript)
if (NOT chaiscript_POPULATED)
    FetchContent_MakeAvailable(chaiscript)
endif()
    
FetchContent_Declare(
    pocketpy
    URL https://github.com/pocketpy/pocketpy/archive/refs/tags/v2.0.5.zip
    URL_HASH SHA256=B7B3AA7C063C99A73513F41A31E37C371AFA28CCF941BA3AF3B23A550749D668
    SOURCE_DIR ../3rdparty/pocketpy
    )
FetchContent_GetProperties(pocketpy)
if (NOT pocketpy_POPULATED)
    FetchContent_MakeAvailable(pocketpy)
endif()

add_custom_command(
    OUTPUT ${pocketpy_SOURCE_DIR}/amalgamated/pocketpy.c ${pocketpy_SOURCE_DIR}/amalgamated/pocketpy.h
    COMMAND python amalgamate.py 
    WORKING_DIRECTORY ${pocketpy_SOURCE_DIR}
    DEPENDS pocketpy
    CODEGEN
    )

add_library(pocketpylib STATIC
    ${pocketpy_SOURCE_DIR}/amalgamated/pocketpy.c ${pocketpy_SOURCE_DIR}/amalgamated/pocketpy.h
)

set(CMAKE_CURRENT_BINARY_DIR "../intermediate")
set(CMAKE_CXX_STANDARD 20)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB PROJ_SOURCES "lib/*.cpp")
file(GLOB PROJ_HEADERS "lib/*.h")

add_definitions(-DNOMINMAX)

add_library(lib STATIC ${PROJ_SOURCES} ${PROJ_HEADERS})
target_link_libraries(lib PUBLIC pocketpylib)

file(GLOB PROJ_SOURCES "app/*.cpp")
file(GLOB PROJ_HEADERS "app/*.h")

add_executable(app ${PROJ_SOURCES} ${PROJ_HEADERS})
target_compile_options(app PRIVATE /bigobj /utf-8)
target_include_directories(app PUBLIC lib)
target_link_libraries(app PUBLIC lib)

target_include_directories(app PUBLIC ${chaiscript_SOURCE_DIR}/include)
target_include_directories(app PUBLIC ${pocketpy_SOURCE_DIR}/amalgamated)
target_include_directories(app PUBLIC ${pocketpy_SOURCE_DIR}/include)

