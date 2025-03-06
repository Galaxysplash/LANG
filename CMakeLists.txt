cmake_minimum_required(VERSION 3.30)
project(Lang)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    src
)

add_executable(
    Lang
    src/main.cpp
        src/framework/import.cpp
        src/framework/import.h
        src/framework/parser.cpp
        src/framework/parser.h
        src/summary/program.cpp
        src/summary/program.h
        src/tests/unit_test.cpp
        src/tests/unit_test.h
        src/framework/code.cpp
        src/framework/code.h
        src/exceptions/custom_err.cpp
        src/exceptions/custom_err.h
        src/tests/run.cpp
        src/tests/run.h
        src/framework/lexer.cpp
        src/framework/lexer.h
        src/framework/data_type.h
        src/global/global_variables.h
        src/framework/tree.cpp
        src/framework/tree.h
)
