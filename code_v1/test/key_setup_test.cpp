#include <iostream>
#include "../include/key_setup.h"
#include "../include/init.h"

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
    key_setup(key);

    int error_counter = 0;
    for(int i = 0; i < 8; i++) {
        std::cout << "k[" << i << "] = " << std::hex << sub_key[i] << ", mong doi = " << sub_key_check[i] << "\n";

        if(sub_key[i] != sub_key_check[i]) error_counter++;
    }

    uint32_t X_check[8] = {
        0x328404BB, 0x6DBFFDB6, 0xC59434D3, 0x1A442F64,
        0x9D0EE3E6, 0xE9D6B223, 0x80198946, 0x2D428548
    };

    uint32_t C_check[8] = {
        0x223B1DE5, 0x6FD212ED, 0xDCEEA5A6, 0x307352DF,
        0x5E7308A6, 0xE9A643CA, 0xC7C10140, 0x5F05DC74
    };

    

    for(int i = 0; i < 8; i++) {
        std::cout << "X[" << i << "] = " << std::hex << X[i] << ", mong doi = " << X_check[i] << "\n";
        std::cout << "C[" << i << "] = " << std::hex << C[i] << ", mong doi = " << C_check[i] << "\n";

        if(X[i] != X_check[i]) error_counter++;
        if(C[i] != C_check[i]) error_counter++;
    }
    if(error_counter > 0) {
        std::cout << "Not ok!\n";
        return 1;
    }

    std::cout << "ok !\n";
    return 0;
}