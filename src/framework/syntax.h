#pragma once

#include <vector>
#include <string>
#include <string_view>

constexpr std::string_view ANYTHING_STR = "???";

bool filter_instruction(
    const std::vector<std::string> & instructions,
    const std::vector<std::string_view> && filter
);