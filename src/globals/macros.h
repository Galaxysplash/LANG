#pragma once

#include <unordered_map>
#include <string>
#include <string_view>

#define HASH_TABLE(DATA_TYPE) std::unordered_map<std::string, DATA_TYPE>
#define PRIORITY_LIST std::initializer_list<std::initializer_list<std::string_view>>