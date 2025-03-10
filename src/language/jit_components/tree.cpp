#include "tree.h"

#include <cstdint>
#include <iostream>
#include <ostream>
#include <stack>

#include "parser.h"
#include "global/core.h"
#include "global/variables.h"

double tree::numbers(
    const instruction & instruction_in
) {
    build(instruction_in);

    return eval_numbers();
}

double tree::eval_numbers() {
    double sum = 0.0;
    double data_buffer = 0.0; {
        try {
            if (!s_nums.empty()) {
                data_buffer = s_nums[0].data;
            }
        }catch(...) {}
    }

    std::stack<double> results_stack{};

    for (size_t i = 0; const auto& [data, head]: s_nums) {
        if (i != 0) {
            switch (head) {
                case '*':
                    data_buffer *= data;
                break;
                case '/':
                    data_buffer /= data;
                break;
                default:
                    results_stack.push(data_buffer);
                data_buffer = data;
                break;
            }
        }

        if (i == s_nums.size() - 1) {
            results_stack.push(data_buffer);
            data_buffer = data;
        }
        //foot
        ++i;
    }

    if (!results_stack.empty()) {
        const uint16_t start_stack_size = results_stack.size();

        for (uint16_t i = 0; i < start_stack_size; ++i) {
            sum += results_stack.top();
            results_stack.pop();
        }
    }

    if (!s_nums.empty()) {
        s_nums.clear();
    }

    return sum;
}

void tree::build(
    const instruction & instruction_in
) {
    get_numbers_and_head(
        instruction_in,
        [&](bool & stop,
            const int i,
            const double & number_in,
            const std::string_view & head_ref
        ) {
            if (i == 0) {
                s_nums.emplace_back(number_in, head_ref);
                return;
            }

            bool valid = false;

            for (const auto& head_char_ref: head_ref) {
                if (core::is_a_sign(head_char_ref)) {
                    valid = true;
                   break;
                }
           }

            {
                stop = !valid;
               if (valid) {
                   s_nums.emplace_back(number_in, head_ref);
               } else {
                    std::cerr << "error, you HAVE to put a operator between the numbers or else you code will miserably fail!\n";
               }
            }
    });
}

void tree::get_numbers_and_head(
    const instruction & instruction_in,
    const std::function<void(
        bool & stop,
        int idx,
        const double & number_in,
        const std::string & head_in
    )> & func_in
) {
    std::string str_buffer{};
    bool stop = false;
    const std::function call_func = [&func_in](bool & stop_ref, int& count_for_calls_ref, const double& number_in, const std::string& str_buffer_in) {
        func_in(stop_ref, count_for_calls_ref, number_in, str_buffer_in);
        ++count_for_calls_ref;
    };

#pragma region func_in_not_allowed_to_call___func_in___directly_but_instead_call___call_func
#define func_in FORBIDDEN
    for (int count_for_calls = 0; const std::string& potential_number_ref: instruction_in) {
        if (g_num_list.contains(potential_number_ref)) {
            call_func(stop, count_for_calls, g_num_list[potential_number_ref], str_buffer);
        }
        else {
            try {
                call_func(stop, count_for_calls, std::stod(potential_number_ref), str_buffer);
                str_buffer.clear();
            } catch(...) {
                str_buffer += potential_number_ref;
            }
        }

        if (stop) {
            printf("stop!");
            s_nums.clear();
            return;
        }
    }
#pragma endregion
}