#pragma once

#include <functional>
#include <string_view>


struct instruction;

struct core {
    static void filter_instruction(
        const instruction & instruction_in,
        const std::initializer_list<std::string_view> & filter_ref,
        const std::function<void(instruction & instruction_ref)> & func_in
    );

    static void filter_instruction(
        const instruction &instruction_in,
        const std::initializer_list<std::string_view> &&filter_move,
        const std::function<void(instruction &instruction_ref)> &&func_in
    );

    static bool is_a_sign(char c_in);

    static bool is_txt(const std::string_view &str_in);
};
