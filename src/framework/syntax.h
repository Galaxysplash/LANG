#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <functional>

struct code;


constexpr std::string_view ANYTHING_STR = "???";

void filter_instruction(
    const code & code_in,
    const std::vector<std::string_view> & filter_ref,
    const std::function<void(std::vector<std::string_view>& str_list_ref)> & func_in
);

void filter_instruction(
    const code & code_in,
    const std::vector<std::string_view> && filter_move,
    const std::function<void(std::vector<std::string_view>& str_list_ref)> && func_in
);

void filter_variable(
    const code & code_in,
    const std::string_view && type_name_move,
    const std::function<void(const std::string& name, const std::string& assigment)> && func_in
);