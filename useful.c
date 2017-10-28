#include "compress.h"

u_char set_bit (u_char byte, int bit_index) {

    return (byte | (1 << (7 - bit_index)));
}

int is_bit_set (u_char byte, short int i) {

    return (byte & (1 << i));
}
