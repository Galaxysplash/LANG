#include "tree.h"

#include <cstdint>
#include <iostream>
#include <stack>

#include "parser.h"
#include "global/variables.h"

void tree::run(
    const instruction & instruction_in
) {
    build(instruction_in);
    exec();
    clear();
}

void tree::exec() {
    std::cout << eval_numbers() << "\n";
}

double tree::eval_numbers() {
    double sum = 0;
    double data_buffer = s_nums[0].data;
    std::vector<double> between_results;

    for (size_t i = 0; const auto& [data, head]: s_nums) {
        bool already_pushed_back = false;
        if (i != 0) {
            switch (head) {
                default:
                    between_results.push_back(data_buffer);
                    data_buffer = data;
                    std::cout << "pushed_back in i = " << i << "\n";
                    already_pushed_back = true;
                break;
                case '*':
                    data_buffer *= data;
                break;
                case '/':
                    data_buffer /= data;
                break;
            }
        }

        if (!already_pushed_back && i == s_nums.size() - 1) {
            std::cout << "loop_end!\n";
            between_results.push_back(data_buffer);
            data_buffer = data;
        }
        //foot
        ++i;
    }

    for (const auto& e: between_results) {
        std::cout << "e " << e << "\n";
        sum += e;
    }
    
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

void tree::clear() {
    s_nums.clear();
}
