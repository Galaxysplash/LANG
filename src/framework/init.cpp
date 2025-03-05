#include "init.h"

#include <fstream>
#include <functional>
#include <iostream>

#include "framework/code.h"

//private
static constexpr unsigned char STR_START_SIZE = 5;
static constexpr char SPECIAL_CHARS[] = {',', ';', '\n', ':', '.', '\t', '\r', '='};
static constexpr char SPACE = ' ';


void read_file(
    const int argc, const char **argv, std::string &ret
) {
    if (argc < 2) return;

    std::ifstream file;

    file.open(argv[1]);
    file >> ret;
    file.close();
}

void str_to_code(
    code &ret, const std::string &txt
) {
    std::string word{};
    word.reserve(STR_START_SIZE);

    for (const char c: txt) {
        process_char(ret, word, c);
    }

    new_word(ret, word);
}

void new_word(code &ret, std::string &word_ref) {
    if (!word_ref.empty()) {
        ret.get().emplace_back(word_ref);
        word_ref.clear();
        word_ref.reserve(STR_START_SIZE);
    }
}

void process_char(code &ret_ref, std::string& word_ref, const char c) {
    bool special_char = false;

    if (c != TXT_INDICATOR)
    {
        for (const char SIGN: SPECIAL_CHARS) {
            if (c == SIGN) {
                special_char = true;

                new_word(ret_ref, word_ref);
                word_ref.push_back(c);
                new_word(ret_ref, word_ref);
                break;
            }
        }
        if (c == SPACE) {
            new_word(ret_ref, word_ref);
            special_char = true;
        }
    }
    if (!special_char) {
        word_ref.push_back(c);
    }
}
