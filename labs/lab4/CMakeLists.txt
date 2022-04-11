cmake_minimum_required(VERSION 3.14)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        lab4
        src/main.cpp
        src/lib/WeightedGraph.h
)

add_executable(
        lab4_unit
        test/unit/catch_main.cpp
        src/lib/WeightedGraph.h
        test/unit/lib/WeightedGraphTest.cpp)