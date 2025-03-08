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
    _ops_list_for_current_line.clear();
}

void tree::scan_trough_list(
    const instruction & instruction_in,
    const priority_list & priority_list_in,
    const std::function<void(
        uint16_t i = 0,
        const std::string_view &op,
        const std::string_view &tail
    )> && func_move
) {
    for (const std::string & instruction_part_ref : instruction_in) {
        for (uint16_t priority = 0; const std::initializer_list<std::string_view> & ops_priority_ref : priority_list_in) {
            for (const std::string_view & op_ref : ops_priority_ref) {
                if (op_ref.data() == instruction_part_ref.c_str()) {
                    core::filter_instruction(
                        instruction_in,
                        {op_ref.data(), ANYTHING_STR},
                        [&](const instruction & unknown_in) {
                            try {
                                func_move(priority, op_ref, unknown_in[0]);
                            } catch (...) {
                                func_move(priority, op_ref, "");
                            }
                    });
                }
            }
            ++priority;
        }
    }
}

void tree::build(
    const instruction & instruction_in,
    const priority_list && ops_priority_list_move,
    const priority_list && keyword_priority_list_move,
    const bool in_terminal
) {
    scan_trough_list(
        instruction_in,
        ops_priority_list_move,
        [&](
            const uint16_t priority = 0,
            const std::string_view & op_ref,
            const std::string_view & tail_ref
        ) {
            try {
                _ops_list_for_current_line.at(priority).emplace_back(op_ref);
            } catch (...) {
                _ops_list_for_current_line.emplace_back(std::vector{op_ref});
            }
            try {
                _nums_list_for_current_line.emplace_back(std::stod(std::string(tail_ref)));
            }catch(...) {
                _nums_list_for_current_line.emplace_back(1);
            }
    });
}



