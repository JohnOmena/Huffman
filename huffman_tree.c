#include "huffman_tree.h"

struct huffman_tree {
    h_tree *left;     // filho da esquerda
    h_tree *right;    // filho da direita
    h_tree *next;     // ponteiro para o próximo nó da lista (priority queue)
    u_int frequency; // frequência do byte
    u_char byte;     // byte
};

h_tree* create_empty_huffman_tree (h_tree *tree) {
    return NULL;
}
