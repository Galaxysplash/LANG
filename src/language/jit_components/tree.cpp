#include "tree.h"

#include "parser.h"

void tree::exec() {
    for (const auto& num: s_nums) {

    }

    clear();
}

void tree::build(
    const instruction & instruction_in,
    const str_list && keyword_priority_list_move,
    const bool in_terminal
) {
    get_numbers_and_head(
        instruction_in,
        [&](
            const double & number_in,
            const std::string_view & head_ref
        ) {
        s_nums.emplace_back(number_in, head_ref);
    });
}

void tree::get_numbers_and_head(
    const instruction & instruction_in,
    const std::function<void(
        const double & number_in,
        const std::string & head_in
    )> & func_in
) {
    std::string str_buffer{};

    for (const std::string& instruction_part_ref: instruction_in) {
        try {
            func_in(std::stod(instruction_part_ref), str_buffer);
            str_buffer.clear();
        } catch(...) {
            str_buffer += instruction_part_ref;
        }
    }
}

void tree::clear() {
    s_nums.clear();
}