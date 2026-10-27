
#ifndef NEXT_STATE_H
#define NEXT_STATE_H

#include <cstdint>
#include "rotate_left.h"
#include "counter.h"

// Cap nhat trang thai Rabbit
inline void next_state() {

    // Cap nhat bo dem C va carry
    counter_system();

    uint32_t g[8];

    // Tinh g-function
    for (int i = 0; i < 8; i++) {
        uint32_t t = X[i] + C[i];
        uint64_t square = uint64_t(t) * t;

        g[i] = uint32_t(square) ^ uint32_t(square >> 32);
    }

    // Cap nhat cac bien trang thai X
    for (int i = 0; i < 8; i++) {
        if (i & 1) {
            X[i] = g[i]
                 + rotate_left(g[(i + 7) % 8], 8)
                 + g[(i + 6) % 8];
        } else {
            X[i] = g[i]
                 + rotate_left(g[(i + 7) % 8], 16)
                 + rotate_left(g[(i + 6) % 8], 16);
        }
    }
}

#endif
