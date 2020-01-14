#ifndef huffman_tree
#define huffman_tree

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "pq.h"

struct node {
	unsigned char charac;		//Armazena o caracter
	int priority;			//Alterar para void *priority //Armazena a prioridade
	node *left;			//Guarda o ponteiro do lado esquedo
	node *right;			//Guarda o ponteiro do lado direito
	node *next;			//Guarda o ponteiro para o próximo
};

node* create_node();
node* create_huff_node(node *left, node *right);
node* create_huff(pq *pq);
int isEmpty(node *tree);
int isLeaf(node *tree);
void size_tree(node *tree, long long int *size);
void print_huff_tree(node *node);

#endif