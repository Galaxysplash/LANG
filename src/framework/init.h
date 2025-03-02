#pragma once

#include <vector>
#include <string_view>

void read(
    int argc, const char** argv, std::string& ret
);

void split(
    std::vector<std::string_view>& ret, const std::string_view& txt
);

