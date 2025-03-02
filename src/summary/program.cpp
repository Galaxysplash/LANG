#include "program.h"

#include <iostream>
#include <map>
#include <ranges>
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
    const auto f = instructions | std::views::filter([](const std::string& i) -> bool {
        return true;
    });
}

void execute_code() {
    printf("\ne.size: %d\n", static_cast<int>(num_list.size()));
}