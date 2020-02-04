#include "../Headers/descompress.h"

void read_header(FILE *in_file, unsigned short *size_tree, unsigned short *size_trash) {
    unsigned char byte1;
    unsigned char byte2;
    int i;
    //pega o cabeçallho
    for(i = 0; i < 2; i++) {
        if(i == 0) fscanf(in_file, "%c", &byte1);
        if(i == 1) fscanf(in_file, "%c", &byte2);
    }

    //size_trash recebe o tamanho do lixo
    *size_trash   = byte1;
    *size_trash >>= 5;
    //size_tree recebe o tamanho da árvore
    *size_tree   = byte1;
    *size_tree <<= 11;
    *size_tree >>= 3;
    *size_tree  |=  byte2;
}

node_tree *build_tree(FILE *in_file, unsigned short size_tree, int *i, node_tree *tree) {
    //cria a árvore de forma recursiva
    if((unsigned short) i != size_tree) {
        unsigned char charac = getc(in_file);
        i += 1;
        if(charac == '*') {
            tree        = new_node(charac, NULL, NULL);
            tree->left  = build_tree(in_file, size_tree, i, tree->left);
            tree->right = build_tree(in_file, size_tree, i, tree->right);
        }
        else {
            if(charac == 92) {
                i   += 1;
                charac     = getc(in_file);
                tree = new_node(charac, NULL, NULL);
                i   += 1;
            }
            else {
                tree = new_node(charac, NULL, NULL);
                i   += 1;
            }
        }
    }
    return tree;
}

node_tree *new_node(unsigned short charac, node_tree *left, node_tree *right) {
    node_tree *new = (node_tree *) malloc(sizeof(node_tree));
    new->charac    = charac;
    new->left      = left;
    new->right     = right;

    return new;
}

int is_bit_set(unsigned char charac, int position) {
	unsigned short mask = 1;
    mask <<= position - 1;
    mask &= charac;
	return(mask);
}

int isDLeaf(node_tree *tree) {
	return ((tree->left == NULL) && (tree->right == NULL));
}

void write_file(FILE *in_file, FILE *descompress_file,unsigned short size_trash,unsigned short size_tree,node_tree *huff) {
    unsigned char charac, last;
    unsigned char last_byte;
    int total_bytes;

    fseek(in_file, -1, SEEK_END);
    last_byte = getc(in_file);
    total_bytes = ftell(in_file);
    fseek(in_file, (2+size_tree), 0);
    int i = 2 + size_tree;
    int free;
    node_tree *current = huff;

    while(i < total_bytes - 1) {
        charac = getc(in_file);
        free   = 8;

        while(free > 0) {
            if(is_bit_set(charac,free) != 0) {       
                if(current->right != NULL)
                    current = current->right;
            }
            else {
                if(current->left != NULL)
                    current = current->left;
            }
            if(isDLeaf(current)) {
                fprintf(descompress_file,"%c",current->charac);
                current = huff;
            }
            
            free--;
        }
        i++;
    }

    charac     = getc(in_file);
    size_trash = 8 - (size_trash % 8);
    free       = 8;

    while((free > 0) && (size_trash > 0)) {
        if(is_bit_set(charac,free) != 0) {       
            if(current->right != NULL)
                current = current->right;
        }
        else {
            if(current->left != NULL)
                current = current->left;
        }
        if(isDLeaf(current)) {
            fprintf(descompress_file,"%c",current->charac);
            current = huff;
        }
        
        free--;
        size_trash--;
    }    
}

int isDempty(node_tree *tree) {
	return (tree == NULL);
}
