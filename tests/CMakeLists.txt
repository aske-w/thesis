find_package(Catch2 3 REQUIRED)

set(TEST_SOURCES
    ${TEST_SOURCES}
    bitstream.cpp
    java_port.cpp
    test.cpp
)

add_executable(${NAME}_tests ${TEST_SOURCES})
target_link_libraries(${NAME}_tests PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
include_directories(include)
add_subdirectory(helpers)
catch_discover_tests(${NAME}_tests)

target_link_libraries(${NAME}_tests PUBLIC ${CMAKE_PROJECT_NAME}_lib)