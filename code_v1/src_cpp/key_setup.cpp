#include "../include/key_setup.h"

void split_key(uint8_t input_key[16], uint16_t sub_key[16]) {
    for(int i = 0; i < 8; i++) {
        sub_key[i] = uint16_t(input_key[2 * i]) | (uint16_t(input_key[2 * i + 1]) << 8);
    }
}