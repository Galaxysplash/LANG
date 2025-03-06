#include "program.h"

#include <chrono>
#include <thread>
#include <format>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>

#include "framework/syntax.h"
#include "framework/init/init.h"
#include "framework/code.h"

static std::unordered_map<std::string_view, double> num_list;
static std::unordered_map<std::string_view, std::string> txt_list;
static std::unordered_map<std::string_view, bool> bit_list;



void program::start(
    const int argc,
    const char** argv,
    code& code_ref
)
{
    const bool in_terminal = argc <= 1;
    const std::unordered_map<std::string_view, std::function<void()>> one_word_commands = {
        {"exit", [&]() {
            exit(0);
        }},
        {"help", [&]() {
            printf("create variables with: \n");
            printf("a) foo: num = 10\n");
            printf("b) foo: txt = \"hello world\"\n");
            printf("c) foo: bit = true\n");
            printf("\n");
            printf("exit the program with: 'exit'\n");
        }}
    };

    if (!in_terminal) {
        get_code(argc, argv, code_ref);

        analyze_and_exec(in_terminal, code_ref, one_word_commands);
    }
    else {
        bool first_time = true;
        // ReSharper disable once CppDFAEndlessLoop
        while (true) {
            constexpr unsigned char max_input_buffer_length = 100;
            char c_str_buffer[max_input_buffer_length];

            if (first_time) {
                printf("LANG: type in commands or 'help', if you don't know any.\n");

                first_time = false;
            }
            printf("=>");
            std::cin.getline(c_str_buffer, max_input_buffer_length);
            str_to_code(code_ref, c_str_buffer);
            printf("\n");

            try {
                analyze_and_exec(in_terminal, code_ref, one_word_commands);
            } catch (const std::exception& e) {
                printf("Internal C++ error, when running the code: %s\n", e.what());
            }

            code_ref.clear();

            std::this_thread::sleep_for(std::chrono::seconds(1));

            printf("\n");
        }
    }
}

void program::analyze_and_exec(
    const bool in_terminal,
    const code& code_in,
    const std::unordered_map<std::string_view, std::function<void()>>& one_word_commands_in
)
{
    analyze_code(code_in, {"+-", "*/"}, in_terminal);

    exec_absract_syntax_tree();
    exec_basic_instructions(code_in, in_terminal, one_word_commands_in);
}

void program::get_code(const int argc, const char** argv, code& ret)
{
    std::string txt_buffer;

    read_file(argc, argv, txt_buffer);
    str_to_code(ret, txt_buffer);
}

void program::analyze_code(
    const code& code_in,
    const std::initializer_list<std::string_view>&& ops_priority,
    const bool in_terminal
)
{
    try_add_variables(code_in, in_terminal);
}

void program::exec_absract_syntax_tree()
{
}

void program::check_for_one_word_instruction(
    const code& code_in,
    const std::string_view& instruction_in,
    const std::function<void()>& func_in
) {
    for (const auto& instruction: code_in) {
        if (instruction == instruction_in) {
            func_in();
        }
    }
}

void program::try_add_variables(const code& instructions, const bool in_terminal) {
    syntax::filter_variable(instructions, "num", [&in_terminal](const std::string_view& name, const std::string_view& assigment) {
        if (!num_list.contains(name)) {
            try {
               const double& num = std::stod(std::string(assigment));

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

    syntax::filter_variable(instructions, "txt", [&in_terminal](const std::string_view& name, const std::string_view& assigment) {
        if (!txt_list.contains(name)) {
            txt_list[name] = assigment;

            if (in_terminal) {
                std::cout << std::format("NOTED: {} = {}", name, assigment) << "\n";
            }
        }
        else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });

    syntax::filter_variable(instructions, "bit", [&in_terminal](const std::string_view& name, const std::string_view& assigment) {
        if (!bit_list.contains(name)) {
            enum class assigment_enum {
                _null,
                _true,
                _false
            };

            auto assigment_buffer = assigment_enum::_null;

            if (assigment == "true") {
                assigment_buffer = assigment_enum::_true;
                bit_list[name] = true;
            }
            else if (assigment == "false") {
                assigment_buffer = assigment_enum::_false;
                bit_list[name] = false;
            }

            if (assigment_buffer != assigment_enum::_null && in_terminal) {
                printf("%s\n", std::format("NOTED: {} = {}", name, assigment).c_str());
            }
            else {
                printf("%s\n", std::format("error, bit could not be created, assignment is '{}'!", name).c_str());
            }
        } else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });
}

void program::exec_basic_instructions(
    const code& instructions,
    const bool in_terminal,
    const std::unordered_map<std::string_view, std::function<void()>>& one_word_commands_in
) {
    syntax::filter_instruction(instructions, {"print"}, [&in_terminal](const std::vector<std::string_view>& txt) {

    });

    if (in_terminal) {
        for (const auto&[keyword, func]: one_word_commands_in) {
            check_for_one_word_instruction(instructions, keyword, [&func]() {
                func();
            });
        }
    }
}
