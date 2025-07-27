add_executable(run_tests
    tests.cpp
    ../external/catch2/catch_amalgamated.cpp
)

target_link_libraries(run_tests PRIVATE interpreter_lib)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/tests")