#include <stdio.h>
#include <string.h>
#include "compress.h"
#include "screen.h"
#include "huffman_tree.h"
#include "useful.h"

struct huffman_tree {
    h_tree *left;     // filho da esquerda
    h_tree *right;    // filho da direita
    h_tree *next;     // ponteiro para o próximo nó da lista (priority queue)
    u_int frequency;  // frequência do byte
    u_char byte;      // byte
    int quant_nodes;  // antos nós tem a fila de prioridade
};

int is_huff_file (char *file_name) {

    char str[] = ".huff"; // string de comparação
    int i;
    int j = 0;

    for (i = strlen(file_name) - 5 ; i < strlen(file_name) ; i++, j++) {

        if (file_name[i] != str[j]) { /* Se o caracter do nome do arquivo for diferente
                                         do caracter da string de comparação, retorna 0
                                         pois não se trata de um arquivo .huff*/
            return 0;
        }
    }

    return 1;
}

 void write_original_file (FILE *compressed_file, FILE *original_file, h_tree *tree, int trash_size) {

    h_tree *tree_aux;      // ponteiro auxiliar para um nó de árvore
    u_char byte, byte_aux; // variáveis para manipular os bytes lidos
    short int i;           // controlador de index do byte

    tree_aux = tree;       // tree aponta para a raiz da árvore

    fread(&byte, sizeof(u_char), 1, compressed_file);
    byte_aux = byte;

    while (fread(&byte, sizeof(u_char), 1, compressed_file) == 1) {

        for (i = 7 ; i >= 0 ; i--) {

            if (is_leaf(tree_aux)) { // se for uma folha, escreve o byte do nó e retorna à raiz

                fwrite(&tree_aux->byte, sizeof(u_char), 1, original_file);
                tree_aux = tree;
            }

            if (!is_bit_set(byte_aux, i)) { // lê os bits e vai para a esquerda ou direita na árvore

                tree_aux = tree_aux->left;
            }
            else {

                tree_aux = tree_aux->right;
            }
        }
        byte_aux = byte;
    }

    for (i = 7 ; i >= trash_size - 1; i--) { // esse loop é para tratar o último byte
                                             // que contem lixo
        if (is_leaf(tree_aux)) {

            fwrite(&tree_aux->byte, sizeof(u_char), 1, original_file);
            tree_aux = tree;
        }

        if (!is_bit_set(byte_aux, i)) {

            tree_aux = tree_aux->left;
        }
        else {

            tree_aux = tree_aux->right;
        }
    }
}

void decompress_file () {

    FILE *compressed_file = NULL;           // ponteiro para o arquivo compactado
    FILE *original_file = NULL;             // ponteiro para o arquivo original

    char compressed_file_name[MAX_STR_LEN]; // nome do arquivo compactado
    char original_file_name[MAX_STR_LEN];   // nome do arquivo original

    printf("  ____         ___                                               _             \n");
    printf(" |___ \\       /   \\___  ___  ___ ___  _ __ ___  _ __   __ _  ___| |_ __ _ _ __ \n");
    printf("   __) |     / /\\ / _ \\/ __|/ __/ _ \\| '_ ` _ \\| '_ \\ / _` |/ __| __/ _` | '__|\n");
    printf("  / __/ _   / /_//  __/\\__ \\ (_| (_) | | | | | | |_) | (_| | (__| || (_| | |   \n");
    printf(" |_____(_) /___,' \\___||___/\\___\\___/|_| |_| |_| .__/ \\__,_|\\___|\\__\\__,_|_|   \n");
    printf("                                               |_|                             \n\n");

    printf(" Digite o nome do arquivo compactado.\n\n Exemplo: arquivo.huff\n > ");
    scanf("%[^\n]s", compressed_file_name);
    getchar();

    compressed_file = fopen(compressed_file_name, "rb");

    // verifica se o arquivo foi aberto corretamente ou se o arquivo digitado tem extensão .huff
    while ((!open_file_test(compressed_file)) || (!is_huff_file(compressed_file_name))) {

        clear_screen();
        printf(" Erro na abertura do arquivo!\n\n");

        if (!is_huff_file(compressed_file_name)) {

            printf(" O arquivo digitado não possui extensão .huff\nEntre com um arquivo válido.\n\n");
        }

        printf(" Digite o nome do arquivo compactado:\n\n Exemplo: arquivo.huff\n > ");
        scanf("%[^\n]s", compressed_file_name);
        getchar();

        compressed_file = fopen(compressed_file_name, "rb");
    }

    printf("\n Digite o nome do arquivo de saída:\n > ");
    scanf("%[^\n]s", original_file_name);
    getchar();

    clear_screen();
    printf(" Aguarde... o arquivo está sendo descompactado... \n\n");

    u_char trash_size; // variavel para armazenar o tamanho do lixo
    u_char tree_size;  // variavel para armazenar o tamanho da string da árvore

    int *tree_s = (int*) malloc(sizeof(int));
    int trash_s;

    fread(&trash_size, sizeof(u_char), 1, compressed_file);
    fread(&tree_size, sizeof(u_char), 1, compressed_file);
    trash_size = (trash_size >> 5);

    trash_s = trash_size;  // copiando os valores para variáveis inteiras
    (*tree_s) = tree_size; // copiando os valores para variáveis inteiras

    h_tree* huff_tree = create_empty_huffman_tree(); // criando uma árvore vazia
    huff_tree = reconstruct_huff_tree(compressed_file, huff_tree); // reconstruindo a árvore de Huffman

    original_file = fopen(original_file_name, "wb");
    write_original_file(compressed_file, original_file, huff_tree, trash_s); // escrevendo o arquivo original

    fclose(compressed_file); // fechando os arquivos utilizados
    fclose(original_file);   // fechando os arquivos utilizados

    printf(" Arquivo descompactado!\n\n");
}
