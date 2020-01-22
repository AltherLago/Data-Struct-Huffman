#include "../Headers/compress.h"

#define DEBUG 1

void frequency(FILE *file, int amount[]) {
        unsigned char charac;        
        while(fscanf(file, "%c", &charac) != EOF) {// Charac é o valor do caracter na tabela ASCII,
                amount[charac] += 1;               // adicionando a quantidade dela que existe
        }
}

void print_new_file(FILE *file, hash *hash){
        rewind(file); // reler o arquivo do início
        FILE *new_file = fopen("compress.huff", "wb");
        unsigned char charac;
        unsigned char byte = 0;
        int free           = 8;
        int fill           = 0;


        while (fscanf(file, "%c", &charac) != EOF){
                fill     = (int) (int*) (hash->matriz[charac][0] - '0');
                int i    = 1;

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
        //inputSenter
        fputc(byte, new_file); //imprimir último byte compresso
}

void find_trash(node *tree, hash *hash, unsigned short *size_trash){
        if(isLeaf(tree)){
                *size_trash += ( (int) (int*) hash->matriz[tree->charac][0] - '0' ) * tree->priority;
        }
        else if (tree->charac == '*'){
                find_trash(tree->left, hash, size_trash);
                find_trash(tree->right, hash, size_trash);
        }
}
