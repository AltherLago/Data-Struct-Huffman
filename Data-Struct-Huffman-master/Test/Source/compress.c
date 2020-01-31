#include "../Headers/compress.h"

#define DEBUG 0

//CONTA A FREQUÊNCIA DE CADA CARACTER
void frequency(FILE *file, int amount[]) {
        unsigned char charac;        
        while(fscanf(file, "%c", &charac) != EOF) {// Charac é o valor do caracter na tabela ASCII,
                amount[charac] += 1;                      // adicionando a quantidade dela que existe
        }
        //amount[10] -= 1;
}

//CALCULA O TOTAL DE BITS PRESENTE NO ARQUIVO
void total_bits(node *tree, hash *hash, unsigned short *size_trash){
        if(isLeaf(tree)){
                int size_way           = (int) hash->matriz[tree->charac][0] - '0';
                int number_repetitions = (int) tree->priority;
                *size_trash           +=  size_way * number_repetitions;
        }
        else if (tree->charac == '*'){
                total_bits(tree->left, hash, size_trash);
                total_bits(tree->right, hash, size_trash);
        }
}

//CALCULA O TAMANHO DO LIXO
void mod_trash(unsigned short *size_trash){
        *size_trash = 8 - (*size_trash % 8) ;
        if(*size_trash == 8) {
                *size_trash = 0;
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
//PREENCHE O CABEÇALHO
void complete_header(unsigned short trash, unsigned short size, unsigned short *header){
        *header   = trash;
        *header <<= 13;
        *header  |= size;
}

//IMPRIME O CABEÇALHO NO ARQUIVO COMPRESSO
void print_header(unsigned short sixteen, FILE *new_file){
        unsigned char byte2 = (unsigned char) sixteen;
        sixteen           >>= 8;
        unsigned char byte1 = (unsigned char) sixteen;
        if(DEBUG){
                printf("Sixteen_1: %d", byte1);
                printf("\nSixteen_2: %d\n\n", byte2);
        }
        fputc(byte1, new_file);
        fputc(byte2, new_file);
}

//IMPRIME O ARQUIVO COMPRESSO
void print_new_file(FILE *file, hash *hash, FILE *new_file){

        unsigned char charac;
        unsigned char byte = 0;
        int free           = 8;
        int fill           = 0;
        int size_way       = 0;

        while (fscanf(file, "%c", &charac) != EOF){
                size_way = (int) (int*) (hash->matriz[charac][0] - '0');
                fill     = size_way;
                int i    = 1; //count position

                while(fill > 0){
                        if(free == 0){
                                fputc(byte, new_file);
                                free = 8;
                                byte = 0;
                        }
                        if(hash->matriz[charac][i] == (unsigned char *) '0'){
                                byte <<= 1;
                                free--;
                        } else if (hash->matriz[charac][i] == (unsigned char *) '1'){
                                byte <<= 1;
                                byte++;
                                free--;
                        } else{
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
                if(DEBUG){
                        printf("\nlast byte: %d\n", byte);
                }
                byte <<= free;
                fputc(byte, new_file); //imprimir último byte compresso
        }
        fclose(new_file);
        fclose(file);
}
