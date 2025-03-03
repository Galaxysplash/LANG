#include "functionl_extensions.h"

#include <ranges>


template <typename T>
void multi_filter(
    const std::vector<std::string>& instructions,
    std::vector<T>&& filter,
    const std::function<void(const std::vector<T>&& list)>&& func
)
{
    unsigned char unconfirmed = filter.size();

    std::views::reverse(filter);

    instructions | std::views::filter([&](const T& str) -> bool
        {
            if (filter.front() == str)
            {
                filter.pop_back();
                --unconfirmed;
                return true;
            }

            return false;
        }
    );

    if (unconfirmed == 0)
    {
        func(filter);
    }
}