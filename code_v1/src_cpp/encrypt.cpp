#include "../include/encrypt.h"
#include "../include/init.h"
#include "../include/key_setup.h"
#include "../include/iv_setup.h"
#include "../include/next_state.h"

vector<unsigned int> encrypt(const vector<unsigned int>& plain_text, bool do_iv_setup){
    // Dua trang thai cua he thong ve gia tri ban dau
    init();
    key_setup();
    if(do_iv_setup){
        iv_setup();
    }
    // Tao mang ket qua
    int n = plain_text.size();
    vector<unsigned int> cipher_text(n);
    
    for(int i = 0; i < n; i += 8){
        next_state();
        for(int j = 0; j < 8 && i < n; j+=2, i++){
            cipher_text[i] = plain_text[i] ^ X[j] ^ (X[(j + 5) % 8] >> 16) ^ (X[(j + 3) % 8] << 16);

        }
    }

    return cipher_text;
} 