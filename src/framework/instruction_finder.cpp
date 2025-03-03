#include "instruction_finder.h"

#include <ranges>

bool instruction_finder(
    const std::vector<std::string> &txt_list,
    const std::initializer_list<std::string_view> &filter
)
{
    unsigned char unconfirmed = filter.size();

    for (const auto& item: filter) {

        printf("for loop in 'instruction_finder.cpp' executed!\n");

        auto a = txt_list | std::views::filter([&](const std::string_view& str) -> bool
            {
                const bool ret = str == item;

                printf("filter executed in 'instruction_finder.cpp'!\n");

                if (ret) {
                   --unconfirmed;
                    printf("conformation succeeded in 'instruction_finder.cpp'!\n");
                }
                else {
                    printf("conformation failed in 'instruction_finder.cpp'!\n");
                }

                return ret;
            }
        );

        for (const auto& _item: a) {
            printf("\n%s\n", _item.c_str());
        }
    }

    printf("unconfirmed in %d 'instruction_finder.cpp'\n", unconfirmed);

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
