#include "syntax.h"

#include <iostream>


void bind_instruction(
    const std::string& instruction,
    const std::initializer_list<std::pair<const std::string, std::function<void()>>>&& compare_list,
    const std::function<void()>&& default_case_func
) {
    for (const auto&[comparison, func]: compare_list) {
        if (instruction == comparison) {
            func();
            return;
        }
    }

    default_case_func();
}

