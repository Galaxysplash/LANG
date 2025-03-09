#pragma once

#include <cstdint>
#include <functional>

#include "global/pre_compiled.h"

struct instruction;


struct tree {
    static void exec();

    static void build(
        const instruction & instruction_in,
        const str_list && keyword_priority_list_move,
        bool in_terminal
    );

private:
    static std::vector<double> _nums_list_for_current_line;
    static std::vector<char> _multiplication_division;

    static void get_numbers_and_head(
        const char_list & char_list_in,

    );

    static void clear();
};

struct a {

};

template <a T>
struct b {

};