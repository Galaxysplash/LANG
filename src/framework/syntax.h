#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <functional>

struct code;


constexpr std::string_view ANYTHING_STR = "???";

void filter_instruction(
    const code &instructions,
    const std::vector<std::string_view> & filter,
    const std::function<void(const code& str_list_ref)> & func
);

void filter_instruction(
    const code &instructions,
    const std::vector<std::string_view> &&filter,
    const std::function<void(const code& str_list_ref)> &&func
);

void filter_variable(
    const code& instructions,
    const std::string_view && type_name_move,
    const std::function<void(const std::string& name, const std::string& assigment)> && func
);