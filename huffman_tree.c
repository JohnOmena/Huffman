#include "huffman_tree.h"
#include "compress.h"
#include "priority_queue.h"
#include "useful.h"

// Estrutura de um nó
struct huffman_tree {
    h_tree *left;     // filho da esquerda
    h_tree *right;    // filho da direita
    h_tree *next;     // ponteiro para o próximo nó da lista (priority queue)
    u_int frequency;  // frequência do byte
    u_char byte;      // byte
};

// Cria um ponteiro para um nó vazio
h_tree* create_empty_huffman_tree () {
    return NULL;
}

// Cria um nó pai de dois nós dados
h_tree* create_parent_node (h_tree *node1, h_tree *node2) {
    h_tree *parent_node = create_node('*', node1->frequency + node2->frequency); // Aloca memória para o nó pai
    parent_node->left = node2;  // node1 é o filho da esquerda
    parent_node->right = node1; // node2 é o filho da direita
    parent_node->next = NULL;   // o ponteiro para o próximo nó é iniciado como NULL

    return parent_node;         // retorna o ponteiro para o nó pai
}

// Constrói a Árvore de Huffman a partir da fila de prioridades
h_tree* construct_huffman_tree (Prio_queue *p_queue) {

    h_tree *parent_node = create_empty_huffman_tree(); // cria um ponteiro vazio para um nó

    // Enquanto a fila não for vazia
    while (p_queue->head->next != NULL) {
        // Desenfileiro os dois primeiros nós de p_queue e cria um nó pai a partir deles
        parent_node = create_parent_node(dequeue_node(p_queue), dequeue_node(p_queue));
        add_parent_node(p_queue, parent_node); // Adiciona o nó pai na fila
    }

    return p_queue->head; // retorna o nó raiz da Árvore de Huffman
}

// Verifica se o nó é vazio
int tree_empty (h_tree *tree) {
    return (tree == NULL);
}

// Imprime a Árvore de Huffman em pré ordem
void print_pre_order (h_tree *tree) {
    if (!tree_empty(tree)) {
        if (tree->byte == '\n') {
            printf("\\n");
        }
        else {
            printf("%c", tree->byte);
        }
        print_pre_order(tree->left);
        print_pre_order(tree->right);
    }
}

u_int huffman_tree_height (h_tree *tree, u_int height) {

    if ((tree->left == NULL) && (tree->right == NULL)) {
        return height;
    }
    else {
        return max(huffman_tree_height(tree->left, height + 1), huffman_tree_height(tree->right, height + 1));
    }
}
