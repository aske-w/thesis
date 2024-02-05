cmake_minimum_required(VERSION 3.26)
set(NAME thesis)
project(${NAME})

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_subdirectory(src)

add_executable(${NAME} ${SOURCES})
