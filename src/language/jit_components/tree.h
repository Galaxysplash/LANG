#pragma once

#include <cstdint>
#include <functional>

#include "global/pre_compiled.h"

struct instruction;

struct tree {
    static void exec();

    static void build();

private:
    static std::vector<double> _nums_list_for_current_line;
    static std::vector<std::string_view> _ops_list_for_current_line;
};