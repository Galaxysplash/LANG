#pragma once

#include <unordered_map>
#include <string_view>

#define hash_table(DATA_TYPE) std::unordered_map<std::string_view, DATA_TYPE>