
/*
 * Seta um bit no local dado. Recebe um byte e um
 * bit_index que indica a posição do bit a ser setado.
 * Retorna o byte setado.
 */
u_char set_bit (u_char byte, int bit_index);

/*
 * Verifica se o bit está setado em um local dado.
 * Recebe um byte e um int que indica a posição
 * do bit a ser testado. Retorna 1 caso o bit
 * esteja setado e 0 caso contrário.
 */
int is_bit_set (u_char byte, short int i);
