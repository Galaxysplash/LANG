#include "tree.h"
#include "globals/global_variables.h"

void tree::exec() {
}

void tree::scan_though_list(
    const priority_list_t &
) {

}

void tree::build(
    const instruction & instruction_in,
    const priority_list_t && ops_priority_list_move,
    const priority_list_t && keyword_priority_list_move,
    const bool in_terminal
) {
    for (const std::initializer_list<std::string_view> & ops_priority_ref : ops_priority_list_move) {
        for (const std::string_view & op_ref : ops_priority_ref) {
            for (const std::string & instruction_part_ref : instruction_in) {
                if (op_ref.data() == instruction_part_ref.c_str()) {

                }
            }
        }
    }
}
