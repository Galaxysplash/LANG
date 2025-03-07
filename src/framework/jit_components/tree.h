#pragma once
#include <initializer_list>
#include <string_view>

struct instruction;

struct tree {
    static void exec();
    static void build(
        const instruction& instruction_in,
        const std::initializer_list<std::string_view>&& ops_priority,
        bool in_terminal
    );
};
