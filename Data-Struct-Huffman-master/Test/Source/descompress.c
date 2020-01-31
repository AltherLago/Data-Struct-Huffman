#include "../Headers/descompress.h"
#define DEBUG 1

node_tree *new_node(unsigned short charac, node_tree *left, node_tree *right) {
    node_tree *new = (node_tree *) malloc(sizeof(node_tree));
    new->charac = charac;
    new->left = left;
    new->right = right;

    return new;
}

int isDempty(node_tree *tree) {
	return (tree == NULL);
}

void print_dec_tree(node_tree *node) {
	if(isDempty(node)) {
		printf("()");
		return;
	}
	else {
		printf("(%d", node->charac);
		print_dec_tree(node->left);
		print_dec_tree(node->right);
		printf(")");
	}
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

node_tree *get_tree(FILE *in_file, unsigned short size_tree, int *i, node_tree *tree) {
    if(i != size_tree) {
        unsigned char c = getc(in_file);
        i += 1;
        if(c == '*') {
            tree = new_node(c, NULL, NULL);
            tree->left = get_tree(in_file, size_tree, &i, tree->left);
            tree->right = get_tree(in_file, size_tree, &i, tree->right);
        }
        else {
            if(c == 92) {
                i += 1;
                c = getc(in_file);
                tree = new_node(c, NULL, NULL);
                i += 1;
            } 
            else {
                tree = new_node(c, NULL, NULL);
                i += 1;
            }
        }
    }
    return tree;
}

