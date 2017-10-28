#include "compress.h"

// Declaração de TAD
typedef struct prio_queue Prio_queue;
typedef struct huffman_tree h_tree;

struct prio_queue {
    h_tree* head; // Ponteiro para o primeiro elemento da priority queue
    int quant_nodes;
};


/*
 * Cria uma fila de prioridades vazia. Sem parâmetros. Retorna um
 * ponteiro para o primeiro item da fila.
 */
Prio_queue* create_queue();

/*
 * Cria um nó. Recebe um caractere e sua frequência. Retorna um
 * ponteiro para um nó.
 */
h_tree* create_node(u_char ch, u_int freq);

/*
 * Verifica se a fila está vazia. Recebe um ponteiro para o
 * primeiro item da fila. Retorna 1 caso a fila seja vazia
 * e 0 caso contrário.
 */
int que_empty(Prio_queue* p);

/*
 * Adiciona um nó na fila de prioridade. Recebe um ponteiro
 * para o primeiro item da fila, um caractere e sua frequência.
 * Não retorna nada.
 */
void add_node_queue(Prio_queue* p, u_char ch, u_int freq);

/*
 * Adiciona um nó pai de outros dois nós dados na fila de priori-
 * dade. Recebe um ponteiro para o primeiro item da fila, e um
 * ponteiro para um nó pai. Não retorna nada;
 */
void add_parent_node (Prio_queue *p_queue, h_tree *parent_node);

/*
 * Remove um item da fila de prioridade. Recebe um ponteiro para
 * o primeiro item da fila. Retorna um ponteiro para o item remo-
 * vido.
 */
h_tree* dequeue_node (Prio_queue *p_queue);

/*
 * Constrói uma fila de prioridade a partir de um array de
 * frequência dado. Recebe um ponteiro para o primeiro item
 * da fila e o array de frequências. Não retorna nada;
 */
void construct_queue(Prio_queue* queu, u_int str[]);
