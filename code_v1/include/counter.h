#include "bin_convert.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;
unsigned long long maxsize = 4294967296ll; // 0x100000000
unsigned int key[8];
unsigned int iv[2];
unsigned int X[8];
unsigned int C[8],old_C[8];
unsigned int A[8];
unsigned int carry;


void counter_system(){
	long long temp;
	long long b = 0;
	for (int i = 0; i < 8; i++) old_C[i] = C[i];

	temp = (C[0] % maxsize) + (A[0] % maxsize) + carry;
    C[0] = (unsigned int)(temp % maxsize);

	for (int i = 1; i < 8; i++) {
		temp = (C[i] % maxsize) + (A[i] % maxsize) + (old_C[i-1] > C[i-1]);
		C[i] = (unsigned int)(temp % maxsize);
	}
	carry = (old_C[7] > C[7]);
}