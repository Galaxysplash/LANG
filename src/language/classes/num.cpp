#include "num.h"

#include <algorithm>

num_expr::num_expr(
    const std::initializer_list<char> && list_move,
    const double& num_in
) : _num(num_in * (std::ranges::count(list_move, '-') % 2 == 0 ? 1 : -1)), _head(
    multiply_or_divide_or_remainder(list_move)
) {}

char num_expr::multiply_or_divide_or_remainder
(
    const std::initializer_list<char> & list_in
) {
    for (const auto& e: list_in) {
        switch (e) {
            case '*':
            case '/':
            case '%':
             return e;
            default:
        }
    }

    return ' ';
}
