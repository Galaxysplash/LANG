#include "program.h"
#include "framework/syntax.h"
#include "framework/init.h"

#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>

static std::unordered_map<std::string, double> num_list;
static std::unordered_map<std::string, std::string> txt_list;
static std::unordered_map<std::string, bool> bit_list;

void get_code(const int argc, const char** argv, std::vector<std::string>& ret)
{
    std::string txt_buffer;

    read(argc, argv, txt_buffer);
    split(ret, txt_buffer);
}

void process_code(
    const std::vector<std::string>& instructions,
    const std::initializer_list<std::string_view>&& ops_priority
)
{
    filter_variables(instructions);
}

void execute_code()
{
    printf("\ne.size: %d\n", static_cast<int>(num_list.size()));
}

void filter_variables(const std::vector<std::string>& instructions) {

    filter_variable(instructions, "txt", [&](const std::string& name, const std::string& assigment) {

    });

    filter_variable(instructions, "bit", [&](const std::string& name, const std::string& assigment) {

    });
}

void run(const int argc, const char** argv, std::vector<std::string>& instructions_ref) {
    split(instructions_ref, "a: num = 10");

    process_code(instructions_ref, {"+-", "*/"});

    execute_code();
}
