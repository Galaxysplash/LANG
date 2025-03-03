#include "instruction_finder.h"

#include <ranges>

void instruction_finder(
    const std::vector<std::string>& txt_list,
    const std::initializer_list<std::string_view> && filter,
    const std::function<void(const std::initializer_list<std::string_view> & list)>&& func
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

    if (unconfirmed == 0)
    {
        func(filter);
    }
}