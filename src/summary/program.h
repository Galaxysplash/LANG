# pragma once


#include <initializer_list>
#include <string>

#include "framework/code.h"

void app(
    int argc,
    const char** argv,
    code& code_ref
);

///Runs the code.
void run(
    bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION,
    const code& code_ref
);

///Pulls the code from the file and formats it.
void get_code(
    int argc, const char **argv, code &ret
);

///Analyzes the code and builds an abstract syntax tree.
void analyze_code(
    const code &instructions,
    const std::initializer_list<std::string_view> &&ops_priority,
    bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION
);

///Executes the abstract syntax tree, generated by 'analyze_code(...)'.
void execute_absract_syntax_tree();

void check_for_exit(
    const code& instructions,
    bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION
);

void try_add_variables(const code& instructions);