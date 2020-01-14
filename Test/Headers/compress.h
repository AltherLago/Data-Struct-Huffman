#ifndef compress
#define compress

#include "huff_tree.h"
#include "hash.h"

void frequency(FILE *file, int amount[]);
void get_trash(node *tree, unsigned char *trash, int height);
void add_tree(node *tree, FILE *file);
unsigned char set_bit(unsigned char byte, int i);
void write_file(FILE *file, hash *hash, FILE *compressed, long long int sizeTree);

#endif