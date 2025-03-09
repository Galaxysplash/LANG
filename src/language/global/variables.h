#pragma once

#include "global/pre_compiled.h"
#include "../classes/tree/implicit_func.h"


constexpr inline unsigned char G_TXT_INDICATOR = '"';

inline HASH_TABLE(double) g_num_list;
inline HASH_TABLE(std::string) g_txt_list;
inline HASH_TABLE(bool) g_bit_list;

