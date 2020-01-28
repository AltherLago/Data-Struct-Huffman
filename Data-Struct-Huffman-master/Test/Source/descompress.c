#include "../Headers/descompress.h"
#define DEBUG 1

void read_header(FILE *in_file,unsigned short *size_tree,unsigned short *size_trash)
{
    unsigned char byte1;
    unsigned char byte2;

    int i;

    for(i = 0;i < 2;i++)
    {
        if(i == 0) fscanf(in_file,"%c",&byte1);
        if(i == 1) fscanf(in_file,"%c",&byte2);
    }
    
    if(DEBUG)
    {
        printf("byte1 : %d\n",byte1);
        printf("byte2 : %d\n",byte2);
    }

    *size_trash = byte1;
    *size_trash >>= 5;

    *size_tree = byte1;
    *size_tree <<= 11;
    *size_tree >>= 3;
    *size_tree |=  byte2;

    if(DEBUG) {
        printf("size = %hu, trash = %hu\n", *size_tree, *size_trash);
    }
}