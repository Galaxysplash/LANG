#pragma once

#include <vector>
#include <string>
#include <functional>

bool instruction_finder(
    const std::vector<std::string> & instructions,
    const std::vector<std::string_view> && filter
);