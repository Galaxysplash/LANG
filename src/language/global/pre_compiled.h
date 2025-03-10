#pragma once

#include <initializer_list>
#include <unordered_map>
#include <string_view>

constexpr char G_TXT_INDICATOR = '"';

static constexpr char SPECIAL_SIGNS[] = {',', ';', '\n', ':', '.', '\t', '\r', '=', '+', '-', '/', '*'};
static constexpr char SPACE = ' ';

constexpr std::string_view ANYTHING_STR = "???";

#define VAR_LIST(DATA_TYPE) std::unordered_map<std::string, DATA_TYPE>

using str_list = std::initializer_list<std::string_view>;
using char_list = std::initializer_list<char>;