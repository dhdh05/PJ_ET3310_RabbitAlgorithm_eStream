#include <cstdint>


void split_key(uint8_t input_key[16], uint16_t sub_key[8]);
void init_key_state(uint16_t sub_key[8]);
void key_setup(uint8_t input_key[16]);