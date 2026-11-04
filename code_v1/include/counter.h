#include <cstdint>
uint32_t X[8];
uint32_t C[8];
uint32_t A[8];
uint32_t carry;

void init () {
	for (int i = 0; i < 8; i++) {
		X[i] = C[i] = 0;
	};
	
	A[0] = A[3] = A[6] = 0x4D34D34D;
	A[1] = A[4] = A[7] = 0xD34D34D3;
	A[2] = A[5] = 0x34D34D34;
}

void counter_system() { 
	for (int i = 0; i < 8; i++) {
		uint64_t temp = C[i] + A[i] + carry;
		carry = (uint32_t)(temp >> 32);    // carry = temp div 2^32
		C[i] = (uint32_t)temp;             // C[i] = temp mod 2^32 = giữ lại 32 bit thấp
	}
}