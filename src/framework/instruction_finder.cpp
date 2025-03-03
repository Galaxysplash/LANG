#include "instruction_finder.h"

#include <ranges>
#include <string_view>
#include <bits/ranges_algo.h>

bool instruction_finder(
    const std::vector<std::string> &txt_list,
    const std::initializer_list<std::string_view> &filter
)
{
    unsigned char
    counter = 0;

    for (const std::string& str: txt_list) {
        if (str == ) {
            ++counter;
        }
        else {
        }
    }

    return counter == filter.size();
}

bool instruction_finder(
    const std::vector<std::string> &txt_list,
    const std::initializer_list<std::string_view> &&filter
)
{
    return instruction_finder(txt_list, filter);
}

void instruction_finder(
    const std::vector<std::string>& txt_list,
    const std::initializer_list<std::string_view> && filter,
    const std::function<void()>&& func
)
{
    if (instruction_finder(txt_list, filter))
    {
        func();
    }
}
