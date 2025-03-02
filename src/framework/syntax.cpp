#include "syntax.h"


void analyze(
    const std::vector<std::string_view>& instructions,
    const std::function<void(
        const std::array<std::string_view, CODE_VIEW_SIZE>& code_view
    )>&& function
) {

    std::array<std::string_view, CODE_VIEW_SIZE> view_memory{};

    for (const std::string_view& instruction : instructions) {
        for (int i = 0; i < CODE_VIEW_SIZE; ++i) {
            view_memory[i] = i == 0 ? instruction : view_memory[i - 1];
        }

        try {
            function(view_memory);
        } catch (...) {}
    }
}

void bind_instruction(
    const std::string_view& instruction,
    const std::initializer_list<std::pair<const std::string_view, std::function<void()>>>&& compare_list,
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

