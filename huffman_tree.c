struct huffman_tree {
    h_tree left;     // filho da esquerda
    h_tree right;    // filho da direita
    h_tree next;     // ponteiro para o próximo nó da lista (priority queue)
    u_int frequency; // frequência do byte
    u_char byte;     // byte
};

h_tree* create_empty_huffman_tree (h_tree *tree) {
    return NULL;
}

h_tree* create_huffman_tree (u_char byte, u_int frequency, h_tree *left, h_tree *right) {

}
