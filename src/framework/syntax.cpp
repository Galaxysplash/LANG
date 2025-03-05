#include "syntax.h"

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
        counter = filter_ref[counter] == instruction || any_is_ok ? counter + 1 : 0;

        if (counter == filter_ref.size()) {
            break;
        }

        if (any_is_ok) {
            unknown_code.emplace_back(instruction);
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
        [&](code& code_ref) {
            func(code_ref.front(), code_ref.back());
        }
    );
}


