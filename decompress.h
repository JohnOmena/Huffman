/*
 * Verifica se o arquivo digitado pelo usuário tem extensão
 * .huff ou não. Recebe um ponteiro para a string do nome
 * do arquivo passado pelo usuário. Retorna 1 caso seja um
 * arquivo .huff e 0 caso contrário.
 */
int is_huff_file (char *file_name);

/*
 * Escreve o arquivo descompactado a partir do arquivo com-
 * pactado e da Árvore de Huffman. Recebe um ponteiro para
 * o arquivo compactado, um ponteirp para o arquivo de des-
 * tino, um ponteiro para o nó raíz da Árvore de Huffman e
 * um inteiro que é o tamanho da Árvore de Huffman. Não re-
 * torna nada.
 */
void write_original_file (FILE *compressed_file, FILE *original_file, h_tree *tree, int trash_size);

/*
 * Chama todas as funções necessárias para a descompactação
 * do arquivo .huff. Sem parâmetros. Não retorna nada.
 */
void decompress_file ();
