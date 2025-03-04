#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <functional>

constexpr std::string_view ANYTHING_STR = "???";

void filter_instruction(
    const std::vector<std::string> &instructions,
    const std::vector<std::string_view> & filter,
    const std::function<void(const std::vector<std::string>& str_list_ref)> & func
);

void filter_instruction(
    const std::vector<std::string> &instructions,
    const std::vector<std::string_view> &&filter,
    const std::function<void(const std::vector<std::string>& str_list_ref)> &&func
);

void filter_variable(
    const std::vector<std::string>& instructions,
    const std::string_view && str_view_ref,
    const std::function<void(const std::string& name, const std::string& assigment)> && func
);