#include "lexer.h"

#include <format>

#include "language/classes/instruction.h"
#include "globals/global_variables.h"
#include "globals/constexprs.h"

//private
static constexpr unsigned char S_STR_START_SIZE = 5;

void lexer::str_to_code(
    instruction &ret, const std::string &txt
) {
    std::string word{};
    word.reserve(S_STR_START_SIZE);
    bool txt_indicator = false;

    for (const char c: txt) {
        process_char(ret, word, c, txt_indicator);
    }

    new_word(ret, word);
}

void lexer::new_word(instruction &ret, std::string &word_ref) {
    if (!word_ref.empty()) {
        ret.get().emplace_back(word_ref);
        word_ref.clear();
        word_ref.reserve(S_STR_START_SIZE);
    }
}

void lexer::process_char(instruction &ret_ref, std::string& word_ref, const char c, bool& txt_indicator_ref) {
    if (c == G_TXT_INDICATOR) {
        word_ref.push_back(c);
        txt_indicator_ref = !txt_indicator_ref;
        return;
    }

    if (!txt_indicator_ref) {
        bool special_char = false;

        if (c == SPACE) {
            new_word(ret_ref, word_ref);
            return;
        }

        for (const char SIGN: SPECIAL_SIGNS) {
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
    }

    word_ref.push_back(c);
}
