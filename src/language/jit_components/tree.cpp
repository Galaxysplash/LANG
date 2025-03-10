#include "tree.h"

#include <cstdint>
#include <stack>

#include "parser.h"
#include "global/variables.h"

double tree::numbers(
    const instruction & instruction_in
) {
    build(instruction_in);

    return eval_numbers();
}

double tree::eval_numbers() {
    double sum = 0;
    double data_buffer = s_nums[0].data;
    std::vector<double> between_results{};

    for (size_t i = 0; const auto& [data, head]: s_nums) {
        if (i != 0) {
            switch (head) {
                default:
                    between_results.push_back(data_buffer);
                    data_buffer = data;
                break;
                case '*':
                    data_buffer *= data;
                break;
                case '/':
                    data_buffer /= data;
                break;
            }
        }

        if (i == s_nums.size() - 1) {
            between_results.push_back(data_buffer);
            data_buffer = data;
        }
        //foot
        ++i;
    }

    for (const auto& e : between_results) {
        sum += e;
    }

    s_nums.clear();
    return sum;
}

void tree::build(
    const instruction & instruction_in
) {
    get_numbers_and_head(
        instruction_in,
        [&](
            const double & number_in,
            const std::string_view & head_ref
        ) {
        s_nums.emplace_back(number_in, head_ref);
    });
}

void tree::get_numbers_and_head(
    const instruction & instruction_in,
    const std::function<void(
        const double & number_in,
        const std::string & head_in
    )> & func_in
) {
    std::string str_buffer{};

    for (const std::string& potential_number_ref: instruction_in) {
        if (g_num_list.contains(potential_number_ref)) {
            func_in(g_num_list[potential_number_ref], str_buffer);
        }
        else {
            try {
                func_in(std::stod(potential_number_ref), str_buffer);
                str_buffer.clear();
            } catch(...) {
                str_buffer += potential_number_ref;
            }
        }
    }
}