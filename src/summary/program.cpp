#include "program.h"

#include "framework/syntax.h"
#include "framework/init.h"

#include <chrono>
#include <thread>
#include <format>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>


static std::unordered_map<std::string, double> num_list;
static std::unordered_map<std::string, std::string> txt_list;
static std::unordered_map<std::string, bool> bit_list;



void app(
    const int argc,
    const char** argv,
    std::vector<std::string>& code
)
{
    const bool in_terminal = argc <= 1;
    bool first_time = true;
    constexpr std::string_view EXIT_INSTRUCTION = "exit";
    std::string str_buffer;

    // ReSharper disable once CppDFALoopConditionNotUpdated
    do {
        if (in_terminal) {
            if (first_time) {
                printf(std::format(
                    "Type in code, or '{}' if you want to. (Pay attention to upper and lower case!):\n",
                    EXIT_INSTRUCTION.data()
               ).c_str());

                first_time = false;
            }

            do {
                printf("=>");
                std::cin >> str_buffer;
            } while (str_buffer.empty());
        }

        run(argc, argv, in_terminal, str_buffer, EXIT_INSTRUCTION, code);

        if (in_terminal) {
            code.clear();
            str_buffer.clear();

            std::this_thread::sleep_for(std::chrono::seconds(1));

            printf("\n");
        }
    } while (in_terminal);
}

void run(
    const int argc,
    const char** argv,
    const bool in_terminal,
    const std::string& str,
    const std::string_view& EXIT_INSTRUCTION,
    std::vector<std::string>& instructions_ref
)
{
    if (in_terminal) {
        printf("run!");
        split(instructions_ref, str);
    }
    else {
        get_code(argc, argv, instructions_ref);
    }

    process_code(instructions_ref, {"+-", "*/"}, in_terminal, EXIT_INSTRUCTION);

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
    const bool in_terminal,
    const std::string_view& EXIT_INSTRUCTION
)
{
    try_add_variables(instructions);
    check_if_user_wants_to_exit____if_they_are_in_terminal(instructions, in_terminal, EXIT_INSTRUCTION);
}

void execute_code()
{
    //printf("\ne.size: %d\n", static_cast<int>(num_list.size()));
}

void check_if_user_wants_to_exit____if_they_are_in_terminal(
    const std::vector<std::string>& instructions,
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

void try_add_variables(const std::vector<std::string>& instructions) {
    printf("try_add_variables\n");

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
