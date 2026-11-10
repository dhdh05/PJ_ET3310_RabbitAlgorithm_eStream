#ifndef ROTATE_LEFT_H
#define ROTATE_LEFT_H

#include <cstdint>

// Xoay trai so nguyen 32 bit k vi tri
inline uint32_t rotate_left(uint32_t v, unsigned int k) {
    k &= 31;
    return (k == 0) ? v : ((v << k) | (v >> (32 - k)));
}

#endif
