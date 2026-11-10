#include "../include/counter.h"
#include "../include/init.h"

void counter_system() {
    for (int i = 0; i < 8; i++) {
        uint64_t temp = (uint64_t)C[i] + A[i] + carry;
        carry = (uint32_t)(temp >> 32);   // carry = temp div (2^32 - 1)
        C[i] = (uint32_t)temp; // c[i] = temp mod (2^32 - 1)
    }
}