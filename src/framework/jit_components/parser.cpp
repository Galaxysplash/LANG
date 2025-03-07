#include "parser.h"

#include <string_view>
#include <cstdint>
#include <format>
#include <iostream>

#include "framework/classes/instruction.h"
#include "globals/global_variables.h"


void parser::filter_instruction(
    const instruction & code_in,
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
            unknown_code_buffer.emplace_back(code_in.get().at(i));
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

void parser::filter_instruction(
    const instruction & code_in,
    const std::vector<std::string_view> && filter_move,
    const std::function<void(std::vector<std::string_view>& str_list_ref)> && func_in
)
{
    filter_instruction(code_in, filter_move, func_in);
}

void parser::filter_variable(
    const instruction & code_in,
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

void parser::check_for_one_word_instruction(
    const instruction& code_in,
    const std::string_view& instruction_in,
    const std::function<void()>& func_in
) {
    for (const auto& instruction: code_in) {
        if (instruction == instruction_in) {
            func_in();
        }
    }
}

void parser::exec_basic_instructions(
    const instruction& instructions,
    const bool in_terminal,
    const std::unordered_map<std::string_view, std::function<void()>>& one_word_commands_in
) {
    filter_instruction(instructions, {"print", ANYTHING_STR}, [&in_terminal](const std::vector<std::string_view>& txt) {

    });

    if (in_terminal) {
        for (const auto&[keyword, func]: one_word_commands_in) {
            check_for_one_word_instruction(instructions, keyword, [&func]() {
                func();
            });
        }
    }
}

void parser::try_add_variables(const instruction& instructions, const bool in_terminal) {
    filter_variable(instructions, "num", [&in_terminal](const std::string_view& name, const std::string_view& assigment) {
        if (!num_list.contains(name)) {
            try {
               const double& num = std::stod(std::string(assigment));

               num_list[name] = num;

                if (in_terminal) {
                    printf("%s\n", std::format("NOTED: {} = {}", name, assigment).c_str());
                }
            } catch (...) {
               printf("error for num var, because the assigment couldn't be converted to a number.\n");
            }
        }
        else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });

    filter_variable(instructions, "txt", [&in_terminal](const std::string_view& name, const std::string_view& assigment) {
        if (!txt_list.contains(name)) {
            txt_list[name] = assigment;

            if (in_terminal) {
                std::cout << std::format("NOTED: {} = {}", name, assigment) << "\n";
            }
        }
        else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });

    filter_variable(instructions, "bit", [&in_terminal](const std::string_view& name, const std::string_view& assigment) {
        if (!bit_list.contains(name)) {
            enum class assigment_enum {
                _null,
                _true,
                _false
            };

            auto assigment_buffer = assigment_enum::_null;

            if (assigment == "true") {
                assigment_buffer = assigment_enum::_true;
                bit_list[name] = true;
            }
            else if (assigment == "false") {
                assigment_buffer = assigment_enum::_false;
                bit_list[name] = false;
            }

            if (assigment_buffer != assigment_enum::_null && in_terminal) {
                printf("%s\n", std::format("NOTED: {} = {}", name, assigment).c_str());
            }
            else {
                printf("%s\n", std::format("error, bit could not be created, assignment is '{}'!", name).c_str());
            }
        } else {
            printf("error, variable could not be created, it already exists.\n");
        }
    });
}

void parser::analyze_code(
    const instruction& code_in,
    const std::initializer_list<std::string_view>&& ops_priority,
    const bool in_terminal
)
{
    try_add_variables(code_in, in_terminal);
}

void parser::check_if_its_txt(const instruction & instruction_in) {

}