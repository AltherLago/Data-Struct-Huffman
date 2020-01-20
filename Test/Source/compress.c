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
        FILE *new_file = fopen("compress.txt", "wb");
        unsigned char charac;
        unsigned short *byte;

        while (fscanf(file, "%c", &charac) != EOF){
                int i;
                for (i = 0; i < 7 ; ++i) {
                        //fill_bit(byte, hash); //Seria uma função para preencher o byte
                }
        }
        //inputSenter
        puts("Saio");
}

