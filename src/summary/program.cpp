#include "program.h"

#include <chrono>
#include <thread>
#include <format>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>

#include "framework/syntax.h"
#include "framework/init.h"
#include "framework/code.h"


static std::unordered_map<std::string, double> num_list;
static std::unordered_map<std::string, std::string> txt_list;
static std::unordered_map<std::string, bool> bit_list;



void app(
    const int argc,
    const char** argv,
    code& instructions_ref
)
{
    const bool in_terminal = argc <= 1;
    constexpr std::string_view EXIT_INSTRUCTION = "exit";

    if (!in_terminal) {
        get_code(argc, argv, instructions_ref);

        run(in_terminal, EXIT_INSTRUCTION, instructions_ref);
    }
    else {
        bool first_time = true;
        // ReSharper disable once CppDFAEndlessLoop
        while (true) {
            std::string str_buffer;

            if (first_time) {
                printf(std::format(
                    "Type in code, or '{}' if you want to. (Pay attention to upper and lower case!):\n",
                    EXIT_INSTRUCTION.data()
               ).c_str());

                first_time = false;
            }

            printf("=>");
            std::cin >> str_buffer;
            printf("\n");

            str_to_code(instructions_ref, str_buffer);

            run(in_terminal, EXIT_INSTRUCTION, instructions_ref);

            instructions_ref.clear();
            str_buffer.clear();

            std::this_thread::sleep_for(std::chrono::seconds(1));

            printf("\n");
        }
    }
}

void run(
    const bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION,
    const code& instructions_ref
)
{
    analyze_code(instructions_ref, {"+-", "*/"}, in_terminal, EXIT_INSTRUCTION);

    execute_absract_syntax_tree();
}

void get_code(const int argc, const char** argv, code& ret)
{
    std::string txt_buffer;

    read_file(argc, argv, txt_buffer);
    str_to_code(ret, txt_buffer);
}

void analyze_code(
    const code& instructions,
    const std::initializer_list<std::string_view>&& ops_priority,
    const bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION
)
{
    try_add_variables(instructions);
    check_for_exit(instructions, in_terminal, EXIT_INSTRUCTION);
}

void execute_absract_syntax_tree()
{
}

void check_for_exit(
    const code& instructions,
    const bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION
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

void try_add_variables(const code& instructions) {
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
