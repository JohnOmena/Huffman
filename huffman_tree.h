typedef struct huffman_tree h_tree;

h_tree* create_empty_huffman_tree (h_tree *tree);

h_tree* create_huffman_tree (u_char byte, u_int frequency, h_tree *left, h_tree *right);
