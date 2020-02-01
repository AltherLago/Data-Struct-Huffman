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

node_tree *get_tree(FILE *in_file, unsigned short size_tree, int *i, node_tree *tree);

void print_dec_tree(node_tree *node);

int isDempty(node_tree *tree);

int is_bit_set(unsigned char character, int position);

int isDLeaf(node_tree *tree);

void write_file(FILE *in_file, FILE *descompress_file,unsigned short size_trash,unsigned short size_tree,node_tree *huff);

#endif
