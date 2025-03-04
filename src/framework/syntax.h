#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <unordered_map>

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
    const std::string_view& str_view_ref,
    std::function<void(const std::string& name, const std::string& assigment)>
);

void try_add_variable(
    const std::vector<std::string>& instructions,
    const std::string_view&& type_name,
    const std::unordered_map<std::string, double>& map_ref,
    const std::function<void(const std::string& name, std::string& assigment)> && func
);

/*
template <typename... TS>
void try_add_variables(
    const std::initializer_list<std::vector<std::string>>& instructions,
    const std::initializer_list<std::string_view>&& type_name,
    std::tuple<std::unordered_map<std::string, TS...>>& map_ref
);
*/
