#include "kit.hpp"

#include <string>
#include <fstream>
#include <functional>

namespace kit {
    static constexpr unsigned char STR_START_SIZE = 5;
    static constexpr char RETURN = '\n';
    static constexpr char SIGN_LIST[] = {',', ' '};


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
        std::vector<std::string>& ret, const std::string_view& txt
    ) {
        std::string word{};
        word.reserve(STR_START_SIZE);

        const std::function new_word = [&]() -> void {
            ret.emplace_back(word);
            word.clear();
            word.reserve(STR_START_SIZE);
        };

        for (const char c : txt) {
            for (const char sign : SIGN_LIST) {
                if (c == sign) {
                    new_word();
                    break;
                }
            }

            if (c != RETURN) {
                word.push_back(c);
            }
            else {
                new_word();
                word.push_back(c);
                new_word();
            }
        }

        ret.push_back(word);
    }
} //namespace kit