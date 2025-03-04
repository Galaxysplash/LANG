#pragma once

#include <vector>
#include <string_view>
#include <functional>

//public
constexpr inline unsigned char TXT_INDICATOR = '"';

void read(
    int argc, const char** argv, std::string& ret
);

void split(
    std::vector<std::string>& ret, const std::string& txt
);

void process_char(const std::function<void()>& new_word_lambda, std::string& word_ref, char c);
