#pragma once

#include <string_view>

struct code;

struct lexer {
    static void str_to_code(
        code& ret, const std::string& txt
    );

    static void new_word(code &ret, std::string &word_ref);

    static void process_char(code &ret_ref, std::string& word_ref, char c);
};
