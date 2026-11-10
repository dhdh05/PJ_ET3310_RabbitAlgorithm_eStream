#include "rotate_left.h"

uint32_t rotate_left(uint32_t v, unsigned int k){
    k = k % 32; // xoay k bit
    if (k == 0) return v; // k = 0 thi giu nguyen
    return (v << k) | (v >> (32 - k)); 
    // dich trai k bit, dich phai (32-k) bit de lay lai k bit trai ban dau dua ve cuoi ben phai, OR 2 ket qua
}