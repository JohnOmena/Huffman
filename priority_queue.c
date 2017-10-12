#include <stdlib.h>
#include "huffman_tree.h"
#include "priority_queue.h"

// Estrutura de um nó
struct huffman_tree {
    h_tree *left;     // filho da esquerda
    h_tree *right;    // filho da direita
    h_tree *next;     // ponteiro para o próximo nó da lista (priority queue)
    u_int frequency;  // frequência do byte
    u_char byte;      // byte
};

// Implementação da função de criação de queue
Prio_queue* create_queue(){
    Prio_queue* p = (Prio_queue*) calloc(1, sizeof(Prio_queue)); // Alocando a Lista;

    p->head = NULL; // Setando sua cabeça para NULL (inicialmente)
    return p;

}

// Implementação da função de criar os nodes da lista
h_tree* create_node(u_char by, u_int freq){
    h_tree* nod = (h_tree*) calloc(1, sizeof(h_tree)); // Alocando o node

    // Setando os valores iniciais do node;
    nod->frequency = freq;
    nod->byte = by;
    nod->left = nod->right = nod->next = NULL;

    return nod;
}

// Implementação da função que verifica se a queue esta vazia
int que_empty(Prio_queue* p){
    return (p->head == NULL);
}

// Implementação da função que adiciona o node na lista de prioridade
void add_node_queue(Prio_queue* p, u_char by, u_int freq){

    // cria o node
    h_tree* nod = create_node(by, freq);

    // verfica se a queue esta vazia
    if(que_empty(p) || p->head->frequency >= freq){

        nod->next = p->head;
        p->head = nod;


    } else {

        h_tree* nod_temp = p->head;
        while(nod_temp->next != NULL && nod_temp->next->frequency < freq){
            nod_temp = nod_temp->next;
        }

        nod->next = nod_temp->next;
        nod_temp->next = nod;

    }

}

void add_parent_node (Prio_queue *p_queue, h_tree *parent_node) {

    if(que_empty(p_queue) || p_queue->head->frequency >= parent_node->frequency){

        parent_node->next = p_queue->head;
        p_queue->head = parent_node;

    }
    else {

        h_tree* nod_temp = p_queue->head;
        while(nod_temp->next != NULL && nod_temp->next->frequency < parent_node->frequency){
            nod_temp = nod_temp->next;
        }

        parent_node->next = nod_temp->next;
        nod_temp->next = parent_node;

    }
}

h_tree* dequeue_node (Prio_queue *p_queue) {
    // Verifica se está tentando desenfileirar com a fila vazia

    if (!que_empty(p_queue)) {
        h_tree *node = p_queue->head;        // cria um nó que aponta para a cabeça da fila
        p_queue->head = p_queue->head->next; // a cabeça da fila aponta para o próximo nó
        node->next = NULL;                   // remove a ligação de node com a fila
        return node;                         // retorna node
    }
    return NULL;
}

// Implementação da função que adiciona os nodes a lista de prioridade de acordo com array de freq
void construct_queue(Prio_queue* p, u_int str[]){

    // Adionando os nodes
    int i;
    for(i = 0; i < 256; i++){
        if(str[i] != 0){
        add_node_queue(p, i, str[i]);
        }
    }

}

// Implementação da função que printa a lista
void print_queue(Prio_queue* p){
    int count = 0;
    h_tree* nod = p->head;
    for ( ; nod != NULL ; nod = nod->next){

        if(nod->byte == '\n'){
            if (nod->left == NULL && nod->right == NULL) {
                printf("\\n|%d -> L()R() --> ", nod->frequency);
            }
            else {
                printf("\\n|%d -> L(%c)R(%c) --> ", nod->frequency, nod->left->byte, nod->right->byte);
            }
            count++;
        } else {
            if (nod->left == NULL && nod->right == NULL) {
                printf("%c|%d -> L()R() --> ", nod->byte, nod->frequency);
            }
            else {
                printf("%c|%d -> L(%c)R(%c) --> ", nod->byte, nod->frequency, nod->left->byte, nod->right->byte);
            }
            count++;
        }

        if(count == 5){
            printf("\n");
            count = 0;
        }
    }
    printf("\n");
}
