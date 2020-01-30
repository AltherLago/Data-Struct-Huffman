#ifndef descompress
#define descompress

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_tree node_tree;

struct node_tree {
    node_tree *left;
    node_tree *right;
    unsigned short charac;
};

void read_header(FILE *in_file, unsigned short *size_tree, unsigned short *size_trash);

node_tree *new_node(unsigned short charac, node_tree *left, node_tree *right);

node_tree *build_tree(unsigned short tree_array, unsigned short size_tree);

unsigned short get_tree(FILE *in_file, unsigned short size_tree);

#endif
