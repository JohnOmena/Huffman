#include <string.h>
#include "compress.h"
#include "priority_queue.h"
#include "huffman_tree.h"
#include "screen.h"
#include "useful.h"

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

    u_char byte = 0;         // byte para a escrita no arquivo (0000 0000)
    u_char byte_aux;         // byte de leitura no imput_file
    short int bit_index = 0; // controla a posição dos bits de byte
    int str_index = 0;       // controla a posição dos caracteres das strings de table

    rewind(imput_file);      // Retorna para a posição inicial de leitura/escrita do arquivo
    while (fread(&byte_aux, sizeof(u_char), 1, imput_file) == 1) {

        str_index = 0;
        while (table[byte_aux][str_index] != '\0') {

            if (bit_index == 8) { // quando o byte estiver 'cheio', escreva no arquivo
                //printf("---%d", byte);
                fwrite(&byte, sizeof(u_char), 1, output_file);
                byte = 0;      // reseta o byte
                bit_index = 0; // reseta o controlador dos bits
            }

            if (table[byte_aux][str_index] & 1) {

                byte = set_bit(byte, bit_index); // seta o bit em byte
            }
            str_index++;
            bit_index++;
        }
    }

    fwrite(&byte, sizeof(u_char), 1, output_file); // escreve o último byte

    u_char trash_size = ((8 - bit_index) << 5); // pegando o tamanho do lixo (bit que sobraram na escrita)
    u_char str_tree_size = tree_size;           // tamanho da string da árvore de Huffman

    rewind(output_file);
    fwrite(&trash_size, sizeof(u_char), 1, output_file);    // escreve o tamanho do lixo
    fwrite(&str_tree_size, sizeof(u_char), 1, output_file); // escreve o tamanho da árvore

    return;
}

void compress_file () {

    FILE *imput_file = NULL;                  /* ponteiro para o arquivo de entrada */
    FILE *output_file = NULL;                 /* arquivo de saída */

    char imput_file_name[MAX_STR_LEN];        /* string para guardar o nome do arquivo de entrada */
    char output_file_name[MAX_STR_LEN];       /* string para guardar o nome do arquivo de saída */

    u_int frequency_array[MAX_ARR_LEN] = {0}; /* array de frequência dos bytes do arquivo de entrada */

    printf("  _       ___                                 _             \n");
    printf(" / |     / __\\___  _ __ ___  _ __   __ _  ___| |_ __ _ _ __ \n");
    printf(" | |    / /  / _ \\| '_ ` _ \\| '_ \\ / _` |/ __| __/ _` | '__|\n");
    printf(" | |_  / /__| (_) | | | | | | |_) | (_| | (__| || (_| | |   \n");
    printf(" |_(_) \\____/\\___/|_| |_| |_| .__/ \\__,_|\\___|\\__\\__,_|_|   \n");
    printf("                            |_|                             \n\n");

    printf(" Digite o nome do arquivo que deseja comprimir:\n\n");
    printf(" Exemplo: arquivo.txt\n > ");
    scanf("%[^\n]s", imput_file_name);
    getchar();

    strcpy(output_file_name, imput_file_name);
    strcat(output_file_name, ".huff");

    imput_file = fopen(imput_file_name, "rb");

    while (!open_file_test(imput_file)) {

        getchar(); /* limpa o buffer */
        printf(" Digite o nome do arquivo que deseja comprimir:\n\n");
        printf(" Exemplo: arquivo.txt\n\n > ");
        scanf("%[^\n]s", imput_file_name);

        imput_file = fopen(imput_file_name, "rb");
    }

    clear_screen();
    printf(" Aguarde enquanto o arquivo é compactado ...\n\n");

    frequency_table(imput_file, frequency_array);

    // Criando uma queue vazia e chamando a função de criar a queue a partir do array
    Prio_queue* p_queue = create_queue();

    construct_queue(p_queue, frequency_array);

    h_tree *huff_tree = construct_huffman_tree(p_queue);

    u_char matriz_way[256][256];  // Criar a matriz que vai armazenar os caminhos
    u_char array_temp[256]; // Array que vai armazenar o caminho temporário

    inicializar_table_way(matriz_way); // Inicializa a tabela para indicar que não há caminho ainda olhar o .h para melhores informações
    create_way_table(matriz_way, array_temp, huff_tree, 0); // Cria a tabela com base na huffman_tree

    int *tree_size = (int*) malloc(sizeof(int));      // ponteiro int para pegar o tamanho da árvore

    output_file = fopen(output_file_name, "wb");      // abrindo o arquivo em modo de escrita em binário
    create_header(output_file, huff_tree, tree_size); // criando o cabeçalho
    write_compressed_file(imput_file, output_file, matriz_way, *tree_size); // escrevendo o arquivo comprimido

    printf(" Arquivo compactado!\n\n");

    fclose(imput_file);  // fechando o arquivo de origem
    fclose(output_file); // fechando o arquivo comprimido

    return;
}
