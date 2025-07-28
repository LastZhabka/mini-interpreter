# Mini-Interpreter

A Lisp-like language interpreter implemented. Project is interpreter to the language described in the [Problem Description](docs/problem_description.md). 

## Installation

Download Dependencies
   ```bash
   mkdir -p external/catch2 external/nlohmann
   curl -L https://github.com/catchorg/Catch2/releases/download/v3.4.0/catch_amalgamated.hpp -o external/catch2/catch_amalgamated.hpp
   curl -L https://github.com/catchorg/Catch2/releases/download/v3.4.0/catch_amalgamated.cpp -o external/catch2/catch_amalgamated.cpp
   curl -L https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp -o external/nlohmann/json.hpp
   ```

Install System Dependencies
   ```bash
   sudo apt-get install -y cmake g++ make
   ```

Build the Project
   ```bash
   mkdir -p build && cd build
   cmake .. && cmake --build .
   ```

## Acknowledgement

The problem itself is taken from UBS Coding Challenge.
