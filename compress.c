#include "compress.h"
#include "priority_queue.h"
#include "huffman_tree.h"

// Função para printar a tabela
void print_table_way(u_char table_way[][256]){
    int i, j;
    printf("\n");
    for(i = 0; i < 256 ; i++){
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

// Função para iniciar todas as primeiras posições das colunas com /* para indicar que não há caminho ainda
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

    //for (i = 0 ; i < 256 ; i++) {
    //    if (frequency_array[i] != 0) {
    //        if (i == 10) {
    //            printf("\\n - %d\n", frequency_array[i]);
    //        }
    //        else {
    //            printf("%c - %d\n", i, frequency_array[i]);
    //        }
    //    }
    //}

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
    //print_table_way(matriz_way); // Printa a tabela com os caminhos
    //printf("\nAltura da Àrvode ----> %d\n", tree_height); // imprime a altura da árvore

}
