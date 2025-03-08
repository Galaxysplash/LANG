#pragma once

#include <initializer_list>
#include <string_view>

#include "globals/typedefs.h"

struct instruction;

struct tree {
    static void exec();
    static void scan_though_list(const priority_list& );
    static void build(
        const instruction & instruction_in,
        const priority_list && ops_priority_list_move,
        const priority_list && keyword_priority_list_move,
        bool in_terminal
    );
};
