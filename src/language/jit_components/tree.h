#pragma once

#include <cstdint>
#include <vector>
#include <functional>

#include "classes/tree/nodes/num.h"
#include "global/pre_compiled.h"

struct instruction;

static std::vector<num> s_nums{};

struct tree {
    static double numbers(
        const instruction & instruction_in
    );

private:
    static void build(
        const instruction & instruction_in
    );

    [[nodiscard]] static double eval_numbers();
    
    static void get_numbers_and_head(
        const instruction & instruction_in,
        const std::function<void(
            uint16_t index,
            const double & number_in,
            const std::string & head_in
        )> & func_in
    ) ;
};