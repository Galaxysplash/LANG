#include "instruction_finder.h"

#include <ranges>

template <unsigned char N>
void instruction_finder(
    const std::vector<std::string>& txt_list,
    std::array<std::string_view, N>&& filter,
    const std::function<void(const std::array<std::string_view, N>&& list)>&& func
)
{
    unsigned char unconfirmed = filter.size();

    std::views::reverse(filter);

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