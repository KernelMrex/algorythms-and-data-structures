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
        src/lib/WeightedGraph.h
        src/lib/graph_utils.h
)

add_executable(
        lab3_tests
        src/lib/WeightedGraph.h
        src/lib/graph_utils.h
        test/unit/catch_main.cpp
        test/unit/lib/graph_utils_test.cpp
        test/unit/lib/WeightedGraphTest.cpp
)