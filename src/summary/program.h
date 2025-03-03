# pragma once

#include <initializer_list>
#include <vector>
#include <string>

///Pulls the code from the file and formats it.
void get_code(
    int argc, const char **argv, std::vector<std::string> &ret
);

///Analyzes the code and builds an abstract syntax tree.
void process_code(
    const std::vector<std::string> &instructions,
    const std::initializer_list<std::string> &&ops_priority
);

///Executes the abstract syntax tree, generated by 'process_code(...)'.
void execute_code();
