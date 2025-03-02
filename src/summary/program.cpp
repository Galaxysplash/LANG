#include "program.h"

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

#include <framework/init.h>

static std::unordered_map<std::string, double> num_list;
static std::unordered_map<std::string, std::string> txt_list;
static std::unordered_map<std::string, bool> bit_list;

void get_code(const int argc, const char** argv, std::vector<std::string>& ret) {
    std::string txt_buffer;

    read(argc, argv, txt_buffer);
    split(ret, txt_buffer);
}

void process_code(
    const std::vector<std::string>& instructions,
    const std::initializer_list<std::string>&& ops_priority
) {
    analyze(instructions, [](const std::array<std::string, CODE_VIEW_SIZE>& code_view) {
#pragma region ASSIGNING NICK NAMES
        const unsigned char&
            current_index = CODE_VIEW_SIZE / 2 + 1;
        const auto
            current = code_view[current_index];

#pragma endregion ASSIGNING NICK NAMES

#pragma region LAMBDAS
        const std::function condition_create_variable = [&](
            const std::function<void()>&& create_variable
        ) {
            std::cout << "previous: " << code_view[current_index - 1] << "\n";
            std::cout << "next: " << code_view[current_index + 1] << "\n";
            if (
                code_view[current_index - 1] == ":" &&
                code_view[current_index + 1] == "=" &&
                !num_list.contains(code_view[current_index - 2]) &&
                !txt_list.contains(code_view[current_index - 2]) &&
                !bit_list.contains(code_view[current_index - 2])
            ) {
                printf("lambda worked!\n");
                create_variable();
            }
        };
#pragma endregion LAMBDAS
#pragma region CREATE VARIABLES
        bind_instruction(
            current, {
            {
                "num", [&]() {
                    condition_create_variable([&]() {
                        try {
                            const double& num = std::stof(std::string(code_view[current_index + 1]));
                            num_list[code_view[current_index - 2]] = num;
                        }
                        catch (...){}
                    });
               }
            },
            {
                "bit", [&]() {
                    condition_create_variable([&]() {
                        if (code_view[current_index + 2] == "true") {
                            bit_list[code_view[current_index - 2]] = true;
                        }
                        else if (code_view[current_index + 2] == "false") {
                            bit_list[code_view[current_index - 2]] = false;
                        }
                    });
                }
            },
            {
                "txt", [&]() {
                    condition_create_variable([&]() {
                        const unsigned short potential_txt_max_index = current.size() - 1;
                        bool start_txt_indicator = false, end_txt_indicator = false;
                        std::string txt_buffer{};

                        for (unsigned short i = 0; const char& c: current) {
                            if (c == TXT_INDICATOR) {
                                if (i == 0) {
                                    start_txt_indicator = true;
                                }
                                else if (i == potential_txt_max_index) {
                                    end_txt_indicator = true;
                                }
                            }
                            else {
                                txt_buffer += c;
                            }
                            ++i;
                        }

                        if (start_txt_indicator && end_txt_indicator) {
                            txt_list[code_view[current_index - 2]] = txt_buffer;
                        }
                    });
                }
            }
        });
#pragma endregion CREATE VARIABLES
#pragma region COMPLEX EXPERSSIONS
    bind_instruction(
        current, {
    });
#pragma endregion COMPLEX EXPERSSIONS
    });
}

void execute_code() {
    printf("\ne.size: %d\n", static_cast<int>(num_list.size()));
}