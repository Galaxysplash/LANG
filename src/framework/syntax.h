#pragma once

#include <array>
#include <functional>
#include <utility>
#include <string_view>

static constexpr inline unsigned char CODE_VIEW_SIZE = 5;

static_assert(CODE_VIEW_SIZE % 2 != 0 && CODE_VIEW_SIZE > 4, "'code_view_size' has to be odd!");

void analyze(
    const std::vector<std::string_view>& instructions,
    const std::function<void(
        const std::array<std::string_view, CODE_VIEW_SIZE>& previous_instructions
    )>&& function
);


void bind_instruction(
    const std::string_view& instruction,
    const std::initializer_list<std::pair<const std::string_view, std::function<void()>>>&& compare_list,
    const std::function<void()>&& default_case_func
);


