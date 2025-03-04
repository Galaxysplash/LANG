#include "syntax.h"

#include "init.h"
#include "typedefs.h"
#include "tests/unit_test.h"

void filter_instruction(
    const std::vector<std::string> &instructions,
    const std::vector<std::string_view> & filter,
    const std::function<void(std::vector<std::string>& str_list_ref)> & func
)
{
    unsigned char counter = 0;
    std::vector<std::string> unknown_instructions{};

    for (const std::string& instruction: instructions) {
        const bool any_is_ok = filter[counter] == ANYTHING_STR && !instruction.empty();
        counter = filter[counter] == instruction || any_is_ok ? counter + 1 : 0;

        if (counter == filter.size()) {
            break;
        }

        if (any_is_ok) {
            unknown_instructions.emplace_back(instruction);
        }
    }
    if (counter == filter.size()) {
        func(unknown_instructions);
    }
}

unit_test(test1)
    bool passed = false;
    const std::string txt = "a: num = 10";
    code_t code;

    split(code, txt);


    filter_instruction(
        code, {"???", ":", "num", "=", "???"}, [&](std::vector<std::string>& str_list_ref) {
            passed = true;
        }
    );
unit_test_end(passed, "filter_instruction")

void filter_instruction(
    const std::vector<std::string> &instructions,
    const std::vector<std::string_view> &&filter,
    const std::function<void(std::vector<std::string>& str_list_ref)> && func
)
{
    filter_instruction(instructions, filter, func);
}

void filter_variable(
    const std::vector<std::string>& instructions,
    const std::string_view && str_view_ref,
    const std::function<void(const std::string& name, const std::string& assigment)> && func
)
{
    filter_instruction(
        instructions,
        {ANYTHING_STR, ":", str_view_ref, "=", ANYTHING_STR},
        // ReSharper disable once CppParameterMayBeConstPtrOrRef
        [&](std::vector<std::string>& str_list_ref) {
            func(str_list_ref.front(), str_list_ref.back());
        }
    );
}
