#pragma once

#include <functional>
#include <string_view>
#include <vector>


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
};
