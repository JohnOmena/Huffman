#include "compress.h"

u_int max (u_int num1, u_int num2) {
    if (num1 >= num2) {
        return num1;
    }
    return num2;
}

u_char set_bit (u_char byte, int bit_index) {

    return (byte | (1 << (7 - bit_index)));
}
