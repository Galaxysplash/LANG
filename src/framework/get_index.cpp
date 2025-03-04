#include "get_index.h"

#include <string_view>

#include "tests/unit_test.h"

void get_element_for_index_in_string_view_iterator(const std::initializer_list<std::string_view> &ini_list, std::string_view& buffer, const unsigned char index) {
    unsigned short counter = 0;

    for (const auto& element: ini_list) {
        if (counter == index) {
            buffer = element;
            return;
        }
        ++counter;
    }
}


unit_test(
    test1,
    {
        auto passed = false;

        passed(passed, "get_element_for_index_in_string_view_iterator")
    }
)