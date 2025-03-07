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
        src/framework/jit_components/parser.cpp
        src/framework/jit_components/parser.h
        src/jiter/jiter.cpp
        src/jiter/jiter.h
        src/framework/classes/instruction.cpp
        src/framework/classes/instruction.h
        src/framework/tests/run.cpp
        src/framework/tests/run.h
        src/framework/jit_components/lexer.cpp
        src/framework/jit_components/lexer.h
        src/globals/typedefs.h
        src/globals/global_variables.h
        src/framework/jit_components/tree.cpp
        src/framework/jit_components/tree.h
        src/globals/globals_precompiled.h
)
