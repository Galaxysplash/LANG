#pragma once

#include <initializer_list>
#include <string_view>

#include "globals/macros.h"

struct instruction;

struct tree {
    static void exec();
    static void build(
        const instruction &instruction_in,
        const PRIORITY_LIST && ops_priority_list_move,
        const PRIORITY_LIST && keyword_priority_list_move,
        bool in_terminal
    );
};
