#include "tree.h"

#include <cstdint>
#include <iostream>
#include <stack>

#include "parser.h"

void tree::run(
    const instruction & instruction_in
) {
    build(instruction_in);
    for (const auto& num: s_nums) {
        std::cout << "num: (data: " << num.data << ", head: " << num.head << ")\n";
    }
    exec();
    clear();
}

void tree::exec() {
    std::cout << eval_numbers() << "\n";
}

double tree::eval_numbers() {
    double sum = 0;
    std::vector<double> num_stack;

    for (double data_buffer = s_nums[0].data, i = 0; const auto& [data, head]: s_nums) {
        if (i != 0) {
            switch (head) {
                case '*':
                    data_buffer *= data;
                break;
                case '/':
                    data_buffer /= data;
                break;
                default:
                    num_stack.push_back(data_buffer);
                    data_buffer = data;
                break;
            }

            if (i <= (static_cast<unsigned int>(s_nums.size()) - 1)) {
                std::cout << "pushed_back_end: " << data_buffer << "\n";
                num_stack.push_back(data_buffer);
            }
        }
        ++i;
    }

    for (const auto& num: num_stack) {
        std::cout << "num: " << num << "\n";
        sum += num;
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

    for (const std::string& instruction_part_ref: instruction_in) {
        try {
            func_in(std::stod(instruction_part_ref), str_buffer);
            str_buffer.clear();
        } catch(...) {
            str_buffer += instruction_part_ref;
        }
    }
}

void tree::clear() {
    s_nums.clear();
}
