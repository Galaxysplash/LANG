#include "syntax.h"

#include <ranges>
#include <iostream>


template <typename T>
void multi_filter(
    const std::vector<std::string>& instructions,
    std::vector<T>&& filter,
    const std::function<void(const std::vector<T>&&)>&& func
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

void bind_instruction(
    const std::string& instruction,
    const std::initializer_list<std::pair<const std::string, std::function<void()>>>&& compare_list,
    const std::function<void()>&& default_case_func
)
{
    for (const auto& [comparison, func] : compare_list)
    {
        if (instruction == comparison)
        {
            func();
            return;
        }
    }

    default_case_func();
}

