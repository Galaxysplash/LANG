#pragma once

#include <string_view>

struct instruction;

struct lexer {
    static void str_to_code(
        instruction& ret, const std::string& txt
    );

    static void new_word(instruction &ret, std::string &word_ref);

    static void process_char(instruction &ret_ref, std::string& word_ref, char c, bool& txt_indicator_ref);
};
