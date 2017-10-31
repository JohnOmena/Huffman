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

/*
 * Recebe a tabela de caminhos e inicia todas as strings de table_way
 * com '\0' indicando que não há caminho para o byte daquela posição
 * da tabela. Não retorna nada.
 */
void inicializar_table_way(u_char table_way[][256]);

/*
 * Testa se o arquivo foi aberto com sucesso. Recebe um ponteiro para
 * arquivo. Retorna 0 caso o arquivo seja NULL e 1 caso contrário.
 */
int open_file_test(FILE *file);

/*
 * Constrói um array de frequência dos bytes de file. Recebe o ponteiro
 * para o arquivo de leitura e um ponteiro para um array. Não retorna
 * nada.
 */
void frequency_table(FILE *file, u_int *frequency_array);

/*
 * Compacta o arquivo passado. Chama as funções necessárias para a com-
 * pactação do arquivo. Sem parâmetros. Não retorna nada.
 */
void compress_file();

/*
 * Cria e escreve o cabeçalho do arquivo .huff. Recebe um ponteiro para o arquivo
 * compactado, um ponteiro para a árvore de Huffman e um ponteiro int
 * para o tamanho da árvore. Não retorna nada.
 */
void create_header (FILE *output_file, h_tree *tree, int *tree_size);

/*
 * Escreve o arquivo compactado. Recebe um ponteiro para o arquivo de origem,
 * um ponteiro para o arquivo de destino, a tabela de caminhos e o tamanho da
 * árvore de Huffman. Não retorna nada.
 */
void write_compressed_file (FILE *imput_file, FILE *output_file, u_char table[][256], int tree_size);
