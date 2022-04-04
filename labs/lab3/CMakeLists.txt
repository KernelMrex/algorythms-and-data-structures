cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(
        lab3
        src/main.cpp
        src/lib/graph_calculator.h
        src/lib/graph_calculator.cpp
        src/lib/SquareMatrix.h
)