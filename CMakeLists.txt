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
        src/language/jiter.cpp
        src/language/jiter.h
        src/language/classes/instruction.cpp
        src/language/classes/instruction.h
        src/tests/run.cpp
        src/tests/run.h
        src/language/jit_components/lexer.cpp
        src/language/jit_components/lexer.h
        src/language/globals/macros.h
        src/language/globals/global_variables.h
        src/language/jit_components/tree.cpp
        src/language/jit_components/tree.h
        src/language/globals/constexprs.h
        src/language/globals/typedefs.h
)
