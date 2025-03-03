#pragma once

#include <initializer_list>
#include <string_view>

void get_index_for_string_view_iterator(const std::initializer_list<std::string_view> &ini_list, std::string_view& buffer, unsigned char index);
