add_subdirectory(algorithms)
add_subdirectory(helpers)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE)