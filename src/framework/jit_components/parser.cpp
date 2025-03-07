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
    const std::function<void(std::vector<std::string>& str_list_ref)> & func_in
) {
    if (filter_ref.empty()) {
        return;
    }
#pragma region filter_instruction
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

    instruction unknown_code_buffer{};

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
#pragma endregion
}

void parser::filter_instruction(
    const instruction & code_in,
    const std::vector<std::string_view> && filter_move,
    const std::function<void(std::vector<std::string>& str_list_ref)> && func_in
) {
    filter_instruction(code_in, filter_move, func_in);
}

void parser::filter_variable(
    const instruction & code_in,
    const std::string_view && type_name_move,
    const std::function<void(const std::string& name, const std::string& assigment)> && func_in
) {
    filter_instruction(
        code_in,
        {ANYTHING_STR, ":", type_name_move, "=", ANYTHING_STR},
        // ReSharper disable once CppParameterMayBeConstPtrOrRef
        [&](std::vector<std::string>& code_ref) -> void {
            unsigned char counter = 0;

            std::string instruction_1{}, instruction_2{};

            for (const std::string& instruction_ref: code_ref) {
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
    const std::unordered_map<std::string, std::function<void()>>& one_word_commands_in
) {
    filter_instruction(instructions, {"print", ANYTHING_STR}, [&in_terminal](const std::vector<std::string>& list) {
        if (const std::string_view print_arg = list.at(0); is_txt(print_arg)) {
            std::cout << "out: " << print_arg << "\n";
        }
        else if (num_list.contains(std::string(print_arg))) {
            std::cout << "out: " << num_list[std::string(print_arg)] << "\n";
        }
        else if (bit_list.contains(std::string(print_arg))) {
            std::cout << "out: " << bit_list[std::string(print_arg)] << "\n";
        }
        else if (txt_list.contains(std::string(print_arg))) {
            std::cout << "out: " << txt_list[std::string(print_arg)] << "\n";
        }
        else {
            if (in_terminal) {
                std::cerr << "error, what you wanted to be printed out was nor in '\"'," <<
                " neither could the system find it in the known variables.\n";
                std::cout << "info: what the system saw is '" << print_arg << "'\n";
                std::cout << "\nknown variables are:";


                std::cout << "\n\nnumbers:\n"; {
                    for (const auto&[num_name_ref, num_ref]: num_list) {
                       std::cout << "-" << num_name_ref << " with the value of " << num_ref << "\n";
                    }

                    if (num_list.empty()) {
                        std::cout << "none\n";
                    }
                }

                std::cout << "\n\nbits:\n"; {
                    // ReSharper disable once CppUseElementsView
                   for (const auto&[bit_name_ref, bit_ref]: bit_list) {
                       if (bit_ref) {
                           std::cout << "-" << bit_name_ref << " with the value of true\n";
                       }
                       else {
                           std::cout << "-" << bit_name_ref << " with the value of false\n";
                       }
                   }

                    if (bit_list.empty()) {
                        std::cout << "none\n";
                    }
                }

                std::cout << "\n\ntexts:\n"; {
                    for (const auto&[txt_name_ref, txt_ref]: txt_list) {
                       std::cout << "-" << txt_ref << " with the value of " << txt_name_ref << "\n";
                    }

                    if (txt_list.empty()) {
                        std::cout << "none\n";
                    }
                }

                std::cout << "\n";
            }
        }
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
#pragma region try_add_variables
#define new_variable_condition (!num_list.contains(name) && !txt_list.contains(name) && !bit_list.contains(name))
    filter_variable(instructions, "num", [&in_terminal](const std::string& name, const std::string& assigment) {
        if (new_variable_condition) {
            try {
               const double& num = std::stod(std::string(assigment));

               num_list[std::string(name)] = num;

                if (in_terminal) {
                    printf("%s\n", std::format("NOTED: {} = {}", name, assigment).c_str());
                }
            } catch (...) {
               std::cerr << "error, variable could not be created, because the assigment NEEDS to be a number.\n";
            }
        }
        else {
            std::cerr << "error, variable could not be created, it already exists.\n";
        }
    });

    filter_variable(instructions, "txt", [&in_terminal](const std::string& name, const std::string& assigment) {
        if (new_variable_condition) {
            if (is_txt(assigment)) {
                txt_list[name] = assigment;

               if (in_terminal) {
                   std::cout << std::format("NOTED: {} = {}", name, assigment) << "\n";
               }
            }
            else {
                if (in_terminal) {
                    std::cerr << "error, variable of type txt could not be created assigment NEEDS the '\"' at the begin as well, as at the end.\n";
                }
            }
        }
        else {
            if (in_terminal) {
                std::cerr << "error, variable could not be created, it already exists.\n";
            }
        }
    });

    filter_variable(instructions, "bit", [&in_terminal](const std::string& name, const std::string& assigment) {
        if (new_variable_condition) {
            enum class assigment_enum {
                _null,
                _true,
                _false
            };

            auto assigment_buffer = assigment_enum::_null;

            if (assigment == "true") {
                assigment_buffer = assigment_enum::_true;
                bit_list[std::string(name)] = true;
            }
            else if (assigment == "false") {
                assigment_buffer = assigment_enum::_false;
                bit_list[std::string(name)] = false;
            }

            if (assigment_buffer != assigment_enum::_null && in_terminal) {
                printf("%s\n", std::format("NOTED: {} = {}", name, assigment).c_str());
            }
            else {
                if (in_terminal) {
                    std::cerr << "error, variable could not be created, because the assigment NEEDS to be true or false.\n";
                }
            }
        } else {
            if (in_terminal) {
                std::cerr <<"error, variable could not be created, it already exists.\n";
            }
        }
    });
#pragma endregion try_add_variables
}

void parser::analyze_code(
    const instruction& instruction_in,
    const std::initializer_list<std::string_view>&& ops_priority,
    const bool in_terminal
) {
    try_add_variables(instruction_in, in_terminal);
}

bool parser::is_txt(
    const std::string_view & str_in
) {
#pragma region check_if_its_txt
#define last_instruction (i == str_in.size() - 1)
#define first_instruction (i == 0)
    bool is_txt = true;

    for (uint32_t i = 0; i < str_in.size(); ++i) {
        if (first_instruction || last_instruction) {
            if (str_in.at(i) != TXT_INDICATOR) {
                is_txt = false;
            }
        }
    }

    return is_txt;
#pragma endregion
}