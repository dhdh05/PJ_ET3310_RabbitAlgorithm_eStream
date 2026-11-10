#include <iostream>
#include "../include/key_setup.h"
#include "../include/iv_setup.h"

extern unsigned int X[8];
extern unsigned int C[8];

int main() {
    uint8_t key[16] = {
        0xC2, 0x1F, 0xCF, 0x38, 0x81, 0xCD, 0x5E, 0xE8,
        0x62, 0x8A, 0xCC, 0xB0, 0xA9, 0x89, 0x0D, 0xF8
    }; // Appendix B Key

    uint8_t input_iv[8] = {
        0xC3, 0x73, 0xF5, 0x75, 0xC1, 0x26, 0x7E, 0x59
    }; // Appendix B: IV = 59 7E 26 C1 75 F5 73 C3

    uint32_t sub_iv[2];
    uint32_t sub_iv_check[2] = {
        0x75F573C3, 0x597E26C1
    };

    split_iv(input_iv, sub_iv);
    key_setup(key);
    iv_setup(input_iv);

    int error_counter = 0;
    for (int i = 0; i < 2; i++) {
        std::cout << "iv[" << i << "] = " << std::hex << sub_iv[i] << ", mong doi = " << sub_iv_check[i] << "\n";
        if (sub_iv[i] != sub_iv_check[i]) error_counter++;
    }

    uint32_t X_check[8] = {
        0x2F97203E, 0xCC3B431B, 0x5D40688B, 0xD795D15B,
        0xA235B3A1, 0x8B4CCD3C, 0xCAAFB86C, 0xCA9A5D25
    };

    uint32_t C_check[8] = {
        0x570E6B1C, 0xBD06E63A, 0xB03BDA79, 0x6546A014,
        0xABA7DBF3, 0xBCF3789D, 0xFC944E75, 0xAC3AAFC1
    };

    for (int i = 0; i < 8; i++) {
        std::cout << "X[" << i << "] = " << std::hex << X[i] << ", mong doi = " << X_check[i] << "\n";
        std::cout << "C[" << i << "] = " << std::hex << C[i] << ", mong doi = " << C_check[i] << "\n";

        if (X[i] != X_check[i]) error_counter++;
        if (C[i] != C_check[i]) error_counter++;
    }

    if (error_counter > 0) {
        std::cout << "Not ok!\n";
        return 1;
    }

    std::cout << "ok !\n";
    return 0;
}