#pragma once

#include <functional>
#include <string_view>

struct unit_test {
    unit_test(
        const std::function<bool()> && func,
        const std::string_view && str = ""
    );

private:
    static void print_result(bool passed, const std::string_view & str);
};

