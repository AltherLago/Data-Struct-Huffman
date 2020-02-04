
#include "../Headers/hash.h"


//CRIAR A HASH COLOANDO # EM TODOS OS ESPAÇOS
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
        for(i = 0; i < total_bits + 1; i++) {
                hash->matriz[item][i + 1] = (void *) sequency[i];
                //Preenche em linha a sequência do caminho da letra
                //na posição dela na tabela ASCII
        }
        hash->matriz[item][i] = '\0';
}

//PERCORRE A ÁRVORE BUSCANDO AS FOLHAS PARA CRIAR A SEQUÊNCIA DE BITS
void map_bits(hash *hash, node *tree, int i, int for_bits[]) {
        if(isLeaf(tree)) {
                hash->matriz[tree->charac][0] = (void *) (i + '0'); //Adiciona o tamanho do caminho
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
