cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        lab1
        src/main.cpp
        src/lib/WordCallbackReader.h
        src/lib/WideStringFormatterWriter.h
        src/lib/Args.h
        src/lib/String.h
        src/lib/Vector.h
)

add_executable(
        lab1_tests
        test/lib/VectorTest.cpp
        src/lib/Vector.h
)

add_executable(
        lab1_sandbox
        src/sandbox.cpp
        src/lib/Vector.h
        src/lib/String.h
)