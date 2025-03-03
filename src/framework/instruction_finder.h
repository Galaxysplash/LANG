#pragma once

#include <vector>
#include <string>
#include <functional>

void instruction_finder(
    const std::vector<std::string>& txt_list,
    const std::initializer_list<std::string_view> && filter,
    const std::function<void(const std::initializer_list<std::string_view> & list)>&& func
);
