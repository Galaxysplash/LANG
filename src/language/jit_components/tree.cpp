#include "tree.h"

#include <cstdint>
#include <iostream>
#include <ostream>

#include "parser.h"
#include "classes/implicit_func.h"
#include "global/core.h"
#include "global/variables.h"

void tree::exec() {

    clear();
}

void tree::clear() {
    _nums_list_for_current_line.clear();
    _multiplication_division.clear();
}


void tree::build(
    const instruction & instruction_in,
    const str_list && keyword_priority_list_move,
    const bool in_terminal
) {
    get_numbers_and_head(
        instruction_in,
        char_list{'*', '/'},
        [&](
            const char & op_ref,
            const std::string_view & tail_ref
        ) {


    });

    //---
    _multiplication_division.emplace_back(op_ref);

    try {
        _nums_list_for_current_line.emplace_back(std::stod(std::string(tail_ref)));
    }catch(...) {
        _nums_list_for_current_line.emplace_back(1);
    }
    //---
}

void tree::get_numbers_and_head(
    const instruction & instruction_in,
    std::function<void(

    )> func
) {
}