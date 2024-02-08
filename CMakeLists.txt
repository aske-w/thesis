cmake_minimum_required(VERSION 3.26)
set(NAME thesis)
project(${NAME})

set(CMAKE_CXX_STANDARD 20)
set(DISABLE_ASSERTIONS 0)

if (NOT (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
    set(DISABLE_ASSERTIONS 1)
endif ()

include_directories(include)
add_subdirectory(src)
add_subdirectory(tests)

add_executable(${NAME} ${SOURCES})
