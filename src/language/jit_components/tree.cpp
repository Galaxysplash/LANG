#include "tree.h"
#include "globals/global_variables.h"
#include "globals/macros.h"

void tree::exec() {
}

void tree::build(
    const instruction &instruction_in,
    const std::initializer_list<std::initializer_list<std::string_view>> && ops_priority_list_move,
    const std::initializer_list<std::initializer_list<std::string_view>> && keyword_priority_list_move,
    const bool in_terminal
) {
    for (const std::initializer_list<std::string_view> & ops_priority_ref : ops_priority_list_move) {
        for (const std::string_view & op_ref : ops_priority_ref) {

        }
    }
}
