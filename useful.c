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

void print_binary_file () {

    u_char byte;
    FILE *pfile = fopen("teste.huff", "rb");

    while (fread(&byte, sizeof(u_char), 1, pfile) == 1) {

        printf("[%c]", byte);
    }
}
