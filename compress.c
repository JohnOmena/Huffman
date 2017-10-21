#include <string.h>
#include "compress.h"
#include "priority_queue.h"
#include "huffman_tree.h"
#include "screen.h"
#include "useful.h"

// Função para printar a tabela
void print_table_way(u_char table_way[][256]){
    int i, j;
    printf("\n");
    for(i = 0; i < 256 ; i++){
            if (table_way[i][0] != '\0') {
                printf("%d - ", i);
            }
        for(j = 0; j < 256 ; j ++){
            if(table_way[i][0] == '\0'){
                break;
            } else if (table_way[i][j] != '\0'){
                printf("%c ", table_way[i][j]);
            } else {
                printf("\n");
                break;
            }
        }
    }

}

// Função para iniciar todas as primeiras posições das colunas com \0 para indicar que não há caminho ainda
void inicializar_table_way(u_char table_way[][256]){
    int i;
    for(i = 0; i < 256; i ++){
        table_way[i][0] = '\0';
    }
}

int open_file_test (FILE *file) {

    if (file == NULL) {
        clear_screen();
        printf(" Erro ao abrir o arquivo!\n\n");
        return 0;
    }
    else {
        return 1;
    }
}

void frequency_table (FILE *file, u_int *frequency_array) {

    u_char character;

    while (fread(&character, sizeof(u_char), 1, file) == 1) {
        frequency_array[character]++;
    }

    return;
}

void create_header (FILE *output_file, h_tree *tree, int *tree_size) {

    u_char byte = 0;

    fwrite(&byte, sizeof(u_char), 1, output_file);
    fwrite(&byte, sizeof(u_char), 1, output_file);

    write_huff_tree(tree, tree_size, output_file);
}

void write_compressed_file (FILE *imput_file, FILE *output_file, u_char table[][256], int tree_size) {

    u_char byte = 0;
    u_char byte_aux;
    short int bit_index = 0;
    int str_index = 0;

    rewind(imput_file);
    while (fread(&byte_aux, sizeof(u_char), 1, imput_file) == 1) {

        str_index = 0;
        while (table[byte_aux][str_index] != '\0') {

            if (bit_index == 8) {
                //printf("---%d", byte);
                fwrite(&byte, sizeof(u_char), 1, output_file);
                byte = 0;
                bit_index = 0;
            }

            if (table[byte_aux][str_index] & 1) {

                byte = set_bit(byte, bit_index);
            }
            str_index++;
            bit_index++;
        }
    }
    //printf("---%d", byte);
    fwrite(&byte, sizeof(u_char), 1, output_file);
    //printf("\nBIT = %d\n", bit_index);

    u_char trash_size = ((8 - bit_index) << 5);
    u_char str_tree_size = tree_size;
    //printf("str size = %d", str_tree_size);
    //printf("trash = %d", trash_size);

    rewind(output_file);
    fwrite(&trash_size, sizeof(u_char), 1, output_file);
    fwrite(&str_tree_size, sizeof(u_char), 1, output_file);

    //print_binary_file();
    return;
}

void compress_file () {

    FILE *imput_file = NULL;                  /* ponteiro para o arquivo de entrada */
    FILE *output_file = NULL;                 /* arquivo de saída */

    char imput_file_name[MAX_STR_LEN];        /* string para guardar o nome do arquivo de entrada */
    char output_file_name[MAX_STR_LEN];       /* string para guardar o nome do arquivo de saída */

    u_int frequency_array[MAX_ARR_LEN] = {0}; /* array de frequência dos bytes do arquivo de entrada */
    //u_int i;                                /* controlador de loop */

    printf("Digite o nome do arquivo que deseja comprimir:\n");
    printf(" Exemplo: arquivo.txt\n > ");
    scanf("%[^\n]s", imput_file_name);

    strcpy(output_file_name, imput_file_name);
    strcat(output_file_name, ".huff");

    imput_file = fopen(imput_file_name, "rb");

    while (!open_file_test(imput_file)) {

        getchar(); /* limpa o buffer */
        printf(" Digite o nome do arquivo que deseja comprimir:\n");
        printf(" Exemplo: arquivo.txt\n\n > ");
        scanf("%[^\n]s", imput_file_name);

        imput_file = fopen(imput_file_name, "rb");
    }

    //puts(imput_file_name);
    //puts(output_file_name);

    frequency_table(imput_file, frequency_array);
    // frequency_array[10] = 0;

    /*for (i = 0 ; i < 256 ; i++) {
        if (frequency_array[i] != 0) {
            if (i == 10) {
                printf("\\n - %d\n", frequency_array[i]);
            }
            else {
                printf("%c - %d\n", i, frequency_array[i]);
            }
        }
    }*/

    // Criando uma queue vazia e chamando a função de criar a queue a partir do array
    Prio_queue* p_queue = create_queue();

    construct_queue(p_queue, frequency_array);

    //print_queue(p_queue); // para verificar se a lista está correta

    //quant_nodes_queue(p_queue); // Verificar a quantidade de nodes na Queue

    h_tree *huff_tree = construct_huffman_tree(p_queue);

    //print_pre_order(huff_tree); // conferir se a árvore está correta

    //u_int tree_height = huffman_tree_height(huff_tree, 0); // conta qual a altura da árvore

    u_char matriz_way[256][256];  // Criar a matriz que vai armazenar os caminhos
    u_char array_temp[256]; // Array que vai armazenar o caminho temporário

    inicializar_table_way(matriz_way); // Inicializa a tabela para indicar que não há caminho ainda olhar o .h para melhores informações
    create_way_table(matriz_way, array_temp, huff_tree, 0); // Cria a tabela com base na huffman_tree
    // print_table_way(matriz_way); // Printa a tabela com os caminhos

    int *tree_size = (int*) malloc(sizeof(int));

    output_file = fopen(output_file_name, "wb");
    create_header(output_file, huff_tree, tree_size);
    write_compressed_file(imput_file, output_file, matriz_way, *tree_size);

    printf(" > Arquivo comprimido!\n");

    fclose(imput_file);
    fclose(output_file);

    return;
}
