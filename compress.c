#include <stdio.h>
#include "compress.h"
#include "screen.h"
#include "priority_queue.h"
#include "huffman_tree.h"

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

void compress_file () {

    FILE *imput_file = NULL;                  /* ponteiro para o arquivo de entrada */

    char imput_file_name[MAX_STR_LEN];        /* string para guardar o nome do arquivo de entrada */

    u_int frequency_array[MAX_ARR_LEN] = {0}; /* array de frequência dos bytes do arquivo de entrada */
    u_int i;                                  /* controlador de loop */

    printf("Digite o nome do arquivo que deseja comprimir:\n");
    printf(" Exemplo: arquivo.txt\n > ");
    scanf("%[^\n]s", imput_file_name);

    imput_file = fopen(imput_file_name, "rb");

    while (!open_file_test(imput_file)) {

        getchar(); /* limpa o buffer */
        printf(" Digite o nome do arquivo que deseja comprimir:\n");
        printf(" Exemplo: arquivo.txt\n\n > ");
        scanf("%[^\n]s", imput_file_name);

        imput_file = fopen(imput_file_name, "rb");
    }

    //puts(imput_file_name);

    frequency_table(imput_file, frequency_array);

    for (i = 0 ; i < 256 ; i++) {
        if (frequency_array[i] != 0) {
            if (i == 10) {
                printf("\\n - %d\n", frequency_array[i]);
            }
            else {
                printf("%c - %d\n", i, frequency_array[i]);
            }
        }
    }

    // Criando uma queue vazia e chamando a função de criar a queue a partir do array
    Prio_queue* p_queue = create_queue();

    construct_queue(p_queue, frequency_array);

    print_queue(p_queue); // para verificar se a lista está correta

    h_tree *huff_tree = construct_huffman_tree(p_queue);

    print_pre_order(huff_tree); // conferir se a árvore está correta

    u_int tree_height = huffman_tree_height(huff_tree, 0); // conta qual a altura da árvore

    printf("\nAltura da Àrvode ----> %d\n", tree_height); // imprime a altura da árvore
}
