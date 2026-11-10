#include "../include/key_setup.h"
#include "../include/next_state.h"

void split_key(uint8_t input_key[16], uint16_t sub_key[8]) {
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

void key_setup(uint8_t input_key[16]) {
    uint16_t sub_key[8];

    split_key(input_key, sub_key);
    init_key_state(sub_key);

    A[0] = A[3] = A[6] = 0x4D34D34D;
    A[1] = A[4] = A[7] = 0xD34D34D3;
    A[2] = A[5] = 0x34D34D34;

    carry = 0;
    for(int i = 0; i < 4; i++) {
        next_state();
    }
    for(int j = 0; j < 8; j++) {
        C[j] ^= X[(j + 4) % 8]; // chặn việc khôi phục khóa
    }
}