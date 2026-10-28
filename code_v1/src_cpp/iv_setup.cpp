#include "../include/iv_setup.h"
#include "../include/next_state.h"

void split_iv(uint8_t input_iv[8], uint32_t sub_iv[2]) {
    sub_iv[0] = uint32_t(input_iv[0])
              | (uint32_t(input_iv[1]) << 8)
              | (uint32_t(input_iv[2]) << 16)
              | (uint32_t(input_iv[3]) << 24);

    sub_iv[1] = uint32_t(input_iv[4])
              | (uint32_t(input_iv[5]) << 8)
              | (uint32_t(input_iv[6]) << 16)
              | (uint32_t(input_iv[7]) << 24);
}

void modify_counter(uint32_t sub_iv[2]) {
    C[0] ^= sub_iv[0];
    C[1] ^= (sub_iv[1] & 0xFFFF0000) | (sub_iv[0] >> 16);
    C[2] ^= sub_iv[1];
    C[3] ^= (sub_iv[1] << 16) | (sub_iv[0] & 0x0000FFFF);
    C[4] ^= sub_iv[0];
    C[5] ^= (sub_iv[1] & 0xFFFF0000) | (sub_iv[0] >> 16);
    C[6] ^= sub_iv[1];
    C[7] ^= (sub_iv[1] << 16) | (sub_iv[0] & 0x0000FFFF);
}

void iv_setup(uint8_t input_iv[8]) {
    uint32_t sub_iv[2];

    split_iv(input_iv, sub_iv);
    iv[0] = sub_iv[0];
    iv[1] = sub_iv[1];

    modify_counter(sub_iv);

    for (int i = 0; i < 4; i++) {
        next_state();
    }
}