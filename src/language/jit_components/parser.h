#pragma once

#include <vector>
#include <string_view>
#include <functional>

#include "classes/core/instruction.h"
#include "global/pre_compiled.h"

struct instruction;

struct parser {
    static void filter_variable(
        const instruction & code_in,
        const std::initializer_list<std::string_view> && variable_syntax_move,
        const std::function<void(const std::string& name, const std::string& assigment)> && func_in
    );

    static void check_for_one_word_instruction(
        const instruction &code_in,
        const std::string_view &instruction_in,
        const std::function<void()> &func_in
    );

    static void exec_basic_instructions(
        const instruction &instructions, bool in_terminal,
        const std::unordered_map<std::string, std::function<void()>> &
        one_word_commands_in
    );

    static void try_add_variables(
        const instruction& instruction_in,
        bool in_terminal,
        const std::function<void(
            const std::function<void(const std::string&, const std::string&)> & try_create_num_func_ref,
            const std::function<void(const std::string&, const std::string&)> & try_create_txt_func_ref,
            const std::function<void(const std::string&, const std::string&)> & try_create_bit_func_ref
        )> && create_variables_lambda_in
    );

    static bool is_txt(
        const std::string_view &str_in
    );
};