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
    code& code_ref
)
{
    const bool in_terminal = argc <= 1;
    constexpr std::string_view EXIT_INSTRUCTION = "exit";
    constexpr unsigned char max_input_buffer_length = 100;

    if (!in_terminal) {
        get_code(argc, argv, code_ref);

        run(in_terminal, EXIT_INSTRUCTION, code_ref);
    }
    else {
        bool first_time = true;
        // ReSharper disable once CppDFAEndlessLoop
        while (true) {
            char c_str_buffer[max_input_buffer_length];

            if (first_time) {
                printf(std::format(
                    "Type in code, or '{}' if you want to. (Pay attention to upper and lower case!):\n",
                    EXIT_INSTRUCTION.data()
               ).c_str());

                first_time = false;
            }

            printf("=>");
            std::cin.getline(c_str_buffer, max_input_buffer_length);

            str_to_code(code_ref, c_str_buffer);

            run(in_terminal, EXIT_INSTRUCTION, code_ref);

            code_ref.clear();

            std::this_thread::sleep_for(std::chrono::seconds(1));

            printf("\n");
        }
    }
}

void run(
    const bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION,
    const code& code_ref
)
{
    analyze_code(code_ref, {"+-", "*/"}, in_terminal, EXIT_INSTRUCTION);

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
    try_add_variables(instructions, in_terminal);
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

void try_add_variables(const code& instructions, const bool in_terminal) {
    filter_variable(instructions, "num", [&in_terminal](const std::string& name, const std::string& assigment) {
        if (!num_list.contains(name)) {
            try {
               const double& num = std::stod(assigment);

               num_list[name] = num;

                if (in_terminal) {
                    printf("%s\n", std::format("NOTED: {} = {}", name, assigment).c_str());
                }
            } catch (...) {
               printf("error for num var, because the assigment couldn't be converted to a number.\n");
            }
        }
        else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });

    filter_variable(instructions, "txt", [&in_terminal](const std::string& name, const std::string& assigment) {
        if (!txt_list.contains(name)) {
            txt_list[name] = assigment;

            if (in_terminal) {
                printf("%s\n", std::format("NOTED: {} = '{}'", name, assigment).c_str());
            }
        }
        else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });

    filter_variable(instructions, "bit", [&in_terminal](const std::string& name, const std::string& assigment) {
        if (!bit_list.contains(name)) {
            enum class assigment_enum {
                _null,
                _true,
                _false
            };

            assigment_enum assigment_buffer = assigment_enum::_null;

            if (assigment == "true") {
                assigment_buffer = assigment_enum::_true;
                bit_list[name] = true;
            }
            else if (assigment == "false") {
                assigment_buffer = assigment_enum::_false;
                bit_list[name] = false;
            }

            if (assigment_buffer != assigment_enum::_null) {
                printf("%s\n", std::format("NOTED: {} = {}", name, assigment).c_str());
            }
        } else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });
}
