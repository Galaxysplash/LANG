#pragma once

#include <string_view>

#include "node.h"


struct num : node {
    num(
        const double& num_in,
        const std::string_view & head_ref
    );

    double _num;
    char _head;

private:
    static char multiply_or_divide_or_remainder(
        const std::string_view& list_in
    );
};
