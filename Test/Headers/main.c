//gcc -g main.c pq.c huff_tree.c hash.c compress.c -o huff -w
#include "pq.h"
#include "huff_tree.h"
#include "hash.h"
#include "compress.h"

#define DEBUG 0

int main() {
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
			pq_amount = enqueue_amount(amount);
			
			node *tree = create_huff(pq_amount);

			hash *hash = create_hash();

			if(DEBUG) {
				print(tree);
				printf("\n");
				print_hash(hash);
				printf("\n");
			}

			int for_bits[256];
			memset(for_bits, 0, 256);
			map_bits(hash, tree, 0, for_bits);

			long long int size  = 0;
			unsigned char trash = 0;

			size_tree(tree, &size);

//------------------------------------------------------
			int bytes[2] = {0};
			get_trash(tree, &trash, 0);//trash é o tamanho total de bits do arquivo
			trash = 8 - (trash % 8);

			if(trash == 8) {
				trash = 0;
			}
			bytes[0] = trash << 5;
			bytes[0] |= size >> 8;
			bytes[1] = size;

			FILE *compressed = fopen("file.huff", "wb");

			fprintf(compressed, "%c%c", bytes[0], bytes[1]);
			add_tree(tree, compressed);
			rewind(file);
			write_file(file, hash, compressed, size);
			fclose(file);

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
