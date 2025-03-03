#pragma once

#include <vector>
#include <string>
#include <functional>

bool instruction_finder(
    const std::vector<std::string> &txt_list,
    const std::initializer_list<std::string_view> & filter
);

bool instruction_finder(
    const std::vector<std::string>& txt_list,
    const std::initializer_list<std::string_view> && filter
);

void instruction_finder(
    const std::vector<std::string>& txt_list,
    const std::initializer_list<std::string_view> && filter,
    const std::function<void()>&& func
);
