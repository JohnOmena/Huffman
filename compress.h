#include <stdlib.h>
#include <stdio.h>

// tamanho máximo de uma string
#define MAX_STR_LEN 256

// tamanho máximo de um array
#define MAX_ARR_LEN 256

typedef unsigned char u_char;
typedef unsigned int u_int;

/*  Function: open_file_test - Testa o ponteiro file e indica se a
        abertura do arquivo foi bem o mal sucedida.

    Parameters:
        - FILE *file - Ponteiro para arquivo.

    Return: Inteiro 0 se a abertura foi mal-sucedida e 1 caso contrário.
*/
int open_file_test(FILE *file);


/*  Function: frequency_table - Constroi um array de frequência de bytes
        do arquivo apontado por file.

    Parameters:
        - FILE *file - ponteiro para arquivo
        - u_int *frequency_array- ponteiro para o array de frequências

    Return: Nothing
*/
void frequency_table(FILE *file, u_int *frequency_array);

/*  Function: compress_file - comprime um arquivo usando a codificação de Huffman

    Parameters:
        - <lista de parâmetros>

    Return: <descrição>
*/
void compress_file();

/* Function: way_table - cria os caminhos de todos as folhas presentes na arvore de huffman em uma matriz

    Parameters:

        - u_int way - matriz que possui os caminhos de cada folha
        - h_tree huff_tree - arvore de huffman montada

    Return: Nothing
*/
