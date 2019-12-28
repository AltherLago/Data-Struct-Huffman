/*
1. Lista de frequência

1.1 Read the file
1.2 Count frequency      //(char[++1] -> a(55)) (unsignedchar frenquency[+=1])
1.3 Creat priority queue //(<frequency) (Hash and Queue)

2. Huffman Tree

2.1 Retira os dois nós menos frequentes
2.2 Agrupa estre dois nós em um nó pai
2.3 Adiciona o nó pai na priority queue

3. Tabela de código (Hash)

3.1 Percorre a Huffman Tree para montar o dicionário // Hash[0] = a -> 1 -> 1
com o novo código de cada símbolo

4. Codificação (Compactação)

4.1 Print arquivo Huffman
(Percorre o texto original e cria um novo arquivo substituindo
        cada letra por uma seqência binária correspodente) [shiftbit <<]

4.2 Contar e salvar o lixo nos 3 primeiros bits do cabeçalho

4.3 Salvar a árvore nos 13 bits restantes    010 = (0 - 7) / 00000000000000 = *CB*AB   | --00 0000 trash = 2 = 10

5. Decodificação (Descompactação)

5.1 Ler o texto em binário e percorrer a Huffman Tree
        (0 -> Left, 1 -> Right)
5.2 Encontrar a FOLHA imprimir no arquivo o símbolo correspondente


6. Organizar arquivos

6.1 arquivos.c -> implementação
6.2 arquivos.h -> cabeçalho

Semana 1

1. Lista de frequência

Semana 2

2. Huffman Tree

Semana 3

3. Tabela de código (Hash)

Semana 4 Semana 5

4. Codificação (Compactação)

Semana 6

5. Decodificação e 6. Organização
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 0

//função utilizada para test isolados
void test();

//Implementação do que vai ficar na main
void implementacion();

//Ler arquivo txt
void read_file();

int main(){

        //test();

        implementacion();

        return 0;
}

//função utilizada para test isolados
void test(){
}

//Implementação do que vai ficar na main
void implementacion(){
        read_file();
}

//Ler arquivo txt
void read_file() {
        char caractere[10];
        fgets(caractere, 10, stdin);
        for (int i = 0; i < 10; ++i) {
                printf("%d\n", caractere[i]);
        }
        /*
        while(scanf("%c", &caractere) != EOF){
                printf("Caractere:%c \nCount: %d: \n", caractere, i);
                ++i;
        }
         */
}