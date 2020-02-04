#include <stdlib.h>
#include <stdio.h>
#include "Headers/pq.h"
#include "Headers/huff_tree.h"
#include "Headers/hash.h"
#include "Headers/compress.h"
#include "Headers/descompress.h"

void menu() {
        system("clear");
        printf("\n");
        printf("\n\t\t\t###       ### ###       ### ############# ############# #####                #####    #######    #####          ###");
        printf("\n\t\t\t###       ### ###       ### ############# ############# ######              ######   #########   ######         ###");
        printf("\n\t\t\t###       ### ###       ### ###           ###           ### ###            ### ###  ####   ####  ### ###        ###");
        printf("\n\t\t\t###       ### ###       ### ###           ###           ###  ###          ###  ### ####     #### ###  ###       ###");
        printf("\n\t\t\t###       ### ###       ### ###           ###           ###   ###        ###   ### ###       ### ###   ###      ###");
        printf("\n\t\t\t############# ###       ### ############  ############  ###    ###      ###    ### ############# ###    ###     ###");
        printf("\n\t\t\t############# ###       ### ############  ############  ###     ###    ###     ### ############# ###     ###    ###");
        printf("\n\t\t\t###       ### ###       ### ###           ###           ###      ###  ###      ### ###       ### ###      ###   ###");
        printf("\n\t\t\t###       ### ####     #### ###           ###           ###       ######       ### ###       ### ###       ###  ###");
        printf("\n\t\t\t###       ###  ####   ####  ###           ###           ###        ####        ### ###       ### ###        ### ###");
        printf("\n\t\t\t###       ###   #########   ###           ###           ###                    ### ###       ### ###         ######");
        printf("\n\t\t\t###       ###    #######    ###           ###           ###                    ### ###       ### ###          #####\n\n\n");
}

int main() {
        menu();

        while(1) {
                printf("1 - Compress\n");
                printf("2 - Descompress\n");
                printf("3 - Quit\n\n");

                int option, amount[256] = {0};
                char name[256];
                scanf("%d", &option);

                if(option == 1) {
                        printf("\nFILE NAME: ");
                        scanf(" %[^\n]", name);
                        printf("\n");

                        FILE *file = fopen(name, "rb");

                        if(file == NULL) {
                                printf("Invalid file.\n");
                                break;
                        }

                        frequency(file, amount);

                        pq *pq_amount = create_pq();
                        pq_amount     = enqueue_amount(amount);

                        node *tree = create_huff(pq_amount);

                        hash *hash = create_hash();

                        int for_bits[256];
                        memset(for_bits, 0, 256);
                        map_bits(hash, tree, 0, for_bits);

                        unsigned short trash   = 0;
                        total_bits(tree, hash, &trash);
                        mod_trash (&trash);

                        unsigned short size    = 0;
                        size_tree(tree, &size);

                        unsigned short header  = 0;
                        complete_header(trash, size, &header);

                        rewind(file); // reler o arquivo do início
                        FILE *compress_file = fopen("compress.huff", "wb");
                        print_header(header, compress_file);
                        print_huff_tree_in_file(tree, compress_file);
                        print_new_file(file, hash, compress_file);

                        break;
                }
                else if(option == 2) {
                        char format[20],
                                input_file[256];
                        printf("Input file name: \nEx.: file.huff\n\n");
                        scanf("%s", input_file);

                        FILE *in_file = fopen(input_file, "rb");

                        if(in_file == NULL) {
                                printf("Invalid file.\n");
                                break;
                        }
                        printf("Output format: \nEx.: png\n\n");
                        scanf("%s", format);

                        unsigned short size_tree;
                        unsigned short size_trash;
                        read_header(in_file, &size_tree, &size_trash);

                        node_tree *dec_tree;
                        unsigned char t_array[size_tree];
                        int count  = 0;
                        dec_tree   = build_tree(in_file, size_tree, &count, dec_tree);

                        unsigned char out_file[256];
                        strcpy(out_file, "descompress.");
                        strcat(out_file, format);

                        FILE *descompress_file = fopen(out_file, "wb");
                        write_file(in_file, descompress_file, size_trash, size_tree, dec_tree);

                        fclose(in_file);
                        fclose(descompress_file);

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
