#pragma once

#include <cstdint>
#include <functional>

#include "global/pre_compiled.h"

struct instruction;

struct tree {
    static void exec();

    static void build(
        const instruction & instruction_in,
        const priority_list && ops_priority_list_move,
        const priority_list && keyword_priority_list_move,
        bool in_terminal
    );

private:
    static std::vector<double> _nums_list_for_current_line;
    static std::vector<std::string_view> _ops_list_for_current_line;
};