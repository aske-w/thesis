find_package(Catch2 3 REQUIRED)

set(TEST_SOURCES
    bitstream.cpp
    test.cpp
)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(tests)