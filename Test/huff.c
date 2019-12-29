#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

typedef struct node node;
typedef struct pq pq;
typedef struct hash hash;

struct node {
	unsigned char charac;	//Armazena o caracter
	int priority;			//Alterar para void *priority //Armazena a prioridade
	node *left;				//Guarda o ponteiro do lado esquedo
	node *right;			//Guarda o ponteiro do lado direito
	node *next;				//Guarda o ponteiro para o próximo
};

struct pq {
	int size;				//Armazena o tamanho da fila de prioridade
	node *head;				//Guarda o nó da cabeça da fila de prioridade
};

struct hash {
	int *matriz[256][256];
};

pq* create_pq() {
	pq* new_queue = (pq*) malloc(sizeof(pq));
	new_queue->head = NULL;
	new_queue->size = 0;
	return new_queue;
}

node* create_node() {
	node* new_node = (node*) malloc(sizeof(node));
	new_node->priority = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->next = NULL ;
	return new_node;
}

node* c_tree(unsigned char charac, int amount, node *left, node *right) {
	node *tree = (node*) malloc(sizeof(node));
	tree->charac = charac;
	tree->priority = amount;
	tree->next = NULL;
	tree->left = left;
	tree->right = right;

	return tree;
}

hash *create_hash () {
	hash *new_hash = (hash*) malloc(sizeof(hash));

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			new_hash->matriz[i][j] = '#';
		}
	}
	return new_hash;
}

//CRIA A FILA EM ORDEM CRESCENTE
void enqueue(pq *pq, node *tree) {
	node *aux = tree;

	if(pq->size == 0) {
		pq->size += 1;
		aux->next = pq->head;
		pq->head = aux;
	}
	else {
		pq->size += 1;
		node *c = pq->head;
		node *p = NULL;

		while((c != NULL) && (c->priority < aux->priority)) { //Depois de feita a soma dos dois menores, se forem maior do que o next da fila aqui será feita a troca de posição
			p = c;
			c = c->next;
		}
		if(p == NULL) {
			aux->next = pq->head;
			pq->head = aux;
			return;
		}
		p->next = aux;
		aux->next = c;
	}
}

//PROCURA OS CARACTERES E SUAS FREQUENCIAS E MANDA PARA COLOCA-LOS EM FILA
pq* enqueue_amount(int amount[]) {
	pq *pq_new = (pq*) malloc(sizeof(pq));
	pq_new->head = NULL;
	node* new_node;

	for(int i = 0; i < 256; i++) {
		if(amount[i]) {										//Quando achar algo diferente de 0, i será o caracter e amount[i] será sua frequência
			new_node = c_tree(i, amount[i], NULL, NULL);	//Já cria em formato de árvore com os ponteiros para esquerda e direita
			enqueue(pq_new, new_node);						//Coloca na fila
		}
	}

	return pq_new;
}

//REMOVE O PRIMEIRO ELEMENTO DA FILA
node *dequeue(pq *pq) {
	node *aux = pq->head;
	pq->head = pq->head->next;
	pq->size -= 1;
	return aux;
}

//CONSTRÓI A ÁRVORE COM A SOMA DOS CARACTERES DE MENOR FREQUÊNCIA E OS COLOCA COMO FOLHAS
node *create_huff_node(node *left, node *right) {
	node *huff = (node*) malloc(sizeof(node));
	huff->priority = left->priority + right->priority;	//Soma dos dois de menor frequência
	huff->left = left;
	huff->right = right;
	huff->charac = '*';
	huff->next = NULL;
	return huff;
}

//PEGA OS 2 CARACTERES DE MENOR FREQUÊNCIA E COLOCA A SOMA DELES NOVAMENTE NA FILA
node *create_huff(pq *pq) {
	node *huff = create_node();
	// if(pq->size == 1) {
	// 	return create_huff_node(pq->head, NULL);
	// }
	while (pq->size > 1) {
		node *left = dequeue(pq);						//Pega o primeiro elemento da fila que é de menor frequência
		node *right = dequeue(pq);						//							||
		huff = create_huff_node(left, right);			//Manda os dois menores para formar um novo nó pai e eles serão folhas
		enqueue(pq, huff);								//Coloca em fila a cada parte da árvore até que sobre somente a raiz
	}
	return pq->head;
}

//VERIFICA SE A ÁRVORE ESTÁ VAZIA
int isEmpty(node *tree) {
	return (tree == NULL);
}

//VERIFICA SE O NÓ É UMA FOLHA
int isLeaf(node *tree) {
	return ((tree->left == NULL) && (tree->right == NULL));
}

//COLOCA NA HASH A SEQUÊNCIA DE BITS
void add_hash(hash *hash, unsigned char item, int total_bits, int sequency[]) {
	int i;
	for(i = 0; i < total_bits; i++) {
		hash->matriz[item][i] = sequency[i];			//Preenche em linha a sequência da letra na posição dela na tabela ASCII
	}
	//hash->matriz[item][i] = '\0';
}

//PERCORE A ÁRVORE BUSCANDO AS FOLHAS PARA CRIAR A SEQUÊNCIA DE BITS
void map_bits(hash *hash, node *tree, int i, int for_bits[]) {
	if(isEmpty(tree)) {
		return;
	}
	else {
		if(isLeaf(tree)) {
			add_hash(hash, tree->charac, i, for_bits);
			return;
		}
		for_bits[i] = 0;								//Vai adicionar o 0 e andar para a esquerda na chamada
		map_bits(hash, tree->left, i+1, for_bits);
		for_bits[i] = 1;								//Vai adicionar o 1 e andar para a direita na chamada
		map_bits(hash, tree->right, i+1, for_bits);
	}
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

	while(fscanf(file, "%c", &charac) != EOF) { 
		amount[charac] += 1;							//Charac é o valor do caracter na tabela ASCII, adicionando a quantidade dela que existe
	}
	amount[10] -= 1;
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
			pq_amount = enqueue_amount(amount);
			
			node *tree = create_huff(pq_amount);

			print(tree);
			printf("\n");

			hash *hash = create_hash();

			int for_bits[256];
			memset(for_bits, 0, 256);
			map_bits(hash, tree, 0, for_bits);

			for(int i = 0; i < 256; i++) {
				for(int j = 0; j < 256; j++) {
					if(hash->matriz[i][j] != 35) {
						printf("%d %d %d\n", hash->matriz[i][j], i, j);
					}
				}
			}

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
