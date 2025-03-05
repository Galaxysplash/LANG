#include "syntax.h"

#include <iostream>
#include <ostream>
#include <string_view>

#include "init.h"
#include "framework/code.h"

void filter_instruction(
    const code &instructions,
    const std::vector<std::string_view> & filter_ref,
    const std::function<void(code& code_ref)> & func
)
{
    unsigned char counter = 0;
    code unknown_code{};

    for (const std::string& instruction: instructions) {
        const bool any_is_ok = filter_ref[counter] == ANYTHING_STR && !instruction.empty();
        counter = filter_ref[counter] == instruction ? counter + 1 : 0;

        if (any_is_ok) {
            unknown_code.get().push_back(instruction);
            ++counter;
        }

        //this if statement has to be the last one in this for loop
        if (counter == filter_ref.size()) {
            break;
        }
    }

    if (counter == filter_ref.size()) {
        func(unknown_code);
    }
}

void filter_instruction(
    const code &instructions,
    const std::vector<std::string_view> &&filter,
    const std::function<void(code& str_list_ref)> && func
)
{
    filter_instruction(instructions, filter, func);
}

void filter_variable(
    const code& instructions,
    const std::string_view && type_name_move,
    const std::function<void(const std::string& name, const std::string& assigment)> && func
)
{
    filter_instruction(
        instructions,
        {ANYTHING_STR, ":", type_name_move, "=", ANYTHING_STR},
        // ReSharper disable once CppParameterMayBeConstPtrOrRef
        [&](code& code_ref) -> void {
            unsigned char counter = 0;

            std::string instruction_1{}, instruction_2{};
            /*   ^^^^^^
             *This, is intentionally NOT a 'std::string_view'
             * a std::string_view here,
             * would break a lot off stuff (first and for most lambdas).
             * also I have tried to make everything with txt a std::string_view
             * and built wrappers around getting an index from it, which worked,
             * but at the end of the day the buffers were completely messed up.
            */ //------------------------------------------------------------

            for (const std::string& instruction_ref: code_ref) {
                if (counter == 0) {
                    // ReSharper disable once CppJoinDeclarationAndAssignment
                    instruction_1.append(instruction_ref);
                }

                if (counter == code_ref.get().size() -1) {
                    // ReSharper disable once CppJoinDeclarationAndAssignment
                    instruction_2.append(instruction_ref);
                }
                ++counter;
            }
            std::cout << instruction_1 << " " << instruction_2 << std::endl;
            func(instruction_1, instruction_2);
        }
    );
}