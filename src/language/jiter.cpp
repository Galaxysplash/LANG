#include "language/jiter.h"

#include <chrono>
#include <thread>
#include <format>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>

#include "init/import.h"
#include "classes/core/instruction.h"
#include "global/pre_compiled.h"
#include "jit_components/lexer.h"
#include "jit_components/parser.h"
#include "jit_components/tree.h"


void jiter::run(
    const int argc,
    const char** argv,
    instruction& code_ref
)
{
    const bool in_terminal = argc <= 1;
    const HASH_TABLE(std::function<void()>) one_word_commands = {
        {"exit", [&]() {
            exit(0);
        }},
        {"help", [&]() {
            printf("create variables with: \n");
            printf("a) x: num = 10\n");
            printf("b) y: txt = \"hello world\"\n");
            printf("c) z: bit = true\n");
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
                std::cerr << "Internal C++ error, when running the code: " << e.what() << "\n";
                std::cout << "Please report this error to the github repository:\n https://github.com/Galaxysplash/LANG!\n";
            }

            code_ref.clear();

            std::this_thread::sleep_for(std::chrono::seconds(1));

            printf("\n");
        }
    }
}

void jiter::get_code(const int argc, const char** argv, instruction& ret)
{
    std::string str_buffer;

    import::file(argc, argv, str_buffer);
    lexer::str_to_code(ret, str_buffer);
}

void jiter::analyze_and_exec(
    const bool in_terminal,
    const instruction& instruction_in,
    const std::unordered_map<std::string, std::function<void()>>& one_word_commands_in
)
{
    tree::run(instruction_in);

    parser::try_add_variables(instruction_in, in_terminal, [&](
        const std::function<void(const std::string&, const std::string&)> & try_create_num_func_ref,
        const std::function<void(const std::string&, const std::string&)> & try_create_txt_func_ref,
        const std::function<void(const std::string&, const std::string&)> & try_create_bit_func_ref
    ) {
        #define VAR_SYNTAX_FIVE_PARTS(ARG1, ARG2, ARG3, ARG4, ARG5, LAMBDA) \
        parser::filter_variable( \
        instruction_in, \
        {ARG1, ARG2, ARG3, ARG4, ARG5}, \
        [&LAMBDA](const std::string& name, const std::string& assigment) { \
        LAMBDA(name, assigment); \
        });

        #pragma region num
        VAR_SYNTAX_FIVE_PARTS(ANYTHING_STR, ":", "num", "=", ANYTHING_STR, try_create_num_func_ref)
        VAR_SYNTAX_FIVE_PARTS("num", ":", ANYTHING_STR, "=", ANYTHING_STR, try_create_num_func_ref)
        #pragma endregion num

        #pragma region txt
        VAR_SYNTAX_FIVE_PARTS(ANYTHING_STR, ":", "txt", "=", ANYTHING_STR, try_create_txt_func_ref)
        VAR_SYNTAX_FIVE_PARTS("txt", ":", ANYTHING_STR, "=", ANYTHING_STR, try_create_txt_func_ref)
        #pragma endregion txt

        #pragma region bit
        VAR_SYNTAX_FIVE_PARTS(ANYTHING_STR, ":", "bit", "=", ANYTHING_STR, try_create_bit_func_ref)
        VAR_SYNTAX_FIVE_PARTS("bit", ":", ANYTHING_STR, "=", ANYTHING_STR, try_create_bit_func_ref)
        #pragma endregion bit
    });
    tree::exec();
    parser::exec_basic_instructions(instruction_in, in_terminal, one_word_commands_in);
}