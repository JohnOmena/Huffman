#include <stdlib.h>
#include <stdio.h>

// tamanho máximo de uma string
#define MAX_STR_LEN 256

// tamanho máximo de um array
#define MAX_ARR_LEN 256

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef struct huffman_tree h_tree;

// -----------------------------------------------------------------

void print_table_way(u_char table_way[][256]);

void inicializar_table_way(u_char table_way[][256]);

int open_file_test(FILE *file);

void frequency_table(FILE *file, u_int *frequency_array);

void compress_file();

void create_header (FILE *output_file, h_tree *tree, int *tree_size);

void write_compressed_file (FILE *imput_file, FILE *output_file, u_char table[][256], int tree_size);
