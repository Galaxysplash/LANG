#pragma once

#include "macros.h"
#include "language/classes/instruction.h"

constexpr inline unsigned char G_TXT_INDICATOR = '"';

inline HASH_TABLE(double) g_num_list;
inline HASH_TABLE(std::string) g_txt_list;
inline HASH_TABLE(bool) g_bit_list;

inline instruction g_sorted_instruction;

