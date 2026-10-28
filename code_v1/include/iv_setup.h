#pragma once
#include <cstdint>


extern unsigned int iv[2];

void split_iv(uint8_t input_iv[8], uint32_t sub_iv[2]);
void modify_counter(uint32_t sub_iv[2]);
void iv_setup(uint8_t input_iv[8]);