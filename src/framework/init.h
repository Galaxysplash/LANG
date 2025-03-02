#pragma once

#include <vector>
#include <string_view>


//public
constexpr inline unsigned char TXT_INDICATOR = '"';

void read(
    int argc, const char** argv, std::string& ret
);

void split(
    std::vector<std::string>& ret, const std::string& txt
);

