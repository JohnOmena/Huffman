#include "priority_queue.h"
#include <stdlib.h>

// TAD usadas
struct huffman_tree {
    h_tree* left;     // filho da esquerda
    h_tree* right;    // filho da direita
    h_tree* next;     // ponteiro para o próximo nó da lista (priority queue)
    u_int frequency; // frequência do byte
    u_char byte;     // byte
};

struct prio_queue {
    h_tree* head; // Ponteiro para o primeiro elemento da priority queue
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
    if(que_empty(p) || p->head->frequency <= freq){

        nod->next = p->head;
        p->head = nod;


    } else {

        h_tree* nod_temp = p->head;
        while(nod_temp->next != NULL && nod_temp->next->frequency > freq){
            nod_temp = nod_temp->next;
        }

        nod->next = nod_temp->next;
        nod_temp->next = nod;

    }

}

// Implementação da função que adiciona os nodes a lista de prioridade de acordo com array de freq
void end_queue(Prio_queue* p, u_int str[]){

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
            printf("pula de linha - %d\t", nod->frequency);
        } else {
            printf("%c  - %d ", nod->byte, nod->frequency);
        }

        if(count == 5){
            printf("\n");
        }
    }
}
