#pragma once

#include <functional>
#include <string_view>
#include <utility>


struct unit_test_struct {
    unit_test_struct(
        const std::function<std::pair<bool, const std::string_view>()> && func
    );

private:
    static void print_result(bool passed, const std::string_view & str);
};


#define unit_test(name_inst_name) const unit_test_struct name_inst_name { []() -> std::pair<bool, const std::string_view> {

#define unit_test_end(success_boolean, tested_func_name) return {success_boolean, tested_func_name};}};
