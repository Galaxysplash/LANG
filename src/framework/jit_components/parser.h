#pragma once

#include <vector>
#include <string_view>
#include <functional>

#include "framework/classes/instruction.h"

struct instruction;

constexpr std::string_view ANYTHING_STR = "???";

struct parser {
    static void filter_instruction(
      const instruction & code_in,
      const std::vector<std::string_view> & filter_ref,
      const std::function<void(instruction& str_list_ref)> & func_in
    );

    static void filter_instruction(
        const instruction & code_in,
        const std::vector<std::string_view> && filter_move,
        const std::function<void(instruction& str_list_ref)> && func_in
    );

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
        const instruction &instruction_in,
        bool in_terminal
    );

    static bool is_txt(
        const std::string_view &str_in
    );
};