#include "unit_test.h"

#include <cstdio>
#include <format>

unit_test::unit_test(
    const std::function<bool()> &&func,
    const std::string_view &&str
)
{
    print_result(func(), str);
}

void unit_test::print_result(const bool passed, const std::string_view & str) {
    std::string_view
    uint_test_str {"Unit test"},
    success_or_failure {};

    success_or_failure = passed ? "passed" : "failed";

    if (str != "") {
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
