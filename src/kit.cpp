#include "kit.hpp"

#include <string>
#include <functional>

namespace kit {
    static constexpr char sign_list[] = {'\n', ',', ' '};
    static constexpr unsigned char str_start_size = 5;

    void split(
        std::vector<std::string>& ret,
        const std::string_view& txt
    ) {
        std::string word{};
        word.reserve(str_start_size);

        for (const char c : txt) {
            for (const char sign : sign_list) {
                if (c == sign) {
                    ret.push_back(word);
                    word.clear();
                    word.reserve(str_start_size);
                }
            }
            word.push_back(c);
        }

        ret.push_back(word);
    }

    void scan(
        const std::vector<std::string>& instructions,
        const std::function<void(std::array<const std::string&, 5> arr)>&&
    ) {
        std::string_view words{};

        for (const std::string& instruction : instructions) {
            
        }
    }
}