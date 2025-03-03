#include "get_index.h"

#include <string_view>

#include "unit_test.h"

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


void test() {

}

unit_test test1 {[]() -> bool {
    const std::initializer_list<std::string_view> test_ini_list = {"a", "b"};
    std::string_view buffer;
    constexpr unsigned char index = 1;

    get_element_for_index_in_string_view_iterator(test_ini_list, buffer, index);

    return buffer == "b";
}, "get_element_for_index_in_string_view_iterator"};


