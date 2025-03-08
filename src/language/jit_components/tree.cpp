#include "tree.h"

#include "parser.h"
#include "globals/global_variables.h"

void tree::exec() {
}

void tree::scan_trough_list(
    const instruction & instruction_in,
    const priority_list_t & priority_list_in,
    const std::function<void(const std::string_view &op, const std::string_view &head)> && func_move
) {
    for (const std::string & instruction_part_ref : instruction_in) {
        for (const std::initializer_list<std::string_view> & ops_priority_ref : priority_list_in) {
            for (const std::string_view & op_ref : ops_priority_ref) {
                if (op_ref.data() == instruction_part_ref.c_str()) {
                    parser::filter_instruction(
                        instruction_in,
                        {op_ref.data(), ANYTHING_STR},
                        [](const instruction & unknown_in) {

                    });
                }
            }
        }
    }
}

void tree::build(
    const instruction & instruction_in,
    const priority_list_t && ops_priority_list_move,
    const priority_list_t && keyword_priority_list_move,
    const bool in_terminal
) {
    scan_trough_list(instruction_in, ops_priority_list_move, [&]() {

    });

    scan_trough_list(instruction_in, keyword_priority_list_move, [&]() {

    });
}
