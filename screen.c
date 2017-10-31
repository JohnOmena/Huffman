#include <stdlib.h>
#include <ctype.h>
#include "compress.h"
#include "decompress.h"
#include "screen.h"

short int title_screen_flag = 1;

void clear_screen () {
    system("clear");
}

void bye () {

    clear_screen();
    printf("\n\n\n\n                                                  ___     \n");
    printf("                       _____          ___        /  /\\    \n");
    printf("                      /  /::\\        /__/|      /  /:/_   \n");
    printf("                     /  /:/\\:\\      |  |:|     /  /:/ /\\  \n");
    printf("                    /  /:/~/::\\     |  |:|    /  /:/ /:/_ \n");
    printf("                   /__/:/ /:/\\:|  __|__|:|   /__/:/ /:/ /\\\n");
    printf("                   \\  \\:\\/:/~/:/ /__/::::\\   \\  \\:\\/:/ /:/\n");
    printf("                    \\  \\::/ /:/     ~\\~~\\:\\   \\  \\::/ /:/ \n");
    printf("                     \\  \\:\\/:/        \\  \\:\\   \\  \\:\\/:/  \n");
    printf("                      \\  \\::/          \\__\\/    \\  \\::/   \n");
    printf("                       \\__\\/                     \\__\\/    \n");
    getchar();
}

int is_valid_option (short int option) {
    return ((option == 1) || (option == 2) || (option == 0));
}

void title_screen () {

    printf("\n\n\n");
    printf("               ___                __  __             ___    ___              \n");
    printf("              /\\_ \\    __        /\\ \\/\\ \\          /'___\\ /'___\\             \n");
    printf("              \\//\\ \\  /\\_\\    ___\\ \\ \\_\\ \\  __  __/\\ \\__//\\ \\__/             \n");
    printf("    _______     \\ \\ \\ \\/\\ \\ /' _ `\\ \\  _  \\/\\ \\/\\ \\ \\ ,__\\ \\ ,__\\    _______ \n");
    printf("   /\\______\\     \\_\\ \\_\\ \\ \\/\\ \\/\\ \\ \\ \\ \\ \\ \\ \\_\\ \\ \\ \\_/\\ \\ \\_/   /\\______\\\n");
    printf("   \\/______/     /\\____\\\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\____/\\ \\_\\  \\ \\_\\    \\/______/\n");
    printf("                 \\/____/ \\/_/\\/_/\\/_/\\/_/\\/_/\\/___/  \\/_/   \\/_/             \n\n\n\n");

    printf("                -----  Digite qualquer tecla para iniciar  -----");
    getchar();
}

void print_menu (short int *option) {

    printf("                         __ _                     __  __         \n");
    printf("                        / /(_)_ __   /\\  /\\_   _ / _|/ _|        \n");
    printf("               _____   / / | | '_ \\ / /_/ / | | | |_| |_   _____ \n");
    printf("              |_____| / /__| | | | / __  /| |_| |  _|  _| |_____|\n");
    printf("                      \\____/_|_| |_\\/ /_/  \\__,_|_| |_|          \n\n");
    printf("        ---------------------------------------------------------------\n\n");

    printf(" \t\t\t    1. Compactar Arquivo\n\n");
    printf(" \t\t\t    2. Descompactar Arquivo\n\n");
    printf(" \t\t\t    0. Sair\n\n");

    printf(" \t\t\t    Entre com uma das opções: > ");
    scanf("%hd", option);
    getchar();
}

void execute_option (short int option) {

    char decision = '*';

    switch (option) {

        case 1:
            clear_screen();
            compress_file();
            break;
        case 2:
            clear_screen();
            decompress_file();
            break;
        case 0:
            clear_screen();

            printf("   ___     __       _      \n");
            printf("  / _ \\   / _\\ __ _(_)_ __ \n");
            printf(" | | | |  \\ \\ / _` | | '__|\n");
            printf(" | |_| |  _\\ \\ (_| | | |   \n");
            printf("  \\___(_) \\__/\\__,_|_|_|   \n\n");

            printf(" Tem certeza que deseja sair? [S/N] > ");
            scanf("%c", &decision);
            decision = toupper(decision);
            getchar();

            while (!((decision == 'S') || (decision == 'N'))) {

                clear_screen();
                printf(" Entrada inválida! \n\n Entre com -S- para SIM ou -N- para NÃO > ");
                scanf("%c", &decision);
                decision = toupper(decision);
                getchar();
            }

            if (decision == 'S') {

                bye();
                exit(0);
            }
            else {
                clear_screen();
                main_menu();
            }
            break;
        default:
            break;
    }
}

void continue_or_finish () {

    char decision = '*';

    printf(" Deseja realizar mais alguma operação? [S/N] > ");
    scanf("%c", &decision);
    decision = toupper(decision);
    getchar();

    while (!((decision == 'S') || (decision == 'N'))) {

        clear_screen();
        printf(" Entrada inválida! \n\n Entre com -S- para SIM ou -N- para NÃO > ");
        scanf("%c", &decision);
        decision = toupper(decision);
        getchar();
    }

    if (decision == 'N') {
        bye();
        exit(0);
    }
    else {
        clear_screen();
        main_menu();
    }
}


void main_menu () {

    short int option = -1;

    if (title_screen_flag) {
        title_screen();
        title_screen_flag = 0;
    }

    clear_screen();
    print_menu(&option);

    while (!(is_valid_option(option))) {

        clear_screen();
        printf(" Esta opção é inválida!\n\n Entre com -1-, -2- ou -0-\n\n");
        print_menu(&option);
    }

    execute_option(option);
    continue_or_finish();
}
