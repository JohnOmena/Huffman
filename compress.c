#include <stdio.h>
#include "compress.h"
#include "screen.h"

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

    for (i = 32 ; i <= 126 ; i++) {
        if (frequency_array[i] != 0) {
            printf("%c - %d\n", i, frequency_array[i]);
        }
    }


}
