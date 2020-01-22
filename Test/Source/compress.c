#include "../Headers/compress.h"

#define DEBUG 1

//CONTA A FREQUÊNCIA DE CADA CARACTER
void frequency(FILE *file, int amount[]) {
        unsigned char charac;        
        while(fscanf(file, "%c", &charac) != EOF) {// Charac é o valor do caracter na tabela ASCII,
                amount[charac] += 1;                      // adicionando a quantidade dela que existe
        }
}

//IMPRIME O ARQUIVO COMPRESSO
void print_new_file(FILE *file, hash *hash){
        rewind(file); // reler o arquivo do início
        FILE *new_file = fopen("compress.huff", "wb");
        unsigned char charac;
        unsigned char byte = 0;
        int free           = 8;
        int fill           = 0;

        while (fscanf(file, "%c", &charac) != EOF){
                fill     = (int) (int*) (hash->matriz[charac][0] - '0');
                int i    = 1; //DEBUG do passo a passo

                while(fill > 0){
                        if(free == 0){
                                fputc(byte, new_file);
                                free = 8;
                                byte = 0;
                        }
                        if(hash->matriz[charac][i] == (unsigned char*) '0'){
                                byte <<= 1;
                                free--;
                        } else if (hash->matriz[charac][i] == (unsigned char*) '1'){
                                byte <<= 1;
                                byte++;
                                free--;
                        }else{
                                break;
                        }

                        if(DEBUG){
                                printf("charac: %c i: %d byte: %d fill: %d free: %d\n", charac, i, byte, fill, free);
                        }

                        i++;
                        fill--;
                }
        }
        if(free < 8){
                fputc(byte, new_file); //imprimir último byte compresso
        }
}

//CALCULA O TAMANHO DE BITS PRESENTE NO ARQUIVO
void find_trash(node *tree, hash *hash, unsigned short *size_trash){
        if(isLeaf(tree)){
                *size_trash += ( (int) (int*) hash->matriz[tree->charac][0] - '0' ) * tree->priority;
        }
        else if (tree->charac == '*'){
                find_trash(tree->left, hash, size_trash);
                find_trash(tree->right, hash, size_trash);
        }
}

//ME DIZ A QUANTIDADE DE ELEMENTOS
void size_tree(node *tree, unsigned short *size){
        if(isLeaf(tree)){
                *size += 1;
                if (tree->charac == '*' || tree->charac == 92){
                        *size += 1;
                }
        }
        else if(!isEmpty(tree)){
                *size += 1;
                size_tree(tree->left, size);
                size_tree(tree->right, size);
        }
}