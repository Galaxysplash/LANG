#include <string_view>
#include <fstream>
#include <functional>

#include "init.h"

#include <bits/locale_facets_nonio.h>


static constexpr unsigned char STR_START_SIZE = 5;
static constexpr unsigned char TXT_INDICATOR = '"';
static constexpr char SPECIAL_SIGNS[] = {',', ';', '\n', ':', '.', '\t', '\r', '='};
static constexpr char CUT_OUT_SIGNS[] = {' '};


void read(
    const int argc, const char** argv, std::string& ret
) {
    if (argc < 2) return;

    std::ifstream file;

    file.open(argv[1]);
    file >> ret;
    file.close();
}

void split(
    std::vector<std::string_view>& ret, const std::string_view& txt
) {
    std::string word{};
    word.reserve(STR_START_SIZE);

    const std::function new_word = [&]() -> void {
        ret.emplace_back(word);
        word.clear();
        word.reserve(STR_START_SIZE);
    };

    for (const char c : txt) {
        bool special_char = false;

        if (c != TXT_INDICATOR) {
            for (const char SIGN : CUT_OUT_SIGNS) {
                if (c == SIGN) {
                    new_word();
                    break;
                }
            }

            for (const char SIGN : SPECIAL_SIGNS) {
                if (c == SIGN) {
                    special_char = true;
                    new_word();
                    word.push_back(c);
                    new_word();
                    break;
                }
            }
        }
        
        if (!special_char) {
            word.push_back(c);
        }
    }

    ret.push_back(word);
}
