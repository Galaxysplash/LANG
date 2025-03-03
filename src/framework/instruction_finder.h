#pragma once

#include <vector>
#include <string>
#include <functional>

template <unsigned char N>
void instruction_finder(
    const std::vector<std::string>& txt_list,
    std::array<std::string_view, N>&& filter,
    const std::function<void(const std::array<std::string_view, N>&& list)>&& func
);
