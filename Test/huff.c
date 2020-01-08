//gcc -g huff.c -o huff -w

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define DEBUG 1

typedef struct node node;
typedef struct pq pq;
typedef struct hash hash;
//typedef unsigned char un_char;

struct node {
	unsigned char charac;		//Armazena o caracter
	int priority;			//Alterar para void *priority //Armazena a prioridade
	node *left;			//Guarda o ponteiro do lado esquedo
	node *right;			//Guarda o ponteiro do lado direito
	node *next;			//Guarda o ponteiro para o próximo
};

struct pq {
	int size;			//Armazena o tamanho da lista de prioridade
	node *head;			//Guarda o nó da cabeça da lista de prioridade
};

struct hash {
	void *matriz[256][256];
};


pq* create_pq() {
	pq* new_queue = (pq*) malloc(sizeof(pq));
	new_queue->head = NULL;
	new_queue->size = 0;
	return new_queue;
}

node* create_node() {
	node* new_node     = (node*) malloc(sizeof(node));
	new_node->priority = 0;
	new_node->left     = NULL;
	new_node->right    = NULL;
	new_node->next     = NULL ;
	return new_node;
}

//Cria e retorna o nó da "pré" árvore
node* c_tree(unsigned char charac, int amount, node *left, node *right) {
	node *tree     = (node*) malloc(sizeof(node));
	tree->charac   = charac;
	tree->priority = amount;
	tree->next     = NULL;
	tree->left     = left;
	tree->right    = right;

	return tree;
}

hash *create_hash () {
	hash *new_hash = (hash*) malloc(sizeof(hash));

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			new_hash->matriz[i][j] = (unsigned char *)'#';
		}
	}
	return new_hash;
}

//CRIA A FILA EM ORDEM CRESCENTE
void enqueue(pq *pq, node *tree) {//---Sugiro mudar os nomes das variáveis...(p = previus e c = current)
	node *aux = tree;

	if(pq->size == 0) { //Primeiro elemento da fila vazia
		pq->size += 1;
		aux->next = pq->head;
		pq->head  = aux;
	}
	else {
		pq->size += 1;
		node *c   = pq->head;
		node *p   = NULL;

		while((c != NULL)
		      && (c->priority < aux->priority)){
                        //Depois de feita a soma dos
                        // dois menores, se forem maior
                        // do que o next da fila aqui
                        // será feita a troca de posição
			p = c;
			c = c->next;
		}
		if(p == NULL) {
			aux->next = pq->head;
			pq->head  = aux;
			return;
		}
		p->next   = aux;
		aux->next = c;
	}
}

//PROCURA OS CARACTERES E SUAS FREQUENCIAS E MANDA PARA COLOCA-LOS EM FILA
pq* enqueue_amount(int amount[]) {
	pq *pq_new   = (pq*) malloc(sizeof(pq));
	pq_new->head = NULL;
	node* new_node;

        //Quando achar algo diferente de 0, i será o caracter e amount[i] será sua frequência
        //Já cria em formato de árvore com os ponteiros para esquerda e direita
        //Coloca na fila
	for(int i = 0; i < 256; i++) {
		if(amount[i]) {
			new_node = c_tree(i, amount[i], NULL, NULL);
			enqueue(pq_new, new_node);
		}
	}

	return pq_new;
}

//REMOVE O PRIMEIRO ELEMENTO DA FILA
node *dequeue(pq *pq) {
	node *aux = pq->head;
	pq->head  = pq->head->next;
	pq->size -= 1;
	return aux;
}

//CONSTRÓI A ÁRVORE COM A SOMA DOS CARACTERES DE MENOR FREQUÊNCIA E OS COLOCA COMO FOLHAS
node *create_huff_node(node *left, node *right) {
	node *huff     = (node*) malloc(sizeof(node));
	huff->priority = left->priority + right->priority;//Soma dos dois de menor frequência
	huff->left     = left;
	huff->right    = right;
	huff->charac   = '*';
	huff->next     = NULL;

	return huff;
}

//PEGA OS 2 CARACTERES DE MENOR FREQUÊNCIA E COLOCA A SOMA DELES NOVAMENTE NA FILA
node *create_huff(pq *pq) {
	node *huff = create_node();
	while (pq->size > 1) {
		node *left  = dequeue(pq);		    //Pega o primeiro elemento da fila que é de menor frequência
		node *right = dequeue(pq);		    //				||
		huff        = create_huff_node(left, right);//Manda os dois menores para formar um novo nó pai e eles
		enqueue(pq, huff);			    // serão folhas
	}                                                   //Coloca em fila a cada parte da árvore até que sobre
	return pq->head;                                    // somente a raiz
}

//VERIFICA SE A ÁRVORE ESTÁ VAZIA
int isEmpty(node *tree) {
	return (tree == NULL);
}

//VERIFICA SE O NÓ É UMA FOLHA
int isLeaf(node *tree) {
	return ((tree->left == NULL) && (tree->right == NULL));
}

//SALVA O TAMANHO DA ÁRVORE EM PRÉ-ORDEM
void size_tree(node *tree, long long int *size) {
	if(isEmpty(tree)) {
		return;
	}
	if(isLeaf(tree)) {
		if(tree->charac == '*' || tree->charac == '\\') {
			*size += 1;
		}
	}
	*size += 1;
	size_tree(tree->left, size);
	size_tree(tree->right, size);
}

//COLOCA NA HASH A SEQUÊNCIA DE BITS
void add_hash(hash *hash, unsigned char item, int total_bits, int sequency[]) {
	int i;
	for(i = 0; i < total_bits; i++) {
		hash->matriz[item][i] = sequency[i];	//Preenche em linha a sequência da letra
	}                                               // na posição dela na tabela ASCII
	hash->matriz[item][i] = '\0';
}

