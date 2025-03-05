#pragma once

#include <functional>
#include <string_view>
#include <utility>


struct __unit_test_struct {
    __unit_test_struct(
        const std::function<std::pair<bool, const std::string_view>()> && func
    );

private:
    static void print_result(bool passed, const std::string_view & str);
};


#define unit_test(inst_name, passed_boolean_name) const __unit_test_struct inst_name { []() -> std::pair<bool, const std::string_view> { bool passed_boolean_name = false;

#define end_unit_test(passed_boolean_var, tested_func_name) return {passed_boolean_var, tested_func_name};}};
