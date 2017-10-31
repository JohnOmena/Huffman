
/*
 * Limpa a tela do terminal. Sem parâmetros. Não retorna nada.
 */
void clear_screen ();

/*
 * Exibe uma mensagem de encerramento do programa. Sem parâ-
 * metros. Não retorna nada.
 */
void bye ();

/*
 * Verifica se a opção é válida. Recebe um inteiro que é a
 * opção do menu do usuário. Retorna 1 caso a opção seja
 * vpalida e 0 caso contrário.
 */
int is_valid_option (short int option);

/*
 * Imprime a tela de título do programa. Sem parâmetros.
 * Não retorna nada.
 */
void title_screen ();

/*
 * Imprime o menu principal. Recebe um ponteiro int para
 * a opção a ser digitada pelo usuário. Não retorna nada.
 */
void print_menu (short int *option);

/*
 * Executa a função escolhida pelo usuário. Recebe um
 * inteiro que é a opção escolhida pelo usuário. Não
 * retorna nada.
 */
void execute_option (short int option);

/*
 * Ao fim de cada funcionalidade do programa, pergunta
 * se o usuário deseja realizar mais alguma tarefa ou
 * não. Sem parâmetros. Não retorna nada.
 */
void continue_or_finish ();

/*
 * Chama as funções para exibição do menu do programa.
 * Sem parâmetros. Não retorna nada.
 */
void main_menu ();
