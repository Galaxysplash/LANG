# pragma once

#include <initializer_list>
#include <string>
#include <vector>

void app(
    int argc,
    const char** argv,
    std::vector<std::string>& code
);

///Runs the code.
void run(
    int argc,
    const char** argv,
    bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION,
    std::vector<std::string>& instructions_ref
);

///Pulls the code from the file and formats it.
void get_code(
    int argc, const char **argv, std::vector<std::string> &ret
);

///Analyzes the code and builds an abstract syntax tree.
void process_code(
    const std::vector<std::string> &instructions,
    const std::initializer_list<std::string_view> &&ops_priority,
    bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION
);

///Executes the abstract syntax tree, generated by 'process_code(...)'.
void execute_code();

void check_if_user_wants_to_exit____if_they_are_in_terminal(
    const std::vector<std::string>& instructions,
    bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION
);

void try_add_variables(const std::vector<std::string>& instructions);