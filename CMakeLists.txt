cmake_minimum_required(VERSION 3.30)
project(Lang)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    src
)

add_executable(
    Lang
    src/main.cpp
        src/language/init/import.cpp
        src/language/init/import.h
        src/language/jit_components/parser.cpp
        src/language/jit_components/parser.h
        src/jiter/jiter.cpp
        src/jiter/jiter.h
        src/language/classes/instruction.cpp
        src/language/classes/instruction.h
        src/language/tests/run.cpp
        src/language/tests/run.h
        src/language/jit_components/lexer.cpp
        src/language/jit_components/lexer.h
        src/globals/typedefs.h
        src/globals/global_variables.h
        src/language/jit_components/tree.cpp
        src/language/jit_components/tree.h
        src/globals/globals_precompiled.h
)
