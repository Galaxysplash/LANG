cmake_minimum_required(VERSION 3.30)
project(Lang)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    src
)

add_executable(
    Lang
    src/main.cpp
        src/framework/init.cpp
        src/framework/init.h
        src/framework/syntax.cpp
        src/framework/syntax.h
        src/summary/program.cpp
        src/summary/program.h
        src/framework/instruction_finder.cpp
        src/framework/instruction_finder.h
        src/tests/unit_test.cpp
        src/tests/unit_test.h
)
