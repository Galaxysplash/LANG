#pragma once

#include <initializer_list>


struct num_expr {
    num_expr(
        const std::initializer_list<char> && list_move,
        const double& num_in
    );

    double _num;
    char _head;

private:
    static char multiply_or_divide_or_remainder(const std::initializer_list<char> & list_in);
};