#include "syntax.h"

#include <iostream>
#include <ostream>
#include <string_view>
#include <cstdint>

#include "init.h"
#include "framework/code.h"

void syntax::filter_instruction(
    const code & code_in,
    const std::vector<std::string_view> & filter_ref,
    const std::function<void(std::vector<std::string_view>& str_list_ref)> & func_in
)
{
    if (filter_ref.empty()) {
        return;
    }

#define general_code_counter (known_code_counter + unknown_code_counter)
#define unknown_is_wanted (filter_ref[i] == ANYTHING_STR && !code_in[i].empty())

    uint8_t
        known_code_counter = 0,
        unknown_code_counter = 0,
        unknown_code_counter_limit = 0;

    for (const auto& filter_part_ref: filter_ref) {
        if (filter_part_ref == ANYTHING_STR) {
            ++unknown_code_counter_limit;
        }
    }

    std::vector<std::string_view> unknown_code_buffer{};

    for (int32_t i = 0; i < code_in.get().size(); ++i) {
        //body
        if (unknown_is_wanted) {
            unknown_code_buffer.push_back(code_in.get().at(i));
            ++unknown_code_counter;
        }
        else {
            if ((filter_ref[i] == code_in[i])) {
                ++known_code_counter;
            }
            else {
                return;
            }
        }

        //footer
        if (general_code_counter == filter_ref.size()) {
            break;
        }
    }

    if (general_code_counter == filter_ref.size()) {
        func_in(unknown_code_buffer);
    }
}

void syntax::filter_instruction(
    const code & code_in,
    const std::vector<std::string_view> && filter_move,
    const std::function<void(std::vector<std::string_view>& str_list_ref)> && func_in
)
{
    filter_instruction(code_in, filter_move, func_in);
}

void syntax::filter_variable(
    const code & code_in,
    const std::string_view && type_name_move,
    const std::function<void(const std::string_view& name, const std::string_view& assigment)> && func_in
)
{
    filter_instruction(
        code_in,
        {ANYTHING_STR, ":", type_name_move, "=", ANYTHING_STR},
        // ReSharper disable once CppParameterMayBeConstPtrOrRef
        [&](std::vector<std::string_view>& code_ref) -> void {
            unsigned char counter = 0;

            std::string_view instruction_1{}, instruction_2{};

            for (const std::string_view& instruction_ref: code_ref) {
                if (counter == 0) {
                    // ReSharper disable once CppJoinDeclarationAndAssignment
                    instruction_1 = instruction_ref;
                }

                if (counter == code_ref.size() -1) {
                    // ReSharper disable once CppJoinDeclarationAndAssignment
                    instruction_2 = instruction_ref;
                }
                ++counter;
            }

            func_in(instruction_1, instruction_2);
        }
    );
}