#include "syntax.h"

bool filter_instruction(
    const std::vector<std::string> & instructions,
    const std::vector<std::string_view> && filter
)
{
    unsigned char counter = 0;

    for (const std::string& instruction: instructions) {
        if (counter == filter.size()) {
            break;
        }

        counter =
            filter[counter] == instruction ||
            filter[counter] == ANYTHING_STR && !instruction.empty() ?
            counter + 1 : 0;
    }

    return counter == filter.size();
}