#pragma once

#include <functional>

#include "globals/typedefs.h"

struct instruction;

struct tree {
    static void exec();

    static void scan_trough_list(
        const instruction & instruction_in,
        const priority_list_t & priority_list_in,
        const std::function<void(const std::string_view& op, const std::string_view& head)> && func_move
    );

    static void build(
        const instruction & instruction_in,
        const priority_list_t && ops_priority_list_move,
        const priority_list_t && keyword_priority_list_move,
        bool in_terminal
    );
};
