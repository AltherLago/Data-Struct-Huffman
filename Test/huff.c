#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

typedef struct node node;
typedef struct pq pq;


struct node {
	unsigned char charac; //Armazena o caracter
	int priority;         //aqui é para ser void * priority //Armazena a prioridade
	node *left;           //Guarda o ponteiro do lado esquedo
	node *right;          //Guarda o ponteiro do lado direito
	node *next;           //Guarda o ponteiro para o próximo
};

struct pq {
	int size;  //Armazena o tamanho da fila de prioridade
	node *head;//Guarda o nó da cabeça da fila de prioridade
};

///@return novo ponteiro um novo ponteiro para fila de prioridade
pq *   create_pq();

node * create_node() {
	node* new_node     = (node*) malloc(sizeof(node));
	new_node->priority = 0;
	new_node->left     = NULL;
	new_node->right    = NULL;
	new_node->next     = NULL ;
	return new_node;
}

node * c_tree(unsigned char charac, int amount, node *left, node *right) {
	node *tree     = (node*) malloc(sizeof(node));
	tree->charac   = charac;
	tree->priority = amount;
	tree->next     = NULL;
	tree->left     = left;
	tree->right    = right;

	return tree;
}

void    enqueue(pq *pq, node *tree) {
	node *aux = tree;

	if(pq->size == 0) {
		pq->size  += 1;
		aux->next = pq->head;
		pq->head  = aux;
	}
	else {
		pq->size += 1;
		node *c   = pq->head;
		node *p   = NULL;

		while((c != NULL) && (c->priority < aux->priority)) {
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

pq* enqueue_amount(int amount[]) {
	pq *pq_new   = (pq*) malloc(sizeof(pq));
	pq_new->head = NULL;
	node* new_node;

	for(int i = 0; i < 255; i++) {
		if(amount[i]) {
			new_node = c_tree(i, amount[i], NULL, NULL);
			enqueue(pq_new, new_node);
		}
	}

	return pq_new;
}

node *dequeue(pq *pq) {
	node *aux = pq->head;
	pq->head  = pq->head->next;
	pq->size  -= 1;
	return aux;
}

node *create_huff_node(node *left, node *right) {
	node *huff   = (node*) malloc(sizeof(node));
	huff->left   = left;
	huff->right  = right;
	huff->charac = '*';

	if(right == NULL) {
		huff->priority = left->priority;
	}
	else {
		huff->priority = left->priority + right->priority;
	}
	huff->next = NULL;

	return huff;
}

node *create_huff(pq *pq) {
	node *huff = create_node();

	if(pq->size == 1) {
		return create_huff_node(pq->head, NULL);
	}
	while (pq->size > 1) {
		node *left  = dequeue(pq);
		node *right = dequeue(pq);
		huff        = create_huff_node(left, right);
		enqueue(pq, huff);
	}
	return pq->head;
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
		amount[charac] += 1;
	}
}

int main() {
	int option, amount[255] = {0};
	char ascii[255];

	while(1) {
		printf("1 - Compress\n");
		printf("2 - Descompress\n");
		printf("3 - Quit\n");
		
		scanf("%d", &option);

		if(option == 1) {
			printf("FILE NAME: ");
			scanf("%s", ascii);
			printf("\n");

			FILE *file = fopen(ascii, "rb");

			if(file == NULL) {
				printf("Invalid file\n");
				break;
			}

			frequency(file, amount);
			// int j = 0;
			// while(j < 256) {
			// 	if(amount[j] != 0) {
			// 		printf("%d\n", j);
			// 	}
			// 	j++;
			// }
			pq *pq_amount = create_pq();
			pq_amount     = enqueue_amount(amount);
			
			node *tree = create_huff(pq_amount);

			print(tree);
			printf("\n");

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
///@return novo ponteiro um novo ponteiro para fila de prioridade
pq *   create_pq() {
        pq* new_queue   = (pq*) malloc(sizeof(pq));
        new_queue->head = NULL;
        new_queue->size = 0;
        return new_queue;
}