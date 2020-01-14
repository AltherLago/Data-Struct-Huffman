#ifndef hash_table
#define hash_table

#include "huff_tree.h"

typedef struct hash hash;

struct hash {
	void *matriz[256][256];
};

hash *create_hash ();
void add_hash(hash *hash, unsigned char item, int total_bits, int sequency[]);
void map_bits(hash *hash, node *tree, int i, int for_bits[]);
void print_hash(hash *hash);

#endif