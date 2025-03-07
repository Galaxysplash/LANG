cmake_minimum_required(VERSION 3.30)
project(Lang)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    src
)

add_executable(
    Lang
    src/main.cpp
        src/framework/init/import.cpp
        src/framework/init/import.h
        src/framework/jit/parser.cpp
        src/framework/jit/parser.h
        src/jit/jit.cpp
        src/jit/jit.h
        src/classes/code.cpp
        src/classes/code.h
        src/exceptions/custom_err.cpp
        src/exceptions/custom_err.h
        src/tests/run.cpp
        src/tests/run.h
        src/framework/jit/lexer.cpp
        src/framework/jit/lexer.h
        src/globals/typedefs.h
        src/globals/global_variables.h
        src/framework/jit/tree.cpp
        src/framework/jit/tree.h
)
