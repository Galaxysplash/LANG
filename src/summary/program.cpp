#include "program.h"

#include <chrono>
#include <thread>
#include <format>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>

#include "framework/parser.h"
#include "framework/import.h"
#include "framework/code.h"
#include "framework/data_type.h"
#include "framework/lexer.h"
#include "framework/tree.h"


void program::run(
    const int argc,
    const char** argv,
    code& code_ref
)
{
    const bool in_terminal = argc <= 1;
    const hash_table(std::function<void()>) one_word_commands = {
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
            lexer::str_to_code(code_ref, c_str_buffer);
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
    parser::analyze_code(code_in, {"+-", "*/"}, in_terminal);

    tree::exec_absract_syntax_tree();
    parser::exec_basic_instructions(code_in, in_terminal, one_word_commands_in);
}

void program::get_code(const int argc, const char** argv, code& ret)
{
    std::string str_buffer;

    import::file(argc, argv, str_buffer);
    lexer::str_to_code(ret, str_buffer);
}