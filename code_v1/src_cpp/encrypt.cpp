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
    
    return cipher_text;
} 