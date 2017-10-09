// tamanho máximo de uma string
#define MAX_STR_LEN 256

// tamanho máximo de um array
#define MAX_ARR_LEN 256

typedef unsigned char u_char;
typedef unsigned int u_int;

int open_file_test(FILE *file);

void frequency_table(FILE *file, u_int *frequency_array);

void compress();
