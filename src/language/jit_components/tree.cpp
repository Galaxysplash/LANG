#include "tree.h"

#include <cstdint>
#include <iostream>

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

double eval_numbers() {
    double sum = 0;

    for (double data_buffer = s_nums[0].data, i = 0; const auto& [data, head]: s_nums) {
        switch (head) {
            case '*':
                data_buffer *= data;
                break;
            case '/':
                data_buffer /= data;
                break;
            case '%':
                data_buffer = static_cast<int>(data_buffer) % static_cast<int>(data);
                break;
            default:
                data_buffer += data;
                break;
        }

        if (static_cast<int>(i) == s_nums.size() - 1) {
            sum = data_buffer;
        }

        //foot
        data_buffer = data;
        ++i;
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
