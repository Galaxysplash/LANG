#include "core.h"

#include <cstdint>
#include <functional>

#include "classes/core/instruction.h"
#include "global/pre_compiled.h"

void core::filter_instruction(
    const instruction & instruction_in,
    const std::vector<std::string_view> & filter_ref,
    const std::function<void(instruction & instruction_ref)> & func_in
) {
    if (filter_ref.empty()) {
        return;
    }
#pragma region filter_instruction
#define GENERAL_CODE_COUNTER (known_code_counter + unknown_code_counter)
#define UNKNOWN_IS_WANTED (filter_ref[i] == ANYTHING_STR && !instruction_in[i].empty())

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

    for (int32_t i = 0; i < instruction_in.get().size(); ++i) {
        //body
        if (UNKNOWN_IS_WANTED) {
            unknown_code_buffer.emplace_back(instruction_in.get().at(i));
            ++unknown_code_counter;
        }
        else {
            if ((filter_ref[i] == instruction_in[i])) {
                ++known_code_counter;
            }
            else {
                return;
            }
        }

        //footer
        if (GENERAL_CODE_COUNTER == filter_ref.size()) {
            break;
        }
    }

    if (GENERAL_CODE_COUNTER == filter_ref.size()) {
        func_in(unknown_code_buffer);
    }
#pragma endregion
}

void core::filter_instruction(
    const instruction & instruction_in,
    const std::vector<std::string_view> && filter_move,
    const std::function<void(instruction & instruction_ref)> && func_in
) {
    filter_instruction(instruction_in, filter_move, func_in);
}