cmake_minimum_required(VERSION 3.30)
project(Lang)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    src
)

include_directories(
    src/language
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
        src/language/classes/core/instruction.cpp
        src/language/classes/core/instruction.h
        src/tests/run.cpp
        src/tests/run.h
        src/language/jit_components/lexer.cpp
        src/language/jit_components/lexer.h
        src/language/global/variables.h
        src/language/jit_components/tree.cpp
        src/language/jit_components/tree.h
        src/language/global/pre_compiled.h
        src/language/classes/tree/implicit_func.cpp
        src/language/classes/tree/implicit_func.h
        src/language/global/core.cpp
        src/language/global/core.h
        src/language/classes/tree/nodes/num.cpp
        src/language/classes/tree/nodes/num.h
        src/language/classes/tree/nodes/node.cpp
        src/language/classes/tree/nodes/node.h
)