#pragma once

#include <functional>
#include <string_view>
#include <utility>

struct unit_test_struct {
    unit_test_struct(
        const std::function<std::pair<bool, const std::string_view>()> && func
    );

private:
    static void print_result(bool passed, const std::string_view & str);
};


#define passed(success, name) return {success, name};

#define unit_test(test_name, code) \
unit_test_struct test_name { []() -> std::pair<bool, const std::string_view> \
    code \
};
