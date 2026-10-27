#pragma once
#include "rabbit.h"
#include <vector>

vector<unsigned int> encrypt(const vector<unsigned int> plain_text, bool do_iv_setup=true);