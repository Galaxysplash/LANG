#include "num.h"

#include <algorithm>

num::num(
    const double& num_in,
    const std::string_view & head_ref
) : data(num_in * (std::ranges::count(head_ref, '-') % 2 == 0 ? 1 : -1)), head(
    multiply_or_divide_or_remainder(head_ref)
) {}

char num::multiply_or_divide_or_remainder
(
    const std::string_view & list_in
) {
    for (const char& e: list_in) {
        if (e == '*' || e == '/' || e == '%') {
            return e;
        }
    }
    return ' ';
}
