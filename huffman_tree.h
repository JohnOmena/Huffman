#include "compress.h"

typedef struct huffman_tree h_tree;
typedef struct prio_queue Prio_queue;

/*  Function: create_empty_huffman_tree - Cria um ponteiro vazio
        para um nó da árvore de Huffman

    Parameters:
        No parameters

    Return: Ponteiro NULL para uma árvore de Huffman
*/
h_tree* create_empty_huffman_tree ();

/*  Function: create_parent_node - Cria um nó pai a partir de
        dois nós filhos dados

    Parameters:
        - h_tree *node1 - ponteiro para o nó filho da esquerda
        - h_tree *node2 - ponteiro para o nó filho da direita

    Return: Ponteiro para o nó pai de node1 e node2
*/
h_tree* create_parent_node (h_tree *node1, h_tree *node2);

/*  Function: construct_huffman_tree - Constrói a Árvore de Huffman
        a partir da fila de prioridade com os bytes e suas
        frequências

    Parameters:
        Prio_queue * p_queue - ponteiro para a fila de prioridade
        com os nós

    Return: Ponteiro para o nó raiz da Àrvore de Huffman
*/
h_tree* construct_huffman_tree (Prio_queue *p_queue);

int tree_empty (h_tree *tree);

void print_pre_order (h_tree *tree);

u_int huffman_tree_height (h_tree *tree, u_int height);
