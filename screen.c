#include <stdlib.h>
#include <ctype.h>
#include "compress.h"

void clear_screen () {
    system("clear");
}

short int is_a_valid_option (short int option) {
    return ((option == 1) || (option == 2) || (option == 0));
}

void execute_function (short int *option) {

    char decision = '*'; // caractere iniciado com um valor diferente dos valores válidos
    switch (*option) {

        case 1: // chama a função compress()
            clear_screen();
            compress_file();
            break;
        case 2: // chama a função decompress()
            clear_screen();
            puts("Chamou a decopress!");
            break;
        case 0: // verifica se o usuário deseja realmente sair do programa
            clear_screen();
            printf("Tem certeza que deseja sair do programa? [S/N]\n > ");
            scanf("%c", &decision);
            getchar();
            decision = toupper(decision);

            while (!((decision == 'S') || (decision == 'N'))) {

                clear_screen();
                printf("Resposta inválida. \n\nLeia direito! Digite \"S\" para SIM e \"N\" para NÃO. u_u'\n > ");
                scanf("%c", &decision);
                getchar();
                decision = toupper(decision);
            }

            if (decision == 'S') {
                exit(0);
            }
            else {
                clear_screen();
                (*option) = -1; // seta um valor inválido para option para que o loop de
                break;          // main_menu() continue
            }
        default:
            break;
    }
}

void main_menu () {

    short int option = -1;

    clear_screen();
    while (!is_a_valid_option(option)) { // esquanto o opção não for válida...

        printf("1. Compactar Arquivo\n");
        printf("2. Descompactar Arquivo\n");
        printf("0. Sair\n\n");
        printf("> O que deseja fazer? ");

        scanf("%hd", &option);
        getchar();

        if (!is_a_valid_option(option)) {
            clear_screen();
            printf("Leia as opções direito! u_u'\n\n");
        }

        execute_function(&option);
    }
}
