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
    confirmed = 0,
    counter = 0;

    bool previous_success = true;

    for (const std::string& str: txt_list) {
        for (const auto& item: filter) {
            if (str == item) {
                printf("succeed!\n");
                ++confirmed;
            }
            else {
                printf(" f! ");
            }
        }
    }

    return confirmed == filter.size();
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
