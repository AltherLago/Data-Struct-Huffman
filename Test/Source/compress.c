#include "../Headers/compress.h"

#define DEBUG 1

void frequency(FILE *file, int amount[]) {
        unsigned char charac;        
        while(fscanf(file, "%c", &charac) != EOF) {// Charac é o valor do caracter na tabela ASCII,
                amount[charac] += 1;                      // adicionando a quantidade dela que existe
        }
}

void print_new_file(FILE *file, hash *hash){
        puts("Entro");
        FILE *f = fopen("compress.txt", "wb");
        unsigned char charac;
        while (fscanf(file, "%c", &charac) != EOF){
                printf("Nao entro");
                if(DEBUG){
                        printf("Charac: %c\n", charac);
                }
                break;
        }
        puts("Saio");
}

