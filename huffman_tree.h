#include "compress.h"

typedef struct huffman_tree h_tree;
typedef struct prio_queue Prio_queue;

/*
 * Cria um ponteiro para uma árvore vazia. Sem parâmetros.
 * Retorna um ponteiro para o nó raíz da árvore.
 */
h_tree* create_empty_huffman_tree ();

/*
 * Cria um nó pai a partir de dois nós dados. Recebe dois
 * ponteiros para nós. Retorna um ponteiro para um nó cujos
 * filhos são os dois nós passados como parâmetros.
 */
h_tree* create_parent_node (h_tree *node1, h_tree *node2);

/*
 * Constrói a Árvore de Huffman a partir da fila de priori-
 * dades. Recebe um ponteiro para o primeiro item da fila.
 * Retorna um ponteiro para o nó raiz da Árvore de Huffman
 * construída.
 */
h_tree* construct_huffman_tree (Prio_queue *p_queue);

/*
 * Verifica se a árvore está vazia. Recebe um ponteiro para
 * um nó. Retorna 1 caso a árvore esteja vazia e 0 caso con-
 * trário.
 */
int tree_empty (h_tree *tree);

/*
 * Verifica se o nó é uma folha. Recebe um ponteiro para um
 * nó. Retorna 1 caso seja uma folha e 0 caso contrário.
 */
int is_leaf (h_tree *tree);

/*
 * Constrói uma tabela de caminhos a partir de uma Árvore de
 * Huffman dada. Recebe uma matriz, uma array de caracteres,
 * um ponteiro para o nó raíz da Árvore de Huffman e um inteiro
 * para controlar a posição na matriz. Não retorna nada.
 */
void create_way_table(u_char matriz_way[][256], u_char array_temp[], h_tree* huff_tree, int posi);

/*
 * Escreve o caminho na respectiva linha da matriz. Recebe uma
 * matriz, um array de caracteres, um caractere e um inteiro
 * controlar a posição na matriz. Não retorna nada.
 */
void colocar_na_matriz(u_char matriz_way[][256], u_char array_temp[], u_char byte, int posi);

/*
 * Escreve a string da Árvore de Huffman no arquivo de destino.
 * Recebe um ponteiro para o nó raíz da Árvore de Huffman, um
 * ponteiro int para o tamanho da string e um ponteiro para o
 * arquivo de destino. Não retorna nada;
 */
void write_huff_tree (h_tree *tree, int *tree_size, FILE *output_file);

/*
 * Reconstrói a Árvore de Huffman a partir a string no arquivo
 * compactado. Recebe um ponteiro para o arquivo compactado e
 * um ponteiro para o nó raiz da Árvore de Huffman. Retorna um
 * ponteiro para o nó raíz da Árvore de Huffman montada.
 */
h_tree* reconstruct_huff_tree (FILE *compressed_file, h_tree *tree);
