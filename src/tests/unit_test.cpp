#include "unit_test.h"

#include <cstdio>
#include <format>

unit_test_struct::unit_test_struct(
    const std::function<std::pair<bool, const std::string_view>()> && func
)
{
    const auto&[success, str] = func();

    print_result(success, str);
}

void unit_test_struct::print_result(const bool passed, const std::string_view & str) {
    std::string_view
    uint_test_str {"Unit test"},
    success_or_failure {};

    success_or_failure = passed ? "passed" : "failed";

    if (!str.empty()) {
        printf(
            std::format("{} {} for {}!\n", uint_test_str, success_or_failure, str.data()).c_str()
        );
    }
    else {
        printf(
            std::format("{} {}!\n", uint_test_str, success_or_failure).c_str()
        );
    }
}
