#include "compress.h"



// Declaração de TAD
typedef struct prio_queue Prio_queue;
typedef struct huffman_tree h_tree;


struct prio_queue {
    h_tree* head; // Ponteiro para o primeiro elemento da priority queue
    int quant_nodes;
};


// Criação da lista de prioridade
Prio_queue* create_queue();

// Criação do node da lista de prioridade
h_tree* create_node(u_char ch, u_int freq);

// Função que verifica se a queue esta vazia
int que_empty(Prio_queue* p);

// Adicionando um node a lista de prioridade
void add_node_queue(Prio_queue* p, u_char ch, u_int freq);


void add_parent_node (Prio_queue *p_queue, h_tree *parent_node);

// Remove um nó da fila de prioridade
h_tree* dequeue_node (Prio_queue *p_queue);


// Função para printar a lista de prioridade
void print_queue(Prio_queue* p);

// Função de criar a lista final com os nodes inseridos de acordo com o array de freq
void construct_queue(Prio_queue* queu, u_int str[]);

// Função de verificar a quantidade de nodes existentes na queue
int quant_nodes_queue(Prio_queue* p_queue);
