#include "tree.h"
#include "globals/global_variables.h"

void tree::exec() {
}

void tree::build(
    const instruction &instruction_in,
    const std::initializer_list<std::string_view> && ops_priority_move,
    const bool in_terminal
) {
    go_trough_ops(instruction_in, ops_priority_move, in_terminal);
}

void tree::go_trough_ops(
    const instruction &instruction_in,
    const std::initializer_list<std::string_view> & ops_priority_list_ref,
    const bool in_terminal
) {
    for (const std::string_view & ops_priority_ref : ops_priority_list_ref) {

    }
}
