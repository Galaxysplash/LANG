#pragma once

#include <functional>
#include <utility>
#include <string>

static constexpr inline unsigned char CODE_VIEW_SIZE = 5;

static_assert(CODE_VIEW_SIZE % 2 != 0 && CODE_VIEW_SIZE > 4, "'code_view_size' has to be odd!");


void varibales(
    const std::vector<std::string>& instructions,
    std::vector<std::string_view>&& filter,
    const std::function<void()>&& func
);


void bind_instruction(
    const std::string& instruction,
    const std::initializer_list<std::pair<const std::string, std::function<void()>>>&& compare_list,
    const std::function<void()>&& default_case_func = []()
    {
    }
);


