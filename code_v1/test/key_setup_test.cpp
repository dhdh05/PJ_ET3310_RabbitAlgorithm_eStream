#include <iostream>
#include "../include/key_setup.h"

int main() {
    uint8_t key[16] = {
        0xC2, 0x1F, 0xCF, 0x38, 0x81, 0xCD, 0x5E, 0xE8,
        0x62, 0x8A, 0xCC, 0xB0, 0xA9, 0x89, 0x0D, 0xF8
    }; //Appendix B.
    uint16_t sub_key[8];

    uint16_t sub_key_check[8] = {
        0x1FC2, 0x38CF, 0xCD81, 0xE85E,
        0x8A62, 0xB0CC, 0x89A9, 0xF80D
    };

    split_key(key, sub_key);

    int error_counter = 0;
    for(int i = 0; i < 8; i++) {
        std::cout << "k[" << i << "] = " << std::hex << sub_key[i] << ", mong doi = " << sub_key_check[i] << "\n";

        if(sub_key[i] != sub_key_check[i]) error_counter++;
    }

    if(error_counter > 0) {
        std::cout << "Not ok! Chia khoa sai\n";
        return 1;
    }

    std::cout << "ok !Chia khoa thanh 8 phan 16 bit\n";
    return 0;
}