#include "instruction_finder.h"


#include <string_view>

constexpr std::string_view ANYTHING_STR = "???";

bool instruction_finder(
    const std::vector<std::string> & instructions,
    const std::vector<std::string_view> && filter
)
{
    unsigned char counter = 0;

    for (const std::string& instruction: instructions) {
        if (counter == filter.size()) {
            break;
        }
        counter = instruction == filter[counter] || instruction == ANYTHING_STR ? counter + 1 : 0;
    }

    return counter == filter.size();
}