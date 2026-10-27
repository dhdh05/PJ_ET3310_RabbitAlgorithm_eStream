#pragma once
#include "rabbit.h"
#include <vector>

vector<unsigned int> encrypt(const vector<unsigned int>& plain_text, bool do_iv_setup=true);

// plain_text: vector so cua ban ro, moi phan tu la 32 bit
// do_iv_setup: true neu muon thiet lap iv, false neu khong
// return: vector so cua ban ma, moi phan tu la 32 bit
// truoc khi goi ham nay, ae phai goi ham init() de khoi tao cac gia tri A, C, X va key_setup() de thiet lap khoa
