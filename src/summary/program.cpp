#include "program.h"
#include "framework/syntax.h"
#include "framework/init.h"

#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>

static constexpr std::string_view EXIT_INSTRUCTION = "exit";

static std::unordered_map<std::string, double> num_list;
static std::unordered_map<std::string, std::string> txt_list;
static std::unordered_map<std::string, bool> bit_list;

void run(const int argc, const char** argv, const bool in_terminal, std::vector<std::string>& instructions_ref) {
    if (in_terminal) {
        std::string str_buffer;
        printf("type in code, or 'exit' if you want to:\n");
        std::cin >> str_buffer;

        split(instructions_ref, str_buffer);
    }
    else {
        get_code(argc, argv, instructions_ref);
    }

    process_code(instructions_ref, {"+-", "*/"}, in_terminal);

    execute_code();
}

void get_code(const int argc, const char** argv, std::vector<std::string>& ret)
{
    std::string txt_buffer;

    read(argc, argv, txt_buffer);
    split(ret, txt_buffer);
}

void process_code(
    const std::vector<std::string>& instructions,
    const std::initializer_list<std::string_view>&& ops_priority,
    const bool in_terminal
)
{
    try_add_variables(instructions);
    check_if_user_wants_to_exit____if_they_are_in_terminal(instructions, in_terminal);
}

void execute_code()
{
    //printf("\ne.size: %d\n", static_cast<int>(num_list.size()));
}

void check_if_user_wants_to_exit____if_they_are_in_terminal(
    const std::vector<std::string>& instructions,
    const bool in_terminal
)
{
    if (in_terminal) {
        for (const auto& instruction: instructions) {
            if (instruction == EXIT_INSTRUCTION) {
                exit(0);
            }
        }
    }
}

void try_add_variables(const std::vector<std::string>& instructions) {
    filter_variable(instructions, "num", [](const std::string& name, const std::string& assigment) {
        if (!num_list.contains(name)) {
            try {
               const double& num = std::stod(assigment);

               num_list[name] = num;
            } catch (...) {
               printf("error for num var, because the assigment couldn't be converted to a number.\n");
            }
        }
        else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });

    filter_variable(instructions, "txt", [](const std::string& name, const std::string& assigment) {
        if (!txt_list.contains(name)) {
            txt_list[name] = assigment;
        }
        else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });

    filter_variable(instructions, "bit", [](const std::string& name, const std::string& assigment) {
        if (!bit_list.contains(name)) {
            if (assigment == "true") {
                bit_list[name] = true;
            }
            else if (assigment == "false") {
                bit_list[name] = false;
            }
        } else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });
}
