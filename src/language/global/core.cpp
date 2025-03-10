#include "core.h"

#include <cstdint>
#include <functional>

#include "classes/core/instruction.h"
#include "global/pre_compiled.h"

void core::filter_instruction(
    const instruction & instruction_in,
    const std::initializer_list<std::string_view> & filter_ref,
    const std::function<void(instruction & unknown_instruction_ref)> & func_in
) {
    if (filter_ref.size() == 0) {
        return;
    }

    uint8_t
        known_code_counter = 0,
        unknown_code_counter = 0,
        unknown_code_counter_limit = 0;

    for (const auto& filter_part_ref: filter_ref) {
        if (filter_part_ref == ANYTHING_STR) {
            ++unknown_code_counter_limit;
        }
    }

    instruction unknown_code_buffer{};

    for (int32_t i = 0; const auto& filter_part_ref: filter_ref) {
        //body
        if (filter_part_ref == ANYTHING_STR && !instruction_in[i].empty()) {
            unknown_code_buffer.emplace_back(instruction_in.get().at(i));
            ++unknown_code_counter;
        }
        else {
            if (filter_part_ref == instruction_in[i]) {
                ++known_code_counter;
            }
            else {
                return;
            }
        }

        //footer
        if ((known_code_counter + unknown_code_counter) == filter_ref.size()) {
            break;
        }
        ++i;
    }

    if ((known_code_counter + unknown_code_counter) == filter_ref.size()) {
        func_in(unknown_code_buffer);
    }
}

void core::filter_instruction(
    const instruction & instruction_in,
    const std::initializer_list<std::string_view> && filter_move,
    const std::function<void(instruction & unknown_instruction_ref)> && func_in
) {
    filter_instruction(instruction_in, filter_move, func_in);
}