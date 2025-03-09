#pragma once

#include <vector>
#include <functional>

#include "classes/tree/nodes/num.h"
#include "global/pre_compiled.h"

struct instruction;

static std::vector<num> s_nums;

struct tree {
    static void exec();

    static void build(
        const instruction & instruction_in,
        const str_list && keyword_priority_list_move,
        bool in_terminal
    );

private:
    static void get_numbers_and_head(
        const instruction & instruction_in,
        const std::function<void(
            const double& number_in,
            const std::string & head_in
        )> & func_in
    );

    static void clear();
};