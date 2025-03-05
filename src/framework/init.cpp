#include "init.h"

#include <fstream>
#include <functional>

#include "framework/code.h"
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

    const std::function new_word = [&]() -> void {
        if (!word.empty()) {
            ret.emplace_back(word);
            word.clear();
            word.reserve(STR_START_SIZE);
        }
    };

    for (const char c: txt) {
        process_char(new_word, word, c);
    }

    ret.push_back(word);
}

void process_char(const std::function<void()>& new_word_lambda, std::string& word_ref, const char c) {
    if (c == TXT_INDICATOR) {
        word_ref.push_back(c);
        return;
    }

    if (c == SPACE) {
        new_word_lambda();
        return;
    }

    {
        bool special_char = false;
        for (const char SIGN: SPECIAL_CHARS) {
            if (c == SIGN) {
                special_char = true;

                new_word_lambda();
                word_ref.push_back(c);
                new_word_lambda();
                break;
            }
        }
        if (special_char) {
            return;
        }
    }

    word_ref.push_back(c);
}

