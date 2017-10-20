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

int is_leaf (h_tree *tree);

void print_pre_order (h_tree *tree);

u_int huffman_tree_height (h_tree *tree, u_int height);

/* Function: create_away_table - Constroi a tabela de caminhos a partir
        da Árvore de Huffman passada, realizando uma busca para encontrar as folhas
        da Árvore e em paralelo colocando as informações do caminho em um array temporário
        até que seja encontrado uma folha, em seguida apenas sobrescrevemos os dados do array
        na tabela com seu respectivo byte associado a linha desta.

    Parameters:
        u_char matriz_way[][256] - É a matriz que vai receber os caminhos das folhas a partir do array_temp,
            foi colocado 256 de limite para um caminho especifico, mas deveremos analisar e
            colocar o valor correto no pior caso.

        u_char array_temp[] - É um array com 256 espaços de limite que serão preenchidos durantes a busca
            na arvore, seus dados são temporários, pois é modificado a medida que ele anda pela arvore.

        h_tree* huff_tree - É a arvore de Huffman passada para que seja possivel obter os possiveis caminhos

        int posi - É um index para indicar onde o dado 1 ou 0 (indicadores de andei para direita e andei para a esquerda
        na arvore), será colocado no array_temp

    Return: Nenhum
*/
void create_way_table(u_char matriz_way[][256], u_char array_temp[], h_tree* huff_tree, int posi);


/*  Function: colocar_na_matriz - É uma função que auxilia a função create_way_table
        ela apenas pega os dados do array temporario e preenche a tabela com o respectivo
        byte associado a linha desta.

    Parameters:
        u_char matriz_way[][256] - É a que vai receber o caminho do array

        u_char array_temp[] - É o array contendo o caminho de uma folha

        u_char byte - É o byte que indica em qual linha da tabela escreveremos o caminho da folha

        int posi - É o indice que indica até que ponto do array iremos ler para obter o caminho correto
        da folha

    Return: Ponteiro para o nó raiz da Àrvore de Huffman
*/

void colocar_na_matriz(u_char matriz_way[][256], u_char array_temp[], u_char byte, int posi);

void write_huff_tree (h_tree *tree, int *tree_size, FILE *output_file);
