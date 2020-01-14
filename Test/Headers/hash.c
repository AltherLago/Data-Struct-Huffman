#include "hash.h"

hash *create_hash () {
	hash *new_hash = (hash*) malloc(sizeof(hash));

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			new_hash->matriz[i][j] = (unsigned char *)'#';
		}
	}
	return new_hash;
}

//COLOCA NA HASH A SEQUÊNCIA DE BITS
void add_hash(hash *hash, unsigned char item, int total_bits, int sequency[]) {
	int i;
	for(i = 0; i < total_bits; i++) {
		hash->matriz[item][i] = sequency[i];	//Preenche em linha a sequência da letra
	}                                               // na posição dela na tabela ASCII
	hash->matriz[item][i] = '\0';
}

//PERCORE A ÁRVORE BUSCANDO AS FOLHAS PARA CRIAR A SEQUÊNCIA DE BITS
void map_bits(hash *hash, node *tree, int i, int for_bits[]) {
	if(isLeaf(tree)) {
		add_hash(hash, tree->charac, i, for_bits);
		return;
	}
	if(tree->left != NULL) {
		for_bits[i] = '0';				//Vai adicionar o 0 e andar para a esquerda na chamada
		map_bits(hash, tree->left, i+1, for_bits);
	}
	if(tree->right != NULL) {
		for_bits[i] = '1';				//Vai adicionar o 1 e andar para a direita na chamada
		map_bits(hash, tree->right, i+1, for_bits);
	}
}

void print_hash(hash *hash) {
	//printf("%d %d %c %c\n", '\0', '#', 48, 49); //test da table ascii
	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			if(hash->matriz[i][0] == 35){
				continue;
			}
			if(hash->matriz[i][j] != 35 && hash->matriz[i][j] != 0) {
				if(j == 0){
					printf("i:%d = %c ", i, hash->matriz[i][j]);
				}
				else{
					printf("%c ", hash->matriz[i][j]);
				}
			}
			if(hash->matriz[i][j] == 0){
				puts("");
				continue;
			}
		}
	}
}
