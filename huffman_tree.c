#include "huffman_tree.h"
#include "priority_queue.h"
#include "useful.h"

// Estrutura de um nó
struct huffman_tree {
    h_tree *left;     // filho da esquerda
    h_tree *right;    // filho da direita
    h_tree *next;     // ponteiro para o próximo nó da lista (priority queue)
    u_int frequency;  // frequência do byte
    u_char byte;      // byte
    int quant_nodes;   // quantos nós tem a fila de prioridade
};

// Cria um ponteiro para um nó vazio
h_tree* create_empty_huffman_tree () {
    return NULL;
}

// Cria um nó pai de dois nós dados
h_tree* create_parent_node (h_tree *node1, h_tree *node2) {
    h_tree *parent_node = create_node('\*', node1->frequency + node2->frequency); // Aloca memória para o nó pai
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

int is_leaf (h_tree *tree) {
    return ((tree->left == NULL) && (tree->right == NULL));
}

void colocar_na_matriz(u_char matriz[][256], u_char array_temp[], u_char byte, int posi){
    int i;
    for(i = 0; i < posi; i ++){
        matriz[byte][i] = array_temp[i];
    }
    matriz[byte][i] = '\0';
}

void create_way_table(u_char matriz_way[][256], u_char array_temp[], h_tree* huffman_tree, int posi){

    if(huffman_tree->left == NULL && huffman_tree->right == NULL){

        colocar_na_matriz(matriz_way, array_temp, huffman_tree->byte, posi);
        return;
    }

    if (huffman_tree->left != NULL) {
        array_temp[posi] = '0';
        create_way_table(matriz_way, array_temp, huffman_tree->left,  posi + 1);
    }

    if (huffman_tree->right != NULL) {
        array_temp[posi] = '1';
        create_way_table(matriz_way, array_temp, huffman_tree->right, posi + 1);
    }
}

void write_huff_tree (h_tree *tree, int *tree_size, FILE *output_file) {

    if (is_leaf(tree)) {

        if (tree->byte == '\\' || tree->byte == '*') {

            u_char byte = '\\';
            (*tree_size)++;
            fwrite(&byte, sizeof(u_char), 1, output_file);
        }

        (*tree_size)++;
        fwrite(&tree->byte, sizeof(u_char), 1, output_file);

        return;
    }

    (*tree_size)++;
    fwrite(&tree->byte, sizeof(u_char), 1, output_file);

    if (tree->left != NULL) {
        write_huff_tree(tree->left, tree_size, output_file);
    }

    if (tree->right != NULL) {
        write_huff_tree(tree->right, tree_size, output_file);
    }
}

h_tree* reconstruct_huff_tree (FILE *compressed_file, h_tree *tree) {

    u_char byte;

    fread(&byte, sizeof(u_char), 1, compressed_file);

    if (byte == '*') {

        tree = create_node(byte, 0);

        tree->left = reconstruct_huff_tree(compressed_file, tree->left);
        tree->right = reconstruct_huff_tree(compressed_file, tree->right);
    }
    else {

        if (byte == '\\') {

            fread(&byte, sizeof(u_char), 1, compressed_file);
            tree = create_node(byte, 0);
        }
        else {

            tree = create_node(byte, 0);
        }
    }

    return tree;
}
