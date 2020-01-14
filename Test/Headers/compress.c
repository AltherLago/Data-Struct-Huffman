#include "compress.h"

void frequency(FILE *file, int amount[]) {
        unsigned char charac;        
        while(fscanf(file, "%c", &charac) != EOF) {// Charac é o valor do caracter na tabela ASCII,
                amount[charac] += 1;                      // adicionando a quantidade dela que existe
        }
}

//ARMAZENA O TAMANHO DA ÁRVORE E DO LIXO - OBTER O TAMANHO DO LIXO
void get_trash(node *tree, unsigned char *trash, int height) {
	if(!isEmpty(tree)) {
		if(isLeaf(tree)) {
			*trash += tree->priority * height;//Tamanho do lixo na árvore
			height += 1;				//Tamanho da árvore
		}
		get_trash(tree->left, trash, height+1);
		get_trash(tree->right, trash, height+1);
	}
}

//ESCREVE A ÁRVORE EM PRÉ-ORDEM NO ARQUIVO CARACTER POR CARACTER
void add_tree(node *tree, FILE *file) {
	if(!isEmpty(tree)) {
		if((tree->charac == '*' || tree->charac == '\\') && tree->left == NULL && tree->right == NULL) {
			fputc('\\', file);
		}
		fputc(tree->charac, file);
		add_tree(tree->left, file);
		add_tree(tree->right, file);
	}
}

unsigned char set_bit(unsigned char byte, int i) {
	unsigned char mask = 1 << i;
	return (mask | byte);
}

//RECEBE O ARQUIVO, A HASH COM OS BITS DE CADA CARACTER, O ARQUIVO A SER COMPACTADO E O TAMANHO DA ÁRVORE
void write_file(FILE *file, hash *hash, FILE *compressed, long long int sizeTree) {
	unsigned char charac, byte_file = 0;
	int i, j = 0, size = 0, bits = 0, byte = 7;
	rewind(compressed);
	fseek(compressed, 2 + sizeTree, SEEK_SET);
	while(fscanf(file, "%c", &charac) != EOF) {
		j = 0;
		while(hash->matriz[charac][j] != (unsigned char *)'\0') {
			if(hash->matriz[charac][j] != (unsigned char *)'0') {
				byte_file = set_bit(byte_file, byte);
			}
			bits += 1;
			byte -= 1;
			j += 1;

			if(bits == 8) {
				fprintf(compressed, "%c", byte_file);
				byte_file = 0;
				byte = 7;
				bits = 0;
			}
		}
	}
	if(bits != 0) {
		fprintf(compressed, "%c", byte_file);
	}
	fclose(compressed);
}
