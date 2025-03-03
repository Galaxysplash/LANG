#include "instruction_finder.h"

#include <ranges>

bool instruction_finder(
    const std::vector<std::string> &txt_list,
    const std::initializer_list<std::string_view> &filter
)
{
    unsigned char unconfirmed = filter.size();

    for (const auto& item: filter) {
        txt_list | std::views::filter([&](const std::string_view& str) -> bool
            {
                const bool ret = str == item;

                if (ret) {
                   --unconfirmed;
                }

                return ret;
            }
        );
    }

    return unconfirmed <= 0;
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
