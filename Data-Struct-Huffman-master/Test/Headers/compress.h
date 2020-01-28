#ifndef compress
#define compress

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_tree.h"
#include "hash.h"

void frequency(FILE *file, int amount[]);

void print_new_file(FILE *file, hash *hash, FILE *new_file);

void find_trash(node *tree, hash *hash, unsigned short * size_trash);

void size_tree(node *tree, unsigned short *size);

void print_sixteen(unsigned short sixteen, FILE *new_file);

void print_huff_tree_in_file(node *node, FILE *new_file);

#endif
