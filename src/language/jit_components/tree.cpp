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
        [&](
            const char & op_ref,
            const std::string_view & tail_ref
        ) {
            _multiplication_division.emplace_back(op_ref);

            try {
                _nums_list_for_current_line.emplace_back(std::stod(std::string(tail_ref)));
            } catch(...) {
                _nums_list_for_current_line.emplace_back(1);
            }
    });
}

void tree::get_numbers_and_head(
    const instruction & instruction_in,
    const std::function<void(
        const double & number_in,
        const std::string & head_in
    )> & func_in
) {
    std::string str_buffer;

    for (const std::string& instruction_part_ref: instruction_in) {
        try {
            func_in(std::stod(instruction_part_ref), str_buffer);
            str_buffer.clear();
        } catch(...) {
            str_buffer += instruction_part_ref;
        }
    }
}