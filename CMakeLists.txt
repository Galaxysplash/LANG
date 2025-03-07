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
        src/jit/jit.cpp
        src/jit/jit.h
        src/framework/code.cpp
        src/framework/code.h
        src/exceptions/custom_err.cpp
        src/exceptions/custom_err.h
        src/tests/run.cpp
        src/tests/run.h
        src/framework/lexer.cpp
        src/framework/lexer.h
        src/globals/data_types.h
        src/globals/global_variables.h
        src/framework/tree.cpp
        src/framework/tree.h
)
