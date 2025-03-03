#include "program.h"
#include "foundation/functionl_extensions.h"
#include "framework/init.h"

#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>

static std::unordered_map<std::string, double> num_list;
static std::unordered_map<std::string, std::string> txt_list;
static std::unordered_map<std::string, bool> bit_list;

void get_code(const int argc, const char** argv, std::vector<std::string>& ret)
{
    std::string txt_buffer;

    read(argc, argv, txt_buffer);
    split(ret, txt_buffer);
}

void process_code(
    const std::vector<std::string>& instructions,
    const std::initializer_list<std::string>&& ops_priority
)
{
    multi_filter<std::string>(
        instructions,
        {":", "num", "="},
        [](const std::vector<std::string>& list) {
        for (const auto& item : list) {
            std::cout << item << " ";
        }
    });
}

void execute_code()
{
    printf("\ne.size: %d\n", static_cast<int>(num_list.size()));
}
