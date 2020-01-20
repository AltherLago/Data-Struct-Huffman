//gcc -g main.c pq.c huff_tree.c hash.c compress.c -o huff -w
#include <stdlib.h>
#include <stdio.h>
#include "Headers/pq.h"
#include "Headers/huff_tree.h"
#include "Headers/hash.h"
#include "Headers/compress.h"

#define DEBUG 1

int main() {
        printf("\n\n\nENTREI\n\n\n");
	while(1) {
		printf("1 - Compress\n");
		printf("2 - Descompress\n");
		printf("3 - Quit\n");
		
		int option, amount[256] = {0};
		char name[256];
		scanf("%d", &option);

		if(option == 1) {
			printf("FILE NAME: ");
			scanf(" %[^\n]", name);
			printf("\n\n");

			FILE *file = fopen(name, "rb");

			if(file == NULL) {
				printf("Invalid file.\n");
				break;
			}

			frequency(file, amount);

			pq *pq_amount = create_pq();
			pq_amount     = enqueue_amount(amount);

			if(DEBUG){
                                print_pq(pq_amount);
                                printf("\n");
			}

                        node *tree = create_huff(pq_amount);

                        hash *hash = create_hash();

                        int for_bits[256];
                        memset(for_bits, 0, 256);
                        map_bits(hash, tree, 0, for_bits);

                        if(DEBUG) {
                                puts("");
                                print_huff_tree(tree);
                                printf("\n\n");
                                print_hash(hash);
                                printf("\n");
                        }

                        //TODO
                        // 1 - Preencher o byte com o caracter corresponte
                        // 2 - Completando o byte imprime em um novo arquivo
                        // 3 - pegar o tamanho do lixo e fazer o cabeçalho

                        print_new_file(file, hash);

                        break;
		}
		else if(option == 2) {
			char format[20], input_file[256];
			printf("Input file name: (Ex.: file.huff\n\n");
			scanf("%s", input_file);
			printf("Output format: (Ex.: png)\n\n");
			scanf("%s", format);

			FILE *in_file = fopen(input_file, "rb");

			if(in_file == NULL) {
				printf("Invalid file.\n");
				break;
			}



			break;
		}
		else if(option == 3) {
			break;
		}
		else {
			printf("Invalid option\n");
		}
	}

	return 0;
}
/*
 * main: main.c compress.o hash.o huff_tree.o pq.o
    gcc -o main main.c

compress.o: compress.c
    gcc -c compress.c -o compress.o

hash.o: hash.c
    gcc -c hash.c -o hash.o

huff_tree: huff_tree.c
    gcc -c huff_tree.c -o huff_tree.o

pq: pq.c
    gcc -c huff_tree.c -o huff_tree.o

HEADERS = compress.h hash.h huff_tree.h pq.h
OBJECTS = main.o compress.o hash.o huff_tree.o pq.o

default: main

%.o: %.c $(HEADERS)
    gcc -c $< -o $@

program: $(OBJECTS)
    gcc $(OBJECTS) -o $@

clean:
    -rm -f $(OBJECTS)
    -rm -f main

    HEADERS = Headers/compress.h Headers/hash.h Headers/huff_tree.h Headers/pq.h
OBJECTS = compress.o hash.o huff_tree.o pq.o

default: main

%.o: %.c $(HEADERS)
    gcc -c $< -o $@

main: $(OBJECTS)
    gcc $(OBJECTS) -o $@

clean:
    -rm -f $(OBJECTS)
    -rm -f main
 */
