cmake_minimum_required(VERSION 3.10)
project(MiniInterpreter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    interpereter
    external
)

file(GLOB_RECURSE INTERPRETER_SOURCES "src/*.cpp")

add_library(interpreter_lib ${INTERPRETER_SOURCES})

target_include_directories(interpreter_lib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/external"
)

add_subdirectory(tests)

add_executable(run_repl src/repl.cpp)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")

target_link_libraries(run_repl PRIVATE interpreter_lib)