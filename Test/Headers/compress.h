#ifndef compress
#define compress

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_tree.h"
#include "hash.h"

void frequency(FILE *file, int amount[]);

void total_bits(node *tree, hash *hash, unsigned short * size_trash);

void mod_trash(unsigned short * size_trash);

void size_tree(node *tree, unsigned short *size);

void print_header(unsigned short sixteen, FILE *new_file);

void print_huff_tree_in_file(node *node, FILE *new_file);

void print_new_file(FILE *file, hash *hash, FILE *new_file);

#endif
