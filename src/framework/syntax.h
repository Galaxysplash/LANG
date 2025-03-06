#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <functional>

struct code;

constexpr std::string_view ANYTHING_STR = "???";

struct syntax {
    static void filter_instruction(
      const code & code_in,
      const std::vector<std::string_view> & filter_ref,
      const std::function<void(std::vector<std::string_view>& str_list_ref)> & func_in
    );

    static void filter_instruction(
        const code & code_in,
        const std::vector<std::string_view> && filter_move,
        const std::function<void(std::vector<std::string_view>& str_list_ref)> && func_in
    );

    static void filter_variable(
        const code & code_in,
        const std::string_view && type_name_move,
        const std::function<void(const std::string_view& name, const std::string_view& assigment)> && func_in
    );
};