//PERCORE A ÁRVORE BUSCANDO AS FOLHAS PARA CRIAR A SEQUÊNCIA DE BITS
void map_bits(hash *hash, node *tree, int i, int for_bits[]) {
	if(isLeaf(tree)) {
		add_hash(hash, tree->charac, i, for_bits);
		return;
	}
	if(tree->left != NULL) {
		for_bits[i] = '0';				//Vai adicionar o 0 e andar para a esquerda na chamada
		map_bits(hash, tree->left, i+1, for_bits);
	}
	if(tree->right != NULL) {
		for_bits[i] = '1';				//Vai adicionar o 1 e andar para a direita na chamada
		map_bits(hash, tree->right, i+1, for_bits);
	}
}


//ARMAZENA O TAMANHO DA ÁRVORE E DO LIXO - OBTER O TAMANHO DO LIXO
void get_trash(node *tree, unsigned char *trash, int height) {
	if(!isEmpty(tree)) {
		if(isLeaf(tree)) {
			*trash += tree->priority * height;
			height += 1;
		}
		get_trash(tree->left, trash, height+1);
		get_trash(tree->right, trash, height+1);
	}
}

//ESCREVE A ÁRVORE EM PRÉ-ORDEM NO ARQUIVO
void put_tree(node *tree, FILE *file) {
	if(!isEmpty(tree)) {
		if((tree->charac == '*' || tree->charac == '\\') && tree->left == NULL && tree->right == NULL) {
			fputc('\\', file);
		}
		fputc(tree->charac, file);
		put_tree(tree->left, file);
		put_tree(tree->right, file);
	}
}

unsigned char set_bit(unsigned char byte, int i) {
	unsigned char mask = 1 << i;
	return (mask | byte);
}


//
void write_file(FILE *file, hash *hash, FILE *compressed, long long int sizeTree) {
	unsigned char charac, byte_file = 0;
	int i, j = 0, size = 0, bits = 0, byte = 7;
	rewind(compressed);
	fseek(compressed, 2 + sizeTree, SEEK_SET);
	while(fscanf(file, "%c", &charac) != EOF) {
		j = 0;
		while(hash->matriz[charac][j] != (unsigned char *)'\0') {
			if(hash->matriz[charac][j] != (unsigned char *)'0') {
				byte_file = set_bit(byte_file, byte);
			}
			bits += 1;
			byte -= 1;
			j += 1;

			if(bits == 8) {
				fprintf(compressed, "%c", byte_file);
				byte_file = 0;
				byte = 7;
				bits = 0;
			}
		}
	}
	if(bits != 0) {
		fprintf(compressed, "%c", byte_file);
	}
	fclose(compressed);
}

void print(node *node) {
  if(node == NULL) {
    printf("()");
    return;
  }
  else {
    printf("(%u", node->charac);
    print(node->left);
    print(node->right);
    printf(")");
  }
}
void frequency(FILE *file, int amount[]) {
        unsigned char charac;

        // charac = fgetc(file);
        // while(!feof(file)) {
        //         amount[charac] += 1;
        //         charac = fgetc(file);
        // }
        
        while(fscanf(file, "%c", &charac) != EOF) {// Charac é o valor do caracter na tabela ASCII,
                amount[charac] += 1;                      // adicionando a quantidade dela que existe
        }
}

int main() {
	int option, amount[256] = {0};
	char name[256];

	while(1) {
		printf("1 - Compress\n");
		printf("2 - Descompress\n");
		printf("3 - Quit\n");
		
		scanf("%d", &option);

		if(option == 1) {
			printf("FILE NAME: ");
			scanf(" %[^\n]", name);
			printf("\n");

			FILE *file = fopen(name, "rb");

			if(file == NULL) {
				printf("Invalid file\n");
				break;
			}

			frequency(file, amount);

			pq *pq_amount = create_pq();
			pq_amount     = enqueue_amount(amount);
			
			node *tree    = create_huff(pq_amount);

			if(DEBUG){
                                print(tree);
                                printf("\n");
                        }

			hash *hash = create_hash();

			int for_bits[256];
			memset(for_bits, 0, 256);
			map_bits(hash, tree, 0, for_bits);

			if(DEBUG){
			        //printf("%d %d %c %c\n", '\0', '#', 48, 49); //test da table ascii

                                for(int i = 0; i < 256; i++) {
                                        for(int j = 0; j < 256; j++) {
                                                if(hash->matriz[i][0] == 35){
                                                        continue;
                                                }
                                                if(hash->matriz[i][j] != 35
                                                   && hash->matriz[i][j] != 0) {
                                                        if(j == 0){
                                                                printf("i:%d = %c ", i, hash->matriz[i][j]);
                                                        } else{
                                                                printf("%c ", hash->matriz[i][j]);
                                                        }

                                                }
                                                if(hash->matriz[i][j] == 0){
                                                        puts("");
                                                        continue;
                                                }
                                        }
                                }
			}
//------------------------------------------------------
			long long int size  = 0;
			unsigned char trash = 0;

			size_tree(tree, &size);

			int bytes[2] = {0};
			get_trash(tree, &trash, 0);
			trash = 8 - (trash % 8);

			if(trash == 8) {
				trash = 0;
			}
			bytes[0] = trash << 5;
			bytes[0] |= size >> 8;
			bytes[1] = size;
			FILE *compressed = fopen("file.huff", "wb");

			fprintf(compressed, "%c%c", bytes[0], bytes[1]);
			put_tree(tree, compressed);
			rewind(file);
			write_file(file, hash, compressed, size);
			fclose(file);

			break;
		}
		else if(option == 2) {


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
