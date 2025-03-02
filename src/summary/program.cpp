#include "program.h"

#include <string>

#include <framework/init.h>

std::unordered_map<std::string_view, double> num_list;
std::unordered_map<std::string_view, std::string> txt_list;
std::unordered_map<std::string_view, bool> bit_list;

void get_code(const int argc, const char** argv, std::vector<std::string_view>& ret) {
    std::string txt_buffer;

    read(argc, argv, txt_buffer);
    split(ret, txt_buffer);
}

void process_code(
    const std::vector<std::string_view>& instructions,
    const std::initializer_list<std::string_view>&& ops_priority
) {
    analyze(instructions, [](const std::array<std::string_view, CODE_VIEW_SIZE>& code_view) -> void {
        const unsigned char&
            current_index = CODE_VIEW_SIZE / 2 + 1,
            next_index = current_index + 1,
            previous_index = current_index - 1,
            next_index2 = next_index + 1,
            previous_index2 = previous_index - 1;
        const std::string_view
            &current = code_view[current_index],
            &next = code_view[next_index],
            &previous = code_view[previous_index],
            &next2 = code_view[next_index2],
            &previous2 = code_view[previous_index2];

        const std::function condition_create_variable = [&](
            const std::function<void()>&& create_variable
        ) {
            if (previous == ":" && next == "=" && !num_list.contains(previous2)) {
                create_variable();
            }
        };

        bind_instruction(
            current,
            {
                {
                   "num", [&]() {
                        condition_create_variable([&]() {
                            try {
                                const double& num = std::stof(std::string(next2));

                                num_list[previous2] = num;
                            }
                            catch (...){}
                        });
                   }
                },
                {
                    "bit", [&]() {
                        condition_create_variable([&]() {
                            if (next2 == "true") {
                                bit_list[previous2] = true;
                            }
                            else if (next2 == "false") {
                                bit_list[previous2] = false;
                            }
                        });
                    }
                },
                {
                    "txt", [&]() {
                        condition_create_variable([&]() {
                            const unsigned short potential_txt_size = current.size();

                            for (auto i = potential_txt_size - 1; const char& c: current) {
                                
                            }
                        });
                    }
                }
            },
            []() {

            }
        );
    });
}

void execute_code() {

}