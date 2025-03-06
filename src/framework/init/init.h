#pragma once

#include <string_view>
#include <functional>

struct code;
//public
constexpr inline unsigned char TXT_INDICATOR = '"';

void read_file(
    int argc, const char** argv, std::string& ret
);

void str_to_code(
    code& ret, const std::string& txt
);

void new_word(code &ret, std::string &word_ref);

void process_char(code &ret_ref, std::string& word_ref, char c);
