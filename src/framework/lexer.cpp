#include "lexer.h"

#include <format>

#include "code.h"
#include "globals/global_variables.h"

//private
static constexpr unsigned char STR_START_SIZE = 5;
static constexpr char SPECIAL_CHARS[] = {',', ';', '\n', ':', '.', '\t', '\r', '='};
static constexpr char SPACE = ' ';

void lexer::str_to_code(
    code &ret, const std::string &txt
) {
    std::string word{};
    word.reserve(STR_START_SIZE);

    for (const char c: txt) {
        process_char(ret, word, c);
    }

    new_word(ret, word);
}

void lexer::new_word(code &ret, std::string &word_ref) {
    if (!word_ref.empty()) {
        ret.get().emplace_back(word_ref);
        word_ref.clear();
        word_ref.reserve(STR_START_SIZE);
    }
}

void lexer::process_char(code &ret_ref, std::string& word_ref, const char c) {
    bool special_char = false;

    if (c == TXT_INDICATOR) {
        word_ref.push_back(c);
        return;
    }

    if (c == SPACE) {
        new_word(ret_ref, word_ref);
        return;
    }

    for (const char SIGN: SPECIAL_CHARS) {
        if (c == SIGN) {
            special_char = true;

            new_word(ret_ref, word_ref);
            word_ref.push_back(c);
            new_word(ret_ref, word_ref);
            break;
        }
    }

    if (special_char) {
        return;
    }

    word_ref.push_back(c);
}
