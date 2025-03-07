#pragma once

#include <vector>
#include <string_view>
#include <functional>

struct code;

constexpr std::string_view ANYTHING_STR = "???";

struct parser {
    static void filter_instruction(
      const code & code_in,
      const std::vector<std::string_view> & filter_ref,
      const std::function<void(std::vector<std::string_view>& str_list_ref)> & func_in
    );

    static void filter_instruction(
        const code & code_in,
        const std::vector<std::string_view> && filter_move,
        const std::function<void(std::vector<std::string_view>& str_list_ref)> && func_in
    );

    static void filter_variable(
        const code & code_in,
        const std::string_view && type_name_move,
        const std::function<void(const std::string_view& name, const std::string_view& assigment)> && func_in
    );

    static void check_for_one_word_instruction(
        const code &code_in,
        const std::string_view &instruction_in,
        const std::function<void()> &func_in
    );

    static void exec_basic_instructions(
        const code &instructions, bool in_terminal,
        const std::unordered_map<std::string_view, std::function<void()>> &
        one_word_commands_in
    );

    static void try_add_variables(
        const code &instructions,
        bool in_terminal
    );

    static void analyze_code(
        const code &code_in,
        const std::initializer_list<std::string_view> &&ops_priority,
        bool in_terminal
    );

    static void check_if_its_txt(
        const code &code_in
    );
};