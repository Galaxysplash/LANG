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


#define unit_test(name_inst_name) const __unit_test_struct name_inst_name { []() -> std::pair<bool, const std::string_view> {

#define end_unit_test(success_boolean, tested_func_name) return {success_boolean, tested_func_name};}};
