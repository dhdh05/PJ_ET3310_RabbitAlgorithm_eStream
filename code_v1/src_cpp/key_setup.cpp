#include "../include/key_setup.h"
#include "../include/init.h"

void split_key(uint8_t input_key[16], uint16_t sub_key[16]) {
    for(int i = 0; i < 8; i++) {
        sub_key[i] = uint16_t(input_key[2 * i]) | (uint16_t(input_key[2 * i + 1]) << 8);
    }
}

void init_key_state(uint16_t sub_key[8]) {
    for(int j = 0; j < 8; j++) {
        if(j % 2 == 0) {
            X[j] = (uint32_t(sub_key[(j + 1) % 8]) << 16) | sub_key[j];
            C[j] = (uint32_t(sub_key[(j + 4) % 8]) << 16) | sub_key[(j + 5) % 8];
        }
        else {
            X[j] = (uint32_t(sub_key[(j + 5) % 8]) << 16) | sub_key[(j + 4) % 8];
            C[j] = (uint32_t(sub_key[j]) << 16) | sub_key[(j + 1) % 8];
        }
    }
}