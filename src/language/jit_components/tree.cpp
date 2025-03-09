#include "tree.h"

#include <cstdint>
#include <iostream>

#include "parser.h"

void tree::run(
    const instruction & instruction_in
) {
    build(instruction_in);
    exec();
}

void tree::exec() {
    std::cout << eval_numbers() << "\n";
}

long double tree::eval_numbers() {
    double num_buffer = 0;
    long double sum_buffer = 0;

    for (const auto& num: s_nums) {
        switch (num.head) {
            case '*':
                sum_buffer += num_buffer * num.data;
                break;
            case '/':
                sum_buffer += num_buffer / num.data;
                break;
            case '%':
                sum_buffer += static_cast<long double>(
                    static_cast<uint32_t>(num_buffer) %
                    static_cast<uint32_t>(num.data)
                );
                break;
            default:
                break;
        }

        num_buffer = num.data;
    }

    s_nums.clear();
    return sum_buffer;
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