#include "../Headers/descompress.h"
#define DEBUG 1

node_tree *new_node(unsigned short charac, node_tree *left, node_tree *right) {
    node_tree *new = (node_tree *) malloc(sizeof(node_tree));
    new->charac = charac;
    new->left = left;
    new->right = right;

    return new;
}

void read_header(FILE *in_file, unsigned short *size_tree, unsigned short *size_trash) {
    unsigned char byte1;
    unsigned char byte2;

    int i;

    for(i = 0; i < 2; i++) {
        if(i == 0) fscanf(in_file, "%c", &byte1);
        if(i == 1) fscanf(in_file, "%c", &byte2);
    }
    
    if(DEBUG) {
        printf("byte1 : %d\n", byte1);
        printf("byte2 : %d\n", byte2);
    }

    *size_trash = byte1;
    *size_trash >>= 5;

    *size_tree = byte1;
    *size_tree <<= 11;
    *size_tree >>= 3;
    *size_tree |=  byte2;

    if(DEBUG) {
        printf("size = %hu, trash = %hu\n", *size_tree, *size_trash);
    }
}

node_tree *build_tree(unsigned short tree_array, unsigned short size_tree) {
    if(tree_array == '*') {
        //node_tree left = build_tree(tree_array + 1, size_tree);
        //build_tree(tree_array + 1, size_tree);

    }
    else if(tree_array == 92) {
        tree_array += 1;
    }

}

unsigned short get_tree(FILE *in_file, unsigned short size_tree) {
    int *tree_array;
    tree_array = (unsigned short *) malloc(sizeof(unsigned short) * (size_tree));

    for(int i = 0; i < size_tree; i++) {
        tree_array[i] = getc(in_file);
        printf("%d\n", tree_array[i]);
    }

    return tree_array;
}
