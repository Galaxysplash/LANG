#include "instruction_finder.h"


#include <string_view>

#include "foundation/get_index.h"

bool instruction_finder(
    const std::vector<std::string> &txt_list,
    const std::initializer_list<std::string_view> &filter
)
{
    unsigned char counter = 0;

    for (const std::string& str: txt_list) {
        std::string_view str_view_buffer{};

        get_element_for_index_in_string_view_iterator(filter, str_view_buffer, counter);

        counter = str.c_str() == str_view_buffer.data() ? counter + 1 : 0;
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
