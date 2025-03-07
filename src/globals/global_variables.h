#pragma once

#include "typedefs.h"
#include "language/classes/instruction.h"

constexpr inline unsigned char G_TXT_INDICATOR = '"';

inline hash_table(double) g_num_list;
inline hash_table(std::string) g_txt_list;
inline hash_table(bool) g_bit_list;

inline instruction g_sorted_instruction